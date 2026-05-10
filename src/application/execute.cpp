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
 * @file src/application/execute.cpp
 */
#include <iostream>
#include <fstream>
#include <iomanip>
#include <climits>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "utils"
#include "application/manager"
#include "application/prompt"
#include "application/xboard"
#include "ai/adaptive"


/*!
 * Execute a given action and update every necessary component in the
 * application.
 *
 * @param c Command to be executed.
 *
 * @return true if the action was performed successfully, false otherwise.
 */
ActionType ApplicationManager::execute(Command c)
{
    CmdType ct = c.getType();

    // enter analysis mode
    if (ct == CMD_TYPE_ANALYZE)
    {
        // use max depth and max think time
        ai->setDepth(+INT_MAX);
        ai->setTPM(+UINT_MAX);

        // set computer to play both sides
        // NOTE: user needs to press Ctrl+C to make the computer move
        gman->setWhite(PLAYER_TYPE_COMPUTER);
        gman->setBlack(PLAYER_TYPE_COMPUTER);

        return ACTION_TYPE_NONE;
    }

    // show/set cache size limit
    else if (ct == CMD_TYPE_CACHE)
    {
        // turn cache on
        if ((c.getArgument() == "on") || (c.getArgument() == "true"))
            ai->enableCache();

        // turn cache off
        else if ((c.getArgument() == "off") || (c.getArgument() == "false"))
            ai->disableCache();

        // show current cache status
        if (ai->isCacheEnabled())
        {
            char measure = '\0';
            float size = 0;

            cout << "Cache is enabled." << endl;

            // check the current cache size (usage)
            size = ai->getCacheSize();
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
            cout << ai->getCachePositions() << " positions)" << endl;
        }
        else
        {
            cout << "Cache is disabled." << endl;
        }

        return ACTION_TYPE_PROMPT;
    }
    // make the machine play both sides
    else if (ct == CMD_TYPE_AUTO)
    {
        gman->setWhite(PLAYER_TYPE_COMPUTER);
        gman->setBlack(PLAYER_TYPE_COMPUTER);
        cout << "Both players are now controlled by the computer." << endl;

        return ACTION_TYPE_NONE;
    }

    // turn on or off openings book
    else if (ct == CMD_TYPE_BOOK)
    {
        // turn default book on
        if (c.getArgument() == "on")
            useBook(true);

        // turn book off
        else if (c.getArgument() == "off")
            useBook(false);

        // show current use of book
        if (usingBook())
            cout << "Opening book is enabled." << endl;
        else
            cout << "Opening book is disabled." << endl;

        return ACTION_TYPE_PROMPT;
    }

    // change AI depth
    else if (ct == CMD_TYPE_DEPTH)
    {
        int d;
        d = atoi(c.getArgument().c_str());
        ai->setDepth(d);
        cout << "Search depth: " << ai->getDepth() << endl;

        return ACTION_TYPE_PROMPT;
    }

    // display current board's evaluation
    else if (ct == CMD_TYPE_DISPLAY_EVAL)
    {
        displayEval();

        return ACTION_TYPE_PROMPT;
    }

    // load position from a file
    else if (ct == CMD_TYPE_LOAD)
    {
        // before opening the file, perform some robustness checks
        if (!testBoardFile(c.getArgument().c_str()))
        {
            cout << "Error loading position from '" << c.getArgument() << "'" << endl;
            cout << "File is corrupted!" << endl;

            return ACTION_TYPE_PROMPT;
        }

        // open the disk file for loading or return on fail
        ifstream *fin = new ifstream(c.getArgument().c_str());
        if (!fin->is_open())
        {
            cout << "Error loading position from '" << c.getArgument() << "'.";
            cout << endl;
            return ACTION_TYPE_PROMPT;
        }

        // if the file was successfully opened, load the position
        string turn;
        Board *eboard = new Board();
        eboard->load(fin);
        if (eboard->checkIntegrity())
        {
            //delete board;
            gman->restart();
            board = eboard;
            ai->setBoard(board);
            ai->clearCache();
            gman->getGame()->setBoard(board);

            // both players are set to manual
            gman->setWhite(PLAYER_TYPE_HUMAN);
            gman->setBlack(PLAYER_TYPE_HUMAN);

            // reset clocks
            setComputerTime(0);
            setElapsedTime(0);
            ai->setTPM(TIME_PER_MOVE);

            // ask who is set to move
            (*fin) >> turn;
            fin->ignore(1, '\n');
            if (turn == "black")
            {
                Move m;
                gman->getGame()->setPlayer(COLOR_TYPE_BLACK);
                m.setColor(gman->getPlayer());
                m.setType(MOVE_TYPE_NULL);
                gman->getGame()->addToHistory(m);
                gman->getGame()->setCursor(1);
                gman->getGame()->setMinCursor(1);
            }
            else
            {
                gman->getGame()->setCursor(0);
                gman->getGame()->setMinCursor(0);
            }

            // tell the user that the loading was correct
            cout << "Board position loaded from file '" << c.getArgument();
            cout << "'." << endl;

            // disable moves from book
            useBook(false);
        }
        else
        {
            cout << "Invalid position for the loaded board!" << endl;
        }

        fin->close();

        return ACTION_TYPE_PROMPT;
    }
    // set log option (file or off)
    else if (ct == CMD_TYPE_LOG)
    {
        if (c.getArgument() == "")
        {
            if (board->isLogEnabled())
            {
                cout << "Log is enabled. Logging to file '";
                cout << board->getLogFile() << "'." << endl;
            }
            else
            {
                cout << "Log is disabled." << endl;
            }
        }
        else if (c.getArgument() == "off")
        {
            board->enableLog(false);
            cout << "Log is disabled." << endl;
        }
        else
        {
            board->enableLog(true); 
            board->setLogFile(c.getArgument());
            cout << "Log is enabled. Logging to file '";
            cout << board->getLogFile() << "'." << endl;
        }

        return ACTION_TYPE_PROMPT;
    }

    // material: display material
    else if (ct == CMD_TYPE_DISPLAY_MATERIAL)
    {
        displayMaterial();

        return ACTION_TYPE_PROMPT;
    }

    // draw: offer draw to the other player
    else if (ct == CMD_TYPE_DRAW)
    {
        string opt;
        ColorType cur = oppose(gman->getPlayer());
        PlayerType cur_type = PLAYER_TYPE_OTHER;
        
        if (cur == COLOR_TYPE_WHITE)
            cur_type = gman->getWhite();
        else
            cur_type = gman->getBlack();

        if (cur_type == PLAYER_TYPE_HUMAN)
        {
            cout << "Your opponent offers you draw. Take it? ";
            cin >> opt;
            if ((opt == "yes") || (opt == "Yes") || (opt == "y") ||
                (opt == "y") || (opt == "Y") || (opt == "YES"))
            {
                gman->setEnd(END_TYPE_DRAW_AGREE);
                dealEnd();
            }
            else
            {
                cout << "Your opponent did not accept the draw. Continuing..";
                cout << endl;
                cin.ignore(1, '\n');
            }
        }
        else if (cur_type == PLAYER_TYPE_COMPUTER)
        {
            if (ai->acceptDraw())
            {
                gman->setEnd(END_TYPE_DRAW_AGREE);
                dealEnd();
            }
            else
            {
                cout << "Your opponent did not accept the draw. Continuing..";
                cout << endl;
            }
        }

        return ACTION_TYPE_PROMPT;
    }
    // edit a board for setting a position
    else if (ct == CMD_TYPE_EDIT)
    {
        string turn;
        Board *eboard = new Board();
        eboard->edit();
        if (eboard->checkIntegrity())
        {
            //delete board;
            gman->restart();
            board = eboard;
            ai->setBoard(board);
            ai->clearCache();
            gman->getGame()->setBoard(board);

            // reset clocks
            setComputerTime(0);
            setElapsedTime(0);
            ai->setTPM(TIME_PER_MOVE);

            // both players are set to manual
            gman->setWhite(PLAYER_TYPE_HUMAN);
            gman->setBlack(PLAYER_TYPE_HUMAN);

            // ask who is set to move
            cout << "Whose turn [white|black]? ";
            cin >> turn;
            cin.ignore(1, '\n');
            if (turn == "black")
            {
                Move m;
                m.setColor(gman->getPlayer());
                m.setType(MOVE_TYPE_NULL);
                gman->getGame()->addToHistory(m);
                gman->getGame()->setPlayer(COLOR_TYPE_BLACK);
                gman->getGame()->setCursor(1);
                gman->getGame()->setMinCursor(1);
            }

            // disable moves from book
            useBook(false);
        }
        else
        {
            cout << "Invalid position for the edited board!" << endl;
        }

        return ACTION_TYPE_PROMPT;
    }
    // flip the board when displaying
    else if (ct == CMD_TYPE_FLIP)
    {
        Game *g = gman->getGame();
        if (g && g->getBoard())
        {
            g->getBoard()->flip();
            gman->displayBoard();
        }

        return ACTION_TYPE_PROMPT;
    }
    // force the machine to move now
    else if (ct == CMD_TYPE_GO)
    {
        if (gman->getPlayer() == COLOR_TYPE_WHITE)
        {
            gman->setWhite(PLAYER_TYPE_COMPUTER);
            gman->setBlack(PLAYER_TYPE_HUMAN);
            cout << "Computer playing as white." << endl;
        }
        else
        {
            gman->setBlack(PLAYER_TYPE_COMPUTER);
            gman->setWhite(PLAYER_TYPE_HUMAN);
            cout << "Computer playing as black." << endl;
        }

        return ACTION_TYPE_CONTINUE;
    }

    // print help
    else if (ct == CMD_TYPE_HELP)
    {
        displayHelp(c.getArgument());
        return ACTION_TYPE_PROMPT;
    }

    // display game history
    else if (ct == CMD_TYPE_HISTORY)
    {
        gman->displayHistory();
        return ACTION_TYPE_PROMPT;
    }

    // info: display useful information about the game
    else if (ct == CMD_TYPE_INFO)
    {
        // display game phase
        cout << "Game phase: ";
        switch (board->getPhase())
        {
            case PHASE_TYPE_OPENING: cout << "opening.";
                                     break;
            case PHASE_TYPE_MIDDLE:  cout << "middle game.";
                                     break;
            case PHASE_TYPE_END:     cout << "end game.";
                                     break;
            default:                 cout << "unknown.";
        }
        cout << endl;

        // display side to play
        cout << "Side to move: ";
        switch (gman->getPlayer())
        {
            case COLOR_TYPE_WHITE: cout << "white.";
                                   break;
            case COLOR_TYPE_BLACK: cout << "black.";
                                   break;
            default:               cout << "unknown.";
        }
        cout << endl;

        // display last move
        if ((gman->getGame()->getHistory()).size() > 0)
        {
            Move lastMove = (gman->getGame()->getHistory()).back();
            cout << "Last move: " << lastMove.getHuman() << endl;
        }

        // display evaluation
        displayEval();

        // display material
        displayMaterial();

        return ACTION_TYPE_PROMPT;
    }

    // human vs human
    else if (ct == CMD_TYPE_MANUAL)
    {
        gman->setWhite(PLAYER_TYPE_HUMAN);
        gman->setBlack(PLAYER_TYPE_HUMAN);
        cout << "Both players are now controlled by human input." << endl;

        return ACTION_TYPE_PROMPT;
    }

    // new game / restart
    else if (ct == CMD_TYPE_NEW)
    {
        cout << "Starting a new game..." << endl;
        
        // now restart the game
        gman->restart();
        ai->clearCache();

        // reset clocks
        setComputerTime(0);
        setElapsedTime(0);
        ai->setTPM(TIME_PER_MOVE);

        // enable book by default
        useBook(true);
    }

    // don't show analysis (XBoard)
    else if (ct == CMD_TYPE_NOPOST)
    {
        ai->setPost(false);
    }

    // Xboard mode
    else if (ct == CMD_TYPE_XBOARD)
    {
        // launch XBoard
        setXBoard(true);
        XBoard app(gman);
        app.launch();
    }

    // make a test
    else if (ct == CMD_TYPE_TEST)
    {
        string test  = c.getArgument();
        bool v = ai->getVerbose();

        // disable benchmark biases
        ai->setVerbose(false);

        // decide which test to perform
        if (test == "nodes")
        {
            testNodesPerSecond();
        }
        else if (test == "moves")
        {
            testMovesPerSecond();
        }
        else if (test == "perft")
        {
            testPerft();
        }
        else if (test == "")
        {
            testNodesPerSecond();
            testMovesPerSecond();
            testPerft();
        }
        else
        {
            cerr << "Unknown test '" << test << "'" << endl;
        }

        ai->setVerbose(v);

        return ACTION_TYPE_PROMPT;
    }

    // set game time
    else if (ct == CMD_TYPE_TIME)
    {
        unsigned int t = atoi(c.getArgument().c_str());
        if (t > 0)
        {
            // limit time(minutes) to 480 (8 hours)
            if (t > 480)
                t = 480;

            // set computer's total time in seconds (x60)
            setComputerTime(t * 60);

            // elapsed time starts at 0, obviously
            setElapsedTime(0);

            // calculate amount of time per move
            // --> formula: tpm = (total_time - // elapsed time) / (100 - number_of_moves)
            unsigned short current_moves = gman->getGame()->getCursor();
            if (!current_moves)
                current_moves = 0;
            ai->setTPM(calculateTPM(getComputerTime(), getElapsedTime(), current_moves));
        }

        if (getComputerTime() > 0)
            cout << "Computer time for the game: " << getComputerTime() / 60 << " minutes." << endl;
        else 
            cout << "Computer time for the game: unlimited." << endl;

        return ACTION_TYPE_PROMPT;
    }

    // change AI thinking time limit
    else if (ct == CMD_TYPE_TPM)
    {
        int t;
        t = atoi(c.getArgument().c_str());

        // if a new think time was given as a parameter, change TPM and disable
        // computerTime
        if (t > 0)
        {
            ai->setTPM(t);

            // TPM disables computer's game time
            setComputerTime(0);
            setElapsedTime(0);
        }

        cout << "Max. time per move: " << ai->getTPM() << "s" << endl;

        return ACTION_TYPE_PROMPT;
    }

    // perform a null move (change the turn to the other player without making a
    // move)
    else if (ct == CMD_TYPE_PASS)
    {
        // if king under check, cannot perform null move
        if (gman->getGame()->getBoard()->isCheck())
        {
            cout << "Cannot pass because there is a king under check!" << endl;
        }
        else
        {
            Move m;
            m.setColor(gman->getPlayer());
            m.setType(MOVE_TYPE_NULL);
            gman->perform(m);
        }

        return ACTION_TYPE_PROMPT;
    }

    // move the turn to the other player and make computer play (XBoard)
    else if (ct == CMD_TYPE_PLAYOTHER)
    {
        Move m;
        m.setColor(gman->getPlayer());
        m.setType(MOVE_TYPE_NULL);
        gman->perform(m);

        if (gman->getPlayer() == COLOR_TYPE_WHITE)
        {
            gman->setWhite(PLAYER_TYPE_COMPUTER);
            gman->setBlack(PLAYER_TYPE_HUMAN);
            cout << "Computer playing as white." << endl;
        }
        else
        {
            gman->setBlack(PLAYER_TYPE_COMPUTER);
            gman->setWhite(PLAYER_TYPE_HUMAN);
            cout << "Computer playing as black." << endl;
        }

        return ACTION_TYPE_CONTINUE;
    }

    // reply to ping command (XBoard)
    else if (ct == CMD_TYPE_PING)
    {
        cout << "pong " << c.getArgument() << endl;
        return ACTION_TYPE_NONE;
    }

    // show analysis (XBoard)
    else if (ct == CMD_TYPE_POST)
    {
        ai->setPost(true);
    }

    // resign for current player
    else if (ct == CMD_TYPE_RESIGN)
    {
        gman->resign();
        return ACTION_TYPE_RESIGN;
    }

    // save a position to a disk file
    else if (ct == CMD_TYPE_SAVE)
    {
        // open the disk file for loading or return on fail
        string filename = c.getArgument().c_str();
        filename += ".c0b";
        ofstream fout(filename);
        if (!fout.is_open())
        {
            cout << "Error saving position to '" << filename << "'.";
            cout << endl;
            return ACTION_TYPE_PROMPT;
        }

        // if the file was successfully opened, save the position
        fout << board->toEdited();
        fout << "#" << endl;

        // write whose turn it is
        if (gman->getPlayer() == COLOR_TYPE_WHITE)
            fout << "white";
        else
            fout << "black";

        fout.close();

        // tell the user that the saving was correct
        cout << "Current board position saved to file '" << filename;
        cout << "'." << endl;

        return ACTION_TYPE_PROMPT;
    }
    // show board
    else if (ct == CMD_TYPE_SHOW)
    {
        gman->displayBoard();

        return ACTION_TYPE_PROMPT;
    }
    // solve
    else if (ct == CMD_TYPE_SOLVE)
    {
        // check the depth from the argument
        int depth = atoi(c.getArgument().c_str());

        // solve the problem for the moving side
        ai->setColor(gman->getPlayer());
        ai->solve(depth);

        // in solve mode, finish the game
        gman->setEnd(END_TYPE_SOLVE);
        dealEnd();

        return ACTION_TYPE_PROMPT;
    }

    // go back one move
    else if (ct == CMD_TYPE_UNDO)
    {
        // if we want to go back, set game in manual mod
        // * otherwise, cache will make the machine play immediately and we
        //   cannot go back
        gman->setWhite(PLAYER_TYPE_HUMAN);
        gman->setBlack(PLAYER_TYPE_HUMAN);
        gman->takeBack();

        // show the board with the changes
        gman->displayBoard();

        return ACTION_TYPE_PROMPT;
    }

    // go back two moves (XBoard --> "remove" feature)
    else if (ct == CMD_TYPE_REMOVE)
    {
        gman->takeBack();
        gman->takeBack();

        // show the board with the changes
        gman->displayBoard();

        return ACTION_TYPE_PROMPT;
    }

    // set application verbose mode
    else if (ct == CMD_TYPE_VERBOSE)
    {
        if ((c.getArgument() == "on") || (c.getArgument() == "true"))
            verbose = true;
        else if ((c.getArgument() == "off") || (c.getArgument() == "false"))
            verbose = false;

        if (verbose)
            cout << "Verbose mode is enabled." << endl;
        else
            cout << "Verbose mode is disabled." << endl;

        return ACTION_TYPE_PROMPT;
    }

    // set application quiet mode (verbose off)
    else if (ct == CMD_TYPE_QUIET)
    {
        verbose = false;
        cout << "Verbose mode is disabled." << endl;

        return ACTION_TYPE_PROMPT;
    }

    // show application version number
    else if (ct == CMD_TYPE_VERSION)
    {
        cout << PROGRAM_NAME << " (version " << PROGRAM_VERSION << ")" << endl;
        cout << PROGRAM_AUTHOR << endl;
        cout << PROGRAM_WEB << endl;

        return ACTION_TYPE_PROMPT;
    }

    // exit / quit
    else if (ct == CMD_TYPE_QUIT)
    {
        return ACTION_TYPE_EXIT;
    }

    // by default, don't do anything
    return ACTION_TYPE_NONE;
}
