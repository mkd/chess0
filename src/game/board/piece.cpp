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
 * @file src/game/board/piece.cpp
 */
#include <iostream>
#include <sstream>
#include "utils"
#include "game/board/piece"
#include "game/board/square"



/*!
 * Update all the necessary information for a piece when it is moved (for
 * consistency).
 *
 * Note: this function assumes that setPosition() was called before, so that the
 * position is already synchronized.
 *
 * @param b   Pointer to the board with respect to update the piece status.
 */
void Piece::update(Board *b)
{
    // now update the status for the current position
    bb = BitboardFromPosition(position);
    recalculateMoves(b);
    recalculateAttacks(b);

    // if the attacks differ from the moves (case of the pawn)
    if (moves ^ attacks)
        npossible = countBits(moves) + countBits(attacks);
    else
        npossible = countBits(moves);

}


/*!
 * Represent the data of the piece in a human-readable format.
 *
 * @return a string containing the representation of the piece.
 */
string Piece::toString()
{
    ostringstream out(ostringstream::out);

    out << "Piece:     " << pieceName(type) << endl;
    out << "Position:  " << position << endl;
    out << "On board:  ";
    if (isEnabled())
        out << "true";
    else
        out << "false";

    return out.str();
}


/*!
 * Generate a hash with the piece type, position, possible moves, attacks, etc.
 *
 * @return a one-line string with the whole piece status.
 */
string Piece::state()
{
    ostringstream s(ostringstream::out);

    s << pieceName(type) << "-" << position << "-" << moves << "-" << attacks << "-" << npossible;

    return s.str();
}
