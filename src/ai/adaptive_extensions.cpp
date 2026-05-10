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
 * @file src/ai/adaptive_extensions.cpp
 */
#include <map>
#include <algorithm>
#include "utils"
#include "ai/adaptive"
#include "game/board/board"



/*
 * Move sorting function, used to compare two moves by their order.
 *
 * @param m1 First move.
 * @param m2 Second move.
 *
 * @return true if m1 goes before m2 according to the order value.
 */
static bool move_compare(Move m1, Move m2)
{
    return (m1.getOrder() < m2.getOrder());
}


/*!
 * Prepare the moves and necessary data strutures before performing the actual
 * search. This function uses the "global" variable rootMoves, where all the
 * initial root moves are listed (from board->getAllValidMoves()).
 *
 * This function is used to sort moves and enhance the environment for speeding
 * up the alphabeta search.
 */
void Adaptive::initSearch()
{
    // 1) sort moves using MVV/LVA, etc.
    sortMoves(rootMoves);

    // 2) yet move the best moves to be searched first
    for (unsigned int i = 0; i < bestMoves.size(); i++)
    {
        for (unsigned int j = 0; j < rootMoves.size(); j++)
        {
            // if one of bestMoves is still a valid move, move it to the front
            // of the move list, so that it is searched at first
            if (bestMoves[i].equals(rootMoves[j]))
            {
                rootMoves.erase(rootMoves.begin() + j);
                rootMoves.insert(rootMoves.begin(), bestMoves[i]);
            }
        }
    }
}



/*!
 * Sort a list of moves according to their nature and possibly score from a
 * previous search.
 *
 * @param movelist Pointer to the vector containing the list of moves.
 * moves.
 */
void Adaptive::sortMoves(vector<Move> &movelist)
{
    // if only one valid move, do not try to sort anything
    if (movelist.size() <= 1)
        return;

    // 1) set the order for each move, before sorting them
    for (unsigned int i = 0; i < movelist.size(); i++)
    {
        // move priorites:
        // #1 captures sorted by MVV/LVA
        // #2 promotions
        // #3 the rest
        //
        // TODO: killer moves, history heuristics

        // #1 captures sorted by MVV/LVA
        if (movelist[i].isCapture())
        {
            int vo = 0;
            int vd = 0;

            // initialize the sorting
            Piece *po = board->getPieceAt(movelist[i].getOrigin());
            Piece *pd = board->getPieceAt(movelist[i].getDestination());
            vo = po->getValue() * po->getColor();

            // on empassants, no piece is on destination
            if (pd)
                vd = pd->getValue() * pd->getColor();
            else
                vd = VALUE_PAWN;
                
            // now set the ordering number for future sorting
            movelist[i].setOrder(-9000 - vd + vo);
        }

        // #2 promotions
        else if (movelist[i].isPromotion())
        {
            movelist[i].setOrder(10);
        }

        // #3 regular moves (lowest priority)
        else
        {
            movelist[i].setOrder(100);
        }
    }

    // 2) sort the moves using MVV/LVA
    sort(movelist.begin(), movelist.end(), move_compare);

    return;
}
