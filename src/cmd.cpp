/* 
   This file is part of Chess0, a computer chess program based on Winglet chess
   by Stef Luijten.

   Copyright (C) 2019 Claudio M. Camacho

   Chess0 is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   Chess0 is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with Foobar. If not, see <http://www.gnu.org/licenses/>.
   */



// @file board.cpp
//
// This file contains the functionality to execute all commands from the CLI
// interface of Chess0.
#include <iostream>
#include <fstream>
#include <iomanip>
#include <unordered_map>
#include <stdio.h>
#include <sstream>
#include <string>
#include <cstring>
#include <cmath>
#include "definitions.h"
#include "app.h"
#include "functions.h"
#include "board.h"
#include "timer.h"
#include "move.h"
#include "search.h"
#include "cmd.h"
#include "extglobals.h"



using namespace std;



// Global variables used in this part of the program
int curPlayerType;
uint64_t msStart,msStop, moves;
Timer timer;



// initListOfCommands
//
// Initialize the list of commands supported by the application.
void initListOfCommands()
{
    listOfCommands.push_back("auto");
    listOfCommands.push_back("back");
    listOfCommands.push_back("bench");
    listOfCommands.push_back("book");
    listOfCommands.push_back("cache");
    listOfCommands.push_back("depth");
    listOfCommands.push_back("edit");
    listOfCommands.push_back("eval");
    listOfCommands.push_back("exit");
    listOfCommands.push_back("flip");
    listOfCommands.push_back("game");
    listOfCommands.push_back("go");
    listOfCommands.push_back("help");
    listOfCommands.push_back("history");
    listOfCommands.push_back("load");
    listOfCommands.push_back("manual");
    listOfCommands.push_back("moves");
    listOfCommands.push_back("new");
    listOfCommands.push_back("q");
    listOfCommands.push_back("quit");
    listOfCommands.push_back("remove");
    listOfCommands.push_back("resign");
    listOfCommands.push_back("restart");
    listOfCommands.push_back("save");
    listOfCommands.push_back("sd");
    listOfCommands.push_back("show");
    listOfCommands.push_back("solve");
    listOfCommands.push_back("st");
    listOfCommands.push_back("test");
    listOfCommands.push_back("think");
    listOfCommands.push_back("undo");
    listOfCommands.push_back("v");
    listOfCommands.push_back("ver");
    listOfCommands.push_back("version");
}



