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
 * @file board.cpp
 *
 * XXX
 */
#include <iostream>
#include <iomanip>
#include "definitions.h"
#include "functions.h"
#include "extglobals.h"
#include "board.h"


using namespace std;



/*!
 *
 */ 
void Board::init()
{
       flipBoard = false;
 
       for (int i = 0; i < 64; i++) square[i] = EMPTY;
 
       square[E1] = WHITE_KING;
       square[D1] = WHITE_QUEEN;
       square[A1] = WHITE_ROOK;
       square[H1] = WHITE_ROOK;
       square[B1] = WHITE_KNIGHT;
       square[G1] = WHITE_KNIGHT;
       square[C1] = WHITE_BISHOP;
       square[F1] = WHITE_BISHOP;
       square[A2] = WHITE_PAWN;
       square[B2] = WHITE_PAWN;
       square[C2] = WHITE_PAWN;
       square[D2] = WHITE_PAWN;
       square[E2] = WHITE_PAWN;
       square[F2] = WHITE_PAWN;
       square[G2] = WHITE_PAWN;
       square[H2] = WHITE_PAWN;
 
       square[E8] = BLACK_KING;
       square[D8] = BLACK_QUEEN;
       square[A8] = BLACK_ROOK;
       square[H8] = BLACK_ROOK;
       square[B8] = BLACK_KNIGHT;
       square[G8] = BLACK_KNIGHT;
       square[C8] = BLACK_BISHOP;
       square[F8] = BLACK_BISHOP;
       square[A7] = BLACK_PAWN;
       square[B7] = BLACK_PAWN;
       square[C7] = BLACK_PAWN;
       square[D7] = BLACK_PAWN;
       square[E7] = BLACK_PAWN;
       square[F7] = BLACK_PAWN;
       square[G7] = BLACK_PAWN;
       square[H7] = BLACK_PAWN;
 
       initFromSquares(square, WHITE_MOVE, 0, CANCASTLEOO + CANCASTLEOOO, CANCASTLEOO + CANCASTLEOOO, 0);
}



/*!
 * Mirror the board position. The intended use is to test symmetry of the
 * evalaution function.
 *
 * Don't forget to mirror the position back to the original position, after testing the evaluation function.
 *
 * NOTE: move buffers are not effected.
 */
void Board::mirror()
{
 
       int i, mirroredBoard[64];
       unsigned char nextMirror;
       int fiftyMMirror, castleWMirror, castleBMirror, epSqMirror;
       int kmoveBufLen, kendOfGame, kendOfSearch;
 
       nextMirror = !nextMove;
       fiftyMMirror = fiftyMove;
       castleWMirror = castleBlack;
       castleBMirror = castleWhite;
       if (epSquare)
       {
              if (epSquare < 24) epSqMirror = epSquare + 24;
              else epSqMirror = epSquare - 24;
       }
 
       for (i = 0; i < 64; i++)
       {
              mirroredBoard[i] = square[MIRROR[i]];
              // swap piece color (4th bit):
              if (mirroredBoard[i] != EMPTY) mirroredBoard[i] ^= 8;
       }
 
       // keep the move buffer intact:
       kmoveBufLen = moveBufLen[0];
       kendOfGame = endOfGame;
       kendOfSearch = endOfSearch;
       initFromSquares(mirroredBoard, nextMirror, fiftyMMirror, castleWMirror, castleBMirror, epSqMirror);
       moveBufLen[0] = kmoveBufLen;
       endOfGame = kendOfGame;
       endOfSearch = kendOfSearch;
}



/*!
 * Set up the board variables according to the information found in the
 * input[64] array. All board & game initializations are done through this
 * function (including readfen and setup).
 */
