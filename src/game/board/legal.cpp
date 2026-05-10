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
 * @file src/game/board/legal.cpp
 */
#include <sstream>
#include "definitions"
#include "utils"
#include "game/board/board"
#include "game/board/piece"
#include "game/board/pawn"
#include "game/board/knight"
#include "game/board/bishop"
#include "game/board/rook"
#include "game/board/queen"
#include "game/board/king"



/*!
 * Retrieve the list of all possible and valid moves for a color.
 *
 * @param c specify the color of the side to be checked for moves.
 *
 * @return a list with all possible moves that are valid.
 */
vector<Move> Board::getAllValidMoves(ColorType c)
{
    vector<Move> pmovs = getAllMoves(c);
    vector<Move> moves;
    Move         check_move;
    ColorType opcolor = oppose(c);
    Piece *p;

    // remove evil castles
    pmovs = filterCastles(pmovs);

    // filter out pawn captures, due to empassants
    pmovs = filterPawnCaptures(pmovs);

    // filter moves and fill more information
    for (unsigned int i = 0; i < pmovs.size(); i++)
    {
        // many XY are actually captures
        if (pmovs[i].getType() == MOVE_TYPE_XY)
        {
            Piece *moving = getPieceAt(pmovs[i].getOrigin());
            p = getPieceAt(pmovs[i].getDestination()); 

            // special case: king vs king is not allowed
            if (simplePiece(moving->getType()) == PIECE_TYPE_KING)
            {
                // cannot go near a king
                if (p == 0)
                {
                    if (BitboardFromPosition(pmovs[i].getDestination()) &
                            getKingAttacks(oppose(pmovs[i].getColor())))
                        continue;
                }
            }

            // normal captures
            if ((p != 0) && (p->getColor() == opcolor))
                pmovs[i].setCapture(true);        
        }

        // check for unavoided check
        if (isCheck())
        {
            ColorType prev_check = check;
            doMove(pmovs[i]);
            if ((check != prev_check) &&
                (check != COLOR_TYPE_BOTH) &&
                (!isMate()))
                pmovs[i].setValid(true);
            undoMove(pmovs[i]);
        }

        // check for self-discovered check
        else
        {
            doMove(pmovs[i]);
            if ((check == oppose(pmovs[i].getColor())) ||
                (check == COLOR_TYPE_NONE))
                pmovs[i].setValid(true);
            else
                pmovs[i].setValid(false);
            undoMove(pmovs[i]);
        }

        // add move to the list of valid moves
        if (pmovs[i].isValid())
            moves.push_back(pmovs[i]);
    }

    // if no valid moves: mate or stalemate
    if (moves.size() == 0)
    {
        if (isCheck())
        {
            end  = END_TYPE_MATE;
            mate = opcolor;
        }
        else
        {
            end  = END_TYPE_DRAW_STALE;
            mate = COLOR_TYPE_NONE;
        }
    }
    // check if draw because of only two kings left
    else if (pieces.size() < 3)
    {
        mate = COLOR_TYPE_NONE;
        end  = END_TYPE_DRAW_PIECES;
    }

    return moves;
}


/*!
 * Filter out evil castles.
 *
 * This function receives a list of moves and looks for castles. When a castling
 * move is found, it is checked if it can be performed or not, according to the
 * availability of the sqaures between the king and the rook, plus the mobility
 * of the king and the rook (meaning that it must be the very first time that
 * both pieces move).
 *
 * If a castling move is not valid, according to the rules above, it is filtered
 * out.
 *
 * @param moves list of Moves to which apply the filter.
 *
 * @return a list of moves with all the castles filtered out.
 */
vector<Move> Board::filterCastles(vector<Move> moves)
{
    return filterCastlesLong(filterCastlesShort(moves));
}


/*!
 * Filter out evil short castles.
 *
 * This function receives a list of moves and looks for short castles. When a 
 * short castling move is found, it is checked if it can be performed or not,
 * according to the availability of the sqaures between the king and the rook,
 * plus the mobility * of the king and the rook (meaning that it must be the very
 * first time that both pieces move).
 *
 * If a short castling move is not valid, according to the rules above, it is
 * filtered out.
 *
 * @param moves list of Moves to which apply the filter.
 *
 * @return a list of moves with all the short castles filtered out.
 */
