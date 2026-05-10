// Copyright: 2008-2016  Claudio M. Camacho                                       
                                                                           
// This file is part of Chess0.                                              
                                                                            
// Chess0 is free software; you can redistribute it and/or modify            
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.

// Chess0 is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with Chess0; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
// 

// vim:et:ts=4:sw=4

/*!
 * @file src/ai/adaptive.cpp
 */
#include <stdlib.h>
#include <time.h>
#include <float.h>
#include <signal.h>

#ifndef __WIN32__
#include <unistd.h>
#endif

#include <iomanip>
#include <map>
#include "utils"
#include "ai/adaptive"
#include "game/board/board"



// trick for the disgusting C++ signal handling support
Adaptive *me;



/*!
 * Signal handler wrapper, I told you: C++ is disgusting!
 *
 * @param signo Number of signal to handle.
 */
static void interrupt(int signo)
{
    me->handleInterrupt(signo);
}


/*!
 * Dummy function to allow disabling the signal.
 *
 * @param signo Number of signal to handle.
 */
static void nothing(int signo)
{
    if (signo == SIGINT)
        exit(0);
}


/*!
 * Signal handler, which provides the infrastructure for force-move.
 *
 * @param signo Number of signal to handle.
 */
void Adaptive::handleInterrupt(int signo)
{
    // force move
#ifndef __WIN32__
    if ((signo == SIGINT) || (signo == SIGALRM))
#else
    if (signo == SIGINT)
#endif
    interrupted = true;
}


/*!
 * Default constructor.
 */
Adaptive::Adaptive(Board *b, ColorType c, MoveParser *mp, Game *g)
{
    tpm          = TIME_PER_MOVE;
    board        = b;
    color        = c;
    movp         = mp;
    game         = g;
    nodes        = 0;
    cacheHit     = 0;
    xboard       = false;
    useCache     = true;
    interrupted  = false;
    me           = this;
    start        = clock();
    post         = true;
    depth        = AI_SEARCH_DEPTH;
    quiesceDepth = 0;
    quiesceLimit = AI_DEPTH_QUIESCE_LIMIT;
    ABcall       = 0;

    // temporary variables used in subroutine variables
    moved   = 0;
    value   = 0;
    pos     = -1;
    row     = 0;
    col     = 'x';
    moves   = 0;
}


/*!
 * Pick a move and return it.
 *
 * This function is an abstraction layer to the negamax() algorithm, providing a
 * way for picking a random or pseudo-random move from a list of the N best
 * ones (returned by negamax()).
 *
 * @return a Move object that is the final move by the machine.
 */
Move Adaptive::getMove()
{
    vector<Move> selectable;
    vector<Move> myBestMoves;
    vector<Move> tmpBestMoves;

    // set the signal handler for SIGINT (force-move)
    signal(SIGINT, interrupt);
    #ifndef __WIN32__
    signal(SIGALRM, interrupt);
    #endif

    // reset the amount of searched nodes
    nodes = 0;
    cacheHit = 0;

    // prepare the output, if verbose
    if (verbose)
    {
        cout << endl << "Ply\t Score\t    Time\t Nodes\t Best move" << endl;
        cout << flush;
    }

    // watch the time
    start = clock();

    // start iterative deepening at depth=2
    int idepth = 1;
    terminal   = false;
    ABcall     = 0;
#ifndef __WIN32__
    alarm(tpm);  /*!< max time per move */
#endif

    // fetch all the valid moves for the current board and moving side
    myBestMoves = rootMoves = board->getAllValidMoves(color);

    while (!interrupted && (idepth <= depth))
    {
        if (idepth == depth)
            terminal = true;

        // find best moves with negamax()
        tmpBestMoves = negamax(idepth);

        // if negamax() did not (have time to) find any best moves,
        // use the best moves from the previous search
        if (tmpBestMoves.size() > 0)
            bestMoves = myBestMoves = tmpBestMoves;

        idepth++;
    }

    // else, seek for good-enough moves, close to the best
    float best_score = myBestMoves.back().getScore();

    // only select N moves that are the best, use RANDOMIZATION_THRESHOLD to
    // drop the worst moves (moves whose score is RT lower than best score shall
    // be dropped)
    for (unsigned int i = 0; i < myBestMoves.size(); i++)
    {
        if ((best_score - myBestMoves[i].getScore()) > RANDOMIZATION_THRESHOLD)
            continue;

        selectable.push_back(myBestMoves[i]);
    }

    // initialize the random seed
    srand(time(NULL));

    // pick any of the best moves
    Move mybest;
    int selected = rand() % selectable.size();
    mybest = selectable[selected];

    // disable interrupts
    signal(SIGINT, nothing);
    #ifndef __WIN32__
    signal(SIGALRM, nothing);
    #endif
    interrupted = false;

    // convert algebraic to SAN notation
    movp->pretty(&mybest);

    // display the last analysis line
    if (verbose)
        displayAnalysis(mybest, start, idepth);

    return mybest;
}


