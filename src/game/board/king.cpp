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
 * @file src/game/board/king.cpp
 */
#include "definitions"
#include "utils"
#include "game/board/board"
#include "game/board/piece"
#include "game/board/king"



/*!
 * Default constructor.
 *
 * @param pt Piece type to be set by default.
 */
King::King(PieceType pt)
{
    type      = pt;
    moves     = 0;
    nmoves    = 0;
    npossible = 0;
    enabled   = true;
    checked   = false;
    staled    = false;
    mated     = false;
    castled   = false;
    bb        = 0;
    position  = -1;
    
    if (pt == PIECE_TYPE_KING_WHITE)
    {
        color = COLOR_TYPE_WHITE;
        value = VALUE_KING;
    }
    else
    {
        color = COLOR_TYPE_BLACK;
        value = -VALUE_KING;
    }
}


/*!
 * Logic for finding the possible pseudo-legal moves where the king can move
 * to.
 *
 * Please notice that the move of castling (both short and long) are not checked
 * in this function, since they depend on the respective rooks and it would be
 * not efficient. This should be checked in a higher-level component instead
 * (such as MoveParser).
 *
 * @param b Pointer to the current board object where to check if the piece can
 *          move to certain squares or not.
 *
 * This function does not check, yet, if the move can be actually performed or
 * not, according to the check/mate rules.
 */
void King::recalculateMoves(Board *b)
{
    BitBoard nonBlockingSquares;

    if (color == COLOR_TYPE_WHITE)
        nonBlockingSquares = ~ b->whitePieces;
    else
        nonBlockingSquares = ~ b->blackPieces;

    moves = b->kingMoves[position] & nonBlockingSquares;
    
    /*
    int tmp;
    int row, col, nrow, ncol;
    Piece *p = 0;

    row = position / 8;
    col = position % 8;

    // reset the moves to none
    moves = 0;

    // calculate north-east (avoiding wrapping)
    tmp  = position + 9;
    nrow = tmp / 8;
    ncol = tmp % 8;
    if ((tmp >= 0) && (tmp <= 63))
    {
        if ((nrow == (row + 1)) && (ncol == (col + 1)))
        {
            p = b->getPieceAt(tmp);
            if (p != 0)
            {
                if (p->getColor() != color)
                    setBit(&moves, tmp);
            }
            else
            {
                    setBit(&moves, tmp);
            }
        }
    }
   
    // calculate south-east (avoiding wrapping)
    tmp  = position - 7;
    nrow = tmp / 8;
    ncol = tmp % 8;
    if ((tmp >= 0) && (tmp <= 63))
    {
        if ((nrow == (row - 1)) && (ncol == (col + 1)))
        {
            p = b->getPieceAt(tmp);
            if (p != 0)
            {
                if (p->getColor() != color)
                    setBit(&moves, tmp);
            }
            else
            {
                    setBit(&moves, tmp);
            }
        }
    }
   
    // calculate south-west (avoiding wrapping)
    tmp  = position - 9;
    nrow = tmp / 8;
    ncol = tmp % 8;
    if ((tmp >= 0) && (tmp <= 63))
    {
        if ((nrow == (row - 1)) && (ncol == (col - 1)))
        {
            p = b->getPieceAt(tmp);
            if (p != 0)
            {
                if (p->getColor() != color)
                    setBit(&moves, tmp);
            }
            else
            {
                    setBit(&moves, tmp);
            }
        }
    }
   
    // calculate north-west (avoiding wrapping)
    tmp  = position + 7;
    nrow = tmp / 8;
    ncol = tmp % 8;
    if ((tmp >= 0) && (tmp <= 63))
    {
        if ((nrow == (row + 1)) && (ncol == (col - 1)))
        {
            p = b->getPieceAt(tmp);
            if (p != 0)
            {
                if (p->getColor() != color)
                    setBit(&moves, tmp);
            }
            else
            {
                    setBit(&moves, tmp);
            }
        }
    }

    // calculate vertical
    tmp = (position + 8);
    if ((tmp >= 0) && (tmp <= 63))
    {
        p = b->getPieceAt(tmp);
        if (p != 0)
        {
            if (p->getColor() != color)
                setBit(&moves, tmp);
        }
        else
        {
                setBit(&moves, tmp);
        }
    }
    tmp = (position - 8);
    if ((tmp >= 0) && (tmp <= 63))
    {
        p = b->getPieceAt(tmp);
        if (p != 0)
        {
            if (p->getColor() != color)
                setBit(&moves, tmp);
        }
        else
        {
                setBit(&moves, tmp);
        }
    }
   
    // calculate horizontal (avoiding wrapping)
    tmp  = (position + 1);
    nrow = tmp / 8;
    if ((tmp >= 0) && (tmp <= 63) && (row == nrow))
    {
        p = b->getPieceAt(tmp);
        if (p != 0)
        {
            if (p->getColor() != color)
                setBit(&moves, tmp);
        }
        else
        {
                setBit(&moves, tmp);
        }
    }
    tmp  = (position - 1);
    nrow = tmp / 8;
    if ((tmp >= 0) && (tmp <= 63) && (row == nrow))
    {
        p = b->getPieceAt(tmp);
        if (p != 0)
        {
            if (p->getColor() != color)
                setBit(&moves, tmp);
        }
        else
        {
                setBit(&moves, tmp);
        }
    }
    */
}


/*!
 * Logic for finding the squares that are currently under the attack of the
 * king.
 *
 * @param b pointer to the current Board.
 *
 * This is actually a copy of moves, since major pieces actually attack the
 * squares where they can move next.
 */
void King::recalculateAttacks(Board *b)
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
vector<Move> King::getAllMoves()
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
        tmp.setOrigin(position),
        tmp.setDestination(ps[i]);
        tmp.setPiece(type);
        tmp.setColor(color);
        tmp.setType(MOVE_TYPE_XY);
        moves.push_back(tmp);
    }

    // add also the castling possibilities (not necessary to check legality)
    if (nmoves == 0)
    {
        tmp.reset();
        tmp.setAlgebraic("0-0");
        tmp.setPiece(type);
        tmp.setColor(color);
        tmp.setType(MOVE_TYPE_CASTLE_SHORT);
        tmp.setCastle(true);
        moves.push_back(tmp);

        tmp.reset();
        tmp.setAlgebraic("0-0-0");
        tmp.setColor(color);
        tmp.setPiece(type);
        tmp.setType(MOVE_TYPE_CASTLE_LONG);
        tmp.setCastle(true);
        moves.push_back(tmp);
    }

    return moves;
}
