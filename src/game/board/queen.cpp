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
 * @file src/game/board/queen.cpp
 */
#include "definitions"
#include "utils"
#include "game/board/queen"
#include "game/board/board"



/*!
 * Default constructor.
 *
 * @param pt Piece type to be set by default.
 */
Queen::Queen(PieceType pt)
{
    type      = pt;
    moves     = 0;
    nmoves    = 0;
    npossible = 0;
    enabled   = true;
    bb        = 0;
    position  = -1;
    
    if (pt == PIECE_TYPE_QUEEN_WHITE)
    {
        color = COLOR_TYPE_WHITE;
        value = VALUE_QUEEN;
    }
    else
    {
        color = COLOR_TYPE_BLACK;
        value = -VALUE_QUEEN;
    }
}


/*!
 * Logic for finding the possible pseudo-legal moves where the queen can move
 * to.
 *
 * @param b Pointer to the current board object where to check if the piece can
 *          move to certain squares or not.
 *
 * This function does not check, yet, if the move can be actually performed or
 * not, according to the check/mate rules.
 */
void Queen::recalculateMoves(Board *b)
{
    int tmp;
    bool north    = true;
    bool south    = true;
    bool east     = true;
    bool west     = true;
    bool ne_slide = true;
    bool se_slide = true;
    bool sw_slide = true;
    bool nw_slide = true;
    int row, nrow, col, ncol;
    ColorType opcolor = oppose(color);
    Piece *tp = 0;

    // store our position in row+column format
    row = position / 8;
    col = position % 8;

    // reset the moves to none
    moves = 0;

    // loop for calculating move offsets
    for (int i = 1; i < 8; i++)
    {
        // calculate north
        if (north)
        {
            tmp = (position + (8 * i));
            if ((tmp >= 0) && (tmp <= 63))
            {
                tp = b->getPieceAt(tmp);
                if (tp == 0)
                {
                    setBit(&moves, tmp);
                }
                else if (tp->getColor() == opcolor)
                {
                    setBit(&moves, tmp);
                    north = false;
                }
                else
                {
                    north = false;
                }
            }
        }

        // calculate south
        if (south)
        {
            tmp = (position - (8 * i));
            if ((tmp >= 0) && (tmp <= 63))
            {
                tp = b->getPieceAt(tmp);
                if (tp == 0)
                {
                    setBit(&moves, tmp);
                }
                else if (tp->getColor() == opcolor)
                {
                    setBit(&moves, tmp);
                    south = false;
                }
                else
                {
                    south = false;
                }
            }
        }
       
        // calculate east
        if (east)
        {
            tmp  = (position + i);
            nrow = tmp / 8;
            if ((tmp >= 0) && (tmp <= 63) && (row == nrow))
            {
                tp = b->getPieceAt(tmp);
                if (tp == 0)
                {
                    setBit(&moves, tmp);
                }
                else if (tp->getColor() == opcolor)
                {
                    setBit(&moves, tmp);
                    east = false;
                }
                else
                {
                    east = false;
                }
            }
        }

        // calculate west
        if (west)
        {
            tmp  = (position - i);
            nrow = tmp / 8;
            if ((tmp >= 0) && (tmp <= 63) && (row == nrow))
            {
                tp = b->getPieceAt(tmp);
                if (tp == 0)
                {
                    setBit(&moves, tmp);
                }
                else if (tp->getColor() == opcolor)
                {
                    setBit(&moves, tmp);
                    west = false;
                }
                else
                {
                    west = false;
                }
            }
        }

        // calculate north-east (avoiding wrapping)
        if (ne_slide)
        {
            tmp = (position + (9 * i));
            nrow = tmp / 8;
            ncol = tmp % 8;
            if ((tmp >= 0) && (tmp <= 63))
            {
                if ((nrow == (row + i)) && (ncol == (col + i)))
                {
                    tp = b->getPieceAt(tmp);
                    if (tp == 0)
                    {
                        setBit(&moves, tmp);
                    }
                    else if (tp->getColor() == opcolor)
                    {
                        setBit(&moves, tmp);
                        ne_slide = false;
                    }
                    else
                    {
                        ne_slide = false;
                    }
                }
            }
        }
       
        // calculate south-east (avoiding wrapping)
        tmp = (position - (7 * i));
        nrow = tmp / 8;
        ncol = tmp % 8;
        if (se_slide)
        {
            if ((tmp >= 0) && (tmp <= 63))
            {
                if ((nrow == (row - i)) && (ncol == (col + i)))
                {
                    tp = b->getPieceAt(tmp);
                    if (tp == 0)
                    {
                        setBit(&moves, tmp);
                    }
                    else if (tp->getColor() == opcolor)
                    {
                        setBit(&moves, tmp);
                        se_slide = false;
                    }
                    else
                    {
                        se_slide = false;
                    }
                }
            }
        }
       
        // calculate south-west (avoiding wrapping)
        tmp = (position - (9 * i));
        nrow = tmp / 8;
        ncol = tmp % 8;
        if (sw_slide)
        {
            if ((tmp >= 0) && (tmp <= 63))
            {
                if ((nrow == (row - i)) && (ncol == (col - i)))
                {
                    tp = b->getPieceAt(tmp);
                    if (tp == 0)
                    {
                        setBit(&moves, tmp);
                    }
                    else if (tp->getColor() == opcolor)
                    {
                        setBit(&moves, tmp);
                        sw_slide = false;
                    }
                    else
                    {
                        sw_slide = false;
                    }
                }
            }
        }
       
        // calculate north-west (avoiding wrapping)
        tmp = (position + (7 * i));
        nrow = tmp / 8;
        ncol = tmp % 8;
        if (nw_slide)
        {
            if ((tmp >= 0) && (tmp <= 63))
            {
                if ((nrow == (row + i)) && (ncol == (col - i)))
                {
                    tp = b->getPieceAt(tmp);
                    if (tp == 0)
                    {
                        setBit(&moves, tmp);
                    }
                    else if (tp->getColor() == opcolor)
                    {
                        setBit(&moves, tmp);
                        nw_slide = false;
                    }
                    else
                    {
                        nw_slide = false;
                    }
                }
            }
        }
    }
}


/*!
 * Logic for finding the squares that are currently under the attack of the
 * queen.
 *
 * @param b pointer to the current Board.
 *
 * This is actually a copy of moves, since major pieces actually attack the
 * squares where they can move next.
 */
void Queen::recalculateAttacks(Board *b)
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
vector<Move> Queen::getAllMoves()
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