vector<Move> Board::filterCastlesShort(vector<Move> moves)
{
    vector<Move> filter;
    ColorType moving;
    King *king = 0;
    Rook *rook = 0;
    Piece *mp1 = 0;
    Piece *mp2 = 0;
    PieceType kingtype;
    PieceType rooktype;
    int middle1, middle2;
    vector<Piece *> opponent;
    bool possible = true;

    for (unsigned int i = 0; i < moves.size(); i++)
    {
        if (moves[i].getAlgebraic() == "0-0")
        { 
            moving = moves[i].getColor();

            // check who is moving
            if (moving == COLOR_TYPE_WHITE)
            {
                king = static_cast<King *>(getPieceAt(4));
                rook = static_cast<Rook *>(getPieceAt(7));
                kingtype = PIECE_TYPE_KING_WHITE;
                rooktype = PIECE_TYPE_ROOK_WHITE;
                middle1 = 5;
                middle2 = 6;
                opponent = getPieces(getPieces(COLOR_TYPE_BLACK));
            }
            else if (moving == COLOR_TYPE_BLACK)
            {
                king = static_cast<King *>(getPieceAt(60));
                rook = static_cast<Rook *>(getPieceAt(63));
                kingtype = PIECE_TYPE_KING_BLACK;
                rooktype = PIECE_TYPE_ROOK_BLACK;
                middle1 = 61;
                middle2 = 62;
                opponent = getPieces(getPieces(COLOR_TYPE_WHITE));
            }
            else
            {
                continue;
            }
    
            // check if there is any piece in between
            mp1 = getPieceAt(middle1);
            mp2 = getPieceAt(middle2);

            // now perform all the checks (king not moved, rook not moved, etc)
            if ((king == 0) || (rook == 0))
                continue;
            else if ((king->getType() != kingtype) || (rook->getType() != rooktype))
                continue;
            else if (king->isMoved() || rook->isMoved())
                continue;
            else if (king->isChecked())
                continue;
            else if ((mp1 != 0) || (mp2 != 0))
                continue;

            // check on-the-move check
            for (unsigned int j = 0; j < opponent.size(); j++)
            {
                if ((opponent[j]->getAttacks() & BitboardFromPosition(middle1))
                    ||
                    (opponent[j]->getAttacks() & BitboardFromPosition(middle2)))
                {
                    possible = false;
                    continue;
                }
            }

            if (possible)
                filter.push_back(moves[i]);
        }
        else
        {
            filter.push_back(moves[i]);
        }
    }

    return filter;
}


/*!
 * Filter out evil long castles.
 *
 * This function receives a list of moves and looks for long castles. When a 
 * long castling move is found, it is checked if it can be performed or not,
 * according to the availability of the sqaures between the king and the rook,
 * plus the mobility * of the king and the rook (meaning that it must be the very
 * first time that both pieces move).
 *
 * If a long castling move is not valid, according to the rules above, it is
 * filtered out.
 *
 * @param moves list of Moves to which apply the filter.
 *
 * @return a list of moves with all the short castles filtered out.
 */
