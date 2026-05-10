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
 * @file src/application/prompt.cpp
 */
#include <sstream>
#include "application/prompt"



/*!
 * Initialize the prompt text and the welcome text.
 *
 * @param p Initial string to provide the promptline.
 * @param w Initial string to provide the welcome message.
 */
Prompt::Prompt(string p, string w)
{
    welcome     = w;
    promptline  = p;
}


/*!
 * Print the prompt to the user.
 *
 * @param color ColorType indicating the current player.
 * @param turn  Number of the turn for an ongoing game.
 */
void Prompt::turn(ColorType color, int turn)
{
    ostringstream line(ostringstream::out);

    if (color == COLOR_TYPE_WHITE)
    {
        line << "White (" << turn << "): ";
    }
    else if (color == COLOR_TYPE_BLACK)
    {
        line << "Black (" << turn << "): ";
    }
    else
    {
        line << promptline;
    }
    
    cout << endl << line.str();
}


/*!
 * Welcome the user and print the prompt for entering commands/movements.
 */
void Prompt::init()
{
    cout << welcome << endl;

    turn();
}


/*!
 * Terminate the program outputing some greetings to the user (graceful quit).
 *
 * @param str String to display to the user before quitting.
 */
void Prompt::terminate(string str)
{
    if (str == "")
    {
        cout << endl << "Goodbye!" << endl;
    }
    else
    {
        cout << endl << str << endl;
    }
}