void Board::initFromSquares(int input[64], unsigned char next, int fiftyM, int castleW, int castleB, int epSq)
{
	int i;
 
	// bitboards
	whiteKing    = 0;
	whiteQueens  = 0;
	whiteRooks   = 0;
	whiteBishops = 0;
	whiteKnights = 0;
	whitePawns   = 0;
	blackKing    = 0;
	blackQueens  = 0;
	blackRooks   = 0;
	blackBishops = 0;
	blackKnights = 0;
	blackPawns   = 0;
	whitePieces  = 0;
	blackPieces  = 0;
	occupiedSquares = 0;
	hashkey = 0;

	// populate the 12 bitboard:
	for (i = 0; i < 64; i++)
	{
		square[i] = input[i];
		if (square[i] == WHITE_KING) 
		{  
			whiteKing    = whiteKing | BITSET[i]; 
			hashkey     ^= KEY.keys[i][WHITE_KING];  
		}
		if (square[i] == WHITE_QUEEN)
		{
			whiteQueens  = whiteQueens  | BITSET[i];
			hashkey     ^= KEY.keys[i][WHITE_QUEEN];  		
		}
		if (square[i] == WHITE_ROOK)
		{
			whiteRooks   = whiteRooks   | BITSET[i];
			hashkey     ^= KEY.keys[i][WHITE_ROOK];  		
		}
		if (square[i] == WHITE_BISHOP)
		{
			whiteBishops = whiteBishops | BITSET[i];
			hashkey     ^= KEY.keys[i][WHITE_BISHOP];  		
		}
		if (square[i] == WHITE_KNIGHT) 
		{
			whiteKnights = whiteKnights | BITSET[i];
			hashkey     ^= KEY.keys[i][WHITE_KNIGHT];  		
		}
		if (square[i] == WHITE_PAWN)   
		{
			whitePawns   = whitePawns   | BITSET[i];
			hashkey     ^= KEY.keys[i][WHITE_PAWN];  		
		}
		if (square[i] == BLACK_KING)   
		{
			blackKing    = blackKing    | BITSET[i];
			hashkey     ^= KEY.keys[i][BLACK_KING];  		
		}
		if (square[i] == BLACK_QUEEN)  
		{
			blackQueens  = blackQueens  | BITSET[i];
			hashkey     ^= KEY.keys[i][BLACK_QUEEN];  		
		}
		if (square[i] == BLACK_ROOK)   
		{
			blackRooks   = blackRooks   | BITSET[i];
			hashkey     ^= KEY.keys[i][BLACK_ROOK];  		
		}
		if (square[i] == BLACK_BISHOP) 
		{
			blackBishops = blackBishops | BITSET[i];
			hashkey     ^= KEY.keys[i][BLACK_BISHOP];  		
		}
		if (square[i] == BLACK_KNIGHT) 
		{
			blackKnights = blackKnights | BITSET[i];
			hashkey     ^= KEY.keys[i][BLACK_KNIGHT];  		
		}
		if (square[i] == BLACK_PAWN)   
		{
			blackPawns   = blackPawns   | BITSET[i];
			hashkey     ^= KEY.keys[i][BLACK_PAWN];  		
		}
	}
 
	whitePieces = whiteKing | whiteQueens | whiteRooks | whiteBishops | whiteKnights | whitePawns;
	blackPieces = blackKing | blackQueens | blackRooks | blackBishops | blackKnights | blackPawns;
	occupiedSquares = whitePieces | blackPieces;
 
	nextMove = next;

	castleWhite = castleW;
	castleBlack = castleB;
	epSquare = epSq;
	fiftyMove = fiftyM;

	if (castleWhite & CANCASTLEOO)  hashkey ^= KEY.wk;
	if (castleWhite & CANCASTLEOOO) hashkey ^= KEY.wq;
	if (castleBlack & CANCASTLEOO)  hashkey ^= KEY.bk;
	if (castleBlack & CANCASTLEOOO) hashkey ^= KEY.bq;
	if (nextMove) hashkey ^= KEY.side;
	if (epSq) hashkey ^= KEY.ep[epSq];
 
	totalWhitePawns = bitCnt(whitePawns) * PAWN_VALUE;
	totalBlackPawns = bitCnt(blackPawns) * PAWN_VALUE;
	totalWhitePieces = 	bitCnt(whiteKnights) * KNIGHT_VALUE + bitCnt(whiteBishops) * BISHOP_VALUE +
							bitCnt(whiteRooks) * ROOK_VALUE + bitCnt(whiteQueens) * QUEEN_VALUE;
	totalBlackPieces = 	bitCnt(blackKnights) * KNIGHT_VALUE + bitCnt(blackBishops) * BISHOP_VALUE +
							bitCnt(blackRooks) * ROOK_VALUE + bitCnt(blackQueens) * QUEEN_VALUE;
	Material  = totalWhitePawns + totalWhitePieces - totalBlackPawns - totalBlackPieces;
 
	endOfGame = 0;
	endOfSearch = 0;
	for (i = 0; i < MAX_PLY; i++) 
	{
		moveBufLen[i] = 0;
		triangularLength[i] = 0;
	}
	inodes = 0;
}



/*!
 * Convert the internal representation of the board into a human-readable string
 * (capable of being shown and represented as a Board in ASCII) and show it on
 * the screen.
 */
void Board::display()
{
    int rank, file;

    // display white front
    cout << endl;
    if (!flipBoard)
    {
        cout << "    +----+----+----+----+----+----+----+----+" << endl;
        for (rank = 8; rank >= 1; rank--)
        {
            cout << setw(3) << rank <<  " |";
            for (file = 1; file <= 8; file++)
            {
                cout << " " << PIECENAMES[square[BOARDINDEX[file][rank]]] << " |";
            }
            cout << endl << "    +----+----+----+----+----+----+----+----+" << endl;
        }
        cout << "      a    b    c    d    e    f    g    h" << endl << endl;
    }

    // display black front
    else
    {
        cout << "    +----+----+----+----+----+----+----+----+" << endl;
        for (rank = 1; rank <= 8; rank++)
        {
            cout << setw(3) << rank << " |";
            for (file = 8; file >= 1; file--)
            {
                cout << " " << PIECENAMES[square[BOARDINDEX[file][rank]]] << " |";
            }
            cout << endl << "    +----+----+----+----+----+----+----+----+" << endl;
        }
        cout << "      h    g    f    e    d    c    b    a" << endl << endl;
    }

    // DEBUG
    //cout << "next=" << (int)board.nextMove << endl;
    //cout << "ep=" << board.epSquare << endl;
    //cout << "fifty=" << board.fiftyMove << endl;
    //cout << "white castle=" << (int)board.castleWhite << endl;
    //cout << "black castle=" << (int)board.castleWhite << endl;
    //cout << "key=" << board.hashkey << endl;
    //cout << "endOfGame=" << board.endOfGame << endl;
    //cout << "endOfSearch=" << board.endOfSearch << endl;
    //cout << "repetitionCount=" << repetitionCount() << endl;
    //cout << "sign=..." << (board.hashkey & 0x00000fff) << endl;
}
