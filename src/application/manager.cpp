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
 * @file src/application/manager.cpp
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



/*!
 * Minimal constructor
 */
ApplicationManager::ApplicationManager()
{
    ApplicationManager(0);
}


/*!
 * Default constructor
 *
 * @param gm Pointer to a GameManager to set the association.
 */
ApplicationManager::ApplicationManager(GameManager *gm)
{
    gman = gm;
    verbose = true;
    xboard  = false;
    using_book = true;
    book = new Book();
}


/*!
 * Launch the ApplicationManager and start managing the program.
 *
 * Typically, this function is called from the main() function, so that all the
 * work is delegated to this method.
 *
 * @return an integer with the error code that the application should return.
 */
int ApplicationManager::launch()
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
    ai = new Adaptive(board, COLOR_TYPE_BLACK,
                      gman->getMoveParser(), gman->getGame());

    // welcome the user
    prompt.init();

    // main loop
    while (1)
    {
        // send data to xboard and reset input buffers
        cout.flush();
        input = "";

        // set verbosity of each component
        if (verbose)
            ai->setVerbose(true);
        else
            ai->setVerbose(false);

        // check if it is the end of the match
        if (gman->isEnd())
            dealEnd();

        // check which type of player is currently trying to move
        if (gman->getPlayer() == COLOR_TYPE_WHITE)
            cur_player = gman->getWhite();
        else
            cur_player = gman->getBlack();

        // read user input
        if (cur_player == PLAYER_TYPE_HUMAN)
        {
            input = getInput();
        }
        else if (cur_player == PLAYER_TYPE_COMPUTER)
        {
            ai->setColor(gman->getPlayer());
            MoveIsFromBook = "";


            // if book enabled
            if (using_book)
            {
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
                cout << endl << "Thinking..." << endl;
                input = ai->getMove().getHuman();
                end   = clock();
            }
            // if the move was form the book, show it with a (%) symbol
            else if (using_book)
            {
                MoveIsFromBook = " [book] ";
            }
        }

        // check which action to do
        for (unsigned int i = 0; i < input.size(); i++)
            if (input[i] == '+')
                input.erase(input.begin() + i);
        itype = getInputType(input, &mtype);


        // if a command was entered, then execute it
        // * from this on, the Application Manager is the last responsible.
        if (itype == INPUT_TYPE_CMD)
        {
            cmd = toCmd(input);

            // if the command is not known, report error
            if (cmd.getType() == CMD_TYPE_UNKNOWN)
                cerr << "Unknown command (" << input << ")" << endl;
            // otherwise, execute the given command
            else
                action = execute(cmd);

            // check for actions up on command execution
            if (action == ACTION_TYPE_PROMPT)
            {
                prompt.turn(gman->getPlayer(), gman->getTurn());
                continue;
            }
            else if (action == ACTION_TYPE_CONTINUE)
            {
                continue;
            }
            else if (action == ACTION_TYPE_EXIT)
            {
                prompt.terminate();
                break;
            }
            else if (action == ACTION_TYPE_RESIGN)
            {
                dealEnd();
            }
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
                cerr << "There are no games running!" << endl;
            // error, if the move is ambiguous
            else if (move.isAmbiguous())
                cerr << "Ambiguous move!" << endl;
            // error, if the move is not valid
            else if (!move.isValid())
                cerr << "Illegal move (" << input << ")" << endl;
            // otherwise, perform the move on the game
            else
            {
                gman->getMoveParser()->pretty(&move);
                status = gman->perform(move);
            }

            // check if end
            if (status == ERROR_NONE_END)
                dealEnd();
        }
        // wrong format or invalid actual move on the board
        else if (itype == INPUT_TYPE_INVALID_MOVE)
        {
            cerr << "Invalid move! (" << input << ")" << endl;
            prompt.turn(gman->getPlayer(), gman->getTurn());
            continue;
        }
        // if no command or movement was entered, print an error 
        // * an input can only be a movement or a command.
        else
        {
            cerr << "Wrong move or command '" << input;
            cerr << "'. Please try again." << endl;
            prompt.turn(gman->getPlayer(), gman->getTurn());
            continue;
        }

        // if the machine is playing, display its move
        if (cur_player == PLAYER_TYPE_COMPUTER)
        {
            // measure how long it takes to think the move
            int timeUsed = (end - start) / CLOCKS_PER_SEC;
            int min  = 0;
            int sec  = 0;
            min  = timeUsed / 60;
            sec  = timeUsed % 60;

            cout << endl << "\aMy move: ";
            string human = move.getHuman();

            // number of move
            int current_move = (gman->getGame()->getCursor() + 1) / 2;
            if (gman->getPlayer() == COLOR_TYPE_WHITE)
                cout << to_string(current_move) << "... ";
            else
                cout << to_string(current_move) << ". ";

            // if check, then add "+" to the move notation
            if (board->isMate())
            {
                human.erase(std::remove(human.begin(), human.end(), '+'), human.end());
                cout << human << "#";
            }
            else if (board->isCheck())
            {
                human.erase(std::remove(human.begin(), human.end(), '#'), human.end());
                cout << human << "+";
            }
            else
            {
                cout << human;
            }

            // show if the move is from the book
            cout << MoveIsFromBook;

            // show how much time was used to think
            cout.fill('0');
            cout << " (time: ";
            cout << setw(2) << min << ":";
            cout << setw(2) << sec;

            // update clock if needed, and show the reamining game time
            if (computerTime > 0)
            {
                elapsedTime += timeUsed;
                ai->setTPM(calculateTPM(computerTime, elapsedTime, gman->getGame()->getCursor() / 2));

                int remainingTime = computerTime - elapsedTime;
                if (remainingTime <= 0)
                    remainingTime = 0;
                unsigned short thour = remainingTime / 3600;
                unsigned short tmin  = (remainingTime % 3600) / 60;
                unsigned short tsec  = (remainingTime % 3600) % 60;

                cout << " / clock: ";
                cout << setw(2) << thour << ":";
                cout << setw(2) << tmin << ":";
                cout << setw(2) << tsec;
            }
            cout << ")" << endl;
        }

        // display the board in every move, if verbose 
        if (verbose) cout << board->toString();

        prompt.turn(gman->getPlayer(), gman->getTurn());
    }

    return 0;
}