// exec()
//
// Execute a given command.
//
// exec() takes an input string (it can be anything) and tries to find a command
// and its arguments, and execute the command. This is how this function works:
//
// 1) convert everyting to lower case, since all commands and arguments are
//    case insensitive
// 2) take only the first and second 'words' from the input string, being the
//    first one the command (cmd) and the second one the argument (arg)
// 3) try to match the command (cmd) in a if-else fashion and execute the given
//    command; apply the argument (arg)  if any
void exec(string input)
{
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


    //
    // Run the command (cmd) through a list of supported commands in an if-else
    // fashion. If the command is found in the list, execute the code associated
    // and use the argument as a parameter, otherwise return without doing
    // anything.
    //
    // See the list of supported commmands below:


    // auto: make the machine play both sides
    if (cmd == "auto")
    {
        wPlayer = PLAYER_TYPE_COMPUTER;
        bPlayer = PLAYER_TYPE_COMPUTER;
        curPlayerType = PLAYER_TYPE_COMPUTER;
        playMode = CPU_CPU;
    }


    // book: turn on or off openings book
    else if (cmd == "book")
    {
        // turn default book on
        if (arg == "on")
        {
            useBook = true;
            usePersonalBook = false;
        }

        // use personal openings
        else if (arg == "personal")
        {
            useBook = true;
            usePersonalBook = true;
        }

        // turn book off
        else if (arg == "off")
        {
            useBook = false;
            usePersonalBook = false;
        }

        // show current use of book
        if (usePersonalBook)
            cout << "Using openings book [personal]." << endl;
        else if (useBook)
            cout << "Opening book is enabled [general]." << endl;
        else
            cout << "Opening book is disabled." << endl;
    }



    // cache: Enable/disable/show cache usage.
    else if (cmd == "cache")
    {
        // turn cache on
        if ((arg == "on") || (arg == "true"))
            useCache = true;

        // turn cache off
        else if ((arg == "off") || (arg == "false"))
        {
            cache.clear();
            useCache = false;
        }

        // show current cache status
        if (useCache)
        {
            char measure = '\0';
            float size = 0;

            cout << "Cache is enabled." << endl;

            // check the current cache size (usage)
            size = cache.size();
            if (size > 1024)
            {
                measure = 'K';
                size /= 1024;
            }
            if (size > 1024)
            {
                measure = 'M';
                size /= 1024;
            }
            if (size > 1024)
            {
                measure = 'G';
                size /= 1024;
            }
            cout << "Current cache size: " << fixed << setprecision(2);
            cout << size << " ";
            cout << measure << "bytes (";
            cout << cache.positions() << " positions)" << endl;
        }
        else
        {
            cout << "Cache is disabled." << endl;
        }
    }



    // depth: change hsearch depth
    else if ((cmd == "depth") || (cmd == "sd"))
    {
        int d;
        d = atoi(arg.c_str());
        if ((d > 3) && (d < SOLVE_MAX_DEPTH))
            board.searchDepth = d;

        cout << "Search depth: " << board.searchDepth << endl;
    }



    // eval: display current board's evaluation
    else if (cmd == "eval")
    {
        displayEval();
    }



    // load: load position from a file
    else if (cmd == "load")
    {
        // convert argument (file name) from string to const char *, for
        // readFen()
        vector<char> char_array(arg.begin(), arg.end());
        char_array.push_back(0);

        // loading a position from a file disables book usage, and sets the game
        // to manual mode
        wPlayer = PLAYER_TYPE_HUMAN;
        bPlayer = PLAYER_TYPE_HUMAN;
        playMode = HUMAN_HUMAN;
        useBook = false;

        // read the FEN string and update the board
        readFen(&char_array[0]);
    }



    // edit: edit a board for setting a position
    else if (cmd == "edit")
    {
        edit();
        useBook = false;
    }



    // flip: flip the board when displaying
    else if (cmd == "flip")
    {
        board.flipBoard = !board.flipBoard;
        board.display();
    }



    // go: force the computer to move now
    else if (cmd == "go")
    {
        if (board.nextMove)
        {
            wPlayer = PLAYER_TYPE_HUMAN;
            bPlayer = PLAYER_TYPE_COMPUTER;
            curPlayerType = bPlayer;
            playMode = HUMAN_CPU;
        }
        else
        {
            wPlayer = PLAYER_TYPE_COMPUTER;
            bPlayer = PLAYER_TYPE_HUMAN;
            curPlayerType = wPlayer;
            playMode = HUMAN_CPU;
        }
    }


    // help: print help about commands
    else if (cmd == "help")
    {
        displayHelp(arg);
    }



    // history: display game history
    else if ((cmd == "history") || (cmd == "game"))
    {
        displayGame();
    }



    // manual: human vs human
    else if (cmd == "manual")
    {
        wPlayer = PLAYER_TYPE_HUMAN;
        bPlayer = PLAYER_TYPE_HUMAN;
        playMode = HUMAN_HUMAN;
        cout << "Both sides are now played by the user." << endl;
    }



    // moves: show the list of valid moves
    else if (cmd == "moves")
    {
        unsigned int i = 0, number = 0;
        char sanMove[12];

        board.moveBufLen[0] = 0;
        board.moveBufLen[1] = movegen(board.moveBufLen[0]);
        cout << endl << "moves from this position:" << endl;

        for (i = board.moveBufLen[0]; i < board.moveBufLen[1]; i++)
        {
            makeMove(board.moveBuffer[i]);
            if (isOtherKingAttacked())
            {
                unmakeMove(board.moveBuffer[i]);
            }
            else
            {
                unmakeMove(board.moveBuffer[i]);
                toSan(board.moveBuffer[i], sanMove);
                cout << ++number << ". " << sanMove << endl;
            }
        }
    }



    // new | restart: new game / restart
    else if ((cmd == "new") || (cmd == "restart"))
    {
        cout << "Starting a new game..." << endl;

        // restart the game
        wPlayer = PLAYER_TYPE_HUMAN;
        bPlayer = PLAYER_TYPE_COMPUTER;
        curPlayerType = wPlayer;
        playMode = HUMAN_CPU;
        cursor = 0;
        numberOfMove = 1;
        gameEnd = END_TYPE_NOEND;

        dataInit();
        board.init();
        cache.clear();

        // enable book by default
        useBook = true;
    }



    // xboard: Xboard mode (protovol ver 1)
    else if (cmd == "xboard")
    {
        // TODO: xboard
    }



    // test | bench: perform test or benchmark
    else if ((cmd == "test") || (cmd == "bench"))
    {
        // disable book and cache
        bool wasUsingCache   = useCache;
        bool wasUsingBook    = useBook;
        useCache = false;
        useBook  = false;


        // test raw moves (make / unmake)
        if (arg == "moves")
        {
            cout << "Testing move performance: " << flush;

            board.moveBufLen[0] = 0;
            board.moveBufLen[1] = movegen(board.moveBufLen[0]);

            // prepare the clock to measure the time of the test
            clock_t start, end;
            float delta;
            long iterations = MOVES_TEST_ITER;
            start = clock();
            for (long i = 0; i < iterations; i++)
            {
                makeMove(board.moveBuffer[0]);
                unmakeMove(board.moveBuffer[0]);
            }
            end = clock();
            delta = (end - start) / (CLOCKS_PER_SEC / 1000);

            cout << iterations/1000000 << " million moves in ";
            cout << fixed << setprecision(2) << delta/1000 << " seconds; speed = ";
            cout << fixed << setprecision(2) << (iterations/1000000)/(delta/1000);
            cout << " Mmps." << endl;
        }

        else if (arg == "perft")
        {
            clock_t start, end;
            uint64_t perftMoves;

            cout << "Testing Perft() function:" << endl;
            cout << "Ply\t  Moves\t     Time\t Moves/s" << endl;
            cout << flush;

            for (int z = 0; z < PERFT_DEPTH_LIMIT; z++)
            {
                board.moveBufLen[0] = 0;

                start = clock();
                perftMoves = perft(z, z);
                end = clock();

                float sec = (end - start) / (CLOCKS_PER_SEC / 1000);
                float speed = perftMoves / sec;

                // PRINT: Depth, Moves, Time, Moves/s
                cout.fill(' ');
                cout << setw(3) << z << "\t" << setw(7) << perftMoves << "\t   " << setw(5) << fixed << setprecision(2) << sec / 1000 << "s\t";
                if (isinf(speed))
                    cout << "  -" << endl;
                else
                    cout << fixed << setw(4) << setprecision(0) << moves/sec << "K" << endl;
                cout << flush;
            }

            cout << endl;
        }

        else
        {
            cout << "Testing node search speed: " << endl << endl << flush;

            // store current AI settings to restore them after the test
            int cur_depth = board.searchDepth;
            uint64_t prevTPM = board.maxTime;


            // change the depth to make sure the test runs in a controlled environment
            board.searchDepth = NODES_TEST_DEPTH;
            board.maxTime = NODES_TEST_TIME * 1000;


            // perform the test and measure the time
            clock_t start;
            clock_t end;
            start = clock();
            board.think();
            end = clock();


            // estimate nodes per second
            double ms = (end - start) / (CLOCKS_PER_SEC / 1000);
            cout << endl << board.inodes << " nodes evaluated in " << fixed << setprecision(2) <<  (ms / 1000) << "s ";
            cout << "(" << fixed << setprecision(2) << (board.inodes / ms);
            cout << " kN/s)." << endl << flush;

            // restore the depth and time settings after the test
            board.maxTime = prevTPM;
            board.searchDepth = cur_depth;
        }


        // re-enable book and cache
        useCache = wasUsingCache;
        useBook  = wasUsingBook;
    }



    // think: change AI thinking time limit
    else if ((cmd == "think") || (cmd == "st"))
    {
        int t;

        if (arg != "")
        {
            t = atoi(arg.c_str());

            if (t < 0)
                t = 0;

            board.maxTime = t * 1000;

            // XXX
            if (XB_MODE)
            {
                XB_CTIM = t * 10;
                board.maxTime = t * 10;
            }
        }

        if (!XB_MODE)
            cout << "Max. time per move: " << (board.maxTime / 1000) << "s" << endl;
    }



    // playother: move the turn to the other player and make computer play (XBoard)
    else if (cmd == "playother")
    {
        // TODO: playother
    }



    // ping: reply to ping command (XBoard)
    else if (cmd == "ping")
    {
        cout << "pong " << arg << endl;
        cout << flush;
    }



    // post: show analysis (XBoard)
    else if (cmd == "post")
    {
        // XXX
    }



    // resign: resign for current player
    else if (cmd == "resign")
    {
        gameEnd = END_TYPE_RESIGN;
    }



    // save: save a position to a disk file
    else if (cmd == "save")
    {
        // open the disk file for loading or return on fail
        string filename = arg.c_str();
        filename += ".c0";
        ofstream fout(filename);
        if (!fout.is_open())
        {
            cout << "Error saving position to '" << filename << "'." << endl;
        }
        else
        { 
            // if the file was successfully opened, save the position
            fout << "[FEN ";
            fout << board.toFEN();
            fout << "]";
            fout.close();

            // tell the user that the saving was correct
            cout << "Current board position saved to file '" << filename;
            cout << "'." << endl;
        }
    }



    // show | display: show current board
    else if ((cmd == "show") || (cmd == "display"))
    {
        board.display();
    }



    // solve: try to find a checkmate for the given position
    else if (cmd == "solve")
    {
        board.searchDepth = SOLVE_MAX_DEPTH;
        board.maxTime = SOLVE_MAX_TIME * 1000;

        // force computer to start thinking
        if (board.nextMove)
        {
            wPlayer = PLAYER_TYPE_HUMAN;
            bPlayer = PLAYER_TYPE_COMPUTER;
            curPlayerType = bPlayer;
            playMode = HUMAN_CPU;
        }
        else
        {
            wPlayer = PLAYER_TYPE_COMPUTER;
            bPlayer = PLAYER_TYPE_HUMAN;
            curPlayerType = wPlayer;
            playMode = HUMAN_CPU;
        }
    }



    // back | undo: go back one move
    else if ((cmd == "back") || (cmd == "undo"))
    {
        if (board.endOfGame)
        {
            unmakeMove(board.gameLine[--board.endOfGame].move);
            board.endOfSearch = board.endOfGame;

            wPlayer = PLAYER_TYPE_HUMAN;
            bPlayer = PLAYER_TYPE_HUMAN;
            playMode = HUMAN_HUMAN;

            cursor--;
            numberOfMove = (cursor / 2) + 1;
        }
        else if (!XB_MODE) cout << "already at start of game" << endl;

        if (!XB_MODE) board.display();
    }



    // remove: go back two moves (XBoard --> "remove" feature)
    else if (cmd == "remove")
    {
        if (board.endOfGame)
        {
            unmakeMove(board.gameLine[--board.endOfGame].move);
            board.endOfSearch = board.endOfGame;
            cursor--;
            numberOfMove = (cursor / 2) + 1;
        }
        else if (!XB_MODE) cout << "already at start of game" << endl;

        if (board.endOfGame)
        {
            unmakeMove(board.gameLine[--board.endOfGame].move);
            board.endOfSearch = board.endOfGame;
            cursor--;
            numberOfMove = (cursor / 2) + 1;
        }
        else if (!XB_MODE) cout << "already at start of game" << endl;

        if (!XB_MODE) board.display();
    }



    // version: show application version number
    else if ((cmd == "version") || (cmd == "ver") || (cmd == "v"))
    {
        cout << PROGRAM_NAME << " (version " << PROGRAM_VERSION << ")" << endl;
        cout << PROGRAM_AUTHOR << endl;
        cout << PROGRAM_WEB << endl;
    }



    // exit | quit: terminate the app
    else if ((cmd == "quit") || (cmd == "exit") || (cmd == "q"))
    {
        terminateApp();
    }
}