vector<Move> Board::filterCastlesLong(vector<Move> moves)
{
    vector<Move> filter;
    ColorType moving;
    King *king = 0;
    Rook *rook = 0;
    Piece *mp1 = 0;
    Piece *mp2 = 0;
    Piece *mp3 = 0;
    PieceType kingtype;
    PieceType rooktype;
    int middle1, middle2, middle3;
    vector<Piece *> opponent;
    bool possible = true;

    for (unsigned int i = 0; i < moves.size(); i++)
    {
        if (moves[i].getAlgebraic() != "0-0-0")
        { 
            filter.push_back(moves[i]);
            continue;
        }

        // check who is moving
        moving = moves[i].getColor();

        // different positions for each side
        if (moving == COLOR_TYPE_WHITE)
        {
            king = static_cast<King *>(getPieceAt(4));
            rook = static_cast<Rook *>(getPieceAt(0));
            kingtype = PIECE_TYPE_KING_WHITE;
            rooktype = PIECE_TYPE_ROOK_WHITE;
            middle1 = 3;
            middle2 = 2;
            middle3 = 1;
            opponent = getPieces(getPieces(COLOR_TYPE_BLACK));
        }
        else if (moving == COLOR_TYPE_BLACK)
        {
            king = static_cast<King *>(getPieceAt(60));
            rook = static_cast<Rook *>(getPieceAt(56));
            kingtype = PIECE_TYPE_KING_BLACK;
            rooktype = PIECE_TYPE_ROOK_BLACK;
            middle1 = 59;
            middle2 = 58;
            middle3 = 57;
            opponent = getPieces(getPieces(COLOR_TYPE_WHITE));
        }
        else
        {
            continue;
        }

        // check if there is any piece in between
        mp1 = getPieceAt(middle1);
        mp2 = getPieceAt(middle2);
        mp3 = getPieceAt(middle3);

        // now perform all the checks (king not moved, rook not moved, etc)
        if ((king == 0) || (rook == 0))
            continue;
        else if ((king->getType() != kingtype) || (rook->getType() != rooktype))
            continue;
        else if (king->isMoved() || rook->isMoved())
            continue;
        else if (king->isChecked())
            continue;
        else if ((mp1 != 0) || (mp2 != 0) || (mp3 != 0))
            continue;

        // check on-the-move check
        for (unsigned int j = 0; j < opponent.size(); j++)
        {
            if ((opponent[j]->getAttacks() & BitboardFromPosition(middle1))
                ||
                (opponent[j]->getAttacks() & BitboardFromPosition(middle2)))
            {
                possible = false;
                continue;
            }
        }

        if (possible)
            filter.push_back(moves[i]);
    }

    return filter;
}


/*!
 * Filter out pawn captures.
 *
 * This function receives a list of moves and looks for pawn captures. Then, it
 * tests if every pawn capture can actually be performed (without checking check
 * conditions), and if it is possible, then it still returns it back. Otherwise,
 * if the move is actually not valid, it will drop it from the list of moves.
 *
 * @param moves List of Moves to which apply the filter.
 *
 * @return a list of moves with all the illegal pawn captures filtered out.
 */
vector<Move> Board::filterPawnCaptures(vector<Move> moves)
{
    vector<Move> filter;
    int orig, dest;
    ColorType color;
    Piece *p;
    BitBoard cur_empassant = 0;

    // now look for legal moves
    for (unsigned int i = 0; i < moves.size(); i++)
    {
        // if the move is not a pawn capture, don't check anything
        if ((moves[i].getType() != MOVE_TYPE_CAPTURE_PAWN) &&
            (moves[i].getType() != MOVE_TYPE_PROMOTION_CAPTURE))
        { 
            filter.push_back(moves[i]);
            continue;
        }

        // estimate the parameters for this very move
        orig  = moves[i].getOrigin();
        dest  = moves[i].getDestination();
        color = moves[i].getColor();
        p = getPieceAt(moves[i].getDestination());

        // if no piece on destination, check for empassant
        if (p == 0)
        {
            // check where is the current empassant pawn, if any
            cur_empassant = getEmpassant();

            // white can capture empassants only at row 5
            if ((color == COLOR_TYPE_WHITE) && ((orig / 8) != 4))
                continue;

            // black can capture empassants only at row 4
            if ((color == COLOR_TYPE_BLACK) && ((orig / 8) != 3))
                continue;

            // now we can safely check empassants for black and white
            //
            // Note: (8 * color) tells if the empassant must be one row up or
            //       down, depending if we are checking on black or white
            if (cur_empassant & BitboardFromPosition(dest - (8 * color)))
            {
                moves[i].setEmpassant(true);
                filter.push_back(moves[i]);
            }
        }
        // there is a piece in the destination, check if it is opponent
        else
        {
            if (p->getColor() == oppose(color))
                filter.push_back(moves[i]);
        }
    }

    return filter;
}