/*!
 * Retrieve an input line from the user.
 *
 * @return a string object containig the user input.
 */
string ApplicationManager::getInput()
{
    char input[MAX_INPUT_SIZE];

    // get a line from the input
    cin.getline(input, MAX_INPUT_SIZE);
    string input_str(input);
    if (cin.eof())
    {
        prompt.terminate();
        exit(0);
    }

    return input_str;
}


/*!
 * Analyze a given input and try to discover its nature. Set the mtype to the
 * concrete MoveType analyzed with the input. If the input is not a move, then
 * set it to MOVE_TYPE_INVALID.
 *
 * @param input String with the user's input from UI.
 * @param mtype Pointer to a MoveType value where to set the type of move.
 *
 * @return an integer value (which should be used as a constant definition),
 * telling which type of input was given.
 */
InputType ApplicationManager::getInputType(string input, MoveType *mtype)
{
    if ((cmdp.translate(input)).getType() != CMD_TYPE_UNKNOWN)
    {
        *mtype = MOVE_TYPE_INVALID;
        return INPUT_TYPE_CMD;
    }

    // check if the input could be an apparent movement
    if ((input.length() < 2) || (input.length() > 8))
        return INPUT_TYPE_INVALID_MOVE;

    // check further if it is an actual move or not
    // move_pawn => column + row (e.g. e4, d4, f3, b7..)
    if ((input.length() == 2) && (isColumn(input[0]))
                              && (isRow(input[1]))
                              && (input[1] != '8'))
    {
        *mtype = MOVE_TYPE_PAWN;
        return INPUT_TYPE_MOVE;
    }

    // move_piece_simple => piece + column|row + column|row (e.g. Nd4)
    // castle_short => 0-0
    else if (input.length() == 3)
    {
        if ((input == "0-0") || (input == "O-O"))
        {
            *mtype = MOVE_TYPE_CASTLE_SHORT;
            return INPUT_TYPE_MOVE;
        }
        else if (isPiece(input[0]) && isColumn(input[1]) && isRow(input[2]))
        {
            *mtype = MOVE_TYPE_SIMPLE;
            return INPUT_TYPE_MOVE;
        }
        else if (isColumn(input[0]) && (input[1] == 'x') && isColumn(input[2]))
        {
            *mtype = MOVE_TYPE_CAPTURE_PAWN_SHORT;
            return INPUT_TYPE_MOVE;
        }
        else if (isPiece(input[0]) && (input[1] == 'x') && isColumn(input[2]))
        {
            *mtype = MOVE_TYPE_CAPTURE_SIMPLE_SHORT;
            return INPUT_TYPE_MOVE;
        }
        else
        {
            *mtype = MOVE_TYPE_INVALID;
            return INPUT_TYPE_ERROR;
        }
    }

    // move_orig_dest   => column + row + column + row (e.g. d2d4)
    // capture_simple   => piece|column + 'x' + column + row (e.g. exd4, Nxd4)
    // promotion_simple => column + row + '=' + piece
    else if (input.length() == 4)
    {
        // promotion
        if (isColumn(input[0]) && isRow(input[1]) && (input[2] == '=') &&
            isPiece(input[3])  && (input[3] != 'K') && (input[3] != 'k'))
        {
            *mtype = MOVE_TYPE_PROMOTION_SIMPLE;
        }

        // regular move
        else if ((isColumn(input[0])) && (isRow(input[1]))
                                 && (isColumn(input[2]))
                                 && (isRow(input[3])))
        {
            if (input.substr(0, 2) != input.substr(2, 2))
                *mtype = MOVE_TYPE_XY;
            else
                *mtype = MOVE_TYPE_INVALID;
        }

        // check for captures
        else if (isColumn(input[0]) && (input[1] == 'x'))
        {
            *mtype = MOVE_TYPE_CAPTURE_PAWN;
        }
        else if (isPiece(input[0]) && (input[1] == 'x'))
        {
            *mtype = MOVE_TYPE_CAPTURE_SIMPLE;
        }
        // check for ambiguous move
        else if (isPiece(input[0]) && (isColumn(input[1]) || isRow(input[1]))
                                   && isColumn(input[2]) && isRow(input[3]))
        {
            *mtype = MOVE_TYPE_AMBIGUOUS;
        }
        else
        {
            *mtype = MOVE_TYPE_INVALID;
        }

        return INPUT_TYPE_MOVE;
    }
    // move_piece_ambiguous    => piece + column|row + column + row
    // castle_long             => 0-0-0
    // promotion_capture_short => column + 'x' + column + '=' + piece
    else if (input.length() == 5)
    {
        // promotion
        if (isColumn(input[0]) && (input[1] == 'x') && isColumn(input[2]) &&
            (input[3] == '=')  && (input[4] != 'K') && (input[4] != 'k'))
        {
            *mtype = MOVE_TYPE_PROMOTION_CAPTURE_SHORT;
            return INPUT_TYPE_MOVE;
        }
        else if ((input == "0-0-0") || (input == "O-O-O"))
        {
            *mtype = MOVE_TYPE_CASTLE_LONG;
            return INPUT_TYPE_MOVE;
        }
        else if (isPiece(input[0]) && (isColumn(input[1]) || isRow(input[1]))
                                   && (input[2] == 'x')
                                   && isColumn(input[3]) && isRow(input[4]))
        {
            *mtype = MOVE_TYPE_CAPTURE_LONG;
            return INPUT_TYPE_MOVE;
        }
        else
        {
            *mtype = MOVE_TYPE_INVALID;
            return INPUT_TYPE_ERROR;
        }
    }
    // promotion_capture => column + 'x' + column + '8' + '=' + piece
    else if (input.length() == 6)
    {
        // promotion
        if (isColumn(input[0]) && (input[1] == 'x') && isColumn(input[2]) &&
            ((input[3] == '8') || (input[3] == '1')) && (input[4] == '=') &&
            (input[5] != 'K') && (input[5] != 'k'))
        {
            *mtype = MOVE_TYPE_PROMOTION_CAPTURE;
            return INPUT_TYPE_MOVE;
        }
        else
        {
            *mtype = MOVE_TYPE_INVALID;
        }
    }

    // by default, a movement is invalid until proven otherwise
    return INPUT_TYPE_ERROR;
}