/*!
 * Negamax wrapper function which calculates the best move.
 *
 * @param d depth to which look at
 *
 * @see adaptive_extensions.cpp
 *
 * @return a copy of the list of myBestMoves.
 */
vector<Move> Adaptive::negamax(int d)
{
    float score;
    ColorType opcolor = oppose(color);
    string boardSerial;
    vector<Move> myBestMoves;
    bool cached = false;

    // set alpha / beta (originally -inf / +inf)
    float alpha = -FLT_MAX;
    float beta  = +FLT_MAX;

    /*!
     * Order moves for a faster search using the following criteria:
     * 1) MVV/LVA
     * 2) Best moves from previous search are analyzed first
     *
     * @see adaptive_extensions.cpp
     */
    initSearch();

    // force move is disabled until the user forces the move or time is up
    interrupted = false;

    // alpha-beta search in each possible node
    // @precondition: board->isEnd() == false
    for (unsigned int i = 0; i < rootMoves.size(); i++)
    {
        score = 0;
        nodes++;

        // apply the move
        board->doMove(rootMoves[i]);

        // if the score is in the cache, then pick it up
        if (useCache)
        {
            boardSerial = board->toSerial(color, alpha, beta, d);
            auto t = cache.find(boardSerial);
            if (t == cache.end())
                cached = false;
            else
            {
                cacheHit++;
                score = t->second;
                cached = true;
            }
        }

        // if not found, then perform the search and store the result
        if (!cached)
        {
            // score not cached, perform a search
            score = -alphabeta(d, -beta, -alpha, opcolor);

            // store the move in the cache, if cache enabled
            if ((score != FLT_MAX) && (score != -FLT_MAX))
                cache[boardSerial] = score;
        }

        // undo the applied move
        board->undoMove(rootMoves[i]);

        // if interrupted, quit the search
        if (interrupted)
            return myBestMoves;

        // always store a move if it improves the current best move
        if ((score > alpha) || (alpha == -FLT_MAX))
        {
            // store a better move
            Move localBest = rootMoves[i];
            alpha = score;
            localBest.setScore(alpha);
            movp->pretty(&localBest);
            myBestMoves.push_back(localBest);

            // display analysis
            if (verbose && (d > 1))
                displayAnalysis(localBest, start, d);
        }
    }

    return myBestMoves;
}


/*!
 * Alpha-beta function that uses the negamax principle, with the assumption that
 * the chess game is an even-score game with negative scores for the black and
 * positive scores for the white.
 *
 * @param d depth until the search can go.
 * @param alpha alpha restriction for pruning.
 * @param beta beta restriction for pruning.
 * @param c color of the opponent to minimize.
 *
 * @return a float with the best possible evaluation score.
 */
