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
 * @file src/game/manager.cpp
 */
#include "utils"
#include "game/manager"



/*!
 * Default constructor.
 */
GameManager::GameManager()
{
    // by default, human vs computer
    white = PLAYER_TYPE_HUMAN;
    black = PLAYER_TYPE_COMPUTER;

    // associate the game with the moveparser
    movp.setGame(&game);
}


/*!
 * Safely invoke a method from an internal game to represent the current
 * situation board.
 */
void GameManager::displayBoard()
{
    game.displayBoard();
}


/*!
 * Perform a given move and update every necessary component in the
 * game.
 *
 * Please notice that any move coming here is supposed to be already validated
 * by another component. This part of the code (the method perform()) will just
 * update the board, unknownlingly and independently of the rules of chess.
 *
 * Nevertheless, further checking (double-check) functionality could be added to
 * this function or any other method in the GameManager class, if it is
 * necessary in the future.
 *
 * Additionally, any performed move will be inserted in the game history stack.
 *
 * @param move Move to be performed on an ongoing game.
 *
 * @return a proper Error code (@see src/definitions)
 */
Error GameManager::perform(Move move)
{
    // moving color must match the current turn color
    if (move.getColor() != game.getPlayer())
        return ERROR_DIFCOLOR;

    // update board
    return game.perform(move);
}


/*!
 * Check the color of the player who is about to move in the current game.
 *
 * @return a ColorType, being either COLOR_TYPE_WHITE or COLOR_TYPE_BLACK.
 */
ColorType GameManager::getPlayer()
{
    return game.getPlayer();
}


/*!
 * Check the number of turn of the current game. Please notice that, if a game
 * was not started, still theh turn will be 1.
 *
 * On the other line, even if a game is finished, a number N will be returned,
 * indicating that the game is at that very move.
 *
 * @return an integer from 1 to N, where N is the number of moves performed in
 *         the current game. Return 0 if an internal error happened.
 */
int GameManager::getTurn()
{
    return game.getTurn();
}


/*!
 * Display the list of moves of the current game.
 */
void GameManager::displayHistory()
{
    cout << "Game history:" << endl;
    reportIfError(game.displayHistory());
    cout << endl;
}


/*!
 * Translate a given move input into an internal x1y1-x2y2 movement object.
 *
 * @param input User-entered input.
 * @param mtype Type of move, typically predicted by the ApplicationManager.
 *
 * @return a Move object with all the information relative to the generated
 *         move.
 */
Move GameManager::toMove(string input, MoveType mtype)
{
    return movp.translate(input, mtype, &game);
}


/*!
 * Take back one move, if possible.
 *
 * Note: this functionality is fully delegated to the Game object.
 *
 * @return ERROR_BACK_BEGIN if the game has ended (no more moves left
 *         forward), ERROR_NONE otherwise.
 */
void GameManager::takeBack()
{
    reportIfError(game.undo());
}


/*!
 * Restart a game.
 *
 * Note: this functionality is fully delegated to the Game object.
 */
void GameManager::restart()
{
    // by default, human vs computer
    white = PLAYER_TYPE_HUMAN;
    black = PLAYER_TYPE_COMPUTER;

    // reset the whole game
    game.restart();
}


/*!
 * Resign.
 */
void GameManager::resign()
{
    game.setEnd(END_TYPE_RESIGN);
}


/*!
 * End the game.
 */
void GameManager::end()
{
    game.setEnd(END_TYPE_RESIGN);
}
