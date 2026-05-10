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
 * @file src/game/board/pawn.cpp
 */
#include "definitions"
#include "utils"
#include "game/board/board"
#include "game/board/piece"
#include "game/board/pawn"



/*!
 * Default constructor.
 *
 * @param pt Piece type to be set by default.
 */
Pawn::Pawn(PieceType pt)
{
    type      = pt;
    moves     = 0;
    nmoves    = 0;
    npossible = 0;
    enabled   = true;
    bb        = 0;
    position  = -1;

    if (pt == PIECE_TYPE_PAWN_WHITE)
    {
        color = COLOR_TYPE_WHITE;
        value = VALUE_PAWN;
    }
    else
    {
        color = COLOR_TYPE_BLACK;
        value = -VALUE_PAWN;
    }
}


/*!
 * Logic for finding the possible pseudo-legal moves where the pawn can move
 * to.
 *
 * @param b Pointer to the current board object where to check if the piece can
 *          move to certain squares or not.
 *
 * This function does not check, yet, if the move can be actually performed or
 * not, according to the check/mate rules.
 */
void Pawn::recalculateMoves(Board *b)
{
    // reset the moves to none
    moves = 0;

    BitBoard test;
    BitBoard move;
  
    // 1-square moves 
    if (color == COLOR_TYPE_WHITE)
        move = bb << 8;
    else
        move = bb >> 8;
    test = move & (b->whitePieces | b->blackPieces);

    if (!test)
        moves |= move;

    // pawns at home can move 2 squares (if they can move 1)
    if (!test && !nmoves)
    {
        if (color == COLOR_TYPE_WHITE)
            move = bb << 16;
        else
            move = bb >> 16;
        test = move & (b->whitePieces | b->blackPieces);

        if (!test)
            moves |= move;
    }
}


/*!
 * Logic for finding the possible pseudo-legal moves where the pawn can attack
 * to.
 *
 * Note: this function differs from the rest of pieces in the fact that, here,
 * the attacks are actual attacks, meaning that, if there is not an opponent's
 * piece on the attack square, the attack is not valid. This is used for two
 * reasons:
 * 
 *  1) simplicity: empassant taking is doable with this, otherwise it is too
 *     complex
 *  2) pawns' pseudo-legal attacks do not influence heuristic, so the error
 *     margin in this optimization is neglectable, for the scope of this
 *     application
 *
 * @param b pointer to the current Board.
 */
void Pawn::recalculateAttacks(Board *b)
{
    // reset the attacks to none
    attacks = 0;

    if (color == COLOR_TYPE_WHITE)
        attacks = b->whitePawnAttacks[position];
    else if (color == COLOR_TYPE_BLACK)
        attacks = b->blackPawnAttacks[position];
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
vector<Move> Pawn::getAllMoves()
{
    vector<int> ps;
    vector<Move> mymoves;
    Move tmp;
    char c;

    ps = positionsFromBitboard(attacks);
    for (unsigned int i = 0; i < ps.size(); i++)
    {
        tmp.reset();
        c = getColumn();
        string algebraic(1, c);
        algebraic.append("x");
        algebraic.append(bunmap(ps[i]));

        if (((ps[i] >= 0) && (ps[i] <= 7)) ||
            ((ps[i] >= 56) && (ps[i] <= 63)))
        {
            algebraic.append("=Q");
            tmp.setType(MOVE_TYPE_PROMOTION_CAPTURE);
            tmp.setPromotion(true);
        }
        else
        {
            tmp.setType(MOVE_TYPE_CAPTURE_PAWN);
        }
        tmp.setAlgebraic(algebraic);
        tmp.setPiece(type);
        tmp.setOrigin(position);
        tmp.setDestination(ps[i]);
        tmp.setCapture(true);
        tmp.setColor(color);
        mymoves.push_back(tmp);
    }
    
    ps = positionsFromBitboard(moves);
    for (unsigned int i = 0; i < ps.size(); i++)
    {
        tmp.reset();
        string algebraic;
        if (((ps[i] >= 0) && (ps[i] <= 7)) ||
            ((ps[i] >= 56) && (ps[i] <= 63)))
        {
            algebraic.append(bunmap(ps[i]));
            algebraic.append("=Q");
            tmp.setType(MOVE_TYPE_PROMOTION_SIMPLE);
            tmp.setPromotion(true);
        }
        else
        {
            algebraic.append(bunmap(position));
            algebraic.append(bunmap(ps[i]));
            tmp.setType(MOVE_TYPE_XY);
        }
        tmp.setAlgebraic(algebraic);
        tmp.setPiece(type);
        tmp.setOrigin(position);
        tmp.setDestination(ps[i]);
        tmp.setColor(color);
        mymoves.push_back(tmp);
    }

    return mymoves;
}
