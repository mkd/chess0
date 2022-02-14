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
#include <map>

#include "extglobals.h"
#include "definitions.h"
#include "functions.h"
#include "app.h"



using namespace std;



// uciLoop()
//
// Main program loop accepting UCI commands and executing them. This part of
// the application does not have a user interface (not even a CLI prompt).
int uciLoop(void)
{
    string cmd  = "";


    // turn off verbosity and flag UCI mode
    UCI = true;
    beQuiet = true;


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
        cmd.clear();
        cout << endl;


        // read from the input
        std::getline(cin, cmd);


        // Process the 'input' here and execute, if it is a valid command.
        //
        // isready
        if (cmd == "isready")
        {
            cout << "readyok" << endl;
        }


        else if ((cmd == "d") || (cmd == "display") || (cmd == "show"))
        {
            board.display();
        }


        // go
        else if (cmd.find("go") != string::npos)
        {
            // XXX
        }


        // ucinewgame
        else if (cmd == "ucinewgame")
        {
            istringstream ss2(STARTPOS);
            string arg1, arg2, arg3, arg4, arg5 = "0", arg6 = "1";
            ss2 >> arg1 >> arg2 >> arg3 >> arg4 >> arg5 >> arg6;

            if (!arg1.empty() && !arg2.empty() && !arg3.empty() &&
                !arg4.empty() && !arg5.empty() && !arg6.empty())
            {
                vector<char> args1(arg1.c_str(), arg1.c_str() + arg1.size() + 1);
                vector<char> args2(arg2.c_str(), arg2.c_str() + arg2.size() + 1);
                vector<char> args3(arg3.c_str(), arg3.c_str() + arg3.size() + 1);
                vector<char> args4(arg4.c_str(), arg4.c_str() + arg4.size() + 1);
                setupFen(args1.data(), args2.data(), args3.data(), args4.data(), atoi(arg5.c_str()), atoi(arg6.c_str()));
            }
        }


        // position startpos moves ...
        //
        // Set the starting position and parse moves given after the "moves"
        // argument. Iterate over the moves and apply them, in order, if
        // they are valid.
        else if (cmd.find("position startpos") != string::npos)
        {
            istringstream ss2(STARTPOS);
            string arg1, arg2, arg3, arg4, arg5 = "0", arg6 = "1";
            ss2 >> arg1 >> arg2 >> arg3 >> arg4 >> arg5 >> arg6;

            if (!arg1.empty() && !arg2.empty() && !arg3.empty() &&
                !arg4.empty() && !arg5.empty() && !arg6.empty())
            {
                vector<char> args1(arg1.c_str(), arg1.c_str() + arg1.size() + 1);
                vector<char> args2(arg2.c_str(), arg2.c_str() + arg2.size() + 1);
                vector<char> args3(arg3.c_str(), arg3.c_str() + arg3.size() + 1);
                vector<char> args4(arg4.c_str(), arg4.c_str() + arg4.size() + 1);
                setupFen(args1.data(), args2.data(), args3.data(), args4.data(), atoi(arg5.c_str()), atoi(arg6.c_str()));
            }

            size_t movesIndex = cmd.find("moves ");
            string moveList;
            if (movesIndex != string::npos)
            {
                moveList = cmd.substr(movesIndex + 6);
                istringstream iss(moveList);
                vector<string> inputMoves{istream_iterator<string>{iss},
                                          istream_iterator<string>{}};
                vector<string> validMoveList;

                // apply each move, if legal
                for (string i: inputMoves)
                {
                    string inputMove = "";

                    // create a vector with all valid moves in UCI format (e.g., "e2e4")
                    map<string, string> validMoves = getValidMoves();
                    for (map<string, string>::iterator it = validMoves.begin(); it != validMoves.end(); ++it)
                    {
                        validMoveList.push_back (it->second);
                    }

                    // if valid move, make the move
                    if (find(validMoveList.begin(), validMoveList.end(), i) != validMoveList.end())
                    {
                        Move myMove;

                        // generate the pseudo-legal move list
                        board.moveBufLen[0] = 0;
                        board.moveBufLen[1] = movegen(board.moveBufLen[0]);

                        // check to see if the user move is also found in the pseudo-legal move list
                        if (isValidTextMove(i, myMove))
                        {
                            makeMove(myMove);

                            // post-move check to see if we are leaving our king in check
                            if (isOtherKingAttacked())
                            {
                                unmakeMove(myMove);
                            }
                        }
                    }
                }
            }
        }

        // position fen ... moves ...
        //
        // Set the board position according to the given FEN string and parse
        // moves given after the "moves" argument. Iterate over the moves and
        // apply them, in order, if they are valid.
        else if (cmd.find("position fen") != string::npos)
        {
            string fenInput = cmd.substr(13);
            istringstream ss2(fenInput);
            string arg1, arg2, arg3, arg4, arg5 = "0", arg6 = "1";
            ss2 >> arg1 >> arg2 >> arg3 >> arg4 >> arg5 >> arg6;

            if (!arg1.empty() && !arg2.empty() && !arg3.empty() &&
                !arg4.empty() && !arg5.empty() && !arg6.empty())
            {
                vector<char> args1(arg1.c_str(), arg1.c_str() + arg1.size() + 1);
                vector<char> args2(arg2.c_str(), arg2.c_str() + arg2.size() + 1);
                vector<char> args3(arg3.c_str(), arg3.c_str() + arg3.size() + 1);
                vector<char> args4(arg4.c_str(), arg4.c_str() + arg4.size() + 1);
                setupFen(args1.data(), args2.data(), args3.data(), args4.data(), atoi(arg5.c_str()), atoi(arg6.c_str()));
            }

            size_t movesIndex = cmd.find("moves ");
            string moveList;
            if (movesIndex != string::npos)
            {
                moveList = cmd.substr(movesIndex + 6);
                istringstream iss(moveList);
                vector<string> inputMoves{istream_iterator<string>{iss},
                                          istream_iterator<string>{}};
                vector<string> validMoveList;

                // apply each move, if legal
                for (string i: inputMoves)
                {
                    string inputMove = "";

                    // create a vector with all valid moves in UCI format (e.g., "e2e4")
                    map<string, string> validMoves = getValidMoves();
                    for (map<string, string>::iterator it = validMoves.begin(); it != validMoves.end(); ++it)
                    {
                        validMoveList.push_back (it->second);
                    }

                    // if valid move, make the move
                    if (find(validMoveList.begin(), validMoveList.end(), i) != validMoveList.end())
                    {
                        Move myMove;

                        // generate the pseudo-legal move list
                        board.moveBufLen[0] = 0;
                        board.moveBufLen[1] = movegen(board.moveBufLen[0]);

                        // check to see if the user move is also found in the pseudo-legal move list
                        if (isValidTextMove(i, myMove))
                        {
                            makeMove(myMove);

                            // post-move check to see if we are leaving our king in check
                            if (isOtherKingAttacked())
                            {
                                unmakeMove(myMove);
                            }
                        }
                    }
                }
            }
        }


        // stop
        else if (cmd == "stop")
        {
            // stop engine from thinking
            stopEngine = true;
        }

        
        // quit
        else if (cmd == "quit") 
        {
            exit(0);
        }


        // uci
        else if (cmd == "uci")
        {
            UCI = true;
            beQuiet = true;

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
