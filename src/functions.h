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



// @file functions.h
//
// This file contains a list of all functions that will be visible across
// multiple files.
#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_



#include <iostream>
#include "board.h"
#include "move.h"



using namespace std;



unsigned int  bitCnt(BitMap);
int           captgen(int);
void          dataInit();
void          displayBitmap(BitMap);
void          displayMove(Move &);
void		  displayPV();
void		  commands();
BOOLTYPE      doIniCommand(const char *);
unsigned int  firstOne(BitMap);
void          info();
BOOLTYPE      isAttacked(BitMap &, const unsigned char &);
BOOLTYPE      isOtherKingAttacked();
BOOLTYPE      isOwnKingAttacked();
unsigned int  lastOne(BitMap);
void          makeBlackPromotion(unsigned int, unsigned int &);
void          makeCapture(unsigned int &, unsigned int &);
void          makeMove(Move &);
void          makeWhitePromotion(unsigned int, unsigned int &);
int           movegen(int);
void		  mstostring(U64 dt, char *);
U64           perft(int, int);
BOOLTYPE      readFen(char *, int);
void		  readIniFile();
void          setup();
void          setupFen(char *, char *, char *, char *, int , int );
void		  test(char *);
void		  timeControl();
BOOLTYPE	  toSan(Move &, char *);
void          unmakeBlackPromotion(unsigned int, unsigned int &);
void          unmakeCapture(unsigned int &, unsigned int &);
void          unmakeMove(Move &);
void          unmakeWhitePromotion(unsigned int, unsigned int &);
string        getInput();
void          terminateApp();
string        bunmap(int);
BOOLTYPE      isValidTextMove(char *, Move &);



/*!
 * Check if the given character represents a piece (N for Knight, B for
 * Bishop, R for Rook, Q for Queen and K for King).
 *
 * @param p Char holding a piece letter.
 *
 * @return true of p is N, B, R, Q, or K, false otherwise.
 */
inline bool isPiece(char p)
{
    return ((p == 'N') || (p == 'B') || (p == 'R') || (p == 'Q') ||
            (p == 'K'));
}




#endif // _FUNCTIONS_H_
