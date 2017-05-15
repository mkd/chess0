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



/*!
 * @file definitions.h
 *
 * TODO: document
 */
#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <stdint.h>
 
#define PROG_NAME "Chess0"
#define PROG_VERSION "Chess0 1.0dev"

#define MAX_CMD_BUFF     256   // Console command input buffer
#define MAX_MOV_BUFF    4096   // Max number of moves that we can store (all plies)
#define MAX_PLY           64   // Max search depth
#define MAX_GAME_LINE   1024   // Max number of moves in the (game + search) line that we can store


/*!
 * Different execution modes of Chess0x:
 * - XBOARD: the program will be quiet and interact with a graphical user
 *           interface (GUI), by using the Winboard/Xboard protocol.
 *
 * - CLI:    the program will be verbose and interact with the user through the
 *           command line of the system, using text-based input and commands.
 */
#define APP_MODE_XBOARD 1
#define APP_MODE_CLI    2


typedef uint64_t U64;
typedef uint64_t BitMap;
typedef short SHORTINT;
typedef unsigned short USHORTINT;
typedef int BOOLTYPE;
 
#endif