float Adaptive::alphabeta(int d, float alpha, float beta, ColorType c)
{
    float score;
    ColorType opcolor = oppose(c);
    vector<Move> moves;
    string boardSerial;
    bool cached = false;

    // increment the amount of nodes being searched
    ABcall++;

    // if interrupted, return immediately
    if (interrupted)
        return alpha;

    // if the game has ended, return the board evaluation
    // * note: eval() here must return -inf, 0 or +inf
    if (board->isEnd())
        return (c * eval());

    // if bottom depth of the search tree, perform one last deep search
    if (terminal || (d == 0))
        return quiesce(alpha, beta, c);

    // get all moves in this ply to be evaluated
    moves = board->getAllValidMoves(c);

    // find end of game (stalemate or checkmate)
    if ((moves.size() == 0) && (board->getEnd() == END_TYPE_DRAW_STALE))
        return 0;

    // sort moves for faster search
    // @see adaptive_extensions.cpp
    sortMoves(moves);

    // check possible branches
    for (unsigned int i = 0; i < moves.size(); i++)
    {
        nodes++;
        score = 0;

        // search the opponent's best move
        board->doMove(moves[i]);

        if (useCache)
        {
            boardSerial = board->toSerial(color, alpha, beta, d);
            auto t = cache.find(boardSerial);
            if (t == cache.end())
                cached = false;
            else
            {
                cacheHit++;
                score = t->second;
                cached = true;
            }
        }

        // if not found, then perform the search and store the result
        if (!cached)
        {
            // score not cached, perform a search
            score = -alphabeta(d - 1, -beta, -alpha, opcolor);

            // store the move in the cache, if cache enabled
            if ((score != FLT_MAX) && (score != -FLT_MAX))
                cache[boardSerial] = score;
        }

        // undo the move that was analyzed
        board->undoMove(moves[i]);

        // beta cut-off
        if (score >= beta)
            return beta;

        // alpha narrowing
        if (alpha < score)
        {
            alpha = score;
            movp->pretty(&moves[i]);
        }
    }

    // if checkmate move found, stop search
    if (alpha == FLT_MAX)
    {
        interrupted = true;
        return 0;

    }

    // return best value
    return alpha;
}


/*!
 * Quiescence search.
 *
 * Perform a search indefinitely until all the following conditions happen:
 * a) no more possible captures
 * b) no more checks possible
 * c) no more pawn promotions
 *
 * @param alpha alpha restriction for pruning.
 * @param beta beta restriction for pruning.
 * @param c color of the opponent to minimize.
 *
 * @return a float with the best possible evaluation score.
 */
float Adaptive::quiesce(float alpha, float beta, ColorType c)
{
    float score = alpha;
    float stand_pat;
    string boardSerial;
    bool cached = false;
    ColorType opcolor = oppose(c);
    vector<Move> moves;

    // if interrupted, return immediately
    if (interrupted || (quiesceDepth >= quiesceLimit))
        return alpha;

    // calculate the "stand-pat"
    stand_pat = (c * eval());

    // see if current stand_pat is good or not
    if (stand_pat >= beta)
        return beta;
    if (alpha < stand_pat)
        alpha = stand_pat;

    // get all moves in this ply to be evaluated
    moves = board->getAllValidMoves(c);

    // check all possible captures / checks, thus looking for quiescence
    for (unsigned int i = 0; i < moves.size(); i++)
    {
        nodes++;

        // if a move is not critical, then skip it
        if (!moves[i].isCapture() && !board->isCheck() && !moves[i].isPromotion())
            continue;

        // perform a recursive quiescence searchperform a recursive quiescence
        board->doMove(moves[i]);
        quiesceDepth++;

        // if the score is in the cache, then pick it up
        if (useCache)
        {
            boardSerial = board->toSerial(color, alpha, beta, depth + quiesceDepth);
            auto t = cache.find(boardSerial);
            if (t == cache.end())
                cached = false;
            else
            {
                cacheHit++;
                score = t->second;
                cached = true;
            }
        }

        // if not found, then perform the search and store the result
        if (!cached)
        {
            // score not cached, perform a search
            score = -quiesce(-beta, -alpha, opcolor);

            // store the move in the cache, if cache enabled
            if ((score != FLT_MAX) && (score != -FLT_MAX))
                cache[boardSerial] = score;
        }

        quiesceDepth--;
        board->undoMove(moves[i]);

        // the score passed the limit, return beta
        if (score >= beta)
            return beta;

        // the score has improved, save it
        if (score > alpha)
            alpha = score;
    }

    // if checkmate move found, stop search
    if (alpha == FLT_MAX)
    {
        interrupted = true;
        return 0;
    }

    // return best value
    return alpha;
}
