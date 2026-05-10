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
 * @file src/application/xboard.cpp
 */
#include <algorithm>
#include <iostream>
#include <string>
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include "utils"
#include "game/game"
#include "application/manager"
#include "application/prompt"
#include "application/book"
#include "ai/adaptive"
#include "application/xboard"



/*!
 * Default constructor
 *
 * @param gm Pointer to a GameManager to set the association.
 */
XBoard::XBoard(GameManager *gm)
{
    gman = gm;
    verbose = false;
    xboard  = true;
    using_book = true;
    book = new Book();
}


/*!
 * Launch the XBoard and start managing the program.
 *
 * Typically, this function is called from the main() function, so that all the
 * work is delegated to this method.
 *
 * @return an integer with the error code that the application should return.
 */
int XBoard::launch()
{
    // temporary variables
    InputType   itype;
    MoveType    mtype;
    ActionType  action = ACTION_TYPE_OTHER;
    Command     cmd;
    Move        move;
    string      input;
    PlayerType  cur_player;
    string      MoveIsFromBook = "";

    // time measurements
    clock_t start = 0;
    clock_t end   = 0;
    computerTime  = 0;
    elapsedTime   = 0;

    // necessary components
    board = gman->getGame()->getBoard();
    ai = new Adaptive(board, COLOR_TYPE_BLACK, gman->getMoveParser(),
                      gman->getGame());

    // tell the AI engine to not to spit out any information
    ai->setXBoard(true);
    ai->setVerbose(true);

    // initialize and configure XBoard
    cout << "feature san=1" << endl;
    cout << "feature time=0" << endl;
    cout << "feature sigint=0" << endl;
    cout << "feature sigterm=0" << endl;
    cout << "feature reuse=0" << endl;
    cout << "feature myname=\"Chess0\"" << endl;
    cout << "feature colors=0" << endl;
    cout << "feature done=1" << endl;

    // main loop
    while (1)
    {
        // send data to xboard and reset input buffers
        cout.flush();
        input = "";

        // check if it is the end of the match
        if (gman->isEnd())
            dealEnd();

        // check which type of player is currently trying to move
        if (gman->getPlayer() == COLOR_TYPE_WHITE)
            cur_player = gman->getWhite();
        else
            cur_player = gman->getBlack();

        // read input
        if (cur_player == PLAYER_TYPE_HUMAN)
        {
            input = getInput();
        }
        else if (cur_player == PLAYER_TYPE_COMPUTER)
        {
            ai->setColor(gman->getPlayer());

            // measure how long it takes to think the move
            int timeUsed = (end - start) / CLOCKS_PER_SEC;

            // if book enabled
            if (using_book)
            {
                MoveIsFromBook = "";

                // try to get a move from the opening book
                // Note: the sequence is assumed to be consistent with the game
                string BookSequence = gman->getGame()->getHistorySequence();
                if (BookSequence == "")
                    BookSequence = "%";
                input = book->getReplyTo(BookSequence);
            }

            // if no move from the book, enter search mode
            if (input.empty())
            {
                start = clock();
                input = ai->getMove().getHuman();
                end   = clock();
            }

            // update clock if needed, and show the reamining game time
            if (computerTime > 0)
            {
                elapsedTime += timeUsed;
                ai->setTPM(calculateTPM(computerTime, elapsedTime, gman->getGame()->getCursor() / 2));
            }
        }

        // check which action to do
        for (unsigned int i = 0; i < input.size(); i++)
            if (input[i] == '+')
                input.erase(input.begin() + i);

        // support for XBoard castling (e1g1, e8g8, e1c1 and e8c8)
        if ((input == "e1g1") || (input == "e8g8"))
            input = "0-0";
        else if ((input == "e1c1") || (input == "e8c8"))
            input = "0-0-0";

        // check the input (validity, legality, etc)
        itype = getInputType(input, &mtype);

        // if a command was entered, then execute it
        // * from this on, the Application Manager is the last responsible.
        if (itype == INPUT_TYPE_CMD)
        {
            cmd = toCmd(input);

            // if the command is not known, report an error
            if (cmd.getType() == CMD_TYPE_UNKNOWN)
            {
                cout << "Error (unknown command): " << input << endl;
                cout.flush();
            }
            // otherwise, execute the given command
            else
                action = execute(cmd);

            // check for actions up on command execution
            if (action == ACTION_TYPE_PROMPT)
                continue;
            else if (action == ACTION_TYPE_CONTINUE)
                continue;
            else if (action == ACTION_TYPE_EXIT)
                break;
        }

        // if a movemement was entered, then perform it on the game
        // * If no game is running, the Game Manager is the last responsible of
        //   taking care of the situation.
        else if (itype == INPUT_TYPE_MOVE)
        {
            move = gman->toMove(input, mtype);
            Error status = ERROR_NONE;

            // error, if there is no game so there is no move
            if (move.getType() == MOVE_TYPE_NOGAME)
            {
                cout << "Error (no game): " << input << endl;
                cout.flush();
            }
            // error, if the move is ambiguous
            else if (move.isAmbiguous())
            {
                cout << "Illegal move (ambiguous): " << move.getHuman();
                cout << endl;
                cout.flush();
            }
            // error, if the move is not valid
            else if (!move.isValid())
            {
                cout << "Illegal move (invalid): " << input << endl;
                cout.flush();
            }
            // otherwise, perform the move on the game
            else
            {
                status = gman->perform(move);

                // send move to xboard
                if (cur_player == PLAYER_TYPE_COMPUTER)
                {
                    cout << "move " << move.getHuman() << endl;
                    cout.flush();
                }

                // check if end
                if (status == ERROR_NONE_END)
                    dealEnd();
            }
        }

        // wrong format or invalid actual move on the board
        else if (itype == INPUT_TYPE_INVALID_MOVE)
        {
            cout << "Illegal (invalid): " << input << endl;
            cout.flush();
            continue;
        }

        // if no command or movement was entered, print an error 
        // * an input can only be a movement or a command.
        else
        {
            cout << "Illegal move (Wrong move or command): ";
            cout << input << endl;
            cout.flush();
            continue;
        }
    }

    return 0;
}


/*!
 * Execute a given action and update every necessary component in the
 * application.
 *
 * @param c Command to be executed.
 *
 * @return true if the action was performed successfully, false otherwise.
 */
ActionType XBoard::execute(Command c)
{
    CmdType ct = c.getType();

    // change AI depth
    if (ct == CMD_TYPE_DEPTH)
    {
        int d;
        d = atoi(c.getArgument().c_str());
        ai->setDepth(d);

        return ACTION_TYPE_PROMPT;
    }
    // offer draw to the other player
    else if (ct == CMD_TYPE_DRAW)
    {
        string opt;
       
        // ask the computer for draw 
        if (ai->acceptDraw())
        {
            gman->setEnd(END_TYPE_DRAW_AGREE);
            dealEnd();
        }
        else
        {
            // TODO: what to send to xboard when no draw accepted ???
            cout << endl;
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
        }
        else
        {
            gman->setBlack(PLAYER_TYPE_COMPUTER);
            gman->setWhite(PLAYER_TYPE_HUMAN);
        }

        return ACTION_TYPE_CONTINUE;
    }
    // start a new game
    else if (ct == CMD_TYPE_NEW)
    {
        gman->restart();
    }
    // resign for current player
    else if (ct == CMD_TYPE_RESIGN)
    {
        gman->resign();
        dealEnd();
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
    }
    // exit
    else if (ct == CMD_TYPE_QUIT)
    {
        return ACTION_TYPE_EXIT;
    }

    return ACTION_TYPE_NONE;
}