/*!
 * Translate a given command input into an internal action command.
 *
 * @param input String with the user-entered input.
 *
 * @return a Command object containing the internal command for the program.
 */
Command ApplicationManager::toCmd(string input)
{
    return cmdp.translate(input);
}


/*!
 * Display the current material situation on the board.
 *
 * @param ai AI engine to call for the evaluation.
 */
void ApplicationManager::displayMaterial()
{
    float mat = ai->evalMaterial();

    cout << "Material evaluation: ";
    if (mat >= 0)
        cout << "+";
    cout << mat << endl;
}


/*!
 * Display the current heuristic evaluation according to the board.
 */
void ApplicationManager::displayEval()
{
    float h = ai->eval();

    cout << "Evaluation: ";
    if (h >= 0)
        cout << "+";
    cout << setw(4) << fixed << setprecision(2) << h << endl;
}


/*!
 * Deal with the end of the current match.
 */
void ApplicationManager::dealEnd()
{
    cout << endl;

    // deal with different ends
    switch (gman->getEnd())
    {
        case END_TYPE_RESIGN:
            if (gman->getPlayer() == COLOR_TYPE_WHITE)
                cout << "0-1 {White resigns}" << endl;
            else
                cout << "1-0 {Black resigns}" << endl;
            break;
        case END_TYPE_DRAW:
            cout << "1/2-1/2 {Draw}" << endl;
            break;
        case END_TYPE_DRAW_50RULE:
            cout << "1/2-1/2 {Draw by the 50 moves rule}" << endl;
            break;
        case END_TYPE_DRAW_3RULE:
            cout << "1/2-1/2 {Draw by repetition}" << endl;
            break;
        case END_TYPE_DRAW_PIECES:
            cout << "1/2-1/2 {Draw due to not enough pieces}" << endl;
            break;
        case END_TYPE_DRAW_AGREE:
            cout << "1/2-1/2 {Draw by players agreement}" << endl;
            break;
        case END_TYPE_DRAW_STALE:
            cout << "1/2-1/2 {Stalemate}" << endl;
            break;
        case END_TYPE_MATE:
            if (gman->getPlayer() == COLOR_TYPE_WHITE)
                cout << "1-0 {White wins}" << endl;
            else
                cout << "0-1 {Black wins}" << endl;
            break;
        case END_TYPE_SOLVE:
            break;
        default:
            cout << "The game was abnormally ended!" << endl;
    }

    // don't let the computer control the program after a game
    gman->setWhite(PLAYER_TYPE_HUMAN);
    gman->setBlack(PLAYER_TYPE_HUMAN);

    // if we are not XBoard, ask the user what to do next
    if (!xboard)
    {
        // tell how to play another match
        cout << "Want to play another one? Enter the command 'restart'." << endl;

        cout << endl << "Your command: ";

        // clean the input, if necessary
        if (cin.peek() == '\n')
            cin.ignore(1, '\n');
    }
}
