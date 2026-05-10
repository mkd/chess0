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
 * @file src/game/move.cpp
 */
#include <sstream>
#include "game/move"
#include "utils"



/*!
 * Default constructor.
 */
Move::Move()
{
    reset();
}


/*!
 * Reset a move to empty (defaults)
 */
void Move::reset()
{
    algebraic = "";
    human     = "";
    piece     = PIECE_TYPE_X;
    orig      = 0;
    dest      = 0;
    type      = MOVE_TYPE_INVALID;
    color     = COLOR_TYPE_WHITE;
    valid     = false;
    ambiguous = false;
    capture   = false;
    empassant = false;
    castle    = false;
    promotion = false;
    end       = false;
    score     = 0;
    learned   = false;
    order     = 0;
}


/*!
 * Fill all the information of the move according to another given move.
 *
 * @param mv Move object from where to copy the data.
 */
void Move::fill(Move mv)
{
    algebraic = mv.getAlgebraic();
    human     = mv.getHuman();
    piece     = mv.getPiece();
    orig      = mv.getOrigin();
    dest      = mv.getDestination();
    type      = mv.getType();
    color     = mv.getColor();
    valid     = mv.isValid();
    ambiguous = mv.isAmbiguous();
    capture   = mv.isCapture();
    empassant = mv.isEmpassant();
    castle    = mv.isCastle();
    promotion = mv.isPromotion();
    end       = mv.isEnd();
    score     = mv.getScore();
}


/*!
 * Set the type of movement, including invalid and wrong movement types.
 *
 * @param t Type of move to be set.
 */
void Move::setType(MoveType t)
{
    type = t;

    // for consistency, when the move type is MOVE_TYPE_INVALID, then validity
    // should be turned off (valid = false)
    if (type == MOVE_TYPE_INVALID)
        valid = false;

    // check if it is a capture
    if ((type == MOVE_TYPE_CAPTURE_PAWN) ||
        (type == MOVE_TYPE_CAPTURE_SIMPLE) ||
        (type == MOVE_TYPE_CAPTURE_LONG))
        capture = true;
}


/*!
 * Set the validity of a move.
 *
 * @param v Validty of a move (valid or not).
 */
void Move::setValid(bool v)
{
    valid = v;

    // implicitly specify that a non-valid move is of type INVALID
    if (!valid)
        type = MOVE_TYPE_INVALID;
}


/*!
 * Create a string containing the internal representation (position integers of
 * origin and destination) of the current move.
 *
 * @return a string containing the numbers of the squares of the move in the
 *         internal representation of the program.
 */
string Move::toStringInternal()
{
    ostringstream out(ostringstream::out);

    out << getOrigin() << "-" << getDestination();

    return out.str();
}


/*!
 * Check the type of the move and return a human-readable string containing the
 * type name of the move.
 *
 * @return a string containing the type name of the move.
 */
string Move::getTypeString()
{
    switch (type)
    {
        case MOVE_TYPE_VALID:
            return "valid move, unknown type";
            break;
        case MOVE_TYPE_NOGAME:
            return "invalid move, no game running";
            break;
        case MOVE_TYPE_INVALID:
            return "invalid move";
            break;
        case MOVE_TYPE_WRONG_MOVE:
            return "wrong move";
            break;
        case MOVE_TYPE_PAWN:
            return "valid move, pawn move";
            break;
        case MOVE_TYPE_SIMPLE:
            return "valid move, simple move";
            break;
        case MOVE_TYPE_CASTLE_SHORT:
            return "valid move, short castle";
            break;
        case MOVE_TYPE_XY:
            return "valid move, XY move";
            break;
        case MOVE_TYPE_CAPTURE_PAWN:
            return "valid move, capture made by pawn";
            break;
        case MOVE_TYPE_CAPTURE_PAWN_SHORT:
            return "valid move, capture pawn short";
            break;
        case MOVE_TYPE_CAPTURE_SIMPLE:
            return "valid move, capture simple";
            break;
        case MOVE_TYPE_CAPTURE_SIMPLE_SHORT:
            return "valid move, capture simple short";
            break;
        case MOVE_TYPE_AMBIGUOUS:
            return "valid move, ambiguous move";
            break;
        case MOVE_TYPE_CASTLE_LONG:
            return "valid move, long castle";
            break;
        case MOVE_TYPE_CAPTURE_LONG:
            return "valid move, capture ambiguous";
            break;
        case MOVE_TYPE_PROMOTION_SIMPLE:
            return "valid move, promotion simple";
            break;
        case MOVE_TYPE_PROMOTION_CAPTURE:
            return "valid move, promotion capture";
            break;
        case MOVE_TYPE_PROMOTION_CAPTURE_SHORT:
            return "valid move, promotion capture_short";
            break;
        default:
            return "unknown move type";
    }
}


/*!
 * Represent the data of the move in a human-readable format.
 *
 * @return a string containing the representation of the move.
 */
string Move::toString()
{
    ostringstream out(ostringstream::out);

    out << "Algebraic: " << algebraic << endl;
    out << "Human:     " << human << endl;
    out << "Piece:     " << pieceName(piece) << endl;
    out << "From-to:   " << orig << "-" << dest << endl;
    out << "Move type: " << getTypeString() << endl;
    out << "Score:     " << getScore() << endl;
    out << "Player:    ";
    if (color == COLOR_TYPE_WHITE)
        out << "white";
    else if (color == COLOR_TYPE_BLACK)
        out << "black";
    else
        out << "unknown";
    out << endl;
    out << "Valid:     ";
    (valid) ? out << "true" : out << "false";
    out << endl;
    out << "Ambiguous: ";
    (ambiguous) ? out << "true" : out << "false";
    out << endl;
    out << "Capture:   ";
    (capture) ? out << "true" : out << "false";
    out << endl;
    out << "Empassant: ";
    (empassant) ? out << "true" : out << "false";
    out << endl;
    out << "Castling:  ";
    (castle) ? out << "true" : out << "false";
    out << endl;
    out << "Promotion: ";
    (promotion) ? out << "true" : out << "false";
    out << endl;

    return out.str();
}


/*!
 * Compare a move field by field.
 *
 * @param m Move to be compared with.
 *
 * @return true if m is identical to this Move object, false otherwise.
 */
bool Move::equals(Move mv)
{
    // if every single field matches, then they are equal, with the exceptions:
    // * turn -> this is obvious, same move at different turns
    if ((mv.getAlgebraic() == algebraic) &&
        (mv.getPiece() == piece) &&
        (mv.getOrigin() == orig) &&
        (mv.getDestination() == dest) &&
        (mv.getType() == type) &&
        (mv.getColor() == color) &&
        (mv.isValid() == valid) &&
        (mv.isAmbiguous() == ambiguous) &&
        (mv.isCapture() == capture) &&
        (mv.isEmpassant() == empassant) &&
        (mv.isCastle() == castle) &&
        (mv.isPromotion() == promotion) &&
        (mv.isEnd() == end))
    {
        return true;
    }

    // if any of the fields does not match, then not equal
    return false;
}
