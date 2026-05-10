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
 * @file src/game/board/square.cpp
 */
#include <sstream>
#include "utils"
#include "game/board/square"



/*!
 * Default constructor
 */
Square::Square()
{
    color       = COLOR_TYPE_EMPTY;
    position    = 0;
}


/*!
 * Convert to a human-readable string this square.
 */
string Square::toString()
{
    ostringstream me(ostringstream::out);

    me << "Square " << position << ":" << endl << endl;
    me << " Color:";
    if (color == COLOR_TYPE_WHITE)
        me << "white";
    else
        me << "black";
    me << endl;
    me << " Piece: " << pieceName(piece->getType());
    me << endl << endl;

    return me.str();
}
