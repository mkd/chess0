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



// @file qsearch.cpp
//
// XXX
#include "definitions.h" 
#include "extglobals.h" 
#include "functions.h" 
#include "board.h" 



unsigned short  quiesceDepth = 0;
unsigned short  quiesceLimit = AI_DEPTH_QUIESCE_LIMIT;



// Quiescence search.
//
// Perform a search indefinitely until all the following conditions happen:
// a) no more possible captures
// b) no more checks possible
// c) no more pawn promotions
int Board::qsearch(int ply, int alpha, int beta)
{
    int i, j, val;

    // if reached qsearch limit, return value
    if (quiesceDepth >= quiesceLimit)
        return board.eval();


    if (timedout)
        return 0;


    triangularLength[ply] = ply;
    if (isOwnKingAttacked()) return alphabetapvs(ply, 1, alpha, beta);
    val = board.eval();
    if (val >= beta) return val;
    if (val > alpha) alpha = val;


    // generate captures & promotions:
    // captgen returns a sorted move list
    moveBufLen[ply+1] = captgen(moveBufLen[ply]);
    for (i = moveBufLen[ply]; i < moveBufLen[ply+1]; i++)
    {
        makeMove(moveBuffer[i]);
        {
            if (!isOtherKingAttacked()) 
            {
                inodes++;
                quiesceDepth++;

                if (--countdown <=0) readClockAndInput();
                val = -qsearch(ply+1, -beta, -alpha);
                unmakeMove(moveBuffer[i]);
                if (val >= beta) return val;
                if (val > alpha)
                {
                    alpha = val;
                    triangularArray[ply][ply] = moveBuffer[i];
                    for (j = ply + 1; j < triangularLength[ply+1]; j++) 
                    {
                        triangularArray[ply][j] = triangularArray[ply+1][j];
                    }
                    triangularLength[ply] = triangularLength[ply+1];
                }
            }
            else unmakeMove(moveBuffer[i]);
        }
    }

    return alpha;
}
