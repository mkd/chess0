// This file is part of Chess0, a computer chess program based on Winglet chess
// by Stef Luijten.
//
// Copyright (C) 2022 Claudio M. Camacho
//
// Chess0 is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Chess0 is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Foobar. If not, see <http://www.gnu.org/licenses/>.



// @file uci.cpp
//
// This file contains implementation of the UCI protocol.
#include <iostream>
#include <sstream>
#include <vector>
#include <list>

#include "uci.h"
#include "extglobals.h"
#include "definitions.h"
#include "functions.h"



using namespace std;



// uciLoop()
//
// Main program loop accepting UCI commands and executing them. This part of
// the application does not have a user interface (not even a CLI prompt).
int uciLoop(void)
{
    string inputStr;
    string cmd  = "";
    string arg  = "";
    string tStr = "";
    list<string> input;


    // Prompt the user for input from the command line
    cout << PROGRAM_NAME << " v" << PROGRAM_VERSION << endl << endl;
    cout << "id name " << PROGRAM_NAME << endl;
    cout << "id author " << PROGRAM_AUTHOR << endl;
    cout << "uciok" << endl;



    // UCI engine main loop:
    // - Wait for an input
    // - Read the input and check if it is a move or a command
    // - If invalid command, ignore
    // - If valid command, execute and return to previous prompt
    while (1)
    {
        // Clear both the input and output buffer, to make sure the new input
        // isn't altered from something entered during the program's output
        input.clear();
        tStr = "";
        cout << endl;


        // read from the input
        std::getline(cin, inputStr);
        std::istringstream iss(inputStr);
        while (iss >> tStr)
        {
            input.push_back(tStr);
        }


        // extract the command from the input
        cmd = input.front();
        if (input.size() > 1)
            arg = *std::next(input.begin(), 1);


        /*for (auto const &i: input) {
            std::cout << i << std::endl;
        }*/


        // Process the 'input' here and execute, if it is a valid command.
        //
        // isready
        if (cmd == "isready")
        {
            cout << "readyok" << endl;
        }


        // ucinewgame
        else if (cmd == "ucinewgame")
        {
            istringstream ss2(STARTPOS);
            string arg1, arg2, arg3, arg4, arg5 = "0", arg6 = "1";
            ss2 >> arg1 >> arg2 >> arg3 >> arg4 >> arg5 >> arg6;

            if (!arg.empty() && !arg2.empty() && !arg3.empty() &&
                !arg4.empty() && !arg5.empty() && !arg6.empty())
            {
                vector<char> args1(arg.c_str(), arg.c_str() + arg.size() + 1);
                vector<char> args2(arg2.c_str(), arg2.c_str() + arg2.size() + 1);
                vector<char> args3(arg3.c_str(), arg3.c_str() + arg3.size() + 1);
                vector<char> args4(arg4.c_str(), arg4.c_str() + arg4.size() + 1);
                setupFen(args1.data(), args2.data(), args3.data(), args4.data(), atoi(arg5.c_str()), atoi(arg6.c_str()));
            }
        }


        // position
        else if (cmd == "position")
        {
            if (arg == "startpos")
            {

            }

        }

        
        // quit
        else if (cmd == "quit")
        {
            exit(0);
        }


        // uci
        else if (cmd == "uci")
        {
            cout << "id name " << PROGRAM_NAME << endl;
            cout << "id author " << PROGRAM_AUTHOR << endl;
            cout << "uciok" << endl;
        }


        // unknown command
        else
        {
            cout << "Unknown command: " << cmd << endl;
        }
    }

    return 0;
}
