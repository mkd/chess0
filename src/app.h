/* 
    This file is part of Chess0, a computer chess program based on Winglet chess
    by Stef Luijten.
    
    Copyright (C) 2017 Claudio M. Camacho
                                                                           
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



// @file app.h
//
// This file contains all the variables and method definitions that can
// be used across the whole application.
#ifndef _APP_H_
#define _APP_H_

#include <vector>
#include <unordered_map>
#include "definitions.h"

using namespace std;



/*!
 * Application types and definitions.
 */
#define PLAYER_TYPE_HUMAN    1
#define PLAYER_TYPE_COMPUTER 2

#define HUMAN_CPU   1
#define HUMAN_HUMAN 2
#define CPU_CPU     3


// different types of inputs
enum InputType
{
    INPUT_TYPE_MOVE,
    INPUT_TYPE_CMD,
    INPUT_TYPE_INVALID,
};



/*!
 * Application methods and variables.
 */
extern int             appMode;
extern vector<string>  listOfCommands;
extern string          lastErrorMessage;
extern vector<string>  history;
extern bool            useCache;
extern EndType         gameEnd;

int startApp(int);
void prompt(unsigned);
std::string getInput();
void terminateApp();
void changeSide();
uint64_t perft(unsigned, ColorType);
void dealEnd();
InputType getInputType(string);
void displayGame();
string getGameSequence();



/*!
 * Game status variables.
 */
extern int playMode;
extern int wPlayer;
extern int bPlayer;
extern int curPlayerType;
extern unsigned numberOfMove;
extern unsigned cursor;
extern ColorType gameMate;
extern bool useBook;
extern bool usePersonalBook;



/*!
 * Built-in helper functions.
 */
inline bool isFile(char c) { return ((c >= 'a' ) && (c <= 'h')); }
inline bool isRank(char r) { return ((r >= '1' ) && (r <= '8')); }



/*!
 * Cache implementation is rather rudimentary in chess0x. Instead of
 * using Least Recent Use (LRU) or similar, Chess0 simply keeps adding
 * new positions to the cache without any limit. This is due to the fact
 * that LRU introduces some delay when looking at the cache size and
 * doing the replacement itself. Since chess0x can use a few megabytes
 * even after a very long thinking, it should not go beyond the 1GByte
 * for 1h+ games. If someone complains about not having a limit for the
 * cache, then I'll implement some cache cleaning up functionality.
 *
 * Why unordered_map? Well, using std::map has the same behavior (plus
 * it allows LRU-like deletion of oldest items, due to its ordered
 * nature), however it is 3-8x times slower in most situations. Using
 * unordered_map the performance is greatly improved, brining around 20%
 * overall performance to the whole AI engine.
 */
extern unordered_map<string, int> cache;


#endif // _APP_H_
