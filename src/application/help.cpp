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
 * @file src/application/help.cpp
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <iomanip>
#include "utils"
#include "application/manager"
#include "application/prompt"
#include "ai/adaptive"



/*!
 * Display help information, either general or about a concrete command.
 */
void ApplicationManager::displayHelp(string which)
{
    // no specific command
    if (which == "")
    {
        cout << "List of commands: (help COMMAND to get more help)" << endl;
        cout << "auto  book  cache  depth  draw  edit  eval  flip  go  help" << endl;
        cout << "history  info  load  log  manual  material  new  pass  resign" << endl;
        cout << "save  show  solve  test  think  undo  verbose  version quit" << endl;
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
        cout << "book [on | off]" << endl;
        cout << " Enable or disable the moves from the book for the computer.";
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

    // help depth
    else if (which == "depth")
    {
        cout << "depth [N]" << endl;
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

    // help draw
    else if (which == "draw")
    {
        cout << "draw" << endl;
        cout << " Offer draw to your opponent. If the draw is accepted,";
        cout << endl;
        cout << " the match ends in draw score. Otherwise, the match just";
        cout << endl;
        cout << " continues as normal." << endl;
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

    // help info
    else if (which == "info")
    {
        cout << "info" << endl;
        cout << " Display some useful information about the current game,";
        cout << endl;
        cout << " including the phase of the game, the side to move, the";
        cout << endl;
        cout << " last move on the board, the overall evaluation and the";
        cout << endl;
        cout << " material balance." << endl;
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

    // help log
    else if (which == "log")
    {
        cout << "log [FILENAME|off]" << endl;
        cout << " Enable or disable logging to a disk file. By issuing";
        cout << endl;
        cout << " this command without parameters, chess0 will display";
        cout << endl;
        cout << " the current status of the logging setting. If you";
        cout << endl;
        cout << " specify a parameter different than 'off', chess0 will";
        cout << endl;
        cout << " start writing log output to a file with the name given";
        cout << endl;
        cout << " in the parameter. On the other hand, if you give the";
        cout << endl;
        cout << " parameter 'off', the logging support will be disabled.";
        cout << endl;
        cout << endl;
        cout << " Please note that logging is disabled by default. Moreover";
        cout << endl;
        cout << " it is only implemented in the Board module, so far.";
        cout << endl;
    }

    // help material
    else if (which == "material")
    {
        cout << "material" << endl;
        cout << " Display the material balance of the current game." << endl;
    }

    // help manual
    else if (which == "manual")
    {
        cout << "manual" << endl;
        cout << " Set both players to be played by human input." << endl;
    }

    // help new 
    else if (which == "new")
    {
        cout << "new" << endl;
        cout << " Start a new game." << endl;
    }

    // help pass
    else if (which == "pass")
    {
        cout << "pass" << endl;
        cout << " Make a null move. This means that no move is actually";
        cout << endl;
        cout << " performed on the board, but the turn moves over the" << endl;
        cout << " other player. This command is mainly used for testing";
        cout << endl;
        cout << " certain positions." << endl;
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
        cout << " this command saves a position, not a match (do not confuse";
        cout << endl;
        cout << " with the PGN format.";
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

    // help think (time per move)
    else if (which == "think")
    {
        cout << "think [N]" << endl;
        cout << " Set the maximum amount of time the engine can think" << endl;
        cout << " before performing a move. The time must be a minimum of" << endl;
        cout << " 1 (seconds) and there is no maximum limit. Setting the" << endl;
        cout << " thinking time to 0 allows the engine to think indefinitely " << endl;
        cout << " (or until it hits the depth limit, if there is any)." << endl;
        cout << " Using this command disables the game clock (time)." << endl;
    }

    // help time
    else if (which == "time")
    {
        cout << "time [N]" << endl;
        cout << " Set the clock time for the game (in minutes). Using this" << endl;
        cout << " command will let the computer adjust its own time per move" << endl;
        cout << " (TPM) automatically. The closest the clock is to 00:00, the" << endl;
        cout << " less time the computer will think." << endl;
    }

    // help undo
    else if (which == "undo")
    {
        cout << "undo | back" << endl;
        cout << " Take back a move from the game." << endl;
    }

    // help verbose
    else if (which == "verbose")
    {
        cout << "verbose [on|off]" << endl;
        cout << " Set the application into verbose mode, either on or off.";
        cout << endl;
        cout << " In verbose mode, the program will show the status of the";
        cout << endl;
        cout << " board after each move and some other information.";
        cout << endl;
    }

    // help version
    else if (which == "version")
    {
        cout << "version" << endl;
        cout << " Show the application version number, author and website.";
        cout << endl;
    }

    // help quiet
    else if (which == "quiet")
    {
        cout << "quiet" << endl;
        cout << " Alias of 'verbose off'." << endl;
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
