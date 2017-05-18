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



// @file perft.cpp
//
// XXX
#include <iostream>
#include "definitions.h"
#include "extglobals.h"
#include "functions.h"


 
// Raw node count, up to depth, doing a full tree search.
// perft is very similar to the search algorithm - instead of evaluating the leaves, we count them.
//
// Be carefull when calling this function with depths > 7, because it can take a very long
// time before the result is returned: the average branching factor in chess is 35, so every
// increment in depth will require 35x more computer time.
//
// perft is a good way of verifying correctness of the movegenerator and (un)makeMove,
// because you can compare the results with published results for certain test positions.
//
// perft is also used to measure the performance of the move generator and (un)makeMove in terms
// of speed, and to compare different implementations of generating, storing and (un)making moves.
U64 perft(int ply, int depth)
{
       U64 retVal = 0;     
       int i;
 
       // count this node
       if (depth == 0)
              return 1;

 
       // generate moves from this position
       board.moveBufLen[ply+1] = movegen(board.moveBufLen[ply]);
 
       // loop over moves:
       for (i = board.moveBufLen[ply]; i < board.moveBufLen[ply+1]; i++)
       {
              makeMove(board.moveBuffer[i]);
              {
                     if (!isOtherKingAttacked())
                     {
                           // recursively call perft
                           retVal += perft(ply + 1, depth-1);
 
                           #ifdef CHESS0_DEBUG_PERFT
                           if (depth == 1)
                           {
                                  if (board.moveBuffer[i].isCapture()) ICAPT++;
                                  if (board.moveBuffer[i].isEnpassant()) IEP++;
                                  if (board.moveBuffer[i].isPromotion()) IPROM++;
                                  if (board.moveBuffer[i].isCastleOO()) ICASTLOO++;
                                  if (board.moveBuffer[i].isCastleOOO()) ICASTLOOO++;
                                  if (isOwnKingAttacked()) ICHECK++;
                           }
                          #endif
                     }
              }
              unmakeMove(board.moveBuffer[i]);
       }
       return retVal;
}
