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

// vim:et:ts=4:sw=4

/*!
 * @file src/game/board/knight.cpp
 */
#include "definitions"
#include "utils"
#include "game/board/board"
#include "game/board/piece"
#include "game/board/knight"



/*!
 * Default constructor.
 *
 * @param pt Piece type to be set by default.
 */
Knight::Knight(PieceType pt)
{
    type      = pt;
    moves     = 0;
    nmoves    = 0;
    npossible = 0;
    enabled   = true;
    bb        = 0;
    position  = -1;

    
    if (pt == PIECE_TYPE_KNIGHT_WHITE)
    {
        color = COLOR_TYPE_WHITE;
        value = VALUE_KNIGHT;
    }
    else
    {
        color = COLOR_TYPE_BLACK;
        value = -VALUE_KNIGHT;

    }
}


/*!
 * Find all pseudo-legal moves for Knight:
 * 1) nonBlockingSquares = all the squares where there are no friendly pieces
 * 2) knightMoves[from]  = list of pre-computed moves for Knights
 * 3) pseudo-legal moves = nonBlockingSquares AND possible moves from "position"
 *
 * @param b Pointer to the current board object where to check if the piece can
 *          move to certain squares or not.
 */
void Knight::recalculateMoves(Board *b)
{
    BitBoard nonBlockingSquares;
    if (color == COLOR_TYPE_WHITE)
        nonBlockingSquares = ~ b->whitePieces;
    else
        nonBlockingSquares = ~ b->blackPieces;
    moves = b->knightMoves[position] & nonBlockingSquares;
}


/*!
 * Logic for finding the squares that are currently under the attack of the
 * knight.
 *
 * @param b pointer to the current Board.
 *
 * This is actually a copy of moves, since minor pieces actually attack the
 * squares where they can move next.
 */
void Knight::recalculateAttacks(Board *b)
{
    attacks = moves;
}


/*!
 * Retrieve a list of all possible moves for this piece.
 *
 * Note: this moves are not always valid, they must be checked later on by a
 *       proper component (e.g. MoveParser).
 *
 * Note: also note that the list contains newly created Move objects, these
 *       should be deleted later on, when they are not needed anymore.
 *
 * @return a list of all moves that this piece can perform.
 */
vector<Move> Knight::getAllMoves()
{
    string algebraic = "";
    vector<int> ps = positionsFromBitboard(moves);
    vector<Move> moves;
    Move tmp;

    for (unsigned int i = 0; i < ps.size(); i++)
    {
        tmp.reset();
        algebraic = "";
        algebraic.append(bunmap(position));
        algebraic.append(bunmap(ps[i]));
        tmp.setAlgebraic(algebraic);
        tmp.setOrigin(position);
        tmp.setDestination(ps[i]);
        tmp.setPiece(type);
        tmp.setColor(color);
        tmp.setType(MOVE_TYPE_XY);
        moves.push_back(tmp);
    }

    return moves;
}