// displayHelp()
//
// Display help information, either general or about a concrete command.
void displayHelp(string which)
{
    // no specific command
    if (which == "")
    {
        cout << "List of commands: (help COMMAND to get more help)" << endl;
        cout << "auto  book  cache  depth  edit  eval  flip  game" << endl;
        cout << "go  help  history  load  manual  new  null  pass" << endl;
        cout << "remove  resign  restart  save  sd  show  solve  st" << endl;
        cout << "test  think  undo  version  quit" << endl;
        return;
    }


    // help auto
    else if (which == "auto")
    {
        cout << "auto" << endl;
        cout << " Let the computer play both sides (black and white). This can";
        cout << endl;
        cout << " be the equivalent to 'solve' in other computer chess";
        cout << endl;
        cout << " programs, because the computer plays both sides and finishes";
        cout << endl;
        cout << " the match by itself." << endl;
    }


    // help book
    else if (which == "book")
    {
        cout << "book [on | general | personal | off]" << endl;
        cout << " Enable or disable the moves from the book for the computer.";
        cout << endl << endl;
        cout << " on | general -> use general (wide) opening book" << endl;
        cout << " personal     -> use selected (narrow) opening book" << endl;
        cout << " off          -> disable book moves and force search" << endl;
        cout << endl;
    }


    // help cache
    else if (which == "cache")
    {
        cout << "cache [on | off]" << endl;
        cout << " Let the computer use the transposition tables to find" << endl;
        cout << " previously searched positions faster. This typically" << endl;
        cout << " makes the engine more powerful in middle and end-game." << endl;
        cout << " Please note that using transposition tables can take" << endl;
        cout << " a few hundreds of Megabytes for a ~1h game." << endl;
    }



    // help depth | sd
    else if ((which == "depth") || (which == "sd"))
    {
        cout << "depth | sd [N]" << endl;
        cout << " Set the search depth of the computer to N-plies" << endl;
        cout << " (half-moves). The depth must be a minimum of 1," << endl;
        cout << " and there is no maximum limit. However, consider" << endl;
        cout << " that a depth higher than 7 will result in a very" << endl;
        cout << " long time for obtaining a move from the computer." << endl;
        cout << " If no depth is given, then the application tells" << endl;
        cout << " what is the current search depth." << endl;
    }


    // help flip
    else if (which == "flip")
    {
        cout << "flip" << endl;
        cout << " Flip the board so that when it is displayed, white" << endl;
        cout << " and black sides are flipped." << endl;

    }


    // help show
    else if (which == "show")
    {
        cout << "show" << endl;
        cout << " Display an ASCII representation of the current game's";
        cout << endl;
        cout << " board. The white pieces are represented with capital";
        cout << endl;
        cout << " letters, whereas the black pieces are represented";
        cout << endl;
        cout << " with small letters next to an asterisk." << endl;
    }


    // help edit
    else if (which == "edit")
    {
        cout << "edit" << endl;
        cout << " Enter in position editing mode." << endl << endl;
        cout << " The program will first wipe all the pieces from the";
        cout << endl;
        cout << " board and ask you for entering the white pieces. These";
        cout << endl;
        cout << " pieces are entered one by one (separeted by pressing Enter)";
        cout << endl;
        cout << " and according to the format PIECE+COLUMN+ROW (e.g. Ke2).";
        cout << endl;
        cout << " When the white pieces are done, then enter '.' (dot) and";
        cout << endl;
        cout << " press Enter, so the black pieces are asked to be entered.";
        cout << endl;
        cout << " When the black pieces are entered, then enter '#' (hash)";
        cout << endl;
        cout << " and press Enter to exit from the position editing mode.";
        cout << endl << endl;
        cout << " Please note that, if the position is invalid (such as two";
        cout << endl;
        cout << " kings, or double check), the program will complain and the";
        cout << endl;
        cout << " previous original board will be restored.";
        cout << endl;
    }


    // help eval
    else if (which == "eval")
    {
        cout << "eval" << endl;
        cout << " Give an absolut heuristic evaluation of the current board.";
        cout << endl;
        cout << " Please note that this command will make use of the current";
        cout << endl;
        cout << " AI engine in use. Thus, depending on the engine, the";
        cout << endl;
        cout << " heuristic evaluation may differ quite much." << endl;
    }


    // help go
    else if (which == "go")
    {
        cout << "go" << endl;
        cout << " Tell the machine to take the control on the current" << endl;
        cout << " turn and play for the player whose turn is the" << endl;
        cout << " the current one. After this command, the machine will";
        cout << endl;
        cout << " always control the side whose control has been taken.";
        cout  << endl;
    }


    // help help
    else if (which == "help")
    {
        cout << "help" << endl;
        cout << " Show the general help." << endl;
    }


    // help history
    else if (which == "history")
    {
        cout << "history" << endl;
        cout << " Display the history (sequence of moves) of the current";
        cout << endl;
        cout << " game." << endl;
    }


    // help load
    else if (which == "load")
    {
        cout << "load FILENAME" << endl;
        cout << " Load a board position from a file. Please note that";
        cout << endl;
        cout << " this command loads a position, not a match (do not confuse";
        cout << endl;
        cout << " with the PGN format). If the file is not valid, or the";
        cout << endl;
        cout << " position in it is not valid, the program will not load it";
        cout << endl;
        cout << " and return to the previously working board position.";
        cout << endl;
        cout << endl;
        cout << " As a note, these board positions (files) are usually saved";
        cout << endl;
        cout << " with the command 'save', although you could manually create";
        cout << endl;
        cout << " and edit your own board position file." << endl;
    }


    // help manual
    else if (which == "manual")
    {
        cout << "manual" << endl;
        cout << " Set both players to be played by human input." << endl;
    }


    // help new/restart
    else if ((which == "new") || (which == "restart"))
    {
        cout << "new | restart" << endl;
        cout << " Start a new game." << endl;
    }



    // help null/pass
    else if ((which == "null") || (which == "pass"))
    {
        cout << "null | pass" << endl;
        cout << " Make a null move, which passes the turn to the other side";
        cout << " without performing any actual move." << endl;
    }


    // help resign
    else if (which == "resign")
    {
        cout << "resign" << endl;
        cout << " Resign and let your opponent win immediately. The game";
        cout << endl;
        cout << " is then finished at this point." << endl;
    }


    // help save
    else if (which == "save")
    {
        cout << "save FILENAME" << endl;
        cout << " Save a board position to a file. Please note that";
        cout << endl;
        cout << " this command saves a position using FEN notation, not an";
        cout << endl;
        cout << " entire match (do not confuse with the PGN format).";
        cout << endl;
        cout << endl;
        cout << " As a note, these board positions (files) are usually loaded";
        cout << endl;
        cout << " with the command 'load', although you could manually create";
        cout << endl;
        cout << " and edit your own board position using the 'edit' command.";
        cout << endl;
    }


    // help solve
    else if (which == "solve")
    {
        cout << "solve [depth]" << endl;
        cout << " Start thinking how to solve the current board. This mode";
        cout << endl;
        cout << " puts the computer to play both sides and makes it try to";
        cout << endl;
        cout << " solve the current situation on the board up to some depth.";
        cout << endl;
        cout << " If no depth is given, the computer will search the solution";
        cout << endl;
        cout << " forever (unless it finds it). Otherwise, it will try to";
        cout << endl;
        cout << " solve the problem and it will give up when it reaches the";
        cout << endl;
        cout << " given depth." << endl;
    }



    // help test
    else if (which == "test")
    {
        cout << "test [moves | nodes | perft]" << endl;
        cout << " Test either the number of moves that can be done and undone";
        cout << endl;
        cout << " per second (without calling evaluation), the number of nodes";
        cout << endl;
        cout << " that can be evaluated per second, and perform a Perft()";
        cout << endl;
        cout << " test which is a standard moves test for computer chess";
        cout << endl;
        cout << " programs to test that the move generator works correctly.";
        cout << endl;
        cout << " If no argument is given, all three tests are performed.";
        cout << endl;
        cout << " Please note that the efficiency of the tests will depend";
        cout << endl;
        cout << " on the situation on the board." << endl;
    }



    // help st | think (time per move)
    else if ((which == "think") || (which == "st"))
    {
        cout << "st | think [N]" << endl;
        cout << " Set the maximum amount of time the engine can think" << endl;
        cout << " before performing a move. The time must be a minimum of" << endl;
        cout << " 1 (seconds) and there is no maximum limit. Setting the" << endl;
        cout << " thinking time to 0 allows the engine to think indefinitely " << endl;
        cout << " (or until it hits the depth limit, if there is any)." << endl;
        cout << " Using this command disables the game clock (time)." << endl;
    }



    // help undo
    else if ((which == "undo") || (which == "back"))
    {
        cout << "undo | back" << endl;
        cout << " Take back a move from the game." << endl;
    }



    // help version
    else if (which == "version")
    {
        cout << "version" << endl;
        cout << " Show the application version number, author and website.";
        cout << endl;
    }



    // help quit
    else if (which == "quit")
    {
        cout << "quit | exit" << endl;
        cout << " Quit the application." << endl;
    }

    // help unknown
    else
    {
        cout << which << endl;
        cout << " No help available for '" << which << "'" << endl;
    }
}



// displayEval()
//
// Display the current heuristic evaluation according to the board.
void displayEval()
{
    float evaluationValue = 0;
    if (board.nextMove)
        evaluationValue = -board.eval() / 100.00f;
    else
        evaluationValue = board.eval() / 100.00f;

    cout << "Evaluation: " << showpos << setw(4) << fixed << setprecision(2) << evaluationValue << endl << "(m: " << (board.Material / 100.00f) << ")" << endl;
    cout << noshowpos;
}
