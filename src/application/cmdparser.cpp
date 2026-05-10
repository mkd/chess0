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
 * @file src/application/cmdparser.cpp
 */
#include "application/cmdparser"



/*!
 * Convert a given input into an internal action command.
 *
 * @param input String which contains the user-entered input.
 *
 * @return a Command object with the internal action command for the program.
 */
Command CmdParser::translate(string input)
{
    Command c;
    string cmd;
    string arg;
    int pos;

    // convert the input to lower case
    for (unsigned int i = 0; i < input.length(); i++)
        input[i] = tolower(input[i]);

    // check if there is any argument
    pos = input.find_first_of(' ', 0);
    cmd = input.substr(0, pos);
    if (pos == -1)
        arg = "";
    else
        arg = input.substr(pos + 1, input.size() - pos - 1);

    // set the command
    c.setName(cmd);
    c.addArgument(arg);

    // now set the type of input
    if (cmd == "analyze")
        c.setType(CMD_TYPE_ANALYZE);

    else if (cmd == "auto")
        c.setType(CMD_TYPE_AUTO);

    else if (cmd == "book")
        c.setType(CMD_TYPE_BOOK);

    else if ((cmd == "cache") || (cmd == "memory"))
        c.setType(CMD_TYPE_CACHE);

    else if ((cmd == "depth") || (cmd == "sd"))
        c.setType(CMD_TYPE_DEPTH);

    else if (cmd == "draw")
        c.setType(CMD_TYPE_DRAW);

    else if (cmd == "edit")
        c.setType(CMD_TYPE_EDIT);

    else if (cmd == "eval")
        c.setType(CMD_TYPE_DISPLAY_EVAL);

    else if (cmd == "flip")
        c.setType(CMD_TYPE_FLIP);

    else if (cmd == "go")
        c.setType(CMD_TYPE_GO);

    else if (cmd == "help")
        c.setType(CMD_TYPE_HELP);

    else if (cmd == "history")
        c.setType(CMD_TYPE_HISTORY);

    else if (cmd == "info")
        c.setType(CMD_TYPE_INFO);

    else if (cmd == "load")
        c.setType(CMD_TYPE_LOAD);

    else if (cmd == "log")
        c.setType(CMD_TYPE_LOG);

    else if ((cmd == "manual") || (cmd == "force"))
        c.setType(CMD_TYPE_MANUAL);

    else if (cmd == "material")
        c.setType(CMD_TYPE_DISPLAY_MATERIAL);

    else if (cmd == "nopost")
        c.setType(CMD_TYPE_NOPOST);

    else if (cmd == "pass")
        c.setType(CMD_TYPE_PASS);

    else if (cmd == "ping")
        c.setType(CMD_TYPE_PING);

    else if (cmd == "playother")
        c.setType(CMD_TYPE_PLAYOTHER);

    else if (cmd == "post")
        c.setType(CMD_TYPE_POST);

    else if (cmd == "remove")
        c.setType(CMD_TYPE_REMOVE);

    else if (cmd == "resign")
        c.setType(CMD_TYPE_RESIGN);

    else if ((cmd == "restart") || (cmd == "new"))
        c.setType(CMD_TYPE_NEW);

    else if (cmd == "save")
        c.setType(CMD_TYPE_SAVE);

    else if (cmd == "show")
        c.setType(CMD_TYPE_SHOW);

    else if (cmd == "solve")
        c.setType(CMD_TYPE_SOLVE);

    else if (cmd == "test")
        c.setType(CMD_TYPE_TEST);

    else if ((cmd == "think") || (cmd == "st"))
        c.setType(CMD_TYPE_TPM);

    else if (cmd == "time")
        c.setType(CMD_TYPE_TIME);

    else if ((cmd == "undo") || (cmd == "back"))
        c.setType(CMD_TYPE_UNDO);

    else if (cmd == "verbose")
        c.setType(CMD_TYPE_VERBOSE);

    else if (cmd == "quiet")
        c.setType(CMD_TYPE_QUIET);

    else if ((cmd == "version") || (cmd == "ver") || (cmd == "v"))
        c.setType(CMD_TYPE_VERSION);

    else if (cmd == "xboard")
        c.setType(CMD_TYPE_XBOARD);

    else if ((cmd == "quit") || (cmd == "exit") || (cmd == "q"))
        c.setType(CMD_TYPE_QUIT);

    else
        c.setType(CMD_TYPE_UNKNOWN);

    return c;
}
