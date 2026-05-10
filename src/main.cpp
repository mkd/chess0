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
 * @file src/main.cpp
 */
#include <iostream>
#include <stdlib.h>
#include "definitions"
#include "utils"
#include "game/manager"
#include "application/manager"
#include "application/xboard"

using namespace std;


/*!
 * This main function is a dummy function that simply delegates all the
 * application work to the ApplicationManager.
 */
int main(int argc, char **argv)
{
    GameManager gm;

    // check if version
    if ((argc >= 2) && (strcmp(argv[1], "-v") == 0))
    {
        cout << PROGRAM_NAME << " (version " << PROGRAM_VERSION << ")" << endl;
        cout << PROGRAM_AUTHOR << endl;
        cout << "Website: http://" << PROGRAM_WEB << endl << endl;
        exit(0);
    }

    // check if we are in xboard mode
    if ((argc >= 2) && (strcmp(argv[1], "xboard") == 0))
    {
        XBoard app(&gm);
        return app.launch();
    }
    else
    {
        ApplicationManager app(&gm);
        return app.launch();
    }
}
