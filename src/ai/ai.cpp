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
 * @file src/ai/ai.cpp
 */
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>
#include <float.h>
#include "utils"
#include "ai/ai"
#include "game/board/board"
#include "game/board/square"
#include "game/board/piece"
#include "game/board/king"



/*!
 * Evaluate the whole situation, including attacks, defenses, material, mobility
 * and position.
 *
 * This function is based on a weighted mean of all values returned by the
 * auxiliar functions: evalMaterial() and evalPosition(). evalPosition()
 * variates depending on the stage of the game (opening, middle-game and
 * end-game).
 *
 * @return a float with a positive number for white leading, negative number for
 *         black leading and 0.0 for an equal situation.
 */
float AI::eval()
{
    // check if it is mate
    EndType end = game->getEnd();
    if (end == END_TYPE_MATE)
    {
        if (game->getPlayer() == COLOR_TYPE_WHITE)
            return +FLT_MAX;
        else
            return -FLT_MAX;
    }
    // check if it is draw
    else if ((end == END_TYPE_DRAW) || (end == END_TYPE_DRAW_50RULE) ||
             (end == END_TYPE_DRAW_3RULE) || (end == END_TYPE_DRAW_PIECES))
    {
        return 0;
    }
    // if no draw nor mate, then return the heuristic evaluation
    else
    {
        return evalMaterial() + evalPosition();
    }
}


/*!
 * Evaluate the current board only taking in account the net material and the
 * basic positional situation for each piece.

 * @return a float with a positive number for white leading, negative number for
 *         black leading and 0.0 for an equal situation.
 */
float AI::evalMaterial()
{
    float est = 0;

    // obtain the list of pieces
    vector<Piece *> pieces = board->getPieces();

    // estimate the material balance
    // * remember that black pieces have a negative value ;-)
    for (size_t i = 0; i < pieces.size(); i++)
    {
        est += pieces[i]->getValue();
    }

    // return material estimate in centipawns
    return (est / 100);
}




/*!
 * Check if a draw is more convinient than the current situation on the board.
 *
 * @return true if the draw offer is accepted, false otherwise.
 */
bool AI::acceptDraw()
{
    Move m = getMove();
    if (m.getScore() > RANDOMIZATION_THRESHOLD)
        return false;

    return true;
}


/*!
 * Chess problem solver.
 *
 * This function is a wrapper over getMove() that tries to search on different
 * search depths until it finds a check mate or a draw score in the board. This
 * is achieved by looking, iteratively, at different depths, and then displaying
 * the first move and the number of plies that it will take to end the game.
 *
 * Note: if the position is complex enough, chess0 will take even days to solve
 *       it.
 *
 * Note: moreover, chess0 is not able to solve problems that end in draw, at
 *       least for now.
 *
 * @param d Maximum depth to which to look at.
 *
 * Note: if the given depth is 0 or negative, chess0 will look forever.
 */
void AI::solve(int d)
{
    unsigned short mydepth = 1;
    unsigned short odepth  = depth;
    Move solution;

    // set depth to something very high, if no limit
    if (d < 1)
        d = SOLVE_MAX_DEPTH;

    // now look for the solution of the problem
    while (mydepth <= d)
    {
        // configure the AI to search to mydepth
        depth = mydepth;

        // tell the user that we are searching
        cout << "Trying to solve at depth " << mydepth << "..." << endl;

        // get the best move
        solution = getMove();

        // moving side mates at mydepth
        if (solution.getScore() == +FLT_MAX)
        {
            // say who is mating and when
            if (color == COLOR_TYPE_WHITE)
                cout << "White";
            else if (color == COLOR_TYPE_BLACK)
                cout << "Black";

            cout << " mates in " << (mydepth / 2) + 1 << " moves" << endl;
            cout << "Mating move: " << solution.getHuman() << endl;

            // restore the normal search depth before quitting
            depth = odepth;
            return;
        }
        // no mate found at mydepth, increase and search again
        else
        {
            mydepth++;
        }
    }

    // if couldn't find a solution, tell the user
    cout << "Could not find a solution in " << mydepth - 1 << " plies!" << endl;
}


/*!
 * Display analysis statistics about the calculation of a move.
 *
 * @param m Move to be displayed.
 * @param t Start time, to calculate the estaimted time of this move.
 * @param d Depth of search.
 */
void AI::displayAnalysis(Move m, clock_t t, int d)
{
    string sequence;

    // do not display anything when in XBoard mode or quiet mode
    if ((xboard && !post) || !verbose)
        return;

    // estimate the time that has gone
    float timeInMS = (clock() - t) / (CLOCKS_PER_SEC / 1000);

    // display depth of search
    cout.fill(' ');
    cout << setw(3) << d << "\t";

    // if check-mate, tell it in words
    cout.fill(' ');
    cout << setw(6);
    if ((color * m.getScore()) == -FLT_MAX)
    {
        cout << " 0-1";
    }
    else if ((color * m.getScore()) == +FLT_MAX)
    {
        cout << " 1-0";
    }
    // if draw
    else if (m.isEnd() && (m.getScore() == 0))
    {
        cout << " ½ - ½";
    }
    // if no check-mate, display the score
    else
    {
        cout << showpos << fixed << setprecision(2);
        cout << (color * m.getScore());

        // reset formatting of the output
        cout << noshowpos;
    }
    cout << "\t";

    // display the calculation time delta
    cout.fill(' ');
    cout << setw(7) << fixed << setprecision(2) << timeInMS / 1000 << "s\t";

    // display the amount of nodes searched
    float cacheHitRatio = cacheHit / nodes;
    cout.fill(' ');
    if (cacheHitRatio > CACHE_HIT_LEVEL)
    {
        cout << "Cached" << "\t";
    }
    else
    {
        char nodesUnit = 'K';
        float curNodes;
        if (nodes >= 1000000)
        {
            curNodes = nodes / 1000000;
            nodesUnit = 'M';
        }
        else
        {
            curNodes = nodes / 1000;
            nodesUnit = 'K';
        }
        cout << setw(5) << fixed << setprecision(1) << curNodes << nodesUnit << "\t";
    }

    // display the move analyzed
    movp->pretty(&m);
    string human = m.getHuman();
    cout << " ";
    board->doMove(m);
    int current_move;
    if (game->getPlayer() == COLOR_TYPE_WHITE)
        current_move = ((game->getCursor() + 1) / 2) + 1;
    else
        current_move = (game->getCursor() + 1) / 2;

    // if mate, then add "#" to the move notation
    if ((m.getScore() == -FLT_MAX) || (m.getScore() == +FLT_MAX))
    {
        human.erase(std::remove(human.begin(), human.end(), '+'), human.end());
        human += "#";
    }
    else if (board->isCheck())
    {
        human.erase(std::remove(human.begin(), human.end(), '#'), human.end());
        human += "+";
    }
    if (game->getPlayer() == COLOR_TYPE_WHITE)
        sequence += to_string(current_move) + ". " + human + " ";
    else
        sequence += to_string(current_move) + "... " + human;
    cout << sequence << " ";

    board->undoMove(m);

    cout << endl << flush;
}
