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
 * @file src/game/game.cpp
 */
#include "game/game"



/*!
 * Constructor
 */
Game::Game()
{
    board       = new Board();
    player      = COLOR_TYPE_WHITE;
    turn        = 1;
    cursor      = 0;
    min_cursor  = 0;
}


/*!
 * Destructor
 */
Game::~Game()
{
    delete board;
}


/*!
 * Display, on the UI (the console) a human-readable representation of the
 * current board.
 */
void Game::displayBoard()
{
    cout << board->toString() << endl;;
}


/*!
 * Set the square of the current board to empty.
 *
 * @param pos Integer number corresponding with the square on the board.
 */
void Game::emptySquare(int pos)
{
    board->empty(pos);
}


/*!
 * Set the square of the current board to a given piece.
 *
 * @param piece Piece type which must be set on the given position.
 * @param pos   Position (square integer ID) where to set the piece.
 */
void Game::setPiece(Piece *piece, int pos)
{
    board->setPiece(piece, pos);
}


/*!
 * Safely add a move to the list of moves performed during the game.
 *
 * @param m Move to be added to the history.
 */
void Game::addToHistory(Move m)
{
    string alg = m.getHuman();

    // add '#' to a mate move
    if (board->getEnd() == END_TYPE_MATE)
        alg += "#";
    // add '+' to check moves
    else if (board->isCheck())
        alg += "+";

    m.setHuman(alg);
    history.push_back(m);
}


/*!
 * Pop the last N moves from the game move history.
 *
 * @param n Number of moves that shouuld be removed from the history (from older
 *          to newer).
 */
void Game::removeFromHistory(int n)
{
    for (int i = 0; i < n; i++)
        history.pop_back();
}


/*!
 * Display the list of moves of this game.
 * 
 * @return an Error if the history is empty.
 */
Error Game::displayHistory()
{
    int count = 1;
    Move move;
    vector<Move> moves(history);

    if (moves.size() == 0)
        return ERROR_NO_GAME;

    for (unsigned int i = 0; i < moves.size(); i++)
    {
        move = moves[i];

        if (i % 2)
        {
            cout << move.getHuman() << endl;
            count++;
        }
        else
        {
            cout << count << ". " << move.getHuman();
            cout << ", ";
        }
    }

    return ERROR_NONE;
}


/*!
 * Perform a move.
 *
 * @param m Move to be performed.
 *
 * @return a proper Error code (@see src/definitions)
 */
Error Game::perform(Move m)
{
    // update the board
    if (m.getType() != MOVE_TYPE_NULL)
        board->doMove(m);
    else
        m.setHuman("...");

    // IMPORTANT: check if mate or stalemate after a move is performed
    ColorType opponent = (ColorType) -getPlayer();
    board->getAllValidMoves(opponent).size();

    // add move to the history
    addToHistory(m);

    // update game phase
    board->updatePhase();

    // error if at the end
    if (board->isEnd())
        return ERROR_NEXT_END;

    // update turn
    player = oppose(m.getColor());
    cursor++;
    if (player == COLOR_TYPE_WHITE)
        turn++;

    // if it is the end, then notify
    if (board->isEnd())
        return ERROR_NONE_END;

    return ERROR_NONE;
}


/*!
 * Take a move back.
 *
 * @return ERROR_BACK_BEGIN if the game has ended (no more moves left
 *         forward), ERROR_NONE otherwise.
 */
Error Game::undo()
{
    if (cursor <= min_cursor)
        return ERROR_BACK_BEGIN;

    board->undoMove(history[cursor - 1]);
    removeFromHistory(1);
    cursor--;
    turn = (cursor / 2) + 1;
    (cursor % 2) ? player = COLOR_TYPE_BLACK : player = COLOR_TYPE_WHITE;

    // update game phase
    board->updatePhase();
    
    return ERROR_NONE;
}


/*!
 * Restart a game.
 */
void Game::restart()
{
    board->reset();
    player = COLOR_TYPE_WHITE;
    turn   = 1;
    cursor = 0;
    min_cursor = 0;
    history.clear();
}


/*!
 * Get the whole game history into a linear sequence, encoded in a string.
 *
 * @return a string containing the game history (e.g., 1. e4 e5 2. Nf3).
 */
string Game::getHistorySequence()
{
    int count = 1;
    Move move;
    string sequence = "";
    vector<Move> moves(history);

    for (unsigned int i = 0; i < moves.size(); i++)
    {
        move = moves[i];

        if (i % 2)
        {
            sequence += " " + move.getHuman();
            count++;
        }
        else
        {
            // don't add a blank before the first move
            if (count == 1)
                sequence += to_string(count) + ". " + move.getHuman();
            else
                sequence += " " + to_string(count) + ". " + move.getHuman();
        }
    }

    return sequence;
}
