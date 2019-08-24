/* 
    This file is part of Chess0, a computer chess program based on Winglet chess
    by Stef Luijten.
    
    Copyright (C) 2019 Claudio M. Camacho
                                                                           
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



// This file contains an opening book with theory lines and replies to different
// opening moves.
//
// The majority of the moves have been taken from online Chess databases
// (specially from 365chess.com) and then further analyzed with Stockfish 7.0 to
// avoid opening flaws.
#include <algorithm>
#include <iostream>
#include <sstream>
#include <map>
#include <time.h>
#include <vector>
#include "book.h"
#include "app.h"

using namespace std;


unordered_map<string, string> book;



// initBook
//
// Fill in the openings book with all the theory lines.
void initBook()
{
        // Note: this opening book (book[]) holds a selected set of opening
        // lines that are preferred by the author of this application.


        // White opening
        book["%"] = "e4";


        // first-move replies for Black
        book["1. e4"] = "e5";
        book["1. d4"] = "Nf6";
        book["1. Nf3"] = "Nf6";
        book["1. c4"] = "Nf6";
        book["1. g3"] = "d5";
        book["1. b3"] = "e5";
        book["1. f4"] = "d5";
        book["1. Nc3"] = "d5";
        book["1. b4"] = "e5";


        // 2-ply move for White
        book["1. e4 e5"] = "Nf3";
        book["1. e4 c5"] = "Nf3";
        book["1. e4 c6"] = "d4";
        book["1. e4 e6"] = "d4";
        book["1. e4 Nf6"] = "e5";
        book["1. e4 d6"] = "d4";
        book["1. e4 d5"] = "exd5";


        // B02 Alekhine's defence -- WHITE
        book["1. e4 Nf6 2. e5 Ng8"] = "d4";
        book["1. e4 Nf6 2. e5 Ne4"] = "d3";
        book["1. e4 Nf6 2. e5 Ne4 3. d3 Nc5"] = "d4";
        book["1. e4 Nf6 2. e5 Nd5"] = "d4";
        book["1. e4 Nf6 2. e5 Nd5 3. d4 d6"] = "Nf3";

        book["1. e4 Nf6 2. e5 Nd5 3. d4 d6 4. Nf3 Bg4"] = "Be2";
        book["1. e4 Nf6 2. e5 Nd5 3. d4 d6 4. Nf3 Bg4 5. Be2 e6"] = "0-0";
        book["1. e4 Nf6 2. e5 Nd5 3. d4 d6 4. Nf3 Bg4 5. Be2 Nc6"] = "c4";
        book["1. e4 Nf6 2. e5 Nd5 3. d4 d6 4. Nf3 Bg4 5. Be2 Nc6 6. c4 Nb6"] = "exd6";
        book["1. e4 Nf6 2. e5 Nd5 3. d4 d6 4. Nf3 Bg4 5. Be2 Nc6 6. c4 Nb6 7. exd6 exd6"] = "Nc3";
        book["1. e4 Nf6 2. e5 Nd5 3. d4 d6 4. Nf3 Bg4 5. Be2 Nc6 6. c4 Nb6 7. exd6 cxd6"] = "d5";
        book["1. e4 Nf6 2. e5 Nd5 3. d4 d6 4. Nf3 Bg4 5. Be2 Nc6 6. c4 Nb6 7. exd6 Qxd6"] = "c5";
        book["1. e4 Nf6 2. e5 Nd5 3. d4 d6 4. Nf3 Bg4 5. Be2 c6"] = "c4";
        book["1. e4 Nf6 2. e5 Nd5 3. d4 d6 4. Nf3 Bg4 5. Be2 c6 6. c4 Nb6"] = "Qb3";

        book["1. e4 Nf6 2. e5 Nd5 3. d4 d6 4. Nf3 dxe5"] = "Nxe5";
        book["1. e4 Nf6 2. e5 Nd5 3. d4 Nb6"] = "a4";
        book["1. e4 Nf6 2. e5 Nd5 3. d4 Nb6 4. a4 a5"] = "Nf3";


        // B01 Scandinavian (centre counter) defence -- WHITE
        book["1. e4 d5 2. exd5 Nf6"] = "Nf3";

        book["1. e4 d5 2. exd5 Nf6 3. Nf3 Nxd5"] = "d4";
        book["1. e4 d5 2. exd5 Nf6 3. Nf3 Nxd5 4. d4 g6"] = "c4";
        book["1. e4 d5 2. exd5 Nf6 3. Nf3 Nxd5 4. d4 c6"] = "c4"; 
        book["1. e4 d5 2. exd5 Nf6 3. Nf3 Nxd5 4. d4 Bf5"] = "Bd3";
        book["1. e4 d5 2. exd5 Nf6 3. Nf3 Nxd5 4. d4 Bf5 5. Bd3 Bxd3"] = "Qxd3";
        book["1. e4 d5 2. exd5 Nf6 3. Nf3 Nxd5 4. d4 Nb6"] = "a4";
        book["1. e4 d5 2. exd5 Nf6 3. Nf3 Nxd5 4. d4 Nf6"] = "Nc3";
        book["1. e4 d5 2. exd5 Nf6 3. Nf3 Nxd5 4. d4 e6"] = "c4";
        book["1. e4 d5 2. exd5 Nf6 3. Nf3 Nxd5 4. d4 Bg4"] = "c4";
        book["1. e4 d5 2. exd5 Nf6 3. Nf3 Nxd5 4. d4 Bg4 5. c4 Nb6"] = "c5";
        book["1. e4 d5 2. exd5 Nf6 3. Nf3 Nxd5 4. d4 Bg4 5. c4 Nf6"] = "Be2";
        book["1. e4 d5 2. exd5 Nf6 3. Nf3 Nxd5 4. d4 Bg4 5. c4 Nb4"] = "Qa4+";

        book["1. e4 d5 2. exd5 Nf6 3. Nf3 Bg4"] = "Bb5+";
        book["1. e4 d5 2. exd5 Nf6 3. Nf3 Bg4 4. Bb5+ c6"] = "dxc6";
        book["1. e4 d5 2. exd5 Nf6 3. Nf3 Bg4 4. Bb5+ Nbd7"] = "Nc3";
        book["1. e4 d5 2. exd5 Nf6 3. Nf3 Bg4 4. Bb5+ Nbd7 5. Nc3 g6"] = "d4";
        book["1. e4 d5 2. exd5 Nf6 3. Nf3 Bg4 4. Bb5+ Nbd7 5. Nc3 g6 6. d4 Bg7"] = "h3";
        book["1. e4 d5 2. exd5 Nf6 3. Nf3 Bg4 4. Bb5+ Nbd7 5. Nc3 a6"] = "Be2";
        book["1. e4 d5 2. exd5 Nf6 3. Nf3 Bg4 4. Bb5+ Nbd7 5. Nc3 a6 6. Be2 Nb6"] = "d4";

        book["1. e4 d5 2. exd5 Nf6 3. Nf3 Qxd5"] = "d4";
        book["1. e4 d5 2. exd5 Nf6 3. Nf3 Qxd5 4. d4 Qd8"] = "Bd3";
        book["1. e4 d5 2. exd5 Nf6 3. Nf3 Qxd5 4. d4 Bg4"] = "Be2";

        book["1. e4 d5 2. exd5 Qxd5"] = "Nc3";
        book["1. e4 d5 2. exd5 Qxd5 3. Nc3 Qa5"] = "d4";
        book["1. e4 d5 2. exd5 Qxd5 3. Nc3 Qa5 4. d4 Nf6"] = "Nf3";
        book["1. e4 d5 2. exd5 Qxd5 3. Nc3 Qa5 4. d4 c6"] = "Bd2";
        book["1. e4 d5 2. exd5 Qxd5 3. Nc3 Qa5 4. d4 e5"] = "Nf3";
        book["1. e4 d5 2. exd5 Qxd5 3. Nc3 Qa5 4. d4 e6"] = "Nf3";
        book["1. e4 d5 2. exd5 Qxd5 3. Nc3 Qa5 4. d4 Bf5"] = "Qf3";

        book["1. e4 d5 2. exd5 Qxd5 3. Nc3 Qd7"] = "d4";
        book["1. e4 d5 2. exd5 Qxd5 3. Nc3 Qd7 4. d4 Qd8"] = "Bc4";
        book["1. e4 d5 2. exd5 Qxd5 3. Nc3 Qd7 4. d4 Nf6"] = "Nf3";


        book["1. e4 d5 2. exd5 Qxd5 3. Nc3 Qd6"] = "d4";
        book["1. e4 d5 2. exd5 Qxd5 3. Nc3 Qd6 4. d4 c6"] = "Nf3";
        book["1. e4 d5 2. exd5 Qxd5 3. Nc3 Qd6 4. d4 c6 5. Nf3 Nf6"] = "Be2";
        book["1. e4 d5 2. exd5 Qxd5 3. Nc3 Qd6 4. d4 a6"] = "Nf3";
        book["1. e4 d5 2. exd5 Qxd5 3. Nc3 Qd6 4. d4 a6 5. Nf3 Nf6"] = "g3";
        book["1. e4 d5 2. exd5 Qxd5 3. Nc3 Qd6 4. d4 Nf6"] = "Nf3";
        book["1. e4 d5 2. exd5 Qxd5 3. Nc3 Qd6 4. d4 Nf6 5. Nf3 c6"] = "Be3";
        book["1. e4 d5 2. exd5 Qxd5 3. Nc3 Qd6 4. d4 Nf6 5. Nf3 a6"] = "g3";
        book["1. e4 d5 2. exd5 Qxd5 3. Nc3 Qd6 4. d4 Nf6 5. Nf3 a6 6. g3 Nc6"] = "Bf4";
        book["1. e4 d5 2. exd5 Qxd5 3. Nc3 Qd6 4. d4 Nf6 5. Nf3 a6 6. g3 Nc6 7. Bf4 Qd8"] = "Bg2";
        book["1. e4 d5 2. exd5 Qxd5 3. Nc3 Qd6 4. d4 Nf6 5. Nf3 a6 6. g3 Bg4"] = "h3";


        book["1. e4 d5 2. exd5 Qxd5 3. Nc3 Qd8"] = "d4";
        book["1. e4 d5 2. exd5 Qxd5 3. Nc3 Qd8 4. d4 e5"] = "Nf3";
        book["1. e4 d5 2. exd5 Qxd5 3. Nc3 Qd8 4. d4 e6"] = "Nf3";
        book["1. e4 d5 2. exd5 Qxd5 3. Nc3 Qd8 4. d4 c6"] = "Nf3";
        book["1. e4 d5 2. exd5 Qxd5 3. Nc3 Qd8 4. d4 Nc6"] = "d5";
        book["1. e4 d5 2. exd5 Qxd5 3. Nc3 Qd8 4. d4 Nc6 5. d5 Nb8"] = "Bf4";
        book["1. e4 d5 2. exd5 Qxd5 3. Nc3 Qd8 4. d4 Nc6 5. d5 Ne5"] = "Qe2";
        book["1. e4 d5 2. exd5 Qxd5 3. Nc3 Qd8 4. d4 Nf6"] = "Nf3";
        book["1. e4 d5 2. exd5 Qxd5 3. Nc3 Qd8 4. d4 f5"] = "Nf3";
        book["1. e4 d5 2. exd5 Qxd5 3. Nc3 Qd8 4. d4 f5 5. Nf3 e6"] = "Bc4";
        book["1. e4 d5 2. exd5 Qxd5 3. Nc3 Qd8 4. d4 f5 5. Nf3 Nc6"] = "d5";
        book["1. e4 d5 2. exd5 Qxd5 3. Nc3 Qd8 4. d4 f5 5. Nf3 Nc6 6. d5 Na5"] = "b4";
        book["1. e4 d5 2. exd5 Qxd5 3. Nc3 Qd8 4. d4 f5 5. Nf3 Nc6 6. d5 Nb8"] = "Bc4";

        book["1. e4 d5 2. exd5 Qxd5 3. Nc3 Qe5+"] = "Be2";

		
        // C33 King's gambit accepted -- BLACK
		book["1. e4 e5 2. f4"] = "exf4";
		book["1. e4 e5 2. f4 exf4 3. Bc4"] = "Qh4+";
		book["1. e4 e5 2. f4 exf4 3. Bc4 Qh4+ 4. Ke2"] = "f5";
		book["1. e4 e5 2. f4 exf4 3. Bc4 Qh4+ 4. Kf1"] = "Nf6";
		book["1. e4 e5 2. f4 exf4 3. Nc3"] = "Qh4+";
		book["1. e4 e5 2. f4 exf4 3. Nc3 Qh4+ 4. Ke2"] = "d6";
		book["1. e4 e5 2. f4 exf4 3. Nf3"] = "g5";
		book["1. e4 e5 2. f4 exf4 3. Nf3 g5 4. h4"] = "g4";
		book["1. e4 e5 2. f4 exf4 3. Nf3 g5 4. h3"] = "h6";
		book["1. e4 e5 2. f4 exf4 3. Nf3 g5 4. d4"] = "g4";
		book["1. e4 e5 2. f4 exf4 3. Nf3 g5 4. Nc3"] = "Bg7";
		book["1. e4 e5 2. f4 exf4 3. Nf3 g5 4. Bc4"] = "Bg7";
		book["1. e4 e5 2. f4 exf4 3. Nf3 g5 4. Bc4 Bg7 5. d4"] = "d6";
		book["1. e4 e5 2. f4 exf4 3. Nf3 g5 4. Bc4 Bg7 5. h4"] = "h6";
		book["1. e4 e5 2. f4 exf4 3. Nf3 g5 4. Bc4 Bg7 5. 0-0"] = "h6";
		book["1. e4 e5 2. f4 exf4 3. Nf3 g5 4. Bc4 Bg7 5. 0-0 h6 6. d4"] = "Nc6";


        // C23 Bishop's opening -- BLACK
        book["1. e4 e5 2. Bc4"] = "Nf6";
        book["1. e4 e5 2. Bc4 Nf6 3. d3"] = "c6";
        book["1. e4 e5 2. Bc4 Nf6 3. Nc3"] = "Bc5";
        book["1. e4 e5 2. Bc4 Nf6 3. Nc3 Bc5 4. d3"] = "d6";
        book["1. e4 e5 2. Bc4 Nf6 3. Nc3 Bc5 4. f4"] = "d6";
        book["1. e4 e5 2. Bc4 Nf6 3. Nc3 Bc5 4. Nf3"] = "d6";


        // C40 King's knight opening -- WHITE
        book["1. e4 e5 2. Nf3 Bc5"] = "Nxe5";
        book["1. e4 e5 2. Nf3 Bc5 3. Nxe5 d6"] = "Nc4";
        book["1. e4 e5 2. Nf3 Bc5 3. Nxe5 Nf6"] = "d4";
        book["1. e4 e5 2. Nf3 Bc5 3. Nxe5 Nc6"] = "Nxc6";
        book["1. e4 e5 2. Nf3 Bc5 3. Nxe5 Nc6 4. Nxc6 dxc6"] = "c3";
        book["1. e4 e5 2. Nf3 Bc5 3. Nxe5 Nc6 4. Nxc6 bxc6"] = "d4";
        book["1. e4 e5 2. Nf3 Bc5 3. Nxe5 Qh5"] = "d4";
        book["1. e4 e5 2. Nf3 Bc5 3. Nxe5 Qh5 4. d4 d6"] = "Nxf7";
        book["1. e4 e5 2. Nf3 Bc5 3. Nxe5 Qh5 4. d4 Qxe4+"] = "Be3";


        // C42 Petrov's defence -- WHITE
        book["1. e4 e5 2. Nf3 Nf6"] = "Nxe5";
        book["1. e4 e5 2. Nf3 Nf6 3. Nxe5 Nxe4"] = "Qe2";
        book["1. e4 e5 2. Nf3 Nf6 3. Nxe5 Qe7"] = "d4";
        book["1. e4 e5 2. Nf3 Nf6 3. Nxe5 Qe7 4. d4 Nc6"] = "Nc3";
        book["1. e4 e5 2. Nf3 Nf6 3. Nxe5 Qe7 4. d4 d6"] = "Nf3";
        book["1. e4 e5 2. Nf3 Nf6 3. Nxe5 Qe7 4. d4 d6 5. Nf3 Nxe4"] = "Be2";
        book["1. e4 e5 2. Nf3 Nf6 3. Nxe5 Qe7 4. d4 d6 5. Nf3 Qxe4+"] = "Be2";
        book["1. e4 e5 2. Nf3 Nf6 3. Nxe5 Qe7 4. d4 d6 5. Nf3 Qxe4+ 6. Be2 Bf5"] = "Na3";

        book["1. e4 e5 2. Nf3 Nf6 3. Nxe5 d6 4. Nf3 Qe7"] = "Nc3";
        book["1. e4 e5 2. Nf3 Nf6 3. Nxe5 d6 4. Nf3 Qe7 5. Nc3 d5"] = "e5";
        book["1. e4 e5 2. Nf3 Nf6 3. Nxe5 d6 4. Nf3 Qe7 5. Nc3 c6"] = "Bd3";

        book["1. e4 e5 2. Nf3 Nf6 3. Nxe5 d6"] = "Nf3";
        book["1. e4 e5 2. Nf3 Nf6 3. Nxe5 d6 4. Nf3 Nxe4"] = "d4";
        book["1. e4 e5 2. Nf3 Nf6 3. Nxe5 d6 4. Nf3 Nxe4 5. d4 d5"] = "Bd3";
        book["1. e4 e5 2. Nf3 Nf6 3. Nxe5 d6 4. Nf3 Nxe4 5. d4 d5 6. Bd3 Nc6"] = "0-0";
        book["1. e4 e5 2. Nf3 Nf6 3. Nxe5 d6 4. Nf3 Nxe4 5. d4 d5 6. Bd3 Nc6 7. 0-0 Be7"] = "Nbd2";
        book["1. e4 e5 2. Nf3 Nf6 3. Nxe5 d6 4. Nf3 Nxe4 5. d4 d5 6. Bd3 Bd6"] = "0-0";
        book["1. e4 e5 2. Nf3 Nf6 3. Nxe5 d6 4. Nf3 Nxe4 5. d4 d5 6. Bd3 Bd6 7. 0-0 0-0"] = "c4";
        book["1. e4 e5 2. Nf3 Nf6 3. Nxe5 d6 4. Nf3 Nxe4 5. d4 d5 6. Bd3 Nd6"] = "0-0";
        book["1. e4 e5 2. Nf3 Nf6 3. Nxe5 d6 4. Nf3 Nxe4 5. d4 d5 6. Bd3 Nd6 7. 0-0 Be7"] = "c3";
        book["1. e4 e5 2. Nf3 Nf6 3. Nxe5 d6 4. Nf3 Nxe4 5. d4 d5 6. Bd3 Bf5"] = "0-0";
        book["1. e4 e5 2. Nf3 Nf6 3. Nxe5 d6 4. Nf3 Nxe4 5. d4 d5 6. Bd3 Bf5 7. 0-0 Be7"] = "Re1";
        book["1. e4 e5 2. Nf3 Nf6 3. Nxe5 d6 4. Nf3 Nxe4 5. d4 d5 6. Bd3 f5"] = "c4";
        book["1. e4 e5 2. Nf3 Nf6 3. Nxe5 d6 4. Nf3 Nxe4 5. d4 d5 6. Bd3 Nf6"] = "0-0";
        book["1. e4 e5 2. Nf3 Nf6 3. Nxe5 d6 4. Nf3 Nxe4 5. d4 d5 6. Bd3 Nf6 7. 0-0 Be7"] = "Re1";
        book["1. e4 e5 2. Nf3 Nf6 3. Nxe5 d6 4. Nf3 Nxe4 5. d4 d5 6. Bd3 Bg4"] = "h3";
        book["1. e4 e5 2. Nf3 Nf6 3. Nxe5 d6 4. Nf3 Nxe4 5. d4 d5 6. Bd3 Bg4 7. h3 Bf5"] = "0-0";
        book["1. e4 e5 2. Nf3 Nf6 3. Nxe5 d6 4. Nf3 Nxe4 5. d4 d5 6. Bd3 Bg4 7. h3 Bh5"] = "0-0";
        book["1. e4 e5 2. Nf3 Nf6 3. Nxe5 d6 4. Nf3 Nxe4 5. d4 d5 6. Bd3 Bg4 7. h3 Bxf3"] = "Qxf3";
        book["1. e4 e5 2. Nf3 Nf6 3. Nxe5 d6 4. Nf3 Nxe4 5. d4 d5 6. Bd3 Bb4+"] = "c3";
        book["1. e4 e5 2. Nf3 Nf6 3. Nxe5 d6 4. Nf3 Nxe4 5. d4 d5 6. Bd3 Bb4+ 7. c3 Bd6"] = "Qb3";
        book["1. e4 e5 2. Nf3 Nf6 3. Nxe5 d6 4. Nf3 Nxe4 5. d4 d5 6. Bd3 Be6"] = "0-0";
        book["1. e4 e5 2. Nf3 Nf6 3. Nxe5 d6 4. Nf3 Nxe4 5. d4 d5 6. Bd3 Be6 7. 0-0 Be7"] = "c4";
        book["1. e4 e5 2. Nf3 Nf6 3. Nxe5 d6 4. Nf3 Nxe4 5. d4 d5 6. Bd3 Qe7"] = "0-0";
        book["1. e4 e5 2. Nf3 Nf6 3. Nxe5 d6 4. Nf3 Nxe4 5. d4 d5 6. Bd3 c6"] = "0-0";
        book["1. e4 e5 2. Nf3 Nf6 3. Nxe5 d6 4. Nf3 Nxe4 5. d4 d5 6. Bd3 Be7"] = "0-0";
        book["1. e4 e5 2. Nf3 Nf6 3. Nxe5 d6 4. Nf3 Nxe4 5. d4 d5 6. Bd3 Be7 7. 0-0 Nc6"] = "Nbd2";
        book["1. e4 e5 2. Nf3 Nf6 3. Nxe5 d6 4. Nf3 Nxe4 5. d4 d5 6. Bd3 Be7 7. 0-0 0-0"] = "Re1";
        book["1. e4 e5 2. Nf3 Nf6 3. Nxe5 d6 4. Nf3 Nxe4 5. d4 d5 6. Bd3 Be7 7. 0-0 0-0 8. Re1 Bf5"] = "c4";
        book["1. e4 e5 2. Nf3 Nf6 3. Nxe5 d6 4. Nf3 Nxe4 5. d4 d5 6. Bd3 Be7 7. 0-0 0-0 8. Re1 Nc6"] = "Bxe4";
        book["1. e4 e5 2. Nf3 Nf6 3. Nxe5 d6 4. Nf3 Nxe4 5. d4 d5 6. Bd3 Be7 7. 0-0 0-0 8. Re1 Nc6 9. Bxe4 dxe4"] = "Rxe4";
        book["1. e4 e5 2. Nf3 Nf6 3. Nxe5 d6 4. Nf3 Nxe4 5. d4 d5 6. Bd3 Be7 7. 0-0 0-0 8. Re1 Nf6"] = "Bf4";
        book["1. e4 e5 2. Nf3 Nf6 3. Nxe5 d6 4. Nf3 Nxe4 5. d4 d5 6. Bd3 Be7 7. 0-0 0-0 8. Re1 Nf6 9. Bf4 c5"] = "c3";

        book["1. e4 e5 2. Nf3 Nf6 3. Nxe5 d6 4. Nf3 Nxe4 5. d4 Nc6"] = "Bd3";
        book["1. e4 e5 2. Nf3 Nf6 3. Nxe5 d6 4. Nf3 Nxe4 5. d4 Nc6 6. Bd3 d5"] = "0-0";
        book["1. e4 e5 2. Nf3 Nf6 3. Nxe5 d6 4. Nf3 Nxe4 5. d4 Nc6 6. Bd3 d5 7. 0-0 Be7"] = "Nbd2";
        book["1. e4 e5 2. Nf3 Nf6 3. Nxe5 d6 4. Nf3 Nxe4 5. d4 Nc6 6. Bd3 d5 7. 0-0 Be7 8. Nbd2 Nd6"] = "c3";
        book["1. e4 e5 2. Nf3 Nf6 3. Nxe5 d6 4. Nf3 Nxe4 5. d4 Nc6 6. Bd3 d5 7. 0-0 Bf5"] = "Re1";
        book["1. e4 e5 2. Nf3 Nf6 3. Nxe5 d6 4. Nf3 Nxe4 5. d4 Nc6 6. Bd3 d5 7. 0-0 Bf5 8. Re1 Be7"] = "c4";
        book["1. e4 e5 2. Nf3 Nf6 3. Nxe5 d6 4. Nf3 Nxe4 5. d4 Nc6 6. Bd3 d5 7. 0-0 Bf5 8. Re1 Qe7"] = "c4";
        book["1. e4 e5 2. Nf3 Nf6 3. Nxe5 d6 4. Nf3 Nxe4 5. d4 Nc6 6. Bd3 Nf6"] = "0-0";
        book["1. e4 e5 2. Nf3 Nf6 3. Nxe5 d6 4. Nf3 Nxe4 5. d4 Nc6 6. Bd3 Nf6 7. 0-0 d5"] = "c3";
        book["1. e4 e5 2. Nf3 Nf6 3. Nxe5 d6 4. Nf3 Nxe4 5. d4 Nc6 6. Bd3 Nf6 7. 0-0 Be7"] = "c3";
        book["1. e4 e5 2. Nf3 Nf6 3. Nxe5 d6 4. Nf3 Nxe4 5. d4 Nc6 6. Bd3 f5"] = "d5";

        book["1. e4 e5 2. Nf3 Nf6 3. Nxe5 d6 4. Nf3 Nxe4 5. d4 Be7"] = "Bd3";
        book["1. e4 e5 2. Nf3 Nf6 3. Nxe5 d6 4. Nf3 Nxe4 5. d4 Be7 6. Bd3 d5"] = "0-0";
        book["1. e4 e5 2. Nf3 Nf6 3. Nxe5 d6 4. Nf3 Nxe4 5. d4 Be7 6. Bd3 d5 7. 0-0 Nc6"] = "Nbd2";
        book["1. e4 e5 2. Nf3 Nf6 3. Nxe5 d6 4. Nf3 Nxe4 5. d4 Be7 6. Bd3 d5 7. 0-0 Nf6"] = "Re1";


        // C41 Philidor's defence -- WHITE
        book["1. e4 e5 2. Nf3 d6"] = "d4";

        book["1. e4 e5 2. Nf3 d6 3. d4 exd4"] = "Nxd4";

        book["1. e4 e5 2. Nf3 d6 3. d4 exd4 4. Nxd4 Nf6"] = "Nc3";
        book["1. e4 e5 2. Nf3 d6 3. d4 exd4 4. Nxd4 Nf6 5. Nc3 Bd7"] = "Be3";
        book["1. e4 e5 2. Nf3 d6 3. d4 exd4 4. Nxd4 Nf6 5. Nc3 Be7"] = "Bf4";
        book["1. e4 e5 2. Nf3 d6 3. d4 exd4 4. Nxd4 Nf6 5. Nc3 Be7 6. Bf4 0-0"] = "Qd2";
        book["1. e4 e5 2. Nf3 d6 3. d4 exd4 4. Nxd4 Nf6 5. Nc3 Be7 6. Bf4 0-0"] = "Qd2";
        book["1. e4 e5 2. Nf3 d6 3. d4 exd4 4. Nxd4 Nf6 5. Nc3 c6"] = "Be3";
        book["1. e4 e5 2. Nf3 d6 3. d4 exd4 4. Nxd4 Nf6 5. Nc3 c5"] = "Bb5+";
        book["1. e4 e5 2. Nf3 d6 3. d4 exd4 4. Nxd4 Nf6 5. Nc3 Nbd7"] = "g4";
        book["1. e4 e5 2. Nf3 d6 3. d4 exd4 4. Nxd4 Nf6 5. Nc3 g6"] = "Be3";
        book["1. e4 e5 2. Nf3 d6 3. d4 exd4 4. Nxd4 Nf6 5. Nc3 g6 6. Be3 Ng4"] = "Bf4";
        book["1. e4 e5 2. Nf3 d6 3. d4 exd4 4. Nxd4 Nf6 5. Nc3 g6 6. Be3 Ng4 7. Bf4 Bg7"] = "f3";
        book["1. e4 e5 2. Nf3 d6 3. d4 exd4 4. Nxd4 Nf6 5. Nc3 g6 6. Be3 Bg7"] = "Qd2";
        book["1. e4 e5 2. Nf3 d6 3. d4 exd4 4. Nxd4 Nf6 5. Nc3 g6 6. Be3 Bg7 7. Qd2 0-0"] = "0-0-0";
        book["1. e4 e5 2. Nf3 d6 3. d4 exd4 4. Nxd4 Nf6 5. Nc3 g6 6. Be3 Bg7 7. Qd2 Nc6"] = "f3";

        book["1. e4 e5 2. Nf3 d6 3. d4 exd4 4. Nxd4 g6"] = "Nc3";
        book["1. e4 e5 2. Nf3 d6 3. d4 exd4 4. Nxd4 g6 5. Nc3 Bg7"] = "Be3";
        book["1. e4 e5 2. Nf3 d6 3. d4 exd4 4. Nxd4 g6 5. Nc3 Nf6"] = "Be3";
        book["1. e4 e5 2. Nf3 d6 3. d4 exd4 4. Nxd4 g6 5. Nc3 Nf6 6. Be3 Bg7"] = "Qd2";
        book["1. e4 e5 2. Nf3 d6 3. d4 exd4 4. Nxd4 g6 5. Nc3 Nf6 6. Be3 Bg7 7. Qd2 0-0"] = "0-0-0";
        book["1. e4 e5 2. Nf3 d6 3. d4 exd4 4. Nxd4 Be7"] = "Bd3";
        book["1. e4 e5 2. Nf3 d6 3. d4 exd4 4. Nxd4 Nc6"] = "Nc3";
        book["1. e4 e5 2. Nf3 d6 3. d4 exd4 4. Nxd4 Nd7"] = "Nc3";
        book["1. e4 e5 2. Nf3 d6 3. d4 exd4 4. Nxd4 d5"] = "exd5";
        book["1. e4 e5 2. Nf3 d6 3. d4 exd4 4. Nxd4 d5 5. exd5 Qxd5"] = "Qe2+";
        book["1. e4 e5 2. Nf3 d6 3. d4 exd4 4. Nxd4 c5"] = "Ne2";
        book["1. e4 e5 2. Nf3 d6 3. d4 exd4 4. Nxd4 Bd7"] = "Nc3";
        book["1. e4 e5 2. Nf3 d6 3. d4 exd4 4. Nxd4 h6"] = "c4";
        book["1. e4 e5 2. Nf3 d6 3. d4 exd4 4. Nxd4 a6"] = "c4";
        book["1. e4 e5 2. Nf3 d6 3. d4 exd4 4. Nxd4 a6 5. c4 g6"] = "Nc3";
        book["1. e4 e5 2. Nf3 d6 3. d4 exd4 4. Nxd4 a6 5. c4 g6 6. Nc3 Bg7"] = "Be3";
        book["1. e4 e5 2. Nf3 d6 3. d4 exd4 4. Nxd4 a6 5. c4 Nf6"] = "Nc3";
        book["1. e4 e5 2. Nf3 d6 3. d4 exd4 4. Nxd4 a6 5. c4 Be7"] = "Nc3";
        book["1. e4 e5 2. Nf3 d6 3. d4 exd4 4. Nxd4 a6 5. c4 Ne7"] = "Be3";
        book["1. e4 e5 2. Nf3 d6 3. d4 exd4 4. Nxd4 a6 5. c4 Bd7"] = "Be2";

        book["1. e4 e5 2. Nf3 d6 3. d4 Nf6"] = "dxe5";
        book["1. e4 e5 2. Nf3 d6 3. d4 Nf6 4. dxe5 Nxe4"] = "Bc4";
        book["1. e4 e5 2. Nf3 d6 3. d4 Nd7"] = "Bc4";


        // C41 B00 King's pawn opening -- WHITE
        book["1. e4 d6 2. d4 Nf6"] = "Nc3";
        book["1. e4 d6 2. d4 Nf6 3. Nc3 g6"] = "f4";
        book["1. e4 d6 2. d4 Nf6 3. Nc3 e5"] = "Nf3";
        book["1. e4 d6 2. d4 Nf6 3. Nc3 c6"] = "f4";

        book["1. e4 d6 2. d4 g6"] = "Nc3";
        book["1. e4 d6 2. d4 g6 3. Nc3 Bg7"] = "f4";
        book["1. e4 d6 2. d4 g6 3. Nc3 Bg7 4. f4 Nf6"] = "Nf3";
        book["1. e4 d6 2. d4 g6 3. Nc3 Bg7 4. f4 Nf6 5. Nf3 0-0"] = "Bd3";
        book["1. e4 d6 2. d4 g6 3. Nc3 Nf6"] = "f4";
        book["1. e4 d6 2. d4 g6 3. Nc3 Nf6 4. f4 Bg7"] = "NF3";
        book["1. e4 d6 2. d4 g6 3. Nc3 Nf6 4. f4 Bg7 5. NF3 0-0"] = "Bd3";


        // C60 Ruy Lopez (Spanish opening) -- WHITE
        book["1. e4 e5 2. Nf3 Nc6"] = "Bb5";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6"] = "Ba4";

        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 f6"] = "0-0";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 f6 4. 0-0 d6"] = "d4";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 f6 4. 0-0 Nge7"] = "d4";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 f6 4. 0-0 a6"] = "Bc4";

        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6"] = "0-0";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4"] = "d4";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. d4 Nd6"] = "Bxc6";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. d4 Nd6 6. Bxc6 bxc6"] = "dxe5";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. d4 Nd6 6. Bxc6 dxc6 7. dxe5 Nc4"] = "Qe2";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. d4 Nd6 6. Bxc6 dxc6 7. dxe5 Ne4"] = "Qe2";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. d4 Nd6 6. Bxc6 dxc6 7. dxe5 Nf5"] = "Qxd8+";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. d4 Nd6 6. Bxc6 dxc6 7. dxe5 Nf5 8. Qxd8+ Kxd8"] = "Nc3";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. d4 Nd6 6. Bxc6 dxc6 7. dxe5 Nf5 8. Qxd8+ Kxd8 9. Nc3 Be7"] = "h3";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. d4 Nd6 6. Bxc6 dxc6 7. dxe5 Nf5 8. Qxd8+ Kxd8 9. Nc3 h6"] = "Rd1+";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. d4 Nd6 6. Bxc6 dxc6 7. dxe5 Nf5 8. Qxd8+ Kxd8 9. Nc3 h6 10. Rd1+ Ke8"] = "b3";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. d4 Nd6 6. Bxc6 dxc6 7. dxe5 Nf5 8. Qxd8+ Kxd8 9. Nc3 Be6"] = "Rd1+";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. d4 Nd6 6. Bxc6 dxc6 7. dxe5 Nf5 8. Qxd8+ Kxd8 9. Nc3 Be6 10. Rd1+ Ke8"] = "Ng5";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. d4 Nd6 6. Bxc6 dxc6 7. dxe5 Nf5 8. Qxd8+ Kxd8 9. Nc3 Ke8"] = "Rd1";

        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. d4 Be7"] = "Qe2";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. d4 d6"] = "Qe2";

        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. d4 exd4"] = "Re1";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. d4 exd4 6. Re1 f5"] = "Nxd4";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. d4 exd4 6. Re1 f5 7. Nxd4 Nxd4"] = "Qxd4";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. d4 exd4 6. Re1 d5"] = "Nxd4";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. d4 exd4 6. Re1 d5 7. Nxd4 Bd6"] = "Nxc6";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. d4 exd4 6. Re1 d5 7. Nxd4 Bd6 8. Nxc6 Bxh2+"] = "Kh1";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. d4 exd4 6. Re1 d5 7. Nxd4 Bd6 8. Nxc6 Bxh2+ 9. Kh1 Qh4"] = "Rxe4+";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. d4 exd4 6. Re1 d5 7. Nxd4 Bd6 8. Nxc6 Bxh2+ 9. Kh1 Qh4 10. Rxe4+ dxe4"] = "Qd8+";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. d4 exd4 6. Re1 d5 7. Nxd4 Bd6 8. Nxc6 Bxh2+ 9. Kh1 Qh4 10. Rxe4+ Qxe4"] = "Nd2";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. d4 exd4 6. Re1 d5 7. Nxd4 Bc5"] = "Bxc6+";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. d4 exd4 6. Re1 d5 7. Nxd4 Bc5 8. Bxc6+ bxc6"] = "f3";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. d4 exd4 6. Re1 d5 7. Nxd4 Bc5 8. Bxc6+ bxc6 9. f3 Qh4"] = "g3";

        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. d4 a6"] = "Ba4";

        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Bc5"] = "Nxe5";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Bc5 5. Nxe5 Nxe4"] = "Qg4";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Bc5 5. Nxe5 0-0"] = "Bxc6";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Bc5 5. Nxe5 0-0 6. Bxc6 dxc6"] = "d3";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Bc5 5. Nxe5 0-0 6. Bxc6 bxc6"] = "d4";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Bc5 5. Nxe5 Nd4"] = "Ba4";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Bc5 5. Nxe5 Qe7"] = "Nf3";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Bc5 5. Nxe5 Nxe5"] = "d4";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Bc5 5. Nxe5 Nxe5 6. d4 c6"] = "dxe5";

        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 d6"] = "d4";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Be7"] = "Re1";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 a6"] = "Bxc6";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 a6 5. Bxc6 bxc6"] = "Nxe5";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 a6 5. Bxc6 dxc6"] = "Nxe5";

        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 g6"] = "c3";

        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 f5"] = "Nc3";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 f5 4. Nc3 fxe4"] = "Nxe4";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 f5 4. Nc3 Nf6"] = "exf5";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 f5 4. Nc3 Nd4"] = "Nxe5";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 f5 4. Nc3 Bb4"] = "exf5";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 f5 4. Nc3 d6"] = "d4";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 f5 4. Nc3 d6 5. d4 Ne7"] = "exf5";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 f5 4. Nc3 d6 5. d4 Ne7 6. exf5 Nxf5"] = "d5";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 f5 4. Nc3 d6 5. d4 Ne7 6. exf5 Nxf5 7. d5 a6"] = "Ba4";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 f5 4. Nc3 d6 5. d4 Ne7 6. exf5 Nxf5 7. d5 a6 8. Ba4 b5"] = "Nxb5";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 f5 4. Nc3 d6 5. d4 Ne7 6. exf5 Bxf5"] = "0-0";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 f5 4. Nc3 d6 5. d4 Be7"] = "dxe5";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 f5 4. Nc3 d6 5. d4 Be7 6. dxe5 dxe5"] = "Qxd8+";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 f5 4. Nc3 d6 5. d4 Be7 6. dxe5 dxe5 7. Qxd8+ Bxd8"] = "Nxe5";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 f5 4. Nc3 d6 5. d4 Be7 6. dxe5 dxe5 7. Qxd8+ Kxd8"] = "Bxc6";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 f5 4. Nc3 d6 5. d4 Be7 6. dxe5 dxe5 7. Qxd8+ Kxd8 8. Bxc6 bxc6"] = "Nxe5";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 f5 4. Nc3 d6 5. d4 Bd7"] = "exf5";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 f5 4. Nc3 d6 5. d4 a6"] = "Nxd4";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 f5 4. Nc3 d6 5. d4 exd4"] = "Bxc6+";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 f5 4. Nc3 d6 5. d4 exd4 6. Bxc6+ bxc6"] = "dxe5";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 f5 4. Nc3 d6 5. d4 exd4 6. Bxc6+ bxc6 7. dxe5 dxe5"] = "Qxd8+";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 f5 4. Nc3 d6 5. d4 exd4 6. Bxc6+ bxc6 7. dxe5 dxe5 8. Qxd8+ Kxd8"] = "Nxe5";

        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nge7"] = "Nc3";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Bc5"] = "c3";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nd4"] = "Nxd4";

        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 d6"] = "d4";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 d6 4. d4 exd4"] = "Nxd4";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 d6 4. d4 exd4 5. Nxd4 Bd7"] = "Nc3";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 d6 4. d4 Bg4"] = "dxe5";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 d6 4. d4 Bg4 5. dxe5 dxe5"] = "Qd5";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 d6 4. d4 Bd7"] = "d5";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 d6 4. d4 Bd7 5. d5 Nce7"] = "Bxd7+";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 d6 4. d4 Bd7 5. d5 Nce7 6. Bxd7+ Qxd7"] = "c4";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 d6 4. d4 Bd7 5. d5 Nce7 6. Bxd7+ Qxd7 7. c4 Ng6"] = "Nc3";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 d6 4. d4 Bd7 5. d5 Nce7 6. Bxd7+ Qxd7 7. c4 Ng6 8. Nc3 Be7"] = "h4";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 d6 4. d4 Bd7 5. d5 Nce7 6. Bxd7+ Qxd7 7. c4 Ng6 8. Nc3 Nf6"] = "Bg5";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 d6 4. d4 Bd7 5. d5 Nce7 6. Bxd7+ Qxd7 7. c4 Ng6 8. Nc3 Nf6 9. Bg5 Be7"] = "Bxf6";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 d6 4. d4 Bd7 5. d5 Nce7 6. Bxd7+ Qxd7 7. c4 Ng6 8. Nc3 Nf6 9. Bg5 Be7 10. Bxf6 Bxf6"] = "g3";

        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Bd6"] = "0-0";

        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nd4 4. Nxd4 exd4"] = "0-0";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nd4 4. Nxd4 exd4 5. 0-0 c6"] = "Bc4";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nd4 4. Nxd4 exd4 5. 0-0 c6 6. Bc4 Nf6"] = "d3";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nd4 4. Nxd4 exd4 5. 0-0 c6 6. Bc4 Nf6 7. d3 d5"] = "exd5";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nd4 4. Nxd4 exd4 5. 0-0 c6 6. Bc4 Nf6 7. d3 d5 8. exd5 Nxd5"] = "Re1+";


        // C70 Ruy Lopez -- WHITE
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nf6"] = "0-0";

        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nf6 5. 0-0 Bc5"] = "c3";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nf6 5. 0-0 Bc5 6. c3 Nxe4"] = "d4";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nf6 5. 0-0 Bc5 6. c3 Nxe4 7. d4 exd4"] = "cxd4";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nf6 5. 0-0 Bc5 6. c3 Nxe4 7. d4 exd4 8. cxd4 Ba7"] = "d5";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nf6 5. 0-0 Bc5 6. c3 Nxe4 7. d4 exd4 8. cxd4 Bb6"] = "d5";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nf6 5. 0-0 Bc5 6. c3 Nxe4 7. d4 Ba7"] = "Nbd2";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nf6 5. 0-0 Bc5 6. c3 Nxe4 7. d4 Bb6"] = "Re1";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nf6 5. 0-0 Bc5 6. c3 Nxe4 7. d4 Bb6 8. Re1 d5"] = "Nxe5";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nf6 5. 0-0 Bc5 6. c3 Nxe4 7. d4 Bb6 8. Re1 f5"] = "Qb3";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nf6 5. 0-0 Bc5 6. c3 Bb6"] = "Re1";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nf6 5. 0-0 Bc5 6. c3 0-0"] = "d4";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nf6 5. 0-0 Bc5 6. c3 0-0 7. d4 Ba7"] = "dxe5";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nf6 5. 0-0 Bc5 6. c3 0-0 7. d4 Ba7 8. dxe5 Nxe4"] = "Qd5";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nf6 5. 0-0 Bc5 6. c3 0-0 7. d4 Bb6"] = "Re1";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nf6 5. 0-0 Bc5 6. c3 0-0 7. d4 exd4"] = "e5";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nf6 5. 0-0 Bc5 6. c3 0-0 7. d4 exd4 8. e5 Nd5"] = "cxd4";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nf6 5. 0-0 Bc5 6. c3 0-0 7. d4 exd4 8. e5 Ng5"] = "cxd4";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nf6 5. 0-0 Bc5 6. c3 0-0 7. d4 exd4 8. e5 Ne4"] = "cxd4";


        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nf6 5. 0-0 d6"] = "d4";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nf6 5. 0-0 Be7"] = "Re1";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nf6 5. 0-0 Be7 6. Re1 b5"] = "Bb3";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nf6 5. 0-0 Be7 6. Re1 b5 7. Bb3 0-0"] = "a4";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nf6 5. 0-0 Be7 6. Re1 b5 7. Bb3 0-0 8. a4 b4"] = "a5";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nf6 5. 0-0 Be7 6. Re1 b5 7. Bb3 0-0 8. a4 Bb7"] = "d3";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nf6 5. 0-0 Be7 6. Re1 b5 7. Bb3 0-0 8. a4 Bb7 9. d3 Bc5"] = "Nc3";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nf6 5. 0-0 Be7 6. Re1 b5 7. Bb3 0-0 8. a4 Bb7 9. d3 Bc5 10. Nc3 b4"] = "Nd5";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nf6 5. 0-0 Be7 6. Re1 b5 7. Bb3 0-0 8. a4 Bb7 9. d3 Bc5 10. Nc3 Na5"] = "Ba2";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nf6 5. 0-0 Be7 6. Re1 b5 7. Bb3 0-0 8. a4 Bb7 9. d3 Na5"] = "Ba2";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nf6 5. 0-0 Be7 6. Re1 b5 7. Bb3 0-0 8. a4 Bb7 9. d3 b4"] = "a5";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nf6 5. 0-0 Be7 6. Re1 b5 7. Bb3 0-0 8. a4 Bb7 9. d3 d6"] = "Nbd2";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nf6 5. 0-0 Be7 6. Re1 b5 7. Bb3 0-0 8. a4 Bb7 9. d3 d6 10. Nbd2 Na5"] = "Ba2";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nf6 5. 0-0 Be7 6. Re1 b5 7. Bb3 0-0 8. a4 Bb7 9. d3 d6 10. Nbd2 b4"] = "a5";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nf6 5. 0-0 Be7 6. Re1 b5 7. Bb3 0-0 8. a4 Bb7 9. d3 d6 10. Nbd2 h6"] = "Nf1";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nf6 5. 0-0 Be7 6. Re1 b5 7. Bb3 0-0 8. a4 Bb7 9. d3 d6 10. Nbd2 h6 11. Nf1 Qd7"] = "Ne3";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nf6 5. 0-0 Be7 6. Re1 b5 7. Bb3 0-0 8. a4 Bb7 9. d3 d6 10. Nbd2 Nd7"] = "c3";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nf6 5. 0-0 Be7 6. Re1 b5 7. Bb3 0-0 8. a4 Bb7 9. d3 d6 10. Nbd2 Qd7"] = "c3";

        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nf6 5. 0-0 Be7 6. Re1 b5 7. Bb3 d6"] = "c3";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nf6 5. 0-0 Be7 6. Re1 b5 7. Bb3 d6 8. c3 0-0"] = "h3";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nf6 5. 0-0 Be7 6. Re1 b5 7. Bb3 d6 8. c3 Na5"] = "Bc2";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nf6 5. 0-0 Be7 6. Re1 b5 7. Bb3 d6 8. c3 Bg4"] = "h3";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nf6 5. 0-0 Be7 6. Re1 b5 7. Bb3 d6 8. c3 Bg4 9. h3 Bd7"] = "d4";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nf6 5. 0-0 Be7 6. Re1 b5 7. Bb3 d6 8. c3 Bg4 9. h3 Bxf3"] = "Qxf3";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nf6 5. 0-0 Be7 6. Re1 b5 7. Bb3 d6 8. c3 Bg4 9. h3 Bh5"] = "d3";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nf6 5. 0-0 Be7 6. Re1 b5 7. Bb3 d6 8. c3 h6"] = "h3";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nf6 5. 0-0 Be7 6. Re1 b5 7. Bb3 d6 8. c3 h6 9. h3 0-0"] = "d4";

        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nf6 5. 0-0 a6"] = "Bxc6";

        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nf6 5. 0-0 b5"] = "Bb3";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nf6 5. 0-0 b5 6. Bb3 Bb7"] = "d3";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nf6 5. 0-0 b5 6. Bb3 Be7"] = "d4";

        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 d6"] = "0-0";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 d6 5. 0-0 b5"] = "Bb3";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 d6 5. 0-0 b5 6. Bb3 Nf6"] = "c3";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 d6 5. 0-0 Nf6"] = "Re1";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 d6 5. 0-0 Be7"] = "c3";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 d6 5. 0-0 Be7 6. c3 Nf6"] = "Re1";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 d6 5. 0-0 Be7 6. c3 Nf6 7. Re1 0-0"] = "d4";

        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nge7"] = "c3";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nge7 5. c3 d6"] = "d4";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nge7 5. c3 d6 6. d4 b5"] = "Bc2";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nge7 5. c3 d6 6. d4 Bd7"] = "d5";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nge7 5. c3 d6 6. d4 Bd7 7. d5 Nb8"] = "Bc2";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nge7 5. c3 d6 6. d4 Bd7 7. d5 Na5"] = "Bxd7+";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nge7 5. c3 d6 6. d4 Bd7 7. d5 Na5 8. Bxd7+ Qxd7"] = "0-0";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nge7 5. c3 d6 6. d4 Ng6"] = "d5";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nge7 5. c3 d6 6. d4 Ng6 7. d5 b5"] = "Bc2";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nge7 5. c3 d6 6. d4 exd4"] = "cxd4";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nge7 5. c3 d6 6. d4 Bg4"] = "d5";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nge7 5. c3 d6 6. d4 Bg4 7. d5 b5"] = "Bc2";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nge7 5. c3 d5"] = "Nxe5";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nge7 5. c3 d5 6. Nxe5 b5"] = "Nxc6";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nge7 5. c3 d5 6. Nxe5 b5 7. Nxc6 Nxc6"] = "Bc2";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nge7 5. c3 d5 6. Nxe5 dxe4"] = "Qb3";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nge7 5. c3 d5 6. Nxe5 Qd6"] = "Nxc6";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nge7 5. c3 d5 6. Nxe5 Qd6 7. Nxc6 bxc6"] = "d4";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nge7 5. c3 d5 6. Nxe5 Qd6 7. Nxc6 Nxc6"] = "exd5";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nge7 5. c3 d5 6. Nxe5 Qd6 7. Nxc6 Nxc6 8. exd5 b5"] = "Bc2";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nge7 5. c3 d5 6. Nxe5 Bd7"] = "Nxd7";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nge7 5. c3 d5 6. Nxe5 Bd7 7. Nxd7 Qxd7"] = "exd5";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nge7 5. c3 d5 6. Nxe5 Bd7 7. Nxd7 Qxd7 8. exd5 Nxd5"] = "0-0";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nge7 5. c3 d5 6. Nxe5 Bd7 7. Nxd7 Qxd7 8. exd5 Nxd5 9. 0-0 0-0-0"] = "d4";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nge7 5. c3 b5"] = "Bb3";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nge7 5. c3 b5 6. Bb3 Bb7"] = "d4";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nge7 5. c3 b5 6. Bb3 d5"] = "0-0";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nge7 5. c3 b5 6. Bb3 Na5"] = "Bc2";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nge7 5. c3 b5 6. Bb3 Ng6"] = "d4";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nge7 5. c3 b5 6. Bb3 h6"] = "a4";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nge7 5. c3 Ng6"] = "d4";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nge7 5. c3 Ng6 6. d4 Be7"] = "d5";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nge7 5. c3 Ng6 6. d4 d6"] = "d5";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nge7 5. c3 Ng6 6. d4 d6 7. d5 b5"] = "Bc2";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nge7 5. c3 Ng6 6. d4 d5"] = "Nxe5";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nge7 5. c3 Ng6 6. d4 b5"] = "Bc2";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nge7 5. c3 Ng6 6. d4 Bd6"] = "h4";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nge7 5. c3 Ng6 6. d4 exd4"] = "cxd4";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nge7 5. c3 g6"] = "d4";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nge7 5. c3 g6 6. d4 exd4"] = "cxd4";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nge7 5. c3 g6 6. d4 d6"] = "d5";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nge7 5. c3 g6 6. d4 d6 7. d5 b5"] = "Bc2";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nge7 5. c3 g6 6. d4 b5"] = "Bb3";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nge7 5. c3 g6 6. d4 b5 7. Bb3 Bg7"] = "dxe5";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nge7 5. c3 g6 6. d4 f6"] = "d5";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nge7 5. c3 g6 6. d4 f6 7. d5 Na5"] = "0-0";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nge7 5. c3 g6 6. d4 f6 7. d5 Nb8"] = "c4";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nge7 5. c3 g6 6. d4 Bg7"] = "d5";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nge7 5. c3 g6 6. d4 Bg7 7. d5 Nb8"] = "h4";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nge7 5. c3 g6 6. d4 Bg7 7. d5 Na7"] = "h4";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nge7 5. c3 g6 6. d4 Bg7 7. d5 Na5"] = "0-0";

        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 b5"] = "Bb3";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 b5 5. Bb3 Na5"] = "0-0";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 b5 5. Bb3 Nf6"] = "0-0";

        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 b5 5. Bb3 Nf6 6. 0-0 Bb7"] = "d3";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 b5 5. Bb3 Nf6 6. 0-0 Bc5"] = "a4";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 b5 5. Bb3 Nf6 6. 0-0 d6"] = "c3";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 b5 5. Bb3 Nf6 6. 0-0 Nxe4"] = "Re1";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 b5 5. Bb3 Nf6 6. 0-0 Be7"] = "a4";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 b5 5. Bb3 Nf6 6. 0-0 Be7 7. a4 Bb7"] = "Re1";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 b5 5. Bb3 Nf6 6. 0-0 Be7 7. a4 b4"] = "d4";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 b5 5. Bb3 Nf6 6. 0-0 Be7 7. a4 b4 8. d4 d6"] = "dxe5";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 b5 5. Bb3 Nf6 6. 0-0 Be7 7. a4 b4 8. d4 d6 9. dxe5 Nxe5"] = "Nxe5";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 b5 5. Bb3 Nf6 6. 0-0 Be7 7. a4 b4 8. d4 d6 9. dxe5 Nxe5 10. Nxe5 dxe5"] = "Qxd8+";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 b5 5. Bb3 Nf6 6. 0-0 Be7 7. a4 b4 8. d4 d6 9. dxe5 Nxe5 10. Nxe5 dxe5 11. Qxd8+ Kxd8"] = "Bxf7";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 b5 5. Bb3 Nf6 6. 0-0 Be7 7. a4 b4 8. d4 d6 9. dxe5 Nxe5 10. Nxe5 dxe5 11. Qxd8+ Bxd8"] = "Be3";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 b5 5. Bb3 Nf6 6. 0-0 Be7 7. a4 b4 8. d4 d6 9. dxe5 dxe5"] = "Qxd8+";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 b5 5. Bb3 Nf6 6. 0-0 Be7 7. a4 b4 8. d4 d6 9. dxe5 dxe5 10. Qxd8+ Nxd8"] = "Nxe5";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 b5 5. Bb3 Nf6 6. 0-0 Be7 7. a4 b4 8. d4 d6 9. dxe5 dxe5 10. Qxd8+ Kxd8"] = "Bxf7";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 b5 5. Bb3 Nf6 6. 0-0 Be7 7. a4 b4 8. d4 d6 9. dxe5 dxe5 10. Qxd8+ Bxd8"] = "Be3";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 b5 5. Bb3 Nf6 6. 0-0 Be7 7. a4 b4 8. d4 Nxe4"] = "dxe5";

        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 b5 5. Bb3 Bb7"] = "d4";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 b5 5. Bb3 Bb7 6. d4 exd4"] = "0-0";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 b5 5. Bb3 Be7"] = "d4";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 b5 5. Bb3 Be7 6. d4 exd4"] = "c3";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 b5 5. Bb3 Bc5"] = "c3";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 b5 5. Bb3 g6"] = "0-0";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 b5 5. Bb3 g6 6. 0-0 Bg7"] = "c3";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 b5 5. Bb3 d6"] = "a4";

        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nf6 5. 0-0 Nxe4"] = "d4";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nf6 5. 0-0 Nxe4 6. d4 exd4"] = "Re1";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nf6 5. 0-0 Nxe4 6. d4 b5"] = "Bb3";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nf6 5. 0-0 Nxe4 6. d4 b5 7. Bb3 d5"] = "dxe5";


        // B27 Sicilian defence -- WHITE
        book["1. e4 c5 2. Nf3 d6"] = "d4";
        book["1. e4 c5 2. Nf3 d6 3. d4 Nf6"] = "Nc3";
        book["1. e4 c5 2. Nf3 d6 3. d4 cxd4"] = "Nxd4";

        book["1. e4 c5 2. Nf3 Qc7"] = "Nc3";
        book["1. e4 c5 2. Nf3 Qc7 3. Nc3 e6"] = "d4";
        book["1. e4 c5 2. Nf3 Qc7 3. Nc3 e6 4. d4 cxd4"] = "Nb5";
        book["1. e4 c5 2. Nf3 Qc7 3. Nc3 e6 4. d4 cxd4 5. Nb5 Qa5+"] = "Bd2";
        book["1. e4 c5 2. Nf3 Qc7 3. Nc3 Nc6"] = "d4";
        book["1. e4 c5 2. Nf3 Qc7 3. Nc3 Nc6 4. d4 cxd4"] = "Nxd4";
        book["1. e4 c5 2. Nf3 Qc7 3. Nc3 a6"] = "d4";
        book["1. e4 c5 2. Nf3 Qc7 3. Nc3 a6 4. d4 e6"] = "d5";
        book["1. e4 c5 2. Nf3 Qc7 3. Nc3 a6 4. d4 cxd4"] = "Nd5";

        book["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 Nf6"] = "Nc3";
        book["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 a6"] = "Be3";
        book["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 a6 6. Be3 Ng4"] = "Bg5";
        book["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 a6 6. Be3 Nc6"] = "Be2";
        book["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 a6 6. Be3 Nbd7"] = "f3";

        book["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 a6 6. Be3 g6"] = "f3";
        book["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 a6 6. Be3 g6 7. f3 Bg7"] = "Qd2";
        book["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 a6 6. Be3 g6 7. f3 Bg7 8. Qd2 Nc6"] = "0-0-0";
        book["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 a6 6. Be3 g6 7. f3 Bg7 8. Qd2 Nc6 9. 0-0-0 Nxd4"] = "Bxd4";
        book["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 a6 6. Be3 g6 7. f3 Bg7 8. Qd2 Nc6 9. 0-0-0 h5"] = "Be2";
        book["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 a6 6. Be3 g6 7. f3 Bg7 8. Qd2 Nc6 9. 0-0-0 0-0"] = "";
        book["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 a6 6. Be3 g6 7. f3 Bg7 8. Qd2 h5"] = "Be2";
        book["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 a6 6. Be3 g6 7. f3 Bg7 8. Qd2 h5 9. Be2 0-0"] = "0-0-0";
        book["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 a6 6. Be3 g6 7. f3 Bg7 8. Qd2 h5 9. Be2 Nbd7"] = "0-0";
        book["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 a6 6. Be3 g6 7. f3 Bg7 8. Qd2 h5 9. Be2 Nc6"] = "0-0-0";
        book["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 a6 6. Be3 g6 7. f3 Bg7 8. Qd2 h5 9. Be2 Bd7"] = "0-0-0";

        book["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 a6 6. Be3 Qc7"] = "f3";
        book["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 a6 6. Be3 e6"] = "Be2";
        book["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 a6 6. Be3 e5"] = "Nb3";
        book["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 a6 6. Be3 e5 7. Nb3 Be6"] = "Qd2";
        book["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 a6 6. Be3 e5 7. Nb3 Be6 8. Qd2 Nbd7"] = "f3";
        book["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 a6 6. Be3 e5 7. Nb3 Be6 8. Qd2 b5"] = "a4";
        book["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 a6 6. Be3 e5 7. Nb3 Be6 8. Qd2 Nc6"] = "0-0-0";
        book["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 a6 6. Be3 e5 7. Nb3 Be6 8. Qd2 Qc7"] = "f3";
        book["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 a6 6. Be3 e5 7. Nb3 Be6 8. Qd2 Be7"] = "f3";
        book["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 a6 6. Be3 e5 7. Nb3 Be6 8. Qd2 Be7 9. f3 Qc7"] = "g4";
        book["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 a6 6. Be3 e5 7. Nb3 Be6 8. Qd2 Be7 9. f3 0-0"] = "0-0-0";
        book["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 a6 6. Be3 e5 7. Nb3 Be6 8. Qd2 Be7 9. f3 Nbd7"] = "g4";

        book["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 a6 6. Be3 e5 7. Nb3 Be7"] = "f3";
        book["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 a6 6. Be3 e5 7. Nb3 Qc7"] = "Qd2";
        book["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 a6 6. Be3 e5 7. Nb3 Ng4"] = "Bd2";

        book["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 Nc6"] = "Bg5";
        book["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 Nc6 6. Bg5 e6"] = "Qd2";
        book["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 Nc6 6. Bg5 Bd7"] = "Qd2";
        book["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 Nc6 6. Bg5 Qb6"] = "Qd2";
        book["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 Nc6 6. Bg5 a6"] = "Qd3";
        book["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 Nc6 6. Bg5 g6"] = "Bxf6";
        book["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 Nc6 6. Bg5 g6 7. Bxf6 exf6"] = "Bb5";
        book["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 Nc6 6. Bg5 Qa5"] = "Bb5";
        book["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 Nc6 6. Bg5 Qa5 7. Bb5 Bd7"] = "Nb3";
        book["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 Nc6 6. Bg5 h6"] = "Bxf6";
        book["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 Nc6 6. Bg5 h6 7. Bxf6 exf6"] = "Nd5";
        book["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 Nc6 6. Bg5 h6 7. Bxf6 gxf6"] = "Bb5";
        book["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 Nc6 6. Bg5 h6 7. Bxf6 gxf6 8. Bb5 Bd7"] = "Nf5";
        book["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 Nc6 6. Bg5 e5"] = "Bxf6";
        book["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 Nc6 6. Bg5 e5 7. Bxf6 gxf6"] = "Nf5";
        book["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 Nc6 6. Bg5 e5 7. Bxf6 Qxf6"] = "Ndb5";
        book["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 Nc6 6. Bg5 Nxd4"] = "Qxd4";

        book["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 g6"] = "Be3";
        book["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 g6 6. Be3 Bg7"] = "f3";
        book["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 g6 6. Be3 Bg7 7. f3 Nc6"] = "Qd2";
        book["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 g6 6. Be3 Bg7 7. f3 Nc6 8. Qd2 0-0"] = "g4";
        book["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 g6 6. Be3 Bg7 7. f3 0-0"] = "Qd2";
        book["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 g6 6. Be3 Bg7 7. f3 0-0 8. Qd2 Nc6"] = "g4";
        book["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 g6 6. Be3 a6"] = "f3";
        book["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 g6 6. Be3 a6 7. f3 b5"] = "Qd2";
        book["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 g6 6. Be3 a6 7. f3 b5 8. Qd2 Bb7"] = "a4";
        book["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 g6 6. Be3 a6 7. f3 b5 8. Qd2 Bg7"] = "a4";
        book["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 g6 6. Be3 a6 7. f3 h5"] = "Qd2";
        book["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 g6 6. Be3 a6 7. f3 Bg7"] = "Qd2";
        book["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 g6 6. Be3 a6 7. f3 Bg7 8. Qd2 h5"] = "Be2";
        book["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 g6 6. Be3 a6 7. f3 Bg7 8. Qd2 0-0"] = "g4";
        book["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 g6 6. Be3 a6 7. f3 Bg7 8. Qd2 b5"] = "a4";
        book["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 g6 6. Be3 a6 7. f3 Bg7 8. Qd2 Nc6"] = "0-0-0";
        book["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 g6 6. Be3 a6 7. f3 Bg7 8. Qd2 Nbd7"] = "g4";
        book["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 g6 6. Be3 Nc6"] = "f3";
        book["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 g6 6. Be3 Nc6 7. f3 Bg7"] = "Qd2";
        book["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 g6 6. Be3 Nc6 7. f3 Bg7 8. Qd2 0-0"] = "g4";
        book["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 g6 6. Be3 Nc6 7. f3 Bg7 8. Qd2 0-0 9. g4 h5"] = "h3";

        book["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 e5"] = "Bb5+";
        book["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 e5 6. Bb5+ Nbd7"] = "Nf5";
        book["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 e5 6. Bb5+ Bd7"] = "Bxd7+";
        book["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 e5 6. Bb5+ Bd7 7. Bxd7+ Qxd7"] = "Nde2";
        book["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 e5 6. Bb5+ Bd7 7. Bxd7+ Nbxd7"] = "Nf5";

        book["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 Nc6"] = "c4";
        book["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 a6"] = "c4";
        book["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 e6"] = "c4";
        book["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 e5"] = "Bb5+";
        book["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 g6"] = "c4";

        book["1. e4 c5 2. Nf3 e6"] = "d4";

        book["1. e4 c5 2. Nf3 g6"] = "d4";
        book["1. e4 c5 2. Nf3 g6 3. d4 Bg7"] = "dxc5";
        book["1. e4 c5 2. Nf3 g6 3. d4 Bg7 4. dxc5 Qa5+"] = "c3";
        book["1. e4 c5 2. Nf3 g6 3. d4 Bg7 4. dxc5 Nf6"] = "Nc3";
        book["1. e4 c5 2. Nf3 g6 3. d4 d6"] = "dxc5";
        book["1. e4 c5 2. Nf3 g6 3. d4 d6 4. dxc5 dxc5"] = "Qxd8+";
        book["1. e4 c5 2. Nf3 g6 3. d4 d6 4. dxc5 dxc5 5. Qxd8+ Kxd8"] = "Bc4";
        book["1. e4 c5 2. Nf3 g6 3. d4 Nf6"] = "e5";
        book["1. e4 c5 2. Nf3 g6 3. d4 cxd4"] = "Nxd4";
        book["1. e4 c5 2. Nf3 g6 3. d4 cxd4 4. Nxd4 Nc6"] = "c4";
        book["1. e4 c5 2. Nf3 g6 3. d4 cxd4 4. Nxd4 Nc6 5. c4 Bg7"] = "Be3";
        book["1. e4 c5 2. Nf3 g6 3. d4 cxd4 4. Nxd4 Bg7"] = "Be3";
        book["1. e4 c5 2. Nf3 g6 3. d4 cxd4 4. Nxd4 Nf6"] = "Nc3";
        book["1. e4 c5 2. Nf3 g6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 Bg7"] = "e5";

        book["1. e4 c5 2. Nf3 g6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 Nc6"] = "Nxc6";
        book["1. e4 c5 2. Nf3 g6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 Nc6 6. Nxc6 dxc6"] = "Qxd8+";
        book["1. e4 c5 2. Nf3 g6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 Nc6 6. Nxc6 dxc6 7. Qxd8+ Kxd8"] = "Bc4";
        book["1. e4 c5 2. Nf3 g6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 Nc6 6. Nxc6 bxc6"] = "e5";
        book["1. e4 c5 2. Nf3 g6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 Nc6 6. Nxc6 bxc6 7. e5 Nd5"] = "Nxd5";
        book["1. e4 c5 2. Nf3 g6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 Nc6 6. Nxc6 bxc6 7. e5 Nd5 8. Nxd5 cxd5"] = "Qxd5";
        book["1. e4 c5 2. Nf3 g6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 Nc6 6. Nxc6 bxc6 7. e5 Nh5"] = "Bc4";
        book["1. e4 c5 2. Nf3 g6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 Nc6 6. Nxc6 bxc6 7. e5 Ng8"] = "Bc4";
        book["1. e4 c5 2. Nf3 g6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 Nc6 6. Nxc6 bxc6 7. e5 Ng8 8. Bc4 d5"] = "exd6";
        book["1. e4 c5 2. Nf3 g6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 Nc6 6. Nxc6 bxc6 7. e5 Ng8 8. Bc4 d5 9. exd6 Qxd6"] = "Qf3";
        book["1. e4 c5 2. Nf3 g6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 Nc6 6. Nxc6 bxc6 7. e5 Ng8 8. Bc4 d5 9. exd6 Qxd6 10. Qf3 Nf6"] = "Bf4";
        book["1. e4 c5 2. Nf3 g6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 Nc6 6. Nxc6 bxc6 7. e5 Ng8 8. Bc4 d5 9. exd6 exd6"] = "Qf3";
        book["1. e4 c5 2. Nf3 g6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 Nc6 6. Nxc6 bxc6 7. e5 Ng8 8. Bc4 Nh6"] = "Qf3";
        book["1. e4 c5 2. Nf3 g6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 Nc6 6. Nxc6 bxc6 7. e5 Ng8 8. Bc4 Nh6 9. Qf3 Qa5"] = "0-0";
        book["1. e4 c5 2. Nf3 g6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 Nc6 6. Nxc6 bxc6 7. e5 Ng8 8. Bc4 Nh6 9. Qf3 Qa5 10. 0-0 Qxe5"] = "Bf4";
        book["1. e4 c5 2. Nf3 g6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 Nc6 6. Nxc6 bxc6 7. e5 Ng8 8. Bc4 Nh6 9. Qf3 e6"] = "Ne4";

        book["1. e4 c5 2. Nf3 g6 3. d4 cxd4 4. Nxd4 d6"] = "c4";
        book["1. e4 c5 2. Nf3 g6 3. d4 cxd4 4. Nxd4 d6 5. c4 Bg7"] = "Nc3";
        book["1. e4 c5 2. Nf3 g6 3. d4 cxd4 4. Nxd4 Qa5+"] = "Bd2";
        book["1. e4 c5 2. Nf3 g6 3. d4 cxd4 4. Nxd4 a6"] = "c4";
        book["1. e4 c5 2. Nf3 g6 3. d4 cxd4 4. Nxd4 a6 5. c4 Bg7"] = "Nc3";

        book["1. e4 c5 2. Nf3 a6"] = "c3";
        book["1. e4 c5 2. Nf3 a6 3. c3 d5"] = "exd5";
        book["1. e4 c5 2. Nf3 a6 3. c3 d5 4. exd5 Qxd5"] = "d4";
        book["1. e4 c5 2. Nf3 a6 3. c3 d5 4. exd5 Nf6"] = "Qa4+";
        book["1. e4 c5 2. Nf3 a6 3. c3 d5 4. exd5 Nf6 5. Qa4+ b5"] = "Bxb5+";
        book["1. e4 c5 2. Nf3 a6 3. c3 d5 4. exd5 Nf6 5. Qa4+ Qd7"] = "Qxd7+";
        book["1. e4 c5 2. Nf3 a6 3. c3 d5 4. exd5 Nf6 5. Qa4+ Qd7 6. Qxd7+ Bxd7"] = "c4";
        book["1. e4 c5 2. Nf3 a6 3. c3 d5 4. exd5 Nf6 5. Qa4+ Qd7 6. Qxd7+ Nxd7"] = "c4";
        book["1. e4 c5 2. Nf3 a6 3. c3 d5 4. exd5 Nf6 5. Qa4+ Bd7"] = "Qb3";
        book["1. e4 c5 2. Nf3 a6 3. c3 d5 4. exd5 Nf6 5. Qa4+ Bd7 6. Qb3 b5"] = "a4";
        book["1. e4 c5 2. Nf3 a6 3. c3 d5 4. exd5 Nf6 5. Qa4+ Bd7 6. Qb3 Bc8"] = "c4";
        book["1. e4 c5 2. Nf3 a6 3. c3 d5 4. exd5 Nf6 5. Qa4+ Nbd7"] = "c4";
        book["1. e4 c5 2. Nf3 a6 3. c3 e6"] = "d4";
        book["1. e4 c5 2. Nf3 a6 3. c3 Nf6"] = "e5";
        book["1. e4 c5 2. Nf3 a6 3. c3 g6"] = "d4";
        book["1. e4 c5 2. Nf3 a6 3. c3 b5"] = "d4";
        book["1. e4 c5 2. Nf3 a6 3. c3 d6"] = "d4";
        book["1. e4 c5 2. Nf3 a6 3. c3 d6 4. d4 Qc7"] = "Bd3";
        book["1. e4 c5 2. Nf3 a6 3. c3 d6 4. d4 Nd7"] = "Bd3";
        book["1. e4 c5 2. Nf3 a6 3. c3 d6 4. d4 Nf6"] = "Bd3";
        book["1. e4 c5 2. Nf3 a6 3. c3 d6 4. d4 cxd4"] = "cxd4";
        book["1. e4 c5 2. Nf3 a6 3. c3 d6 4. d4 Qa5"] = "d5";
        book["1. e4 c5 2. Nf3 a6 3. c3 d6 4. d4 Bg4"] = "dxc5";

        book["1. e4 c5 2. Nf3 Nf6"] = "e5";
        book["1. e4 c5 2. Nf3 Nf6 3. e5 Nd5"] = "Nc3";


        // B40 Sicilian defence -- WHITE
        book["1. e4 c5 2. Nf3 e6 3. d4 cxd4"] = "Nxd4";
        book["1. e4 c5 2. Nf3 e6 3. d4 cxd4 4. Nxd4 Nc6"] = "Nc3";

        book["1. e4 c5 2. Nf3 e6 3. d4 cxd4 4. Nxd4 Nf6"] = "Nc3";
        book["1. e4 c5 2. Nf3 e6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 d6"] = "g4";
        book["1. e4 c5 2. Nf3 e6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 d6 6. g4 h6"] = "h4";
        book["1. e4 c5 2. Nf3 e6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 d6 6. g4 Nc6"] = "g5";

        book["1. e4 c5 2. Nf3 e6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 Nc6"] = "Bf4";
        book["1. e4 c5 2. Nf3 e6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 Nc6 6. Bf4 d6"] = "Ndb5";
        book["1. e4 c5 2. Nf3 e6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 Nc6 6. Bf4 Bb4"] = "Nb5";

        book["1. e4 c5 2. Nf3 e6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 Bb4"] = "e5";
        book["1. e4 c5 2. Nf3 e6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 Bb4 6. e5 Nd5"] = "Qg4";
        book["1. e4 c5 2. Nf3 e6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 Bb4 6. e5 Ne4"] = "Qg4";
        book["1. e4 c5 2. Nf3 e6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 Bb4 6. e5 Qc7"] = "exf6";
        book["1. e4 c5 2. Nf3 e6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 Bb4 6. e5 Qc7 7. exf6 Bxc3+"] = "bxc3";
        book["1. e4 c5 2. Nf3 e6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 Bb4 6. e5 Qc7 7. exf6 Bxc3+ 8. bxc3 Qxc3+"] = "Qd2";
        book["1. e4 c5 2. Nf3 e6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 Bb4 6. e5 Qc7 7. exf6 Qe5+"] = "Be3";
        book["1. e4 c5 2. Nf3 e6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 Bb4 6. e5 Qa5"] = "exf6";

        book["1. e4 c5 2. Nf3 e6 3. d4 cxd4 4. Nxd4 Qb6"] = "Nb3";
        book["1. e4 c5 2. Nf3 e6 3. d4 cxd4 4. Nxd4 Bc5"] = "Be3";
        book["1. e4 c5 2. Nf3 e6 3. d4 cxd4 4. Nxd4 d6"] = "c4";
        book["1. e4 c5 2. Nf3 e6 3. d4 cxd4 4. Nxd4 Qc7"] = "Nb5";
        book["1. e4 c5 2. Nf3 e6 3. d4 cxd4 4. Nxd4 g6"] = "Nc3";

        book["1. e4 c5 2. Nf3 e6 3. d4 cxd4 4. Nxd4 a6"] = "Bd3";
        book["1. e4 c5 2. Nf3 e6 3. d4 cxd4 4. Nxd4 a6 5. Bd3 Bc5"] = "Nb3";
        book["1. e4 c5 2. Nf3 e6 3. d4 cxd4 4. Nxd4 a6 5. Bd3 Bc5 6. Nb3 Be7"] = "Qg4";
        book["1. e4 c5 2. Nf3 e6 3. d4 cxd4 4. Nxd4 a6 5. Bd3 Bc5 6. Nb3 Ba7"] = "Qg4";
        book["1. e4 c5 2. Nf3 e6 3. d4 cxd4 4. Nxd4 a6 5. Bd3 Bc5 6. Nb3 Bb6"] = "Qg4";

        book["1. e4 c5 2. Nf3 e6 3. d4 cxd4 4. Nxd4 a6 5. Bd3 Nc6"] = "Nxc6";
        book["1. e4 c5 2. Nf3 e6 3. d4 cxd4 4. Nxd4 a6 5. Bd3 Nc6 6. Nxc6 bxc6"] = "0-0";
        book["1. e4 c5 2. Nf3 e6 3. d4 cxd4 4. Nxd4 a6 5. Bd3 Nc6 6. Nxc6 dxc6"] = "Nd2";


		// B40 Sicilian defence -- WHITE
        book["1. e4 c5 2. Nf3 e6 3. d3 Nc6"] = "g3";
        book["1. e4 c5 2. Nf3 e6 3. d3 Nc6 4. g3 g6"] = "Bg2";
        book["1. e4 c5 2. Nf3 e6 3. d3 Nc6 4. g3 d5"] = "Qe2";
        book["1. e4 c5 2. Nf3 e6 3. d3 Nc6 4. g3 d5 5. Qe2 Nge7"] = "Bg2";
        book["1. e4 c5 2. Nf3 e6 3. d3 Nc6 4. g3 d5 5. Qe2 Be7"] = "e5";
        book["1. e4 c5 2. Nf3 e6 3. d3 Nc6 4. g3 d5 5. Qe2 Be7 6. e5 b6"] = "Bg2";
        book["1. e4 c5 2. Nf3 e6 3. d3 Nc6 4. g3 Nge7"] = "Bg2";
        book["1. e4 c5 2. Nf3 e6 3. d3 Nc6 4. g3 Nf6"] = "Qe2";
        book["1. e4 c5 2. Nf3 e6 3. d3 Nc6 4. g3 Nf6 5. Qe2 d6"] = "Bg2";
        book["1. e4 c5 2. Nf3 e6 3. d3 Nc6 4. g3 Nf6 5. Qe2 d5"] = "exd5";
        book["1. e4 c5 2. Nf3 e6 3. d3 Nc6 4. g3 Nf6 5. Qe2 d5 6. exd5 Qxd5"] = "Nc3";
        book["1. e4 c5 2. Nf3 e6 3. d3 Nc6 4. g3 Nf6 5. Qe2 d5 6. exd5 Nxd5"] = "Bg2";
        book["1. e4 c5 2. Nf3 e6 3. d3 Nc6 4. g3 d6"] = "Bg2";


        // B32 Sicilian defence -- WHITE
        book["1. e4 c5 2. Nf3 Nc6"] = "d4";
        book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4"] = "Nxd4";
        book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 g6"] = "c4";
        book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 g6 5. c4 Nf6"] = "Nc3";
        book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 g6 5. c4 Nf6 6. Nc3 Bg7"] = "Be3";
        book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 g6 5. c4 a6"] = "Nc3";
        book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 g6 5. c4 d6"] = "Nc3";
        book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 g6 5. c4 Qb6"] = "Nb3";
        book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 g6 5. c4 Bg7"] = "Be3";
        book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 g6 5. c4 Bg7 6. Be3 d6"] = "Nc3";
        book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 g6 5. c4 Bg7 6. Be3 Nf6"] = "Nc3";
        book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 g6 5. c4 Bg7 6. Be3 Nf6 7. Nc3 0-0"] = "Be2";

        book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 e5"] = "Nb5";
        book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 e5 5. Nb5 d6"] = "c4";

        book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 e5 5. Nb5 d6 6. c4 Be7"] = "N5c3";
        book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 e5 5. Nb5 d6 6. c4 Be7 7. N5c3 a6"] = "Nd5";
        book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 e5 5. Nb5 d6 6. c4 Be7 7. N5c3 f5"] = "exf5";
        book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 e5 5. Nb5 d6 6. c4 Be7 7. N5c3 f5 8. exf5 Bxf5"] = "Bd3";
        book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 e5 5. Nb5 d6 6. c4 Be7 7. N5c3 Be6"] = "Nd5";
        book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 e5 5. Nb5 d6 6. c4 Be7 7. N5c3 Nf6"] = "Be2";
        book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 e5 5. Nb5 d6 6. c4 Be7 7. N5c3 Nf6 8. Be2 0-0"] = "Be3";
        book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 e5 5. Nb5 d6 6. c4 Be7 7. N5c3 Nf6 8. Be2 Nd4"] = "Be3";
        book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 e5 5. Nb5 d6 6. c4 Be7 7. N5c3 Nf6 8. Be2 Be6"] = "Be3";

        book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 e5 5. Nb5 d6 6. c4 Be6"] = "Bd3";
        book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 e5 5. Nb5 d6 6. c4 a6"] = "N5c3";
        book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 e5 5. Nb5 d6 6. c4 Nf6"] = "N5c3";
        book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 e5 5. Nb5 d6 6. c4 g6"] = "N5c3";
        book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 e5 5. Nb5 d6 6. c4 f5"] = "exf5";
        book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 e5 5. Nb5 d6 6. c4 f5 7. exf5 Bxf5"] = "Bd3";
        book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 e5 5. Nb5 d6 6. c4 h6"] = "Be2";
        book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 e5 5. Nb5 a6"] = "Nd6+";
        book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 e5 5. Nb5 a6 6. Nd6+ Bxd6"] = "Qxd6";
        book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 e5 5. Nb5 a6 6. Nd6+ Bxd6 8. Qxd6 Qe7"] = "Qxe7+";
        book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 e5 5. Nb5 a6 6. Nd6+ Bxd6 8. Qxd6 Qe7 8. Qxe7+ Ngxe7"] = "c4";
        book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 e5 5. Nb5 a6 6. Nd6+ Bxd6 8. Qxd6 Qe7 8. Qxe7+ Ncxe7"] = "Nc3";
        book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 e5 5. Nb5 a6 6. Nd6+ Bxd6 8. Qxd6 Qf6"] = "Qd1";
        book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 e5 5. Nb5 a6 6. Nd6+ Bxd6 8. Qxd6 Nf6"] = "f3";
        book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 e5 5. Nb5 Nf6"] = "Bg5";
        book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 e5 5. Nb5 h6"] = "N1c3";
        book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 e5 5. Nb5 Bc5"] = "N1c3";
        book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 e5 5. Nb5 b6"] = "N1c3";
        book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 e5 5. Nb5 a5"] = "N1c3";

        book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 e6"] = "Nc3";
        book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 e6 5. Nc3 Bb4"] = "Nxc6";
        book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 e6 5. Nc3 Bb4 6. Nxc6 bxc6"] = "Qd4";
        book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 e6 5. Nc3 Bb4 6. Nxc6 Bxc3+"] = "bxc3";
        book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 e6 5. Nc3 Bb4 6. Nxc6 Bxc3+ 7. bxc3 bxc6"] = "Ba3";
        book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 e6 5. Nc3 Bb4 6. Nxc6 Bxc3+ 7. bxc3 dxc6"] = "Qxd8+";
        book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 e6 5. Nc3 Bb4 6. Nxc6 Bxc3+ 7. bxc3 dxc6 8. Qxd8+ Kxd8"] = "Bf4";
        book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 e6 5. Nc3 Nf6"] = "Be2";
        book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 e6 5. Nc3 Nf6 6. Be2 d5"] = "exd5";
        book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 e6 5. Nc3 Nf6 6. Be2 d5 7. exd5 exd5"] = "a3";

        book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 e6 5. Nc3 a6"] = "Be2";
        book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 e6 5. Nc3 Qc7"] = "a3";
        book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 e6 5. Nc3 Qc7 6. a3 a6"] = "f4";
        book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 e6 5. Nc3 Qc7 6. a3 Nxd4"] = "Qxd4";

        book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 Qc7"] = "Nc3";
        book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 Qb6"] = "Nb3";
        book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 d5"] = "exd5";

        book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 Nf6"] = "Nc3";
        book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 e6"] = "Nxc6";
        book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 e6 6. Nxc6 bxc6"] = "e5";
        book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 e5"] = "Ndb5";
        book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 e5 6. Ndb5 a6"] = "Nd6+";
        book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 e5 6. Ndb5 d6"] = "Bg5";
        book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 d5"] = "Bb5";


        // A01 Nimzovich-Larsen attack, modern variation -- BLACK
        book["1. b3 e5 2. e3"] = "d5";
        book["1. b3 e5 2. Bb2"] = "Nc6";
        book["1. b3 e5 2. Bb2 Nc6 3. e3"] = "Nf6";
        book["1. b3 e5 2. Bb2 Nc6 3. e3 Nf6 4. c4"] = "d5";
        book["1. b3 e5 2. Bb2 Nc6 3. c4"] = "Nf6";
        book["1. b3 e5 2. Bb2 Nc6 3. c4 Nf6 4. e3"] = "d5";


        // A15 English, 1...Nf6 (Anglo-Indian defense) -- BLACK
        book["1. c4 Nf6 2. Nf3"] = "e6";
        book["1. c4 Nf6 2. Nf3 e6 3. g3"] = "d5";
        book["1. c4 Nf6 2. Nf3 e6 3. g3 d5 4. Bg2"] = "dxc4";
        book["1. c4 Nf6 2. Nf3 e6 3. Nc3"] = "Bb4";
        book["1. c4 Nf6 2. Nf3 e6 3. Nc3 Bb4 4. Qc2"] = "0-0";
        book["1. c4 Nf6 2. Nf3 e6 3. Nc3 Bb4 4. g3"] = "Bxc3";
        book["1. c4 Nf6 2. Nf3 e6 3. Nc3 Bb4 4. g3 Bxc3 5. dxc3"] = "0-0";
        book["1. c4 Nf6 2. Nf3 e6 3. Nc3 Bb4 4. g3 Bxc3 5. dxc3 0-0 6. Bg2"] = "d6";
        book["1. c4 Nf6 2. Nf3 e6 3. Nc3 Bb4 4. g3 Bxc3 5. bxc3"] = "d6";
        book["1. c4 Nf6 2. Nf3 e6 3. Nc3 Bb4 4. g3 Bxc3 5. bxc3 d6 6. Bg2"] = "0-0";
        book["1. c4 Nf6 2. Nf3 e6 3. Nc3 Bb4 4. Qb3"] = "c5";
        book["1. c4 Nf6 2. Nf3 e6 3. Nc3 Bb4 4. g4"] = "h6";
        book["1. c4 Nf6 2. Nf3 e6 3. Nc3 Bb4 4. d4"] = "b6";
        book["1. c4 Nf6 2. Nf3 e6 3. Nc3 Bb4 4. e3"] = "bxc3";
        book["1. c4 Nf6 2. Nf3 e6 3. Nc3 Bb4 4. e3 Bxc3 5. dxc3"] = "d6";
        book["1. c4 Nf6 2. Nf3 e6 3. Nc3 Bb4 4. e3 Bxc3 5. bxc3"] = "d6";
        book["1. c4 Nf6 2. Nf3 e6 3. Nc3 Bb4 4. b3"] = "Bxc3";
        book["1. c4 Nf6 2. Nf3 e6 3. Nc3 Bb4 4. b3 Bxc3 5. dxc3"] = "b6";
        book["1. c4 Nf6 2. Nf3 e6 3. Nc3 Bb4 4. a3"] = "Bxc3";
        book["1. c4 Nf6 2. Nf3 e6 3. Nc3 Bb4 4. a3 Bxc3 5. bxc3"] = "0-0";
        book["1. c4 Nf6 2. Nf3 e6 3. Nc3 Bb4 4. a3 Bxc3 5. dxc3"] = "b6";

        book["1. c4 Nf6 2. Nf3 e6 3. d4"] = "b6";

        book["1. c4 Nf6 2. g3"] = "e5";
        book["1. c4 Nf6 2. g3 e5 3. Bg2"] = "d5";
        book["1. c4 Nf6 2. d4"] = "e6";
        book["1. c4 Nf6 2. b3"] = "g6";

        book["1. c4 Nf6 2. Nc3"] = "e5";
        book["1. c4 Nf6 2. Nc3 e5 3. Nf3"] = "Nc6";
        book["1. c4 Nf6 2. Nc3 e5 3. Nf3 Nc6 4. e3"] = "Bb4";
        book["1. c4 Nf6 2. Nc3 e5 3. Nf3 Nc6 4. g3"] = "d5";

        book["1. c4 Nf6 2. Nc3 e5 3. Nf3 Nc6 4. e4"] = "Bb4";
        book["1. c4 Nf6 2. Nc3 e5 3. Nf3 Nc6 4. e4 Bb4 5. d3"] = "d6";

        book["1. c4 Nf6 2. Nc3 e5 3. Nf3 Nc6 4. g3 d5 5. d4"] = "exd4";
        book["1. c4 Nf6 2. Nc3 e5 3. Nf3 Nc6 4. g3 d5 5. d4 exd4 6. Nxd4"] = "dxc4";
        book["1. c4 Nf6 2. Nc3 e5 3. Nf3 Nc6 4. g3 d5 5. Bg2"] = "d4";
        book["1. c4 Nf6 2. Nc3 e5 3. Nf3 Nc6 4. g3 d5 5. cxd5"] = "Nxd5";
        book["1. c4 Nf6 2. Nc3 e5 3. Nf3 Nc6 4. g3 d5 5. cxd5 Nxd5 6. d3"] = "Bb4";
        book["1. c4 Nf6 2. Nc3 e5 3. Nf3 Nc6 4. g3 d5 5. cxd5 Nxd5 6. Bg2"] = "Nb6";
        book["1. c4 Nf6 2. Nc3 e5 3. Nf3 Nc6 4. g3 d5 5. cxd5 Nxd5 6. Bg2 Nb6 7. 0-0"] = "Be7";
        book["1. c4 Nf6 2. Nc3 e5 3. Nf3 Nc6 4. g3 d5 5. cxd5 Nxd5 6. Bg2 Nb6 7. d3"] = "Be7";

        book["1. c4 Nf6 2. Nc3 e5 3. g3"] = "Bb4";
        book["1. c4 Nf6 2. Nc3 e5 3. e3"] = "Bb4";
        book["1. c4 Nf6 2. Nc3 e5 3. d3"] = "Bb4";
        book["1. c4 Nf6 2. Nc3 e5 3. a3"] = "c6";
        book["1. c4 Nf6 2. Nc3 e5 3. a3 c6 4. Nf3"] = "e4";
        book["1. c4 Nf6 2. Nc3 e5 3. a3 c6 4. d4"] = "exd4";
        book["1. c4 Nf6 2. Nc3 e5 3. a3 c6 4. d4 exd4 5. Qxd4"] = "d5";
        book["1. c4 Nf6 2. Nc3 e5 3. a3 c6 4. e3"] = "d5";
        book["1. c4 Nf6 2. Nc3 e5 3. a3 c6 4. e3 d5 5. d4"] = "e4";


        // C44 Ponziani opening -- BLACK
        book["1. e4 e5 2. Nf3 Nc6 3. c3"] = "d5";

        book["1. e4 e5 2. Nf3 Nc6 3. c3 d5 4. Qa4"] = "f6";
        book["1. e4 e5 2. Nf3 Nc6 3. c3 d5 4. Qa4 f6 5. d3"] = "Be6";
        book["1. e4 e5 2. Nf3 Nc6 3. c3 d5 4. Qa4 f6 5. exd5"] = "Qxd5";
        book["1. e4 e5 2. Nf3 Nc6 3. c3 d5 4. Qa4 f6 5. exd5 Qxd5 6. d4"] = "Bd7";
        book["1. e4 e5 2. Nf3 Nc6 3. c3 d5 4. Qa4 f6 5. exd5 Qxd5 6. d4 Bd7 7. Qc4"] = "Qxc4";
        book["1. e4 e5 2. Nf3 Nc6 3. c3 d5 4. Qa4 f6 5. exd5 Qxd5 6. d4 Bd7 7. Qc4 Qxc4 8. Bxc4"] = "exd4";

        book["1. e4 e5 2. Nf3 Nc6 3. c3 d5 4. d3"] = "dxe4";
        book["1. e4 e5 2. Nf3 Nc6 3. c3 d5 4. d3 dxe4 5. dxe4"] = "Qxd1+";
        book["1. e4 e5 2. Nf3 Nc6 3. c3 d5 4. d3 dxe4 5. dxe4 Qxd1+ 6. Kxd1"] = "Nf6";
        book["1. e4 e5 2. Nf3 Nc6 3. c3 d5 4. Bb5"] = "dxe4";
        book["1. e4 e5 2. Nf3 Nc6 3. c3 d5 4. Bb5 dxe4 5. Nxe5"] = "Qg5";
        book["1. e4 e5 2. Nf3 Nc6 3. c3 d5 4. exd5"] = "Qxd5";
        book["1. e4 e5 2. Nf3 Nc6 3. c3 d5 4. exd5 Qxd5 5. d4"] = "Nf6";
        book["1. e4 e5 2. Nf3 Nc6 3. c3 d5 4. exd5 Qxd5 5. d4 Nf6 6. Be2"] = "e4";
        book["1. e4 e5 2. Nf3 Nc6 3. c3 d5 4. exd5 Qxd5 5. d4 Nf6 6. Be2 e4 7. Ng1"] = "Bd6";
        book["1. e4 e5 2. Nf3 Nc6 3. c3 d5 4. exd5 Qxd5 5. d4 Nf6 6. Be2 e4 7. Nfd2"] = "e3";
        book["1. e4 e5 2. Nf3 Nc6 3. c3 d5 4. exd5 Qxd5 5. d4 Nf6 6. Be2 e4 7. Nfd2 e3 8. Nc4"] = "Qxg2";
        book["1. e4 e5 2. Nf3 Nc6 3. c3 d5 4. exd5 Qxd5 5. d4 Nf6 6. Be2 e4 7. Nfd2 e3 8. Nf1"] = "Qxg2";
        book["1. e4 e5 2. Nf3 Nc6 3. c3 d5 4. exd5 Qxd5 5. d4 Nf6 6. Be2 e4 7. Nfd2 e3 8. Nf3"] = "exf2+";
        book["1. e4 e5 2. Nf3 Nc6 3. c3 d5 4. exd5 Qxd5 5. d4 Nf6 6. Be2 e4 7. Nfd2 e3 8. Nf3 exf2+ 9. Kxf2"] = "Bd6";
        book["1. e4 e5 2. Nf3 Nc6 3. c3 d5 4. exd5 Qxd5 5. d4 Nf6 6. Be3"] = "Bd6";
        book["1. e4 e5 2. Nf3 Nc6 3. c3 d5 4. exd5 Qxd5 5. d4 Nf6 6. Be3 Bd6 7. c4"] = "Qa5+";
        book["1. e4 e5 2. Nf3 Nc6 3. c3 d5 4. exd5 Qxd5 5. d4 Nf6 6. Be3 Bd6 7. dxe5"] = "Nxe5";
        book["1. e4 e5 2. Nf3 Nc6 3. c3 d5 4. exd5 Qxd5 5. d4 Nf6 6. Be3 Bd6 7. a3"] = "Qe6";
        book["1. e4 e5 2. Nf3 Nc6 3. c3 d5 4. exd5 Qxd5 5. d4 Nf6 6. Be3 Bd6 7. Be2"] = "0-0";
        book["1. e4 e5 2. Nf3 Nc6 3. c3 d5 4. exd5 Qxd5 5. d4 Nf6 6. Be3 Bd6 7. Nbd2"] = "exd4";
        book["1. e4 e5 2. Nf3 Nc6 3. c3 d5 4. exd5 Qxd5 5. d4 Nf6 6. Be3 Bd6 7. Nbd2 exd4 8. cxd4"] = "0-0";
        book["1. e4 e5 2. Nf3 Nc6 3. c3 d5 4. exd5 Qxd5 5. d4 Nf6 6. Be3 Bd6 7. Nbd2 exd4 8. Bxd4"] = "Nxd4";
        book["1. e4 e5 2. Nf3 Nc6 3. c3 d5 4. exd5 Qxd5 5. d4 Nf6 6. Be3 Bd6 7. Nbd2 exd4 8. Bxd4 Nxd4 9. cxd4"] = "0-0";
        book["1. e4 e5 2. Nf3 Nc6 3. c3 d5 4. exd5 Qxd5 5. d4 Nf6 6. Be3 Bd6 7. Nbd2 exd4 8. Bxd4 Nxd4 9. Nxd4"] = "0-0";
        book["1. e4 e5 2. Nf3 Nc6 3. c3 d5 4. exd5 Qxd5 5. d4 Nf6 6. Be3 Bd6 7. Nbd2 exd4 8. Nxd4"] = "Nxd4";
        book["1. e4 e5 2. Nf3 Nc6 3. c3 d5 4. exd5 Qxd5 5. d4 Nf6 6. Be3 Bd6 7. Nbd2 exd4 8. Nxd4 Nxd4 9. Bxd4"] = "0-0";
        book["1. e4 e5 2. Nf3 Nc6 3. c3 d5 4. exd5 Qxd5 5. d4 Nf6 6. Be3 Bd6 7. Nbd2 exd4 8. Nxd4 Nxd4 9. cxd4"] = "0-0";
        book["1. e4 e5 2. Nf3 Nc6 3. c3 d5 4. exd5 Qxd5 5. d4 Nf6 6. Be3 Bd6 7. Nbd2 exd4 8. Bc4"] = "Qh5";
        book["1. e4 e5 2. Nf3 Nc6 3. c3 d5 4. exd5 Qxd5 5. d4 Nf6 6. dxe5"] = "Qxd1+";
        book["1. e4 e5 2. Nf3 Nc6 3. c3 d5 4. exd5 Qxd5 5. d4 Nf6 6. dxe5 Qxd1+ 7. Kxd1"] = "Ng4";
        book["1. e4 e5 2. Nf3 Nc6 3. c3 d5 4. exd5 Qxd5 5. d4 Nf6 6. dxe5 Qxd1+ 7. Kxd1 Ng4 8. Be3"] = "Bf5";
        book["1. e4 e5 2. Nf3 Nc6 3. c3 d5 4. exd5 Qxd5 5. d4 Nf6 6. dxe5 Qxd1+ 7. Kxd1 Ng4 8. Ke1"] = "Bc5";
        book["1. e4 e5 2. Nf3 Nc6 3. c3 d5 4. exd5 Qxd5 5. d4 Nf6 6. dxe5 Qxd1+ 7. Kxd1 Ng4 8. Ke2"] = "Bd7";
        book["1. e4 e5 2. Nf3 Nc6 3. c3 d5 4. exd5 Qxd5 5. d4 Nf6 6. Nxe5"] = "Nxe5";
        book["1. e4 e5 2. Nf3 Nc6 3. c3 d5 4. exd5 Qxd5 5. d4 Nf6 6. Nxe5 Nxe5 7. Qe2"] = "Bd6";
        book["1. e4 e5 2. Nf3 Nc6 3. c3 d5 4. exd5 Qxd5 5. d4 Nf6 6. Nxe5 Nxe5 7. dxe5"] = "Qxd1+";
        book["1. e4 e5 2. Nf3 Nc6 3. c3 d5 4. exd5 Qxd5 5. d4 Nf6 6. Nxe5 Nxe5 7. dxe5 Qxd1+ 8. Kxd1"] = "Ng4";
        book["1. e4 e5 2. Nf3 Nc6 3. c3 d5 4. exd5 Qxd5 5. d4 Nf6 6. Nxe5 Nxe5 7. dxe5 Qxd1+ 8. Kxd1 Ng4 9. Be3"] = "Bf5";
        book["1. e4 e5 2. Nf3 Nc6 3. c3 d5 4. exd5 Qxd5 5. d4 Nf6 6. Nxe5 Nxe5 7. dxe5 Qxd1+ 8. Kxd1 Ng4 9. Ke1"] = "Bc5";
        book["1. e4 e5 2. Nf3 Nc6 3. c3 d5 4. exd5 Qxd5 5. d4 Nf6 6. Nxe5 Nxe5 7. dxe5 Qxd1+ 8. Kxd1 Ng4 9. Ke2"] = "Bc5";
        book["1. e4 e5 2. Nf3 Nc6 3. c3 d5 4. exd5 Qxd5 5. Be2"] = "e5";
        book["1. e4 e5 2. Nf3 Nc6 3. c3 d5 4. exd5 Qxd5 5. Be2 e4 6. Nd4"] = "Nxd4";
        book["1. e4 e5 2. Nf3 Nc6 3. c3 d5 4. exd5 Qxd5 5. Be2 e4 6. Nd4 Nxd4 7. cxd4"] = "Qxd4";


        // C45 Scotch, Schmidt variation -- BLACK
        book["1. e4 e5 2. Nf3 Nc6 3. d4"] = "exd4";
        book["1. e4 e5 2. Nf3 Nc6 3. d4 exd4 4. Bc4"] = "Nf6";
        book["1. e4 e5 2. Nf3 Nc6 3. d4 exd4 4. Bc4 Nf6 5. e5"]= "d5";
        book["1. e4 e5 2. Nf3 Nc6 3. d4 exd4 4. Bc4 Nf6 5. Ng5"]= "d5";
        book["1. e4 e5 2. Nf3 Nc6 3. d4 exd4 4. Bc4 Nf6 5. Nxd4"]= "Nxe4";
        book["1. e4 e5 2. Nf3 Nc6 3. d4 exd4 4. Bc4 Nf6 5. 0-0"]= "Nxe4";
        book["1. e4 e5 2. Nf3 Nc6 3. d4 exd4 4. Bc4 Nf6 5. 0-0 Nxe4 6. Nxd4"] = "d5";
        book["1. e4 e5 2. Nf3 Nc6 3. d4 exd4 4. Bc4 Nf6 5. 0-0 Nxe4 6. Re1"] = "d5";
        book["1. e4 e5 2. Nf3 Nc6 3. d4 exd4 4. Bc4 Nf6 5. 0-0 Nxe4 6. Re1 d5 7. Bxd5"] = "Qxd5";
        book["1. e4 e5 2. Nf3 Nc6 3. d4 exd4 4. Bc4 Nf6 5. 0-0 Nxe4 6. Re1 d5 7. Bxd5 Qxd5 8. Nc3"] = "Qa5";
        book["1. e4 e5 2. Nf3 Nc6 3. d4 exd4 4. Bc4 Nf6 5. 0-0 Nxe4 6. Re1 d5 7. Bxd5 Qxd5 8. Nc3 Qa5 9. Nxe4"] = "Be6";
        book["1. e4 e5 2. Nf3 Nc6 3. d4 exd4 4. Bc4 Nf6 5. 0-0 Nxe4 6. Re1 d5 7. Bxd5 Qxd5 8. Nc3 Qa5 9. Nxe4 Be6 10. Neg5"] = "0-0-0";
        book["1. e4 e5 2. Nf3 Nc6 3. d4 exd4 4. Bc4 Nf6 5. 0-0 Nxe4 6. Re1 d5 7. Bxd5 Qxd5 8. Nc3 Qa5 9. Nxe4 Be6 10. c3"] = "0-0-0";
        book["1. e4 e5 2. Nf3 Nc6 3. d4 exd4 4. Bc4 Nf6 5. 0-0 Nxe4 6. Re1 d5 7. Bxd5 Qxd5 8. Nc3 Qa5 9. Nxe4 Be6 10. c3 0-0-0 11. Bg5"] = "f6";
        book["1. e4 e5 2. Nf3 Nc6 3. d4 exd4 4. Bc4 Nf6 5. 0-0 Nxe4 6. Re1 d5 7. Bxd5 Qxd5 8. Nc3 Qa5 9. Nxe4 Be6 10. c3 0-0-0 11. Bg5 f6 12. Nxf6"] = "dxc3";
        book["1. e4 e5 2. Nf3 Nc6 3. d4 exd4 4. Bc4 Nf6 5. 0-0 Nxe4 6. Re1 d5 7. Bxd5 Qxd5 8. Nc3 Qa5 9. Nxe4 Be6 10. c3 0-0-0 11. cxd4"] = "Bb4";
        book["1. e4 e5 2. Nf3 Nc6 3. d4 exd4 4. Bc4 Nf6 5. 0-0 Nxe4 6. Re1 d5 7. Bxd5 Qxd5 8. Nc3 Qa5 9. Nxe4 Be6 10. c3 0-0-0 11. cxd4 Bb4 12. Bd2"] = "Bxd2";
        book["1. e4 e5 2. Nf3 Nc6 3. d4 exd4 4. Bc4 Nf6 5. 0-0 Nxe4 6. Re1 d5 7. Bxd5 Qxd5 8. Nc3 Qa5 9. Nxe4 Be6 10. c3 0-0-0 11. cxd4 Bb4 12. Rf1"] = "Bc4";


        book["1. e4 e5 2. Nf3 Nc6 3. d4 exd4 4. Bc4 Nf6 5. 0-0 Nxe4 6. c3"] = "d5";
        book["1. e4 e5 2. Nf3 Nc6 3. d4 exd4 4. Bc4 Nf6 5. 0-0 Nxe4 6. c3 d5 7. Bb3"] = "Bg4";
        book["1. e4 e5 2. Nf3 Nc6 3. d4 exd4 4. Bc4 Nf6 5. 0-0 Nxe4 6. c3 d5 7. Bd3"] = "Bd6";
        book["1. e4 e5 2. Nf3 Nc6 3. d4 exd4 4. Bc4 Nf6 5. 0-0 Nxe4 6. c3 d5 7. Bb5"] = "Bd6";
        book["1. e4 e5 2. Nf3 Nc6 3. d4 exd4 4. Bc4 Nf6 5. 0-0 Nxe4 6. c3 d5 7. Qe2"] = "dxc4";
        book["1. e4 e5 2. Nf3 Nc6 3. d4 exd4 4. Bc4 Nf6 5. 0-0 Nxe4 6. c3 d5 7. Qe2 dxc4 8. Qxe4+"] = "Be6";
        book["1. e4 e5 2. Nf3 Nc6 3. d4 exd4 4. Bc4 Nf6 5. 0-0 Nxe4 6. c3 d5 7. Re1"] = "Be7";
        book["1. e4 e5 2. Nf3 Nc6 3. d4 exd4 4. Bc4 Nf6 5. 0-0 Nxe4 6. c3 d5 7. Re1 Be7 8. Bb5"] = "0-0";
        book["1. e4 e5 2. Nf3 Nc6 3. d4 exd4 4. Bc4 Nf6 5. 0-0 Nxe4 6. c3 d5 7. Re1 Be7 8. Bb3"] = "0-0";
        book["1. e4 e5 2. Nf3 Nc6 3. d4 exd4 4. Bc4 Nf6 5. 0-0 Nxe4 6. c3 d5 7. Re1 Be7 8. Bd3"] = "Bg4";
        book["1. e4 e5 2. Nf3 Nc6 3. d4 exd4 4. Bc4 Nf6 5. 0-0 Nxe4 6. c3 d5 7. Re1 Be7 8. Bd3 Bg4 9. Be2"] = "dxc3";
        book["1. e4 e5 2. Nf3 Nc6 3. d4 exd4 4. Bc4 Nf6 5. 0-0 Nxe4 6. c3 d5 7. Re1 Be7 8. Be2"] = "dxc3";


        book["1. e4 e5 2. Nf3 Nc6 3. d4 exd4 4. Nxd4 Nf6 5. e5"] = "Nxe5";
        book["1. e4 e5 2. Nf3 Nc6 3. d4 exd4 4. Nxd4 Nf6 5. e5 Nxe5 6. Qe2"] = "Qe7";
        book["1. e4 e5 2. Nf3 Nc6 3. d4 exd4 4. Nxd4 Nf6 5. e5 Nxe5 6. Qe2 Qe7 7. Nc3"] = "Nc6";
        book["1. e4 e5 2. Nf3 Nc6 3. d4 exd4 4. Nxd4 Nf6 5. e5 Nxe5 6. Qe2 Qe7 7. Nc3 Nc6 8. Ndb5"] = "Qxe2+";
        book["1. e4 e5 2. Nf3 Nc6 3. d4 exd4 4. Nxd4 Nf6 5. e5 Nxe5 6. Qe2 Qe7 7. Nc3 Nc6 8. Ndb5 Qxe2+ 9. Bxe2"] = "Kd8";
        book["1. e4 e5 2. Nf3 Nc6 3. d4 exd4 4. Nxd4 Nf6 5. e5 Nxe5 6. Qe2 Qe7 7. Nc3 Nc6 8. Nxc6"] = "dxc6";
        book["1. e4 e5 2. Nf3 Nc6 3. d4 exd4 4. Nxd4 Nf6 5. e5 Nxe5 6. Qe2 Qe7 7. Nc3 Nc6 8. Nxc6 dxc6 9. Bg5"] = "Qxe2+";
        book["1. e4 e5 2. Nf3 Nc6 3. d4 exd4 4. Nxd4 Nf6 5. e5 Nxe5 6. Qe2 Qe7 7. Nc3 Nc6 8. Nxc6 dxc6 9. Bg5 Qxe2+ 10. Bxe2"] = "Be6";
        book["1. e4 e5 2. Nf3 Nc6 3. d4 exd4 4. Nxd4 Nf6 5. e5 Nxe5 6. Bg5"] = "h6";
        book["1. e4 e5 2. Nf3 Nc6 3. d4 exd4 4. Nxd4 Nf6 5. e5 Nxe5 6. Bg5 h6 7. f4"] = "hxg5";
        book["1. e4 e5 2. Nf3 Nc6 3. d4 exd4 4. Nxd4 Nf6 5. e5 Nxe5 6. Bg5 h6 7. f4 hxg5 8. fxe5"] = "Nd5";
        book["1. e4 e5 2. Nf3 Nc6 3. d4 exd4 4. Nxd4 Nf6 5. e5 Nxe5 6. Bg5 h6 7. Bf4"] = "c6";
        book["1. e4 e5 2. Nf3 Nc6 3. d4 exd4 4. Nxd4 Nf6 5. e5 Nxe5 6. Bg5 h6 7. Bh4"] = "d5";
        book["1. e4 e5 2. Nf3 Nc6 3. d4 exd4 4. Nxd4 Nf6 5. e5 Nxe5 6. Bg5 h6 7. Be3"] = "d5";
        book["1. e4 e5 2. Nf3 Nc6 3. d4 exd4 4. Nxd4 Nf6 5. e5 Nxe5 6. Bg5 h6 7. Bxf6"] = "Qxf6";


        book["1. e4 e5 2. Nf3 Nc6 3. d4 exd4 4. c3"] = "dxc3";
        book["1. e4 e5 2. Nf3 Nc6 3. d4 exd4 4. Nxd4"] = "Nf6";
        book["1. e4 e5 2. Nf3 Nc6 3. d4 exd4 4. Nxd4 Nf6 5. Nxc6"] = "bxc6";
        book["1. e4 e5 2. Nf3 Nc6 3. d4 exd4 4. Nxd4 Nf6 5. Nxc6 bxc6 6. e5"] = "Qe7";
        book["1. e4 e5 2. Nf3 Nc6 3. d4 exd4 4. Nxd4 Nf6 5. Nxc6 bxc6 6. e5 Qe7 7. Qe2"] = "Nd5";
        book["1. e4 e5 2. Nf3 Nc6 3. d4 exd4 4. Nxd4 Nf6 5. Nxc6 bxc6 6. e5 Qe7 7. Qe2 Nd5 8. c4"] = "Ba6";
        book["1. e4 e5 2. Nf3 Nc6 3. d4 exd4 4. Nxd4 Nf6 5. Nxc6 bxc6 6. e5 Qe7 7. Qe2 Nd5 8. c4 Ba6 9. b3"] = "g6";
        book["1. e4 e5 2. Nf3 Nc6 3. d4 exd4 4. Nxd4 Nf6 5. Nxc6 bxc6 6. e5 Qe7 7. Qe2 Nd5 8. c4 Ba6 9. Bd2"] = "Nb6";
        book["1. e4 e5 2. Nf3 Nc6 3. d4 exd4 4. Nxd4 Nf6 5. Nxc6 bxc6 6. e5 Qe7 7. Qe2 Nd5 8. c4 Ba6 9. Bd2 Nb6 10. b3"] = "g6";

        book["1. e4 e5 2. Nf3 Nc6 3. d4 exd4 4. Nxd4 Nf6 5. Nxc6 bxc6 6. Nc3"] = "Bb4";

        book["1. e4 e5 2. Nf3 Nc6 3. d4 exd4 4. Nxd4 Nf6 5. Nxc6 bxc6 6. Bd3"] = "d5";
        book["1. e4 e5 2. Nf3 Nc6 3. d4 exd4 4. Nxd4 Nf6 5. Nxc6 bxc6 6. Bd3 d5 7. exd5"] = "cxd5";
        book["1. e4 e5 2. Nf3 Nc6 3. d4 exd4 4. Nxd4 Nf6 5. Nxc6 bxc6 6. Bd3 d5 7. e5"] = "Ng4";
        book["1. e4 e5 2. Nf3 Nc6 3. d4 exd4 4. Nxd4 Nf6 5. Nxc6 bxc6 6. Bd3 d5 7. Nc3"] = "Bb4";
        book["1. e4 e5 2. Nf3 Nc6 3. d4 exd4 4. Nxd4 Nf6 5. Nxc6 bxc6 6. Bd3 d5 7. Qe2"] = "dxe4";
        book["1. e4 e5 2. Nf3 Nc6 3. d4 exd4 4. Nxd4 Nf6 5. Nxc6 bxc6 6. Bd3 d5 7. Qe2 dxe4 8. Nc3"] = "Bb4";
        book["1. e4 e5 2. Nf3 Nc6 3. d4 exd4 4. Nxd4 Nf6 5. Nxc6 bxc6 6. Bd3 d5 7. Qe2 dxe4 8. Bxe4"] = "Nxe4";
        book["1. e4 e5 2. Nf3 Nc6 3. d4 exd4 4. Nxd4 Nf6 5. Nxc6 bxc6 6. Bd3 d5 7. Qe2 dxe4 8. Bxe4 Nxe4 9. Qxe4+"] = "Qe7";

        book["1. e4 e5 2. Nf3 Nc6 3. d4 exd4 4. Nxd4 Nf6 5. Nc3"] = "Bb4";
        book["1. e4 e5 2. Nf3 Nc6 3. d4 exd4 4. Nxd4 Nf6 5. Nc3 Bb4 6. Bd3"] = "0-0";

        book["1. e4 e5 2. Nf3 Nc6 3. d4 exd4 4. Nxd4 Nf6 5. Nc3 Bb4 6. Nxc6"] = "bxc6";
        book["1. e4 e5 2. Nf3 Nc6 3. d4 exd4 4. Nxd4 Nf6 5. Nc3 Bb4 6. Nxc6 bxc6 7. Bd2"] = "Qe7";
        book["1. e4 e5 2. Nf3 Nc6 3. d4 exd4 4. Nxd4 Nf6 5. Nc3 Bb4 6. Nxc6 bxc6 7. Bd3"] = "d5";
        book["1. e4 e5 2. Nf3 Nc6 3. d4 exd4 4. Nxd4 Nf6 5. Nc3 Bb4 6. Nxc6 bxc6 7. Bd3 d5 8. exd5"] = "0-0";
        book["1. e4 e5 2. Nf3 Nc6 3. d4 exd4 4. Nxd4 Nf6 5. Nc3 Bb4 6. Nxc6 bxc6 7. Bd3 d5 8. 0-0"] = "Bxc3";
        book["1. e4 e5 2. Nf3 Nc6 3. d4 exd4 4. Nxd4 Nf6 5. Nc3 Bb4 6. Nxc6 bxc6 7. Bd3 d5 8. 0-0 Bxc3 9. bxc3"] = "dxe4";


        // C21 Centre game -- BLACK
        book["1. e4 e5 2. d4"] = "exd4";
        book["1. e4 e5 2. d4 exd4 3. Qxd4"] = "Nc6";
        book["1. e4 e5 2. d4 exd4 3. c3"] = "dxc3";
        book["1. e4 e5 2. d4 exd4 3. c3 dxc3 4. Bc4"] = "cxb2";
        book["1. e4 e5 2. d4 exd4 3. c3 dxc3 4. Bc4 cxb2 5. Bxb2"] = "Bb4+";
        book["1. e4 e5 2. d4 exd4 3. c3 dxc3 4. Bc4 cxb2 5. Bxb2 Bb4+ 6. Bc3"] = "Bxc3+";
        book["1. e4 e5 2. d4 exd4 3. c3 dxc3 4. Bc4 cxb2 5. Bxb2 Bb4+ 6. Bc3 Bxc3+ 7. Nxc3"] = "Nc6";
        book["1. e4 e5 2. d4 exd4 3. c3 dxc3 4. Bc4 cxb2 5. Bxb2 Bb4+ 6. Nc3"] = "Nf6";
        book["1. e4 e5 2. d4 exd4 3. c3 dxc3 4. Bc4 cxb2 5. Bxb2 Bb4+ 6. Nd2"] = "Nf6";
        book["1. e4 e5 2. d4 exd4 3. c3 dxc3 4. Bc4 cxb2 5. Bxb2 Bb4+ 6. Nd2 Nf6 7. e5"] = "d5";
        book["1. e4 e5 2. d4 exd4 3. c3 dxc3 4. Bc4 cxb2 5. Bxb2 Bb4+ 6. Nd2 Nf6 7. e5 d5 8. exf6"] = "dxc4";
        book["1. e4 e5 2. d4 exd4 3. c3 dxc3 4. Bc4 cxb2 5. Bxb2 Bb4+ 6. Nd2 Nf6 7. e5 d5 8. exf6 dxc4 9. fxg7"] = "Rg8";
        book["1. e4 e5 2. d4 exd4 3. c3 dxc3 4. Bc4 cxb2 5. Bxb2 Bb4+ 6. Nd2 Nf6 7. Bxf7+"] = "Kxf7";
        book["1. e4 e5 2. d4 exd4 3. c3 dxc3 4. Bc4 cxb2 5. Bxb2 Bb4+ 6. Nd2 Nf6 7. Bxf7+ Kxf7 8. Qb3+"] = "d5";
        book["1. e4 e5 2. d4 exd4 3. c3 dxc3 4. Bc4 cxb2 5. Bxb2 Bb4+ 6. Nd2 Nf6 7. Bxf7+ Kxf7 8. Qb3+ d5 9. Qxb4"] = "Re8";
        book["1. e4 e5 2. d4 exd4 3. c3 dxc3 4. Bc4 cxb2 5. Bxb2 Bb4+ 6. Nd2 Nf6 7. a3"] = "Ba5";
        book["1. e4 e5 2. d4 exd4 3. c3 dxc3 4. Bc4 cxb2 5. Bxb2 Bb4+ 6. Nd2 Nf6 7. Nf3"] = "0-0";
        book["1. e4 e5 2. d4 exd4 3. c3 dxc3 4. Bc4 cxb2 5. Bxb2 Bb4+ 6. Nd2 Nf6 7. Nf3 0-0 8. 0-0"] = "d6";
        book["1. e4 e5 2. d4 exd4 3. c3 dxc3 4. Bc4 cxb2 5. Bxb2 Bb4+ 6. Nd2 Nf6 7. Nf3 0-0 8. 0-0 d6 9. Nb3"] = "Nbd7";

        book["1. e4 e5 2. d4 exd4 3. c3 dxc3 4. Nxc3"] = "Bc5";
        book["1. e4 e5 2. d4 exd4 3. Bc4"] = "Nf6";
        book["1. e4 e5 2. d4 exd4 3. Nf3"] = "Nc6";
        book["1. e4 e5 2. d4 exd4 3. Nf3 Nc6 4. Nxd4"] = "Nf6";
        book["1. e4 e5 2. d4 exd4 3. Nf3 Nc6 4. Nxd4 Nf6 5. Nc3"] = "Bb4";
        book["1. e4 e5 2. d4 exd4 3. Nf3 Nc6 4. Nxd4 Nf6 5. Nxc6"] = "bxc6";


        // C00 French defence -- WHITE
        book["1. e4 e6 2. d4 d5"] = "Nc3";
        book["1. e4 e6 2. d4 d5 3. Nc3 Bb4"] = "exd5";

        book["1. e4 e6 2. d4 c6"] = "Be3";
        book["1. e4 e6 2. d4 c6 3. Be3 d5"] = "Nd2";
        book["1. e4 e6 2. d4 c6 3. Be3 Nf6"] = "Bd3";

        book["1. e4 e6 2. d4 d5"] = "Nc3";

        book["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. exd5 Ne7"] = "dxe6";
        book["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. exd5 Ne7 5. dxe6 Bxe6"] = "Nf3";
        book["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. exd5 Ne7 5. dxe6 0-0"] = "exf7+";
        book["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. exd5 Ne7 5. dxe6 0-0 6. exf7+ Rxf7"] = "Bd3";
        book["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. exd5 Ne7 5. dxe6 0-0 6. exf7+ Rxf7 7. Bd3 Bf5"] = "a3";
        book["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. exd5 Ne7 5. dxe6 0-0 6. exf7+ Rxf7 7. Bd3 Ng6"] = "Bc4";

        book["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. exd5 exd5"] = "Bd3";

        book["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. exd5 exd5 5. Bd3 Nf6"] = "Ne2";
        book["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. exd5 exd5 5. Bd3 Nf6 6. Ne2 Bg4"] = "f3";
        book["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. exd5 exd5 5. Bd3 Nf6 6. Ne2 Bg4 7. f3 Be6"] = "Be3";
        book["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. exd5 exd5 5. Bd3 Nf6 6. Ne2 Bg4 7. f3 Bd7"] = "Bg5";
        book["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. exd5 exd5 5. Bd3 Nf6 6. Ne2 Bg4 7. f3 Bh5"] = "h4";
        book["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. exd5 exd5 5. Bd3 Nf6 6. Ne2 c6"] = "0-0";
        book["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. exd5 exd5 5. Bd3 Nf6 6. Ne2 Nc6"] = "0-0";
        book["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. exd5 exd5 5. Bd3 Nf6 6. Ne2 0-0"] = "0-0";
        book["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. exd5 exd5 5. Bd3 Nf6 6. Ne2 0-0 7. 0-0 c6"] = "a3";
        book["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. exd5 exd5 5. Bd3 Nf6 6. Ne2 0-0 7. 0-0 Re8"] = "a3";
        book["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. exd5 exd5 5. Bd3 Nf6 6. Ne2 0-0 7. 0-0 Bg4"] = "f3";
        book["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. exd5 exd5 5. Bd3 Nf6 6. Ne2 0-0 7. 0-0 Bg4 8. f3 Bh5"] = "Nf4";
        book["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. exd5 exd5 5. Bd3 Nf6 6. Ne2 0-0 7. 0-0 Bg4 8. f3 Bh5 9. Nf4 Bg6"] = "Nxg6";
        book["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. exd5 exd5 5. Bd3 Nf6 6. Ne2 0-0 7. 0-0 Bg4 8. f3 Bh5 9. Nf4 Bg6 10. Nxg6 fxg6"] = "Ne2";
        book["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. exd5 exd5 5. Bd3 Nf6 6. Ne2 0-0 7. 0-0 Bg4 8. f3 Bh5 9. Nf4 Bg6 10. Nxg6 hxg6"] = "f4";
        book["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. exd5 exd5 5. Bd3 Nf6 6. Ne2 0-0 7. 0-0 Bg4 8. f3 Bh5 9. Nf4 Bxc3"] = "bxc3";
        book["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. exd5 exd5 5. Bd3 Nf6 6. Ne2 0-0 7. 0-0 Bg4 8. f3 Bh5 9. Nf4 Bxc3 10. bxc3 Bg6"] = "Nxg6";
        book["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. exd5 exd5 5. Bd3 Nf6 6. Ne2 0-0 7. 0-0 Bg4 8. f3 Bh5 9. Nf4 Bxc3 10. bxc3 Bg6 11. Nxg6 fxg6"] = "c4";
        book["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. exd5 exd5 5. Bd3 Nf6 6. Ne2 0-0 7.  0-0 Bg4 8. f3 Bh5 9. Nf4 Bxc3 10. bxc3 Bg6 11. Nxg6 hxg6"] = "Rb1";

        book["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. exd5 exd5 5. Bd3 Nf6 6. Ne2 0-0 7. 0-0 Bg4 8. f3 Be6"] = "Bg5";
        book["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. exd5 exd5 5. Bd3 Nf6 6. Ne2 0-0 7. 0-0 Bg4 8. f3 Bd7"] = "Bg5";
        book["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. exd5 exd5 5. Bd3 Nf6 6. Ne2 0-0 7. 0-0 h6"] = "a3";
        book["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. exd5 exd5 5. Bd3 Nf6 6. Ne2 0-0 7. 0-0 h6 8. a3 Ba5"] = "b4";
        book["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. exd5 exd5 5. Bd3 Nf6 6. Ne2 0-0 7. 0-0 h6 8. a3 Ba5 9. b4 Bb6"] = "Na4";
        book["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. exd5 exd5 5. Bd3 Nf6 6. Ne2 0-0 7. 0-0 h6 8. a3 Bd6"] = "Nb5";
        book["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. exd5 exd5 5. Bd3 Nf6 6. Ne2 0-0 7. 0-0 h6 8. a3 Be7"] = "Bf4";
        book["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. exd5 exd5 5. Bd3 Nf6 6. Ne2 0-0 7. 0-0 Nc6"] = "a3";
        book["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. exd5 exd5 5. Bd3 Nf6 6. Ne2 0-0 7. 0-0 Nc6 8. a3 Bxc3"] = "bxc3";
        book["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. exd5 exd5 5. Bd3 Nf6 6. Ne2 0-0 7. 0-0 Nc6 8. a3 Ba5"] = "Bg5";
        book["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. exd5 exd5 5. Bd3 Nf6 6. Ne2 0-0 7. 0-0 Nc6 8. a3 Bd6"] = "Bg5";
        book["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. exd5 exd5 5. Bd3 Nf6 6. Ne2 0-0 7. 0-0 Nc6 8. a3 Be7"] = "Re1";

        book["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. exd5 exd5 5. Bd3 Ne7"] = "Qh5";
        book["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. exd5 exd5 5. Bd3 c6"] = "Nf3";
        book["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. exd5 exd5 5. Bd3 c5"] = "dxc5";
        book["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. exd5 exd5 5. Bd3 c5 6. dxc5 Bxc5"] = "Bb5+";
        book["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. exd5 exd5 5. Bd3 c5 6. dxc5 Nc6"] = "Nf3";
        book["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. exd5 exd5 5. Bd3 c5 6. dxc5 Nf6"] = "Ne2";
        book["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. exd5 exd5 5. Bd3 c5 6. dxc5 Nf6 7. Ne2 Bxc5"] = "0-0";
        book["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. exd5 exd5 5. Bd3 c5 6. dxc5 Nf6 7. Ne2 0-0"] = "0-0";
        book["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. exd5 exd5 5. Bd3 c5 6. dxc5 Nf6 7.  Ne2 0-0 8. 0-0 Bxc5"] = "Bg5";
        book["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. exd5 exd5 5. Bd3 c5 6. dxc5 d4"] = "a3";
        book["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. exd5 exd5 5. Bd3 Nc6"] = "Nf3";

        book["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. exd5 Qxd5"] = "Nf3";
        book["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. exd5 Bxc3+"] = "bxc3";
        book["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. exd5 Bxc3+ 5. bxc3 exd5"] = "Bb5+";
        book["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. exd5 Bxc3+ 5. bxc3 exd5 6. Bb5+ c6"] = "Bd3";
        book["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. exd5 Bxc3+ 5. bxc3 exd5 6. Bb5+ c6 7. Bd3 Ne7"] = "Qh5";
        book["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. exd5 Bxc3+ 5. bxc3 exd5 6. Bb5+ c6 7. Bd3 Nf6"] = "Ba3";
        book["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. exd5 Bxc3+ 5. bxc3 exd5 6. Bb5+ c6 7. Bd3 Be6"] = "Ne2";
        book["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. exd5 Bxc3+ 5. bxc3 exd5 6. Bb5+ c6 7. Bd3 Qa5"] = "Rb1";
        book["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. exd5 Bxc3+ 5. bxc3 exd5 6. Bb5+ c6 7. Bd3 c5"] = "dxc5";

        book["1. e4 e6 2. d4 d5 3. Nc3 Nf6"] = "Bg5";
        book["1. e4 e6 2. d4 d5 3. Nc3 Nf6 4. Bg5 dxe4"] = "Nxe4";
        book["1. e4 e6 2. d4 d5 3. Nc3 Nf6 4. Bg5 dxe4 5. Nxe4 Be7"] = "Bxf6";
        book["1. e4 e6 2. d4 d5 3. Nc3 Nf6 4. Bg5 dxe4 5. Nxe4 Be7 6. Bxf6 Bxf6"] = "Nf3";
        book["1. e4 e6 2. d4 d5 3. Nc3 Nf6 4. Bg5 dxe4 5. Nxe4 Nbd7"] = "Nf3";

        book["1. e4 e6 2. d4 d5 3. Nc3 Nf6 4. Bg5 Be7"] = "e5";
        book["1. e4 e6 2. d4 d5 3. Nc3 Nf6 4. Bg5 Be7 5. e5 Ne4"] = "Nxe4";
        book["1. e4 e6 2. d4 d5 3. Nc3 Nf6 4. Bg5 Be7 5. e5 Ne4 6. Nxe4 dxe4"] = "h4";

        book["1. e4 e6 2. d4 d5 3. Nc3 Nf6 4. Bg5 Be7 5. e5 Nfd7"] = "Bxe7";
        book["1. e4 e6 2. d4 d5 3. Nc3 Nf6 4. Bg5 Be7 5. e5 Nfd7 6. Bxe7 Qxe7"] = "f4";
        book["1. e4 e6 2. d4 d5 3. Nc3 Nf6 4. Bg5 Be7 5. e5 Nfd7 6. Bxe7 Qxe7 7. f4 0-0"] = "Nf3";
        book["1. e4 e6 2. d4 d5 3. Nc3 Nf6 4. Bg5 Be7 5. e5 Nfd7 6. Bxe7 Qxe7 7. f4 0-0 8. Nf3 c5"] = "dxc5";
        book["1. e4 e6 2. d4 d5 3. Nc3 Nf6 4. Bg5 Be7 5. e5 Nfd7 6. Bxe7 Qxe7 7. f4 0-0 8. Nf3 c5 9. dxc5 Qxc5"] = "Qd2";
        book["1. e4 e6 2. d4 d5 3. Nc3 Nf6 4. Bg5 Be7 5. e5 Nfd7 6. Bxe7 Qxe7 7. f4 0-0 8. Nf3 c5 9. dxc5 Nxc5"] = "Qd4";
        book["1. e4 e6 2. d4 d5 3. Nc3 Nf6 4. Bg5 Be7 5. e5 Nfd7 6. Bxe7 Qxe7 7. f4 0-0 8. Nf3 c5 9. dxc5 Nc6"] = "Qd2";
        book["1. e4 e6 2. d4 d5 3. Nc3 Nf6 4. Bg5 Be7 5. e5 Nfd7 6. Bxe7 Qxe7 7. f4 0-0 8. Nf3 c5 9. dxc5 a6"] = "Bd3";
        book["1. e4 e6 2. d4 d5 3. Nc3 Nf6 4. Bg5 Be7 5. e5 Nfd7 6. Bxe7 Qxe7 7. f4 0-0 8. Nf3 f5"] = "Qd2";
        book["1. e4 e6 2. d4 d5 3. Nc3 Nf6 4. Bg5 Be7 5. e5 Nfd7 6. Bxe7 Qxe7 7. f4 0-0 8. Nf3 f5 9. Qd2 c5"] ="Nb5";

        book["1. e4 e6 2. d4 d5 3. Nc3 Nf6 4. Bg5 Be7 5. e5 Nfd7 6. Bxe7 Qxe7 7. f4 a6"] = "Qg4";
        book["1. e4 e6 2. d4 d5 3. Nc3 Nf6 4. Bg5 Be7 5. e5 Nfd7 6. Bxe7 Qxe7 7. f4 a6 8. Qg4 f6"] = "Nf3";
        book["1. e4 e6 2. d4 d5 3. Nc3 Nf6 4. Bg5 Be7 5. e5 Nfd7 6. Bxe7 Qxe7 7. f4 a6 8. Qg4 0-0"] = "Bd3";
        book["1. e4 e6 2. d4 d5 3. Nc3 Nf6 4. Bg5 Be7 5. e5 Nfd7 6. Bxe7 Qxe7 7. f4 a6 8. Qg4 g6"] = "Nf3";
        book["1. e4 e6 2. d4 d5 3. Nc3 Nf6 4. Bg5 Be7 5. e5 Nfd7 6. Bxe7 Qxe7 7. f4 a6 8. Qg4 g6 9. Nf3 b5"] = "a3";
        book["1. e4 e6 2. d4 d5 3. Nc3 Nf6 4. Bg5 Be7 5. e5 Nfd7 6. Bxe7 Qxe7 7. f4 a6 8. Qg4 g6 9. Nf3 c5"] = "dxc5";
        book["1. e4 e6 2. d4 d5 3. Nc3 Nf6 4. Bg5 Be7 5. e5 Nfd7 6. Bxe7 Qxe7 7. f4 a6 8. Qg4 g6 9. Nf3 h5"] = "Qg3";

        book["1. e4 e6 2. d4 d5 3. Nc3 dxe4"] = "Nxe4";
        book["1. e4 e6 2. d4 d5 3. Nc3 dxe4 4. Nxe4 Nd7"] = "Nf3";
        book["1. e4 e6 2. d4 d5 3. Nc3 dxe4 4. Nxe4 Bd7"] = "Nf3";
        book["1. e4 e6 2. d4 d5 3. Nc3 dxe4 4. Nxe4 Be7"] = "Nf3";
        book["1. e4 e6 2. d4 d5 3. Nc3 dxe4 4. Nxe4 Qd5"] = "Bd3";
        book["1. e4 e6 2. d4 d5 3. Nc3 dxe4 4. Nxe4 Nf6"] = "Nxf6+";
        book["1. e4 e6 2. d4 d5 3. Nc3 dxe4 4. Nxe4 Nf6 5. Nxf6+ gxf6"] = "Be3";
        book["1. e4 e6 2. d4 d5 3. Nc3 dxe4 4. Nxe4 Nf6 5. Nxf6+ Qxf6"] = "Nf3";
        book["1. e4 e6 2. d4 d5 3. Nc3 dxe4 4. Nxe4 Nf6 5. Nxf6+ Qxf6 6. Nf3 h6"] = "Bd3";
        book["1. e4 e6 2. d4 d5 3. Nc3 dxe4 4. Nxe4 Nf6 5. Nxf6+ Qxf6 6. Nf3 Bd6"] = "Bd3";
        book["1. e4 e6 2. d4 d5 3. Nc3 dxe4 4. Nxe4 Nf6 5. Nxf6+ Qxf6 6. Nf3 Nc6"] = "Bd3";

        book["1. e4 e6 2. d4 d5 3. Nc3 Nc6"] = "e5";
        book["1. e4 e6 2. d4 d5 3. Nc3 Be7"] = "Bd3";
        book["1. e4 e6 2. d4 d5 3. Nc3 c5"] = "exd5";
        book["1. e4 e6 2. d4 d5 3. Nc3 c5 4. exd5 cxd4"] = "Bb5+";
        book["1. e4 e6 2. d4 d5 3. Nc3 c5 4. exd5 exd5"] = "Bb5+";


        book["1. e4 e6 2. d4 c5"] = "d5";

        book["1. e4 e6 2. d4 b6"] = "Bd3";
        book["1. e4 e6 2. d4 b6 3. Bd3 Bg7"] = "Nf3";
        book["1. e4 e6 2. d4 b6 3. Bd3 Bg7 4. Nf3 c5"] = "c3";
        book["1. e4 e6 2. d4 b6 3. Bd3 Bg7 4. Nf3 d6"] = "0-0";
        book["1. e4 e6 2. d4 b6 3. Bd3 Bg7 4. Nf3 g6"] = "Bg5";
        book["1. e4 e6 2. d4 b6 3. Bd3 Bg7 4. Nf3 d5"] = "exd5";
        book["1. e4 e6 2. d4 b6 3. Bd3 Bg7 4. Nf3 Nf6"] = "e5";


        // A45 Queen's pawn game -- BLACK
        book["1. d4 Nf6 2. c4"] = "e6";
        book["1. d4 Nf6 2. Nf3"] = "e6";
        book["1. d4 Nf6 2. Bg5"] = "Ne4";

        book["1. d4 Nf6 2. Bf4"] = "e6";
        book["1. d4 Nf6 2. Bf4 e6 3. Nf3"] = "d5";
        book["1. d4 Nf6 2. Bf4 e6 3. Nf3 d5 4. e3"] = "Bd6";
        book["1. d4 Nf6 2. Bf4 e6 3. Nd2"] = "Nh5";
        book["1. d4 Nf6 2. Bf4 e6 3. Nd2 Nh5 4. Bg3"] = "h6";
        book["1. d4 Nf6 2. Bf4 e6 3. c3"] = "Nh5";
        book["1. d4 Nf6 2. Bf4 e6 3. c3 Nh5 4. Bg3"] = "Nxg3";
        book["1. d4 Nf6 2. Bf4 e6 3. c3 Nh5 4. Bg3 Nxg3 5. hxg3"] = "c5";
        book["1. d4 Nf6 2. Bf4 e6 3. c3 Nh5 4. Bg3 Nxg3 5. fxg3"] = "d5";
        book["1. d4 Nf6 2. Bf4 e6 3. c3 Nh5 4. Bc1"] = "Nf6";
        book["1. d4 Nf6 2. Bf4 e6 3. c3 Nh5 4. Be5"] = "d6";
        book["1. d4 Nf6 2. Bf4 e6 3. c3 Nh5 4. Bd2"] = "Nf6";
        book["1. d4 Nf6 2. Bf4 e6 3. Nc3"] = "d5";
        book["1. d4 Nf6 2. Bf4 e6 3. Nc3 d5 4. Nb5"] = "Na6";
        book["1. d4 Nf6 2. Bf4 e6 3. Nc3 d5 4. e3"] = "Bb4";
        book["1. d4 Nf6 2. Bf4 e6 3. Nc3 d5 4. a3"] = "a6";
        book["1. d4 Nf6 2. Bf4 e6 3. c4"] = "Bb4+";
        book["1. d4 Nf6 2. Bf4 e6 3. c4 Bb4+ 4. Bd2"] = "Be7";
        book["1. d4 Nf6 2. Bf4 e6 3. c4 Bb4+ 4. Nc3"] = "c5";
        book["1. d4 Nf6 2. Bf4 e6 3. e3"] = "c5";
        book["1. d4 Nf6 2. Bf4 e6 3. e3 c5 4. Nf3"] = "d5";

        book["1. d4 Nf6 2. Nc3"] = "d5";
        book["1. d4 Nf6 2. g3"] = "d5";
        book["1. d4 Nf6 2. g3 d5 3. Bg2"] = "c5";
        book["1. d4 Nf6 2. e3"] = "e6";

        book["1. d4 Nf6 2. f4"] = "d5";
        book["1. d4 Nf6 2. f4 d5 3. e3"] = "c5";
        book["1. d4 Nf6 2. f4 d5 3. Nf3"] = "Bf5";


        // E20 Nimzo-Indian defence -- BLACK
        book["1. d4 Nf6 2. c4 e6 3. Nc3"] = "Bb4";

        book["1. d4 Nf6 2. c4 e6 3. e3"] = "d5";
        book["1. d4 Nf6 2. c4 e6 3. e3 d5 4. Nf3"] = "b6";
        book["1. d4 Nf6 2. c4 e6 3. e3 d5 4. Nf3 b6 5. b3"] = "Bb7";
        book["1. d4 Nf6 2. c4 e6 3. e3 d5 4. Nf3 b6 5. Nc3"] = "Bb7";
        book["1. d4 Nf6 2. c4 e6 3. e3 d5 4. Nf3 b6 5. Nc3 Bb7 6. Bd3"] = "Bd6";
        book["1. d4 Nf6 2. c4 e6 3. e3 d5 4. Nf3 b6 5. Bd3"] = "Bd6";
        book["1. d4 Nf6 2. c4 e6 3. e3 d5 4. Nc3"] = "b6";
        book["1. d4 Nf6 2. c4 e6 3. e3 d5 4. Nd2"] = "c5";
        book["1. d4 Nf6 2. c4 e6 3. e3 d5 4. h3"] = "b6";
        book["1. d4 Nf6 2. c4 e6 3. e3 d5 4. h3 b6 5. Nf3"] = "Bb7";
        book["1. d4 Nf6 2. c4 e6 3. e3 d5 4. h3 b6 5. Nc3"] = "Bb7";
        book["1. d4 Nf6 2. c4 e6 3. e3 d5 4. h3 b6 5. Nc3 Bb7 6. a3"] = "Nbd7";
        book["1. d4 Nf6 2. c4 e6 3. e3 d5 4. h3 b6 5. Nc3 Bb7 6. Nf3"] = "Nbd7";
        book["1. d4 Nf6 2. c4 e6 3. e3 d5 4. h3 b6 5. Nc3 Bb7 6. Nf3 Nbd7 7. b3"] = "Bb4";
        book["1. d4 Nf6 2. c4 e6 3. e3 d5 4. h3 b6 5. Nc3 Bb7 6. Nf3 Nbd7 7. cxd5"] = "exd5";
        book["1. d4 Nf6 2. c4 e6 3. e3 d5 4. h3 b6 5. Nc3 Bb7 6. Nf3 Nbd7 7. Qc2"] = "a6";
        book["1. d4 Nf6 2. c4 e6 3. e3 d5 4. h3 b6 5. Nc3 Bb7 6. Nf3 Nbd7 7. Qc2 a6 8. cxd5"] = "exd5";
        book["1. d4 Nf6 2. c4 e6 3. e3 d5 4. h3 b6 5. Nc3 Bb7 6. Nf3 Nbd7 7. Qc2 a6 8. a3"] = "dxc4";
        book["1. d4 Nf6 2. c4 e6 3. e3 d5 4. h3 b6 5. Nc3 Bb7 6. Nf3 Nbd7 7. Qc2 a6 8. a3 dxc4 9. Bxc4"] = "c5";
        book["1. d4 Nf6 2. c4 e6 3. e3 d5 4. h3 b6 5. Nc3 Bb7 6. Nf3 Nbd7 7. Qc2 a6 8. a3 dxc4 9. a4"] = "b5";

        book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. e3"] = "0-0";

        book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. e3 0-0 5. Bd3"] = "c5";
        book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. e3 0-0 5. Bd3 c5 6. a3"] = "Bxc3+";
        book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. e3 0-0 5. Bd3 c5 6. a3 Bxc3+ 7. bxc3"] = "Nc6";
        book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. e3 0-0 5. Bd3 c5 6. d5"] = "Bxc3+";
        book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. e3 0-0 5. Bd3 c5 6. d5 Bxc3+ 7. bxc3"] = "d6";
        book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. e3 0-0 5. Bd3 c5 6. Bd2"] = "d5";
        book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. e3 0-0 5. Bd3 c5 6. Ne2"] = "cxd4";
        book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. e3 0-0 5. Bd3 c5 6. Ne2 cxd4 7. exd4"] = "d5";
        book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. e3 0-0 5. Bd3 c5 6. Ne2 cxd4 7. Nxd4"] = "Nc6";
        book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. e3 0-0 5. Bd3 c5 6. Nf3"] = "d5";

        book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. e3 0-0 5. Bd3 c5 6. Nf3 d5 7. 0-0"] = "Nc6";
        book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. e3 0-0 5. Bd3 c5 6. Nf3 d5 7. 0-0 Nc6 8. a3"] = "Bxc3";
        book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. e3 0-0 5. Bd3 c5 6. Nf3 d5 7. 0-0 Nc6 8. a3 Bxc3 9. bxc3"] = "Qc7";
        book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. e3 0-0 5. Bd3 c5 6. Nf3 d5 7. 0-0 Nc6 8. a3 Bxc3 9. bxc3 Qc7 10. a4"] = "dxc4";
        book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. e3 0-0 5. Bd3 c5 6. Nf3 d5 7. 0-0 Nc6 8. a3 Bxc3 9. bxc3 Qc7 10. a4 dxc4 11. Bxc4"] = "b6";
        book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. e3 0-0 5. Bd3 c5 6. Nf3 d5 7. 0-0 Nc6 8. a3 Bxc3 9. bxc3 Qc7 10. cxd5"] = "exd5";
        book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. e3 0-0 5. Bd3 c5 6. Nf3 d5 7. 0-0 Nc6 8. a3 Bxc3 9. bxc3 Qc7 10. h3"] = "Na5";
        book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. e3 0-0 5. Bd3 c5 6. Nf3 d5 7. 0-0 Nc6 8. a3 Bxc3 9. bxc3 Qc7 10. Bb2"] = "Na5";
        book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. e3 0-0 5. Bd3 c5 6. Nf3 d5 7. 0-0 Nc6 8. a3 Bxc3 9. bxc3 Qc7 10. Bb2 Na5 11. cxd5"] = "exd5";
        book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. e3 0-0 5. Bd3 c5 6. Nf3 d5 7. 0-0 Nc6 8. a3 Bxc3 9. bxc3 Qc7 10. Bb2 Na5 11. cxd5 exd5 12. Ne5"] = "Re8";
        book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. e3 0-0 5. Bd3 c5 6. Nf3 d5 7. 0-0 Nc6 8. a3 Bxc3 9. bxc3 Qc7 10. Bb2 Na5 11. cxd5 exd5 12. dxc5"] = "Bg4";

        book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. e3 0-0 5. Bd3 c5 6. Nf3 d5 7. 0-0 Nc6 8. cxd5"] = "exd5";
        book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. e3 0-0 5. Bd3 c5 6. Nf3 d5 7. 0-0 Nc6 8. dxc5"] = "dxc4";
        book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. e3 0-0 5. Bd3 c5 6. Nf3 d5 7. 0-0 Nc6 8. dxc5 dxc4 9. Bxc4"] = "Bxc5";
        book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. e3 0-0 5. Bd3 c5 6. Nf3 d5 7. 0-0 Nc6 8. Ne2"] = "dxc4";
        book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. e3 0-0 5. Bd3 c5 6. Nf3 d5 7. 0-0 Nc6 8. Ne2 dxc4 9. Bxc4"] = "cxd4";
        book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. e3 0-0 5. Bd3 c5 6. Nf3 d5 7. 0-0 Nc6 8. Ne2 dxc4 9. Bxc4 cxd4 10. Nexd4"] = "Nxd4";
        book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. e3 0-0 5. Bd3 c5 6. Nf3 d5 7. 0-0 Nc6 8. Ne2 dxc4 9. Bxc4 cxd4 10. Nfxd4"] = "Ne5";
        book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. e3 0-0 5. Bd3 c5 6. Nf3 d5 7. 0-0 Nc6 8. Ne2 dxc4 9. Bxc4 cxd4 10. exd4"] = "Be7";

        book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. e3 0-0 5. Bd3 c5 6. Nf3 d5 7. cxd5"] = "exd5";
        book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. e3 0-0 5. Bd3 c5 6. Nf3 d5 7. dxc5"] = "dxc4";
        book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. e3 0-0 5. Bd3 c5 6. Nf3 d5 7. dxc5 dxc4 8. Bxc4"] = "Qxd1+";
        book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. e3 0-0 5. Bd3 c5 6. Nf3 d5 7. dxc5 dxc4 8. Bxc4 Qxd1+ 9. Kxd1"] = "Bxc5";
        book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. e3 0-0 5. Bd3 c5 6. Nf3 d5 7. a3"] = "Bxc3+";
        book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. e3 0-0 5. Bd3 c5 6. Nf3 d5 7. a3 Bxc3+ 8. bxc3"] = "dxc4";
        book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. e3 0-0 5. Bd3 c5 6. Nf3 d5 7. a3 Bxc3+ 8. bxc3 dxc4 9. Bxc4"] = "Qc7";
        book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. e3 0-0 5. Bd3 c5 6. Nf3 d5 7. Bd2"] = "dxc4";
        book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. e3 0-0 5. Bd3 c5 6. Nf3 d5 7. Bd2 dxc4 8. Bxc4"] = "cxd4";
        book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. e3 0-0 5. Bd3 c5 6. Nf3 d5 7. Qc2"] = "cxd4";

        book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. e3 0-0 5. Nge2"] = "d5";
        book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. e3 0-0 5. Nf3"] = "Bxc3+";
        book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. e3 0-0 5. Nf3 Bxc3+ 6. bxc3"] = "d6";
        book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. e3 0-0 5. Nf3 Bxc3+ 6. bxc3 d6 7. Qc2"] = "Re8";
        book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. e3 0-0 5. Nf3 Bxc3+ 6. bxc3 d6 7. Qc2 Re8 8. Bd3"] = "e5";
        book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. e3 0-0 5. Nf3 Bxc3+ 6. bxc3 d6 7. Be2"] = "Re8";
        book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. e3 0-0 5. Nf3 Bxc3+ 6. bxc3 d6 7. Be2 Re8 8. 0-0"] = "Nc6";
        book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. e3 0-0 5. Nf3 Bxc3+ 6. bxc3 d6 7. Bd3"] = "e5";
        book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. e3 0-0 5. Nf3 Bxc3+ 6. bxc3 d6 7. Bd3 e5 8. e4"] = "Re8";
        book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. e3 0-0 5. Nf3 Bxc3+ 6. bxc3 d6 7. Bd3 e5 8. Nd2"] = "Re8";
        book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. e3 0-0 5. Nf3 Bxc3+ 6. bxc3 d6 7. Bd3 e5 8. Qc2"] = "Re8";
        book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. e3 0-0 5. Nf3 Bxc3+ 6. bxc3 d6 7. Bd3 e5 8. Bc2"] = "Nc6";
        book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. e3 0-0 5. Nf3 Bxc3+ 6. bxc3 d6 7. Bd3 e5 8. Bb1"] = "Nc6";
        book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. e3 0-0 5. Nf3 Bxc3+ 6. bxc3 d6 7. Bd3 e5 8. dxe5"] = "dxe5";
        book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. e3 0-0 5. Nf3 Bxc3+ 6. bxc3 d6 7. Bd3 e5 8. dxe5 dxe5 9. e4"] = "Qe7";
        book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. e3 0-0 5. Nf3 Bxc3+ 6. bxc3 d6 7. Bd3 e5 8. dxe5 dxe5 9. Qc2"] = "Qe7";
        book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. e3 0-0 5. Nf3 Bxc3+ 6. bxc3 d6 7. Bd3 e5 8. dxe5 dxe5 9. Bc2"] = "Qxd1+";
        book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. e3 0-0 5. Nf3 Bxc3+ 6. bxc3 d6 7. Bd3 e5 8. dxe5 dxe5 9. Bc2 Qxd1+ 10. Kxd1"] = "e4";
        book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. e3 0-0 5. Nf3 Bxc3+ 6. bxc3 d6 7. Bd3 e5 8. dxe5 dxe5 9. Bc2 Qxd1+ 10. Bxd1"] = "Re8";
        book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. e3 0-0 5. Nf3 Bxc3+ 6. bxc3 d6 7. Bd3 e5 8. dxe5 dxe5 9. Be2"] = "Qe7";
        book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. e3 0-0 5. Nf3 Bxc3+ 6. bxc3 d6 7. Bd3 e5 8. dxe5 dxe5 9. Nxe5"] = "Qe7";
        book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. e3 0-0 5. Nf3 Bxc3+ 6. bxc3 d6 7. Bd3 e5 8. dxe5 dxe5 9. Nxe5 Qe7 10. Nf3"] = "Rd8";
        book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. e3 0-0 5. Nf3 Bxc3+ 6. bxc3 d6 7. Bd3 e5 8. dxe5 dxe5 9. Nxe5 Qe7 10. f4"] = "Nbd7";

        book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. e3 0-0 5. a3"] = "Bxc3+";
        book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. e3 0-0 5. a3 Bxc3+ 6. bxc3"] = "d6";
        book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. e3 0-0 5. Bd2"] = "b6";

        book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. Qc2"] = "0-0";
        book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. Qc2 0-0 5. a3"] = "Bxc3+";
        book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. Qc2 0-0 5. a3 Bxc3+ 6. bxc3"] = "Re8";
        book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. Qc2 0-0 5. a3 Bxc3+ 6. Qxc3"] = "d5";
        book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. Qc2 0-0 5. Nf3"] = "d5";
        book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. Qc2 0-0 5. e3"] = "d5";
        book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. Qc2 0-0 5. Bg5"] = "d5";
        book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. Qc2 0-0 5. Bd2"] = "d5";
        book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. Qc2 0-0 5. e4"] = "d5";
        book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. Qc2 0-0 5. e4 d5 6. e5"] = "Ne4";
        book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. Qc2 0-0 5. e4 d5 6. e5 Ne4 7. Bd3"] = "c5";
        book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. Qc2 0-0 5. e4 d5 6. e5 Ne4 7. Nf3"] = "c5";

        book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. Nf3"] = "c5";
        book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. Nf3 c5 5. g3"] = "0-0";
        book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. Nf3 c5 5. g3 0-0 6. Bg2"] = "cxd4";
        book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. Nf3 c5 5. e3"] = "Bxc3+";
        book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. Nf3 c5 5. e3 Bxc3+ 6. bxc3"] = "b6";
        book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. Nf3 c5 5. d5"] = "d6";
        book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. Nf3 c5 5. d5 d6 6. Bd2"] = "exd5";
        book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. Nf3 c5 5. d5 d6 6. e3"] = "Bxc3+";
        book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. Nf3 c5 5. d5 d6 6. e3 Bxc3+ 7. bxc3"] = "e5";
        book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. Nf3 c5 5. d5 d6 6. g3"] = "Bxc3+";
        book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. Nf3 c5 5. d5 d6 6. g3 Bxc3+ 7. bxc3"] = "Qa5";
        book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. Nf3 c5 5. d5 d6 6. g3 Bxc3+ 7. bxc3 Qa5 8. Qd3"] = "0-0";
        book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. Nf3 c5 5. d5 d6 6. g3 Bxc3+ 7. bxc3 Qa5 8. Qd3 0-0 9. Bg2"] = "exd5";
        book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. Nf3 c5 5. d5 d6 6. g3 Bxc3+ 7. bxc3 Qa5 8. Bd2"] = "Qa6";

        book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. f3"] = "d5";
        book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. g3"] = "c5";

        book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. Bg5"] = "c5";
        book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. Bg5 c5 5. a3"] = "Bxc3+";
        book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. Bg5 c5 5. a3 Bxc3+ 6. bxc3"] = "Qa5";
        book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. Bg5 c5 5. Nf3"] = "h6";
        book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. Bg5 c5 5. Nf3 h6 6. Bh4"] = "g5";
        book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. Bg5 c5 5. Nf3 h6 6. Bh4 g5 7. Bg3"] = "g4";
        book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. Bg5 c5 5. Nf3 h6 6. Bf4"] = "cxd4";
        book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. Bg5 c5 5. Nf3 h6 6. Bf4 cxd4 7. Nxd4"] = "0-0";
        book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. Bg5 c5 5. Nf3 h6 6. Bf4 cxd4 7. Qxd4"] = "d6";
        book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. Bg5 c5 5. Nf3 h6 6. Bxf6"] = "Qxf6";
        book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. Bg5 c5 5. d5"] = "h6";
        book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. Bg5 c5 5. d5 h6 6. Bh4"] = "b6";
        book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. Bg5 c5 5. d5 h6 6. Bf4"] = "0-0";
        book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. Bg5 c5 5. d5 h6 6. Bxf6"] = "Qxf6";
        book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. Bg5 c5 5. Rc1"] = "h6";
        book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. Bg5 c5 5. Rc1 h6 6. Bh4"] = "cxd4";
        book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. Bg5 c5 5. Rc1 h6 6. Bf4"] = "cxd4";
        book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. Bg5 c5 5. Rc1 h6 6. Bxf6"] = "Qxf6";
        book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. Bg5 c5 5. dxc5"] = "Na6";

        book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. a3"] = "Bxc3+";
        book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. a3 Bxc3+ 5. bxc3"] = "c5";
        book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. Qb3"] = "c5";
        book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. Bd2"] = "0-0";
        book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. d5"] = "Bxc3+";
        book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. d5 Bxc3+ 5. bxc3"] = "d6";


        // E12 Queen's Indian defence -- BLACK
        book["1. d4 Nf6 2. c4 e6 3. Nf3"] = "b6";
        book["1. d4 Nf6 2. c4 e6 3. Nf3 b6 4. g3"] = "Bb7";
        book["1. d4 Nf6 2. c4 e6 3. Nf3 b6 4. g3 Bb7 5. Bg2"] = "Bb4+";
        book["1. d4 Nf6 2. c4 e6 3. Nf3 b6 4. a3"] = "Bb7";
        book["1. d4 Nf6 2. c4 e6 3. Nf3 b6 4. a3 Bb7 5. Bf4"] = "Be7";
        book["1. d4 Nf6 2. c4 e6 3. Nf3 b6 4. a3 Bb7 5. Bf4 Be7 6. Nc3"] = "0-0";
        book["1. d4 Nf6 2. c4 e6 3. Nf3 b6 4. a3 Bb7 5. Bg5"] = "Be7";
        book["1. d4 Nf6 2. c4 e6 3. Nf3 b6 4. a3 Bb7 5. e3"] = "d5";
        book["1. d4 Nf6 2. c4 e6 3. Nf3 b6 4. a3 Bb7 5. Nc3"] = "d5";

        book["1. d4 Nf6 2. c4 e6 3. Nf3 b6 4. a3 Bb7 5. Nc3 d5 6. Bg5"] = "Be7";
        book["1. d4 Nf6 2. c4 e6 3. Nf3 b6 4. a3 Bb7 5. Nc3 d5 6. Bg5 Be7 7. e3"] = "0-0";
        book["1. d4 Nf6 2. c4 e6 3. Nf3 b6 4. a3 Bb7 5. Nc3 d5 6. Bg5 Be7 7. e3 0-0 8. Rc1"] = "h6";
        book["1. d4 Nf6 2. c4 e6 3. Nf3 b6 4. a3 Bb7 5. Nc3 d5 6. Bg5 Be7 7. e3 0-0 8. Rc1 h6 9. Bh4"] = "Nbd7";
        book["1. d4 Nf6 2. c4 e6 3. Nf3 b6 4. a3 Bb7 5. Nc3 d5 6. Bg5 Be7 7. e3 0-0 8. Rc1 h6 9. Bf4"] = "c5";
        book["1. d4 Nf6 2. c4 e6 3. Nf3 b6 4. a3 Bb7 5. Nc3 d5 6. Bg5 Be7 7. e3 0-0 8. Rc1 h6 9. Bxf6"] = "Bxf6";
        book["1. d4 Nf6 2. c4 e6 3. Nf3 b6 4. a3 Bb7 5. Nc3 d5 6. Bg5 Be7 7. e3 0-0 8. cxd5"] = "Nxd5";
        book["1. d4 Nf6 2. c4 e6 3. Nf3 b6 4. a3 Bb7 5. Nc3 d5 6. Bg5 Be7 7. e3 0-0 8. cxd5 Nxd5 9. Bxe7"] = "Qxe7";
        book["1. d4 Nf6 2. c4 e6 3. Nf3 b6 4. a3 Bb7 5. Nc3 d5 6. Bg5 Be7 7. e3 0-0 8. cxd5 Nxd5 9. Bxe7 Qxe7 10. Nxd5"] = "Bxd5";

        book["1. d4 Nf6 2. c4 e6 3. Nf3 b6 4. a3 Bb7 5. Nc3 d5 6. Bf4"] = "Bd6";
        book["1. d4 Nf6 2. c4 e6 3. Nf3 b6 4. a3 Bb7 5. Nc3 d5 6. cxd5"] = "Nxd5";
        book["1. d4 Nf6 2. c4 e6 3. Nf3 b6 4. a3 Bb7 5. Nc3 d5 6. cxd5 Nxd5 7. Nxd5"] = "Qxd5";
        book["1. d4 Nf6 2. c4 e6 3. Nf3 b6 4. a3 Bb7 5. Nc3 d5 6. cxd5 Nxd5 7. Na4"] = "Nf6";

        book["1. d4 Nf6 2. c4 e6 3. Nf3 b6 4. Nc3"] = "Bb4";
        book["1. d4 Nf6 2. c4 e6 3. Nf3 b6 4. e3"] = "Bb7";
        book["1. d4 Nf6 2. c4 e6 3. Nf3 b6 4. Bf4"] = "Bb7";
        book["1. d4 Nf6 2. c4 e6 3. Nf3 b6 4. Bg5"] = "Bb7";
        book["1. d4 Nf6 2. c4 e6 3. Nf3 b6 4. e3"] = "Bb7";


        // A45 Trompovsky attack (Ruth, Opovcensky opening) -- BLACK
        book["1. d4 Nf6 2. Bg5 Ne4 3. Bh4"] = "g5";
        book["1. d4 Nf6 2. Bg5 Ne4 3. Bh4 g5 4. f3"] = "c5";
        book["1. d4 Nf6 2. Bg5 Ne4 3. Bh4 g5 4. Bg3"] = "c5";
        book["1. d4 Nf6 2. Bg5 Ne4 3. Bh4 g5 4. Bg3 c5 5. dxc5"] = "Bg7";
        book["1. d4 Nf6 2. Bg5 Ne4 3. Bh4 g5 4. Bg3 c5 5. e3"] = "Nc6";
        book["1. d4 Nf6 2. Bg5 Ne4 3. Bh4 g5 4. Bg3 c5 5. c3"] = "Qb6";
        book["1. d4 Nf6 2. Bg5 Ne4 3. Bh4 g5 4. Bg3 c5 5. Nd2"] = "Nxg3";
        book["1. d4 Nf6 2. Bg5 Ne4 3. Bh4 g5 4. Bg3 c5 5. Nd2 Nxg3 6. hxg3"] = "cxd4";
        book["1. d4 Nf6 2. Bg5 Ne4 3. Bh4 g5 4. Bg3 c5 5. Nd2 Nxg3 6. fxg3"] = "cxd4";

        book["1. d4 Nf6 2. Bg5 Ne4 3. Bf4"] = "c5";
        book["1. d4 Nf6 2. Bg5 Ne4 3. Bf4 c5 4. f3"] = "Qa5+";
        book["1. d4 Nf6 2. Bg5 Ne4 3. Bf4 c5 4. d5"] = "Qb6";
        book["1. d4 Nf6 2. Bg5 Ne4 3. Bf4 c5 4. dxc5"] = "d5";
        book["1. d4 Nf6 2. Bg5 Ne4 3. Bf4 c5 4. e3"] = "Qb6";
        book["1. d4 Nf6 2. Bg5 Ne4 3. Bf4 c5 4. Nd2"] = "Nxd2";
        book["1. d4 Nf6 2. Bg5 Ne4 3. Bf4 c5 4. Nd2 Nxd2 5. Bxd2"] = "cxd4";

        book["1. d4 Nf6 2. Bg5 Ne4 3. Bf4 c5 4. c3"] = "Qb6";
        book["1. d4 Nf6 2. Bg5 Ne4 3. Bf4 c5 4. c3 Qb6 5. Nd2"] = "Nxd2";
        book["1. d4 Nf6 2. Bg5 Ne4 3. Bf4 c5 4. c3 Qb6 5. Nd2 Nxd2 6. Bxd2"] = "cxd4";
        book["1. d4 Nf6 2. Bg5 Ne4 3. Bf4 c5 4. c3 Qb6 5. Nd2 Nxd2 6. Bxd2 cxd4 7. cxd4"] = "Qxd4";
        book["1. d4 Nf6 2. Bg5 Ne4 3. Bf4 c5 4. c3 Qb6 5. Nd2 Nxd2 6. Bxd2 cxd4 7. Nf3"] = "Nc6";
        book["1. d4 Nf6 2. Bg5 Ne4 3. Bf4 c5 4. c3 Qb6 5. Nd2 Nxd2 6. Qxd2"] = "cxd4";
        book["1. d4 Nf6 2. Bg5 Ne4 3. Bf4 c5 4. c3 Qb6 5. Nd2 Nxd2 6. Qxd2 cxd4 7. cxd4"] = "e5";
        book["1. d4 Nf6 2. Bg5 Ne4 3. Bf4 c5 4. c3 Qb6 5. Nd2 Nxd2 6. Qxd2 cxd4 7. Qxd4"] = "Qxb2";
        book["1. d4 Nf6 2. Bg5 Ne4 3. Bf4 c5 4. c3 Qb6 5. Nd2 Nxd2 6. Qxd2 cxd4 7. a3"] = "dxc3";
        book["1. d4 Nf6 2. Bg5 Ne4 3. Bf4 c5 4. c3 Qb6 5. Nd2 Nxd2 6. Qxd2 cxd4 7. a3 dxc3 8. bxc3"] = "d6";
        book["1. d4 Nf6 2. Bg5 Ne4 3. Bf4 c5 4. c3 Qb6 5. Nd2 Nxd2 6. Qxd2 cxd4 7. a3 dxc3 8. Qxc3"] = "Nc6";
        book["1. d4 Nf6 2. Bg5 Ne4 3. Bf4 c5 4. c3 Qb6 5. Qc2"] = "cxd4";
        book["1. d4 Nf6 2. Bg5 Ne4 3. Bf4 c5 4. c3 Qb6 5. Qc2 cxd4 6. cxd4"] = "Nc6";
        book["1. d4 Nf6 2. Bg5 Ne4 3. Bf4 c5 4. c3 Qb6 5. Qc1"] = "d5";
        book["1. d4 Nf6 2. Bg5 Ne4 3. Bf4 c5 4. c3 Qb6 5. Be3"] = "Qxb2";
        book["1. d4 Nf6 2. Bg5 Ne4 3. Bf4 c5 4. c3 Qb6 5. Be3 Qxb2 6. Nd2"] = "Nxc3";
        book["1. d4 Nf6 2. Bg5 Ne4 3. Bf4 c5 4. c3 Qb6 5. Be3 Qxb2 6. Nd2 Nxc3 7. Qc1"] = "Qxc1+";
        book["1. d4 Nf6 2. Bg5 Ne4 3. Bf4 c5 4. c3 Qb6 5. Be3 Qxb2 6. Nd2 Nxc3 7. Qc1 Qxc1+ 8. Rxc1"] = "Nxa2";
        book["1. d4 Nf6 2. Bg5 Ne4 3. Bf4 c5 4. c3 Qb6 5. Be3 Qxb2 6. Nd2 Nxc3 7. Qc1 Qxc1+ 8. Rxc1 Nxa2 9. Rc2"] = "Nb4";
        book["1. d4 Nf6 2. Bg5 Ne4 3. Bf4 c5 4. c3 Qb6 5. Be3 Qxb2 6. Nd2 Nxc3 7. Qc1 Qxc1+ 8. Rxc1 Nxa2 9. Rc2 Nb4 10. Rxc5"] = "N8c6";
        book["1. d4 Nf6 2. Bg5 Ne4 3. Bf4 c5 4. c3 Qb6 5. Be3 Qxb2 6. Nd2 Nxc3 7. Qc1 Qxc1+ 8. Rxc1 Nxa2 9. Rxc5"] = "Nc6";

        book["1. d4 Nf6 2. Bg5 Ne4 3. Bf4 c5 4. Nd2 Nxd2 5. Qxd2"] = "cxd4";
        book["1. d4 Nf6 2. Bg5 Ne4 3. Bf4 c5 4. Nd2 Nxd2 5. Qxd2 cxd4 6. Bxb8"] = "Rxb8";
        book["1. d4 Nf6 2. Bg5 Ne4 3. Bf4 c5 4. Nd2 Nxd2 5. Qxd2 cxd4 6. 0-0-0"] = "d6";
        book["1. d4 Nf6 2. Bg5 Ne4 3. Bf4 c5 4. Nd2 Nxd2 5. Qxd2 cxd4 6. Qxd4"] = "Nc6";
        book["1. d4 Nf6 2. Bg5 Ne4 3. Bf4 c5 4. Nd2 Nxd2 5. Qxd2 cxd4 6. Nf3"] = "d6";
        book["1. d4 Nf6 2. Bg5 Ne4 3. Bf4 c5 4. Nd2 Nxd2 5. Qxd2 cxd4 6. Nf3 d6 7. 0-0-0"] = "e5";
        book["1. d4 Nf6 2. Bg5 Ne4 3. Bf4 c5 4. Nd2 Nxd2 5. Qxd2 cxd4 6. Nf3 d6 7. e3"] = "e5";
        book["1. d4 Nf6 2. Bg5 Ne4 3. Bf4 c5 4. Nd2 Nxd2 5. Qxd2 cxd4 6. Nf3 d6 7. e4"] = "e5";
        book["1. d4 Nf6 2. Bg5 Ne4 3. Bf4 c5 4. Nd2 Nxd2 5. Qxd2 cxd4 6. Nf3 d6 7. Bg3"] = "e5";


        // C55 Two knights defence -- BLACK
        book["1. e4 e5 2. Nf3"] = "Nc6";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4"] = "Nf6";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. d3"] = "Bc5";

        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. c3"] = "Nxe4";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. c3 Nxe4 5. 0-0"] = "d5";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. c3 Nxe4 5. 0-0 d5 6. Bb5"] = "Bd6";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. c3 Nxe4 5. 0-0 d5 6. Bb5 Bd6 7. Re1"] = "0-0";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. c3 Nxe4 5. Bd5"] = "Nf6";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. c3 Nxe4 5. Bd5 Nf6 6. Bxc6"] = "dxc6";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. c3 Nxe4 5. Bd5 Nf6 6. Bxc6 dxc6 7. Nxe5"] = "Nd7";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. c3 Nxe4 5. d4"] = "d5";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. c3 Nxe4 5. d4 d5 6. Bb3"] = "exd4";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. c3 Nxe4 5. d4 d5 6. Bb3 exd4 7. cxd4"] = "Bb4+";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. c3 Nxe4 5. d4 d5 6. Bb3 exd4 7. Nxd4"] = "Bc5";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. c3 Nxe4 5. d4 d5 6. Bb3 exd4 7. h3"] = "Nc5";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. c3 Nxe4 5. d4 d5 6. Bb3 exd4 7. 0-0"] = "Bg4";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. c3 Nxe4 5. d4 d5 6. Bd3"] = "Bg4";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. c3 Nxe4 5. d4 d5 6. Be2"] = "exd4";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. c3 Nxe4 5. d4 d5 6. Be2 exd4 7. cxd4"] = "Bb4+";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. c3 Nxe4 5. d4 d5 6. Be2 exd4 7. Nxd4"] = "Bd6";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. c3 Nxe4 5. d4 d5 6. Be2 exd4 7. 0-0"] = "Bd6";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. c3 Nxe4 5. d4 d5 6. Bb5"] = "exd4";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. c3 Nxe4 5. d4 d5 6. Bb5 exd4 7. Qxd4"] = "Qd7";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. c3 Nxe4 5. d4 d5 6. Bb5 exd4 7. 0-0"] = "Bd6";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. c3 Nxe4 5. d4 d5 6. Bb5 exd4 7. Nxd4"] = "Bd7";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. c3 Nxe4 5. d4 d5 6. Bb5 exd4 7. Nxd4 Bd7 8. 0-0"] = "Nxd4";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. c3 Nxe4 5. d4 d5 6. Bb5 exd4 7. Nxd4 Bd7 8. 0-0 Nxd4 9. Bxd7+"] = "Qxd7";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. c3 Nxe4 5. d4 d5 6. Bb5 exd4 7. Nxd4 Bd7 8. 0-0 Nxd4 9. Bxd7+ Qxd7 10. Qxd4"] = "Bc5";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. c3 Nxe4 5. d4 d5 6. Bb5 exd4 7. Nxd4 Bd7 8. Bxc6"] = "bxc6";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. c3 Nxe4 5. d4 d5 6. Bb5 exd4 7. Nxd4 Bd7 8. Bxc6 bxc6 9. 0-0"] = "Bd6";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. c3 Nxe4 5. d4 d5 6. Bb5 exd4 7. Nxd4 Bd7 8. Bxc6 bxc6 9. Nd2"] = "Bd6";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. c3 Nxe4 5. d4 d5 6. Bb5 exd4 7. Nxd4 Bd7 8. Nxc6"] = "bxc6";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. c3 Nxe4 5. d4 d5 6. Bb5 exd4 7. Nxd4 Bd7 8. Nxc6 bxc6 9. Bd3"] = "Bd6";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. c3 Nxe4 5. d4 d5 6. Bb5 exd4 7. Nxd4 Bd7 8. Nxc6 bxc6 9. Be2"] = "Bc5";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. c3 Nxe4 5. d4 d5 6. Bb5 exd4 7. Nxd4 Bd7 8. Nxc6 bxc6 9. Ba4"] = "Qh4";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. c3 Nxe4 5. d4 d5 6. Bb5 exd4 7. Nxd4 Bd7 8. Nxc6 bxc6 9. Ba4 Qh4 10. 0-0"] = "0-0-0";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. c3 Nxe4 5. d4 d5 6. Bb5 exd4 7. Nxd4 Bd7 8. Nxc6 bxc6 9. Ba4 Qh4 10. Be3"] = "Bd6";

        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. d3 Bc5 5. 0-0"] = "d6";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. d3 Bc5 5. 0-0 d6 6. c3"] = "0-0";

        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. d3 Bc5 5. 0-0 d6 6. a4"] = "a5";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. d3 Bc5 5. 0-0 d6 6. a4 a5 7. c3"] = "0-0";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. d3 Bc5 5. 0-0 d6 6. a4 a5 7. Be3"] = "Bxe3";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. d3 Bc5 5. 0-0 d6 6. a4 a5 7. Be3 Bxe3 8. fxe3"] = "0-0";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. d3 Bc5 5. 0-0 d6 6. a4 a5 7. h3"] = "h6";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. d3 Bc5 5. 0-0 d6 6. a4 a5 7. Nc3"] = "0-0";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. d3 Bc5 5. 0-0 d6 6. a4 a5 7. Nbd2"] = "Ne7";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. d3 Bc5 5. 0-0 d6 6. a4 a5 7. Bg5"] = "h6";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. d3 Bc5 5. 0-0 d6 6. a4 a5 7. Bg5 h6 8. Bh4"] = "g5";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. d3 Bc5 5. 0-0 d6 6. a4 a5 7. Bg5 h6 8. Bh4 g5 9. Bg3"] = "0-0";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. d3 Bc5 5. 0-0 d6 6. a4 a5 7. Bg5 h6 8. Bh4 g5 9. Nxg5"] = "hxg5";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. d3 Bc5 5. 0-0 d6 6. a4 a5 7. Bg5 h6 8. Bh4 g5 9. Nxg5 hxg5 10. Bxg5"] = "Rg8";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. d3 Bc5 5. 0-0 d6 6. a4 a5 7. Bg5 h6 8. Bh4 g5 9. Bxg5"] = "hxg5";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. d3 Bc5 5. 0-0 d6 6. a4 a5 7. Bg5 h6 8. Bh4 g5 9. Bxg5 hxg5 10. Nxg5"] = "Ng4";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. d3 Bc5 5. 0-0 d6 6. a4 a5 7. Bg5 h6 8. Bxf6"] = "Qxf6";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. d3 Bc5 5. 0-0 d6 6. a4 a5 7. Bg5 h6 8. Be3"] = "Bxe3";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. d3 Bc5 5. 0-0 d6 6. a4 a5 7. Bg5 h6 8. Be3 Bxe3 9. fxe3"] = "Ne7";

        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. d3 Bc5 5. 0-0 d6 6. Nc3"] = "Na5";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. d3 Bc5 5. 0-0 d6 6. h3"] = "Na5";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. d3 Bc5 5. 0-0 d6 6. h3 Na5 7. Bb3"] = "Nxb3";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. d3 Bc5 5. 0-0 d6 6. h3 Na5 7. Bb3 Nxb3 8. axb3"] = "0-0";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. d3 Bc5 5. 0-0 d6 6. h3 Na5 7. Bb3 Nxb3 8. cxb3"] = "0-0";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. d3 Bc5 5. 0-0 d6 6. h3 Na5 7. Bd5"] = "c6";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. d3 Bc5 5. 0-0 d6 6. h3 Na5 7. Bg5"] = "Nxc4";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. d3 Bc5 5. 0-0 d6 6. h3 Na5 7. Bg5 Nxc4 8. dxc4"] = "a5";

        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. d3 Bc5 5. c3"] = "d6";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. d3 Bc5 5. c3 d6 6. Bb3"] = "0-0";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. d3 Bc5 5. c3 d6 6. Bb3 0-0 7. 0-0"] = "a5";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. d3 Bc5 5. c3 d6 6. Bb3 0-0 7. 0-0 a5 8. Na3"] = "Bxa3";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. d3 Bc5 5. c3 d6 6. Bb3 0-0 7. 0-0 a5 8. Na3 Bxa3 9. bxa3"] = "d5";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. d3 Bc5 5. c3 d6 6. Bb3 0-0 7. 0-0 a5 8. Nbd2"] = "h6";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. d3 Bc5 5. c3 d6 6. Bb3 0-0 7. 0-0 a5 8. Re1"] = "Re8";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. d3 Bc5 5. c3 d6 6. Bb3 0-0 7. 0-0 a5 8. h3"] = "h6";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. d3 Bc5 5. c3 d6 6. Bb3 0-0 7. h3"] = "h6";

        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. d3 Bc5 5. c3 d6 6. 0-0"] = "0-0";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. d3 Bc5 5. c3 d6 6. Nbd2"] = "0-0";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. d3 Bc5 5. c3 d6 6. b4"] = "Bb6";

        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. d3 Bc5 5. Nc3"] = "0-0";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. d3 Bc5 5. Bg5"] = "h6";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. d3 Bc5 5. Bb3"] = "d6";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. d3 Bc5 5. Nbd2"] = "d6";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. d3 Bc5 5. a4"] = "h6";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. d3 Bc5 5. h3"] = "0-0";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. d3 Bc5 5. h3 0-0 6. 0-0"] = "d6";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. d3 Bc5 5. h3 0-0 6. a3"] = "d6";

        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. d3 Bc5 5. a3"] = "d6";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. d3 Bc5 5. a3 d6 6. Nc3"] = "Bg4";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. d3 Bc5 5. a3 d6 6. c3"] = "h6";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. d3 Bc5 5. a3 d6 6. 0-0"] = "Nd4";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. d3 Bc5 5. a3 d6 6. b4"] = "Bb6";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. d3 Bc5 5. a3 d6 6. Be3"] = "Bxe3";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. d3 Bc5 5. a3 d6 6. Be3 Bxe3 7. fxe3"] = "Ne7";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. d3 Bc5 5. a3 d6 6. h3"] = "0-0";

        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Ng5"] = "d5";

        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. 0-0"] = "Nxe4";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. 0-0 Nxe4 5. Bb5"] = "Be7";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. 0-0 Nxe4 5. Re1"] = "d5";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. 0-0 Nxe4 5. Re1 d5 6. d4"] = "Nxf2";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. 0-0 Nxe4 5. Re1 d5 6. Bb5"] = "Bc5";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. 0-0 Nxe4 5. Re1 d5 6. Bd3 f5 7. Nc3"] = "a6";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. 0-0 Nxe4 5. Re1 d5 6. Bd3 f5 7. Bf1"] = "Bc5";

        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. d4"] = "exd4";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. d4 exd4 5. e5"] = "d5";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. d4 exd4 5. Ng5"] = "d5";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. d4 exd4 5. Nxd4"] = "Nxe4";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. d4 exd4 5. c3"] = "Nxe4";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. d4 exd4 5. 0-0"] = "Nxe4";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. d4 exd4 5. 0-0 Nxe4 6. Re1"] = "d5";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. d4 exd4 5. 0-0 Nxe4 6. Nc3"] = "dxc3";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. d4 exd4 5. 0-0 Nxe4 6. Bd5"] = "Nf6";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. d4 exd4 5. 0-0 Nxe4 6. Nxd4"] = "d5";

        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. d4 exd4 5. 0-0 Nxe4 6. Re1 d5 7. Bxd5"] = "Qxd5";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. d4 exd4 5. 0-0 Nxe4 6. Re1 d5 7. Bxd5 Qxd5 8. Ng5"] = "Be7";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. d4 exd4 5. 0-0 Nxe4 6. Re1 d5 7. Bxd5 Qxd5 8. Ng5 Be7 9. Nxe4"] = "Be6";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. d4 exd4 5. 0-0 Nxe4 6. Re1 d5 7. Bxd5 Qxd5 8. c4"] = "Qe6";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. d4 exd4 5. 0-0 Nxe4 6. Re1 d5 7. Bxd5 Qxd5 8. c4 Qe6 9. Ng5"] = "Nxg5";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. d4 exd4 5. 0-0 Nxe4 6. Re1 d5 7. Bxd5 Qxd5 8. Qd3"] = "Be7";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. d4 exd4 5. 0-0 Nxe4 6. Re1 d5 7. Bxd5 Qxd5 8. Qd3 Be7 9. Qxe4"] = "Qxe4";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. d4 exd4 5. 0-0 Nxe4 6. Re1 d5 7. Bxd5 Qxd5 8. Qd3 Be7 9. Qxe4 Qxe4 10. Rxe4"] = "Bf5";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. d4 exd4 5. 0-0 Nxe4 6. Re1 d5 7. Bxd5 Qxd5 8. Qd3 Be7 9. Rxe4"] = "Bf5";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. d4 exd4 5. 0-0 Nxe4 6. Re1 d5 7. Bxd5 Qxd5 8. Nfd2"] = "f5";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. d4 exd4 5. 0-0 Nxe4 6. Re1 d5 7. Bxd5 Qxd5 8. Nbd2"] = "f5";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. d4 exd4 5. 0-0 Nxe4 6. Re1 d5 7. Bxd5 Qxd5 8. Nc3"] = "Qd7";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. d4 exd4 5. 0-0 Nxe4 6. Re1 d5 7. Bxd5 Qxd5 8. Nc3 Qd7 9. Nxe4"] = "Be7";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. d4 exd4 5. 0-0 Nxe4 6. Re1 d5 7. Bxd5 Qxd5 8. Nc3 Qd7 9. Rxe4+"] = "Be7";

        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. d4 exd4 5. 0-0 Nxe4 6. Re1 d5 7. Nc3"] = "dxc3";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. d4 exd4 5. 0-0 Nxe4 6. Re1 d5 7. Bb5"] = "Bb4";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. d4 exd4 5. 0-0 Nxe4 6. Re1 d5 7. Nxd4"] = "Nxd4";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. d4 exd4 5. 0-0 Nxe4 6. Re1 d5 7. Nxd4 Nxd4 8. Qxd4"] = "Be6";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. d4 exd4 5. 0-0 Nxe4 6. Re1 d5 7. Bg5"] = "f6";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. d4 exd4 5. 0-0 Nxe4 6. Re1 d5 7. Ng5"] = "Be6";

        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Nc3"] = "Nxe4";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Nc3 Nxe4 5. Nxe4"] = "d5";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Nc3 Nxe4 5. Nxe4 d5 6. Bd3"] = "dxe4";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Nc3 Nxe4 5. Nxe4 d5 6. Bd3 dxe4 7. Bxe4"] = "Bd6";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Nc3 Nxe4 5. Nxe4 d5 6. Bb5"] = "dxe4";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Nc3 Nxe4 5. Nxe4 d5 6. Bb5 dxe4 7. Nxe5"] = "Qg5";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Nc3 Nxe4 5. Nxe4 d5 6. Bxd5"] = "Qxd5";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Nc3 Nxe4 5. Nxe4 d5 6. Bxd5 Qxd5 7. Nc3"] = "Qd6";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Nc3 Nxe4 5. Nxe4 d5 6. Bxd5 Qxd5 7. d3"] = "Bf5";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Nc3 Nxe4 5. Bxf7+"] = "Kxf7";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Nc3 Nxe4 5. Bxf7+ Kxf7 6. Nxe4"] = "d5";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Nc3 Nxe4 5. 0-0"] = "Nxc3";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Nc3 Nxe4 5. 0-0 Nxc3 6. bxc3"] = "e4";

        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Nc3 Nxe4 5. 0-0 Nxc3 6. dxc3"] = "f6";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Nc3 Nxe4 5. 0-0 Nxc3 6. dxc3 f6 7. Qd5"] = "Qe7";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Nc3 Nxe4 5. 0-0 Nxc3 6. dxc3 f6 7. Qd5 Qe7 8. Be3"] = "Nd8";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Nc3 Nxe4 5. 0-0 Nxc3 6. dxc3 f6 7. Re1"] = "d6";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Nc3 Nxe4 5. 0-0 Nxc3 6. dxc3 f6 7. Re1 d6 8. Nd4"] = "d5";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Nc3 Nxe4 5. 0-0 Nxc3 6. dxc3 f6 7. Re1 d6 8. Nd4 d5 9. Bb5"] = "Bd7";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Nc3 Nxe4 5. 0-0 Nxc3 6. dxc3 f6 7. Re1 d6 8. Nd4 d5 9. Nxc6"] = "bxc6";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Nc3 Nxe4 5. 0-0 Nxc3 6. dxc3 f6 7. Re1 d6 8. Nd4 d5 9. Nxc6 bxc6 10. Bb3"] = "Be6";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Nc3 Nxe4 5. 0-0 Nxc3 6. dxc3 f6 7. Bb3"] = "d6";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Nc3 Nxe4 5. 0-0 Nxc3 6. dxc3 f6 7. Qe2"] = "g6";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Nc3 Nxe4 5. 0-0 Nxc3 6. dxc3 f6 7. Be3"] = "d6";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Nc3 Nxe4 5. 0-0 Nxc3 6. dxc3 f6 7. Be3 d6 8. Re1"] = "Ne7";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Nc3 Nxe4 5. 0-0 Nxc3 6. dxc3 f6 7. Be3 d6 8. Nh4"] = "Qe7";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Nc3 Nxe4 5. 0-0 Nxc3 6. dxc3 f6 7. Be3 d6 8. Nh4 Qe7 9. Qh5+"] = "Kd8";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Nc3 Nxe4 5. 0-0 Nxc3 6. dxc3 f6 7. Be3 d6 8. b4"] = "Qe7";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Nc3 Nxe4 5. 0-0 Nxc3 6. dxc3 f6 7. Be3 d6 8. Qe2"] = "Qe7";


        // C46 Four knights game -- BLACK
        book["1. e4 e5 2. Nf3 Nc6 3. Nc3"] = "Nf6";

        book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. d4"] = "exd4";
        book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. d4 exd4 5. Nd5"] = "Nb4";
        book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. d4 exd4 5. e5"] = "dxc3";
        book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. d4 exd4 5. e5 dxc3 6. exf6"] = "Qxf6";
        book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. d4 exd4 5. Nxd4"] = "Bb4";
        book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. d4 exd4 5. Nxd4 Bb4 6. Bc4"] = "Nxe4";
        book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. d4 exd4 5. Nxd4 Bb4 6. Bg5"] = "h6";
        book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. d4 exd4 5. Nxd4 Bb4 6. Bg5 h6 7. Nxc6"] = "bxc6";
        book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. d4 exd4 5. Nxd4 Bb4 6. Bg5 h6 7. Nxc6 bxc6 8. Bh4"] = "0-0";
        book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. d4 exd4 5. Nxd4 Bb4 6. Bg5 h6 7. Nxc6 bxc6 8. Bf4"] = "Nxe4";
        book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. d4 exd4 5. Nxd4 Bb4 6. Bg5 h6 7. Bh4"] = "g5";
        book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. d4 exd4 5. Nxd4 Bb4 6. Bg5 h6 7. Bh4 g5 8. Bg3"] = "Nxe4";
        book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. d4 exd4 5. Nxd4 Bb4 6. Bg5 h6 7. Bf4"] = "Nxe4";
        book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. d4 exd4 5. Nxd4 Bb4 6. Nxc6"] = "bxc6";
        book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. d4 exd4 5. Nxd4 Bb4 6. Nxc6 bxc6 7. e5"] = "Qe7";
        book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. d4 exd4 5. Nxd4 Bb4 6. Nxc6 bxc6 7. e5 Qe7 8. Qe2"] = "Nd5";
        book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. d4 exd4 5. Nxd4 Bb4 6. Nxc6 bxc6 7. e5 Qe7 8. f4"] = "d6";
        book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. d4 exd4 5. Nxd4 Bb4 6. Nxc6 bxc6 7. Qd4"] = "Qe7";
        book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. d4 exd4 5. Nxd4 Bb4 6. Nxc6 bxc6 7. Bd3"] = "d5";
        book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. d4 exd4 5. Nxd4 Bb4 6. Nxc6 bxc6 7. Bd3 d5 8. Bd2"] = "0-0";
        book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. d4 exd4 5. Nxd4 Bb4 6. Nxc6 bxc6 7. Bd3 d5 8. e5"] = "Ng4";
        book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. d4 exd4 5. Nxd4 Bb4 6. Nxc6 bxc6 7. Bd3 d5 8. e5 Ng4 9. 0-0"] = "0-0";
        book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. d4 exd4 5. Nxd4 Bb4 6. Nxc6 bxc6 7. Bd3 d5 8. e5 Ng4 9. Bf4"] = "f6";
        book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. d4 exd4 5. Nxd4 Bb4 6. Nxc6 bxc6 7. Bd3 d5 8. exd5"] = "0-0";
        book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. d4 exd4 5. Nxd4 Bb4 6. Nxc6 bxc6 7. Bd3 d5 8. exd5 0-0 9. 0-0"] = "cxd5";
        book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. d4 exd4 5. Nxd4 Bb4 6. Nxc6 bxc6 7. Bd3 d5 8. exd5 0-0 9. dxc6"] = "Bg4";
        book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. d4 exd4 5. Nxd4 Bb4 6. Nxc6 bxc6 7. Bd3 d5 8. exd5 0-0 9. dxc6 Bg4 10. f3"] = "Re8+";
        book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. d4 exd4 5. Nxd4 Bb4 6. Nxc6 bxc6 7. Bd3 d5 8. exd5 0-0 9. dxc6 Bg4 10. f3 Re8+ 11. Kf1"] = "Be6";
        book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. d4 exd4 5. Nxd4 Bb4 6. Nxc6 bxc6 7. Bd3 d5 8. exd5 0-0 9. dxc6 Bg4 10. f3 Re8+ 11. Be2"] = "Nd5";
        book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. d4 exd4 5. Nxd4 Bb4 6. Nxc6 bxc6 7. Bd3 d5 8. exd5 0-0 9. dxc6 Bg4 10. Qd2"] = "Re8+";
        book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. d4 exd4 5. Nxd4 Bb4 6. Nxc6 bxc6 7. Bd3 d5 8. exd5 0-0 9. dxc6 Bg4 10. Qd2 Re8+ 11. Kf1"] = "Bh5";
        book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. d4 exd4 5. Nxd4 Bb4 6. Nxc6 bxc6 7. Bd3 d5 8. exd5 0-0 9. dxc6 Bg4 10. Qd2 Re8+ 11. Be2"] = "Bxc3";
        book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. d4 exd4 5. Nxd4 Bb4 6. Nxc6 bxc6 7. Bd3 d5 8. exd5 0-0 9. dxc6 Bg4 10. Be2"] = "Qe8";

        book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. a3"] = "d5";
        book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. a3 d5 5. exd5"] = "Nxd5";
        book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. a3 d5 5. exd5 Nxd5 6. Bb5"] = "Nxc3";
        book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. a3 d5 5. exd5 Nxd5 6. Bb5 Nxc3 7. bxc3"] = "Bd6";
        book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. a3 d5 5. exd5 Nxd5 6. Bb5 Nxc3 7. dxc3"] = "Qxd1+";
        book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. a3 d5 5. exd5 Nxd5 6. Bb5 Nxc3 7. dxc3 Qxd1+ 8. Kxd1"] = "Bd7";

        book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. Bc4"] = "Nxe4";
        book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. Bc4 Nxe4 5. 0-0"] = "Nxc3";
        book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. Bc4 Nxe4 5. 0-0 Nxc3 6. dxc3"] = "f6";
        book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. Bc4 Nxe4 5. 0-0 Nxc3 6. bxc3"] = "e4";
        book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. Bc4 Nxe4 5. Nxe4"] = "d5";
        book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. Bc4 Nxe4 5. Nxe4 d5 6. Bd3"] = "dxe4";
        book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. Bc4 Nxe4 5. Nxe4 d5 6. Bd3 dxe4 7. Bxe4"] = "Bd6";
        book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. Bc4 Nxe4 5. Nxe4 d5 6. Bxd5"] = "Qxd5";
        book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. Bc4 Nxe4 5. Nxe4 d5 6. Bxd5 Qxd5 7. Nc3"] = "Qd6";
        book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. Bc4 Nxe4 5. Nxe4 d5 6. Bxd5 Qxd5 7. Nc3 Qd6 8. 0-0"] = "Bf5";
        book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. Bc4 Nxe4 5. Bxf7+"] = "Kxf7";
        book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. Bc4 Nxe4 5. Bxf7+ Kxf7 6. Nxe4"] = "d5";
        book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. Bc4 Nxe4 5. Bxf7+ Kxf7 6. Nxe4 d5 7. Nc3"] = "e4";
        book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. Bc4 Nxe4 5. Bxf7+ Kxf7 6. Nxe4 d5 7. Nc3 e4 8. Ng1"] = "Bf5";
        book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. Bc4 Nxe4 5. Bxf7+ Kxf7 6. Nxe4 d5 7. Ng3"] = "e4";
        book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. Bc4 Nxe4 5. Bxf7+ Kxf7 6. Nxe4 d5 7. Ng3 e4 8. Ng1"] = "h5";
        book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. Bc4 Nxe4 5. Bxf7+ Kxf7 6. Nxe4 d5 7. Ng5+"] = "Kg8";


        book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. Bb4"] = "Nd4";

        book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. Bb5 Nd4 5. Ba4"] = "c6";
        book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. Bb5 Nd4 5. Ba4 c6 6. 0-0"] = "a5";
        book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. Bb5 Nd4 5. Ba4 c6 6. 0-0 a5 7. Bb3"] = "d6";
        book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. Bb5 Nd4 5. Ba4 c6 6. d3"] = "Bc5";
        book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. Bb5 Nd4 5. Ba4 c6 6. d3 Bc5 7. Nxe5"] = "0-0";
        book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. Bb5 Nd4 5. Ba4 c6 6. d3 Bc5 7. Nxd4"] = "exd4";
        book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. Bb5 Nd4 5. Ba4 c6 6. d3 Bc5 7. Nxd4 exd4 8. Ne2"] = "d5";
        book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. Bb5 Nd4 5. Ba4 c6 6. d3 Bc5 7. Nxd4 exd4 8. Ne2 d5 9. exd5"] = "Qa5+";
        book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. Bb5 Nd4 5. Ba4 c6 6. d3 Bc5 7. Nxd4 exd4 8. Ne2 d5 9. exd5 Qa5+ 10. c3"] = "dxc3";
        book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. Bb5 Nd4 5. Ba4 c6 6. d3 Bc5 7. Nxd4 exd4 8. Ne2 d5 9. exd5 Qa5+ 10. c3 dxc3 11. Nxc3"] = "Bg4";
        book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. Bb5 Nd4 5. Ba4 c6 6. d3 Bc5 7. Nxd4 exd4 8. Ne2 d5 9. exd5 Qa5+ 10. c3 dxc3 11. Nxc3 Bg4 12. f3"] = "Nxd5";
        book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. Bb5 Nd4 5. Ba4 c6 6. d3 Bc5 7. Nxd4 exd4 8. Ne2 d5 9. exd5 Qa5+ 10. c3 dxc3 11. bxc3"] = "Nxd5";
        book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. Bb5 Nd4 5. Ba4 c6 6. d3 Bc5 7. 0-0"] = "a5";
        book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. Bb5 Nd4 5. Ba4 c6 6. d3 Bc5 7. Bb3"] = "0-0";
        book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. Bb5 Nd4 5. Ba4 c6 6. d3 Bc5 7. Bb3 0-0 8. 0-0"] = "d6";

        book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. Bb5 Nd4 5. Nxd4"] = "exd4";
        book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. Bb5 Nd4 5. Nxd4 exd4 6. e5"] = "dxc3";
        book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. Bb5 Nd4 5. Nxd4 exd4 6. e5 dxc3 7. exf6"] = "Qxf6";
        book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. Bb5 Nd4 5. Nxd4 exd4 6. e5 dxc3 7. exf6 Qxf6 8. dxc3"] = "Bc5";
        book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. Bb5 Nd4 5. Nxd4 exd4 6. e5 dxc3 7. exf6 Qxf6 8. dxc3 Bc5 9. Qe2+"] = "Qe7";
        book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. Bb5 Nd4 5. Nxd4 exd4 6. e5 dxc3 7.  exf6 Qxf6 8. dxc3 Bc5 9. 0-0"] = "0-0";
        book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. Bb5 Nd4 5. Nxd4 exd4 6. Ne2"] = "c6";
        book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. Bb5 Nd4 5. Nxd4 exd4 6. Nd5"] = "Nxd5";
        book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. Bb5 Nd4 5. Nxd4 exd4 6. Nd5 Nxd5 7. exd5"] = "Qe7+";
        book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. Bb5 Nd4 5. Bc4"] = "Bc5";
        book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. Bb5 Nd4 5. Bc4 Bc5 6. Nxe5"] = "Qe7";


        // C58 Fried Liver Attack -- BLACK
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Ng5"] = "d5";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Ng5 d5 5. Nxf7"] = "Kxf7";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Ng5 d5 5. Nxf7 Kxf7 6. exd5"] = "b5";

        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Ng5 d5 5. exd5"] = "Na5";

        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Ng5 d5 5. exd5 Na5 6. b3"] = "h6";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Ng5 d5 5. exd5 Na5 6. b3 h6 7. Nh3"] = "Bg4";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Ng5 d5 5. exd5 Na5 6. b3 h6 7. Nf3"] = "Nxc4";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Ng5 d5 5. exd5 Na5 6. b3 h6 7. Nf3 Nxc4 8. bxc4"] = "e4";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Ng5 d5 5. exd5 Na5 6. b3 h6 7. Nf3 Nxc4 8. bxc4 e4 9. Ne5"] = "Bd6";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Ng5 d5 5. exd5 Na5 6. b3 h6 7. Nf3 Nxc4 8. bxc4 e4 9. Qe2"] = "Bd6";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Ng5 d5 5. exd5 Na5 6. b3 h6 7. Nf3 Nxc4 8. bxc4 e4 9. Ng1"] = "Bc5";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Ng5 d5 5. exd5 Na5 6. b3 h6 7. Nf3 Nxc4 8. bxc4 e4 9. Nh5"] = "Ng4";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Ng5 d5 5. exd5 Na5 6. b3 h6 7. Nf3 Nxc4 8. bxc4 e4 9. Nd4"] = "c6";

        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Ng5 d5 5. exd5 Na5 6. Bb5+"] = "c6";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Ng5 d5 5. exd5 Na5 6. Bb5+ c6 7. dxc6"] = "bxc6";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Ng5 d5 5. exd5 Na5 6. Bb5+ c6 7. dxc6 bxc6 8. Bd3"] = "Nd5";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Ng5 d5 5. exd5 Na5 6. Bb5+ c6 7. dxc6 bxc6 8. Be2"] = "h6";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Ng5 d5 5. exd5 Na5 6. Bb5+ c6 7. dxc6 bxc6 8. Ba4"] = "h6";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Ng5 d5 5. exd5 Na5 6. Bb5+ c6 7. dxc6 bxc6 8. Qf3"] = "Be7";

        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Ng5 d5 5. exd5 Na5 6. Bb5+ c6 7. dxc6 bxc6 8. Bd3 Nd5 9. Nxh7"] = "Nf4";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Ng5 d5 5. exd5 Na5 6. Bb5+ c6 7. dxc6 bxc6 8. Bd3 Nd5 9. Nxh7 Nf4 10. Nxf8"] = "Nxg2+";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Ng5 d5 5. exd5 Na5 6. Bb5+ c6 7. dxc6 bxc6 8. Bd3 Nd5 9. Nxh7 Nf4 10. Nxf8 Nxg2+ 11. Kf1"] = "Bh3";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Ng5 d5 5. exd5 Na5 6. Bb5+ c6 7. dxc6 bxc6 8. Bd3 Nd5 9. Nxh7 Nf4 10. Nxf8 Nxg2+ 11. Ke2"] = "Bg4+";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Ng5 d5 5. exd5 Na5 6. Bb5+ c6 7. dxc6 bxc6 8. Bd3 Nd5 9. Nxh7 Nf4 10. Nxf8 Nxg2+ 11. Ke2 Bg4+ 12. f3"] = "Nf4+";

        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Ng5 d5 5. exd5 Na5 6. Bb5+ c6 7. dxc6 bxc6 8. Bd3 Nd5 9. Nf3"] = "Bd6";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Ng5 d5 5. exd5 Na5 6. Bb5+ c6 7. dxc6 bxc6 8. Bd3 Nd5 9. h4"] = "Nf4";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Ng5 d5 5. exd5 Na5 6. Bb5+ c6 7. dxc6 bxc6 8. Be2 h6 9. Nf3"] = "e4";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Ng5 d5 5. exd5 Na5 6. Bb5+ c6 7. dxc6 bxc6 8. Ba4 h6 9. Nf3"] = "e4";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Ng5 d5 5. exd5 Na5 6. Bb5+ c6 7. dxc6 bxc6 8. Ba4 h6 9. Nf3 e4 10. Qe2"] = "Bc5";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Ng5 d5 5. exd5 Na5 6. Bb5+ c6 7. dxc6 bxc6 8. Ba4 h6 9. Nf3 e4 10. Ne5"] = "Qd4";

        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Ng5 d5 5. exd5 Na5 6. Bb5+ c6 7. dxc6 bxc6 8. Be2 h6 9. Nf3 e4 10. 0-0"] = "exf3";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Ng5 d5 5. exd5 Na5 6. Bb5+ c6 7. dxc6 bxc6 8. Be2 h6 9. Nf3 e4 10. 0-0 exf3 11. Bxf3"] = "Bd6";
        book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Ng5 d5 5. exd5 Na5 6. Bb5+ c6 7. dxc6 bxc6 8. Be2 h6 9. Nf3 e4 10. 0-0 exf3 11. Bxf3 Bd6 12. Re1+"] = "Be6";


        // C65 Ruy Lopez, Berlin defence -- BLACK
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5"] = "Nf6";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0"] = "Nxe4";

        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. Re1"] = "Nd6";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. Re1 Nd6 6. Nxe5"] = "Be7";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. Re1 Nd6 6. Nxe5 Be7 7. Bf1"] = "Nxe5";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. Re1 Nd6 6. Nxe5 Be7 7. Bf1 Nxe5 8. Re5"] = "0-0";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. Re1 Nd6 6. Nxe5 Be7 7. Bd3"] = "Nxe5";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. Re1 Nd6 6. Nxe5 Be7 7. Bd3 Nxe5 8. Rxe5"] = "0-0";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. Re1 Nd6 6. Nxe5 Be7 7. Bd3 Nxe5 8. Rxe5 0-0 9. Qg4"] = "f5";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. Re1 Nd6 6. Nxe5 Be7 7. Bd3 Nxe5 8. Rxe5 0-0 9. Qg4 f5 10. Qg3"] = "Bh4";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. Re1 Nd6 6. Nxe5 Be7 7. Bd3 Nxe5 8. Rxe5 0-0 9. Qg4 f5 10. Qf3"] = "c6";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. Re1 Nd6 6. Nxe5 Be7 7. Bd3 Nxe5 8. Rxe5 0-0 9. Qf3"] = "c6";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. Re1 Nd6 6. Nxe5 Be7 7. Bd3 Nxe5 8. Rxe5 0-0 9. Nc3"] = "c6";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. Re1 Nd6 6. Nxe5 Be7 7. Bd3 Nxe5 8. Rxe5 0-0 9. Nc3 c6 10. Re1"] = "g6";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. Re1 Nd6 6. Nxe5 Be7 7. Bd3 Nxe5 8. Rxe5 0-0 9. Nc3 c6 10. Qg4"] = "f5";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. Re1 Nd6 6. Nxe5 Be7 7. Bd3 Nxe5 8. Rxe5 0-0 9. Nc3 c6 10. Qg4 f5 11. Qg3"] = "Bh4";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. Re1 Nd6 6. Nxe5 Be7 7. Bd3 Nxe5 8. Rxe5 0-0 9. Nc3 c6 10. Qg4 f5 11. Qf3"] = "Ne8";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. Re1 Nd6 6. Nxe5 Be7 7. Bd3 Nxe5 8. Rxe5 0-0 9. Nc3 c6 10. Qg4 f5 11. Qf3 Ne8 12. b3"] = "d5";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. Re1 Nd6 6. Nxe5 Be7 7. Bd3 Nxe5 8. Rxe5 0-0 9. Nc3 c6 10. Qg4 f5 11. Qf3 Ne8 12. Rxf5"] = "Nf6";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. Re1 Nd6 6. Nxe5 Be7 7. Bd3 Nxe5 8. Rxe5 0-0 9. Nc3 c6 10. b3"] = "Ne8";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. Re1 Nd6 6. Nxe5 Be7 7. Bd3 Nxe5 8. Rxe5 0-0 9. Nc3 c6 10. Qf3"] = "Ne8";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. Re1 Nd6 6. Nxe5 Be7 7. Bd3 Nxe5 8. Rxe5 0-0 9. Nc3 c6 10. Qe2"] = "Bf6";

        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. Re1 Nd6 6. Nxe5 Be7 7. Nxc6"] = "dxc6";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. Re1 Nd6 6. Nxe5 Be7 7. Nxc6 dxc6 8. Bd3"] = "0-0";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. Re1 Nd6 6. Nxe5 Be7 7. Nxc6 dxc6 8. Be2"] = "0-0";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. Re1 Nd6 6. Nxe5 Be7 7. Nxc6 dxc6 8. Ba4"] = "0-0";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. Re1 Nd6 6. Nxe5 Be7 7. Nxc6 dxc6 8. Bf1"] = "Be6";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. Re1 Nd6 6. Nxe5 Be7 7. Nxc6 dxc6 8. Bf1 Be6 9. c3"] = "Qd7";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. Re1 Nd6 6. Nxe5 Be7 7. Nxc6 dxc6 8. Bf1 Be6 9. c3 Qd7 10. d4"] = "0-0-0";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. Re1 Nd6 6. Nxe5 Be7 7. Nxc6 dxc6 8. Bf1 Be6 9. d4"] = "Qd7";

        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. Re1 Nd6 6. Nxe5 Be7 7. Ba4"] = "Nxe5";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. Re1 Nd6 6. Nxe5 Be7 7. Ba4 Nxe5 8. Rxe5"] = "0-0";

        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. Re1 Nd6 6. Bxc6"] = "dxc6";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. Re1 Nd6 6. Bxc6 dxc6 7. d4"] = "e4";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. Re1 Nd6 6. Bxc6 dxc6 7. Rxe5+"] = "Be7";

        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. Re1 Nd6 6. Bxc6 dxc6 7. Nxe5"] = "Be7";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. Re1 Nd6 6. Bxc6 dxc6 7. Nxe5 Be7 8. d4"] = "0-0";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. Re1 Nd6 6. Bxc6 dxc6 7. Nxe5 Be7 8. d4 0-0 9. Bf4"] = "Re8";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. Re1 Nd6 6. Bxc6 dxc6 7. Nxe5 Be7 8. d4 0-0 9. Nd2"] = "Re8";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. Re1 Nd6 6. Bxc6 dxc6 7. Nxe5 Be7 8. d4 0-0 9. c3"] = "Re8";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. Re1 Nd6 6. Bxc6 dxc6 7. Nxe5 Be7 8. d4 0-0 9. b3"] = "a5";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. Re1 Nd6 6. Bxc6 dxc6 7. Nxe5 Be7 8. d4 0-0 9. Nc3"] = "Re8";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. Re1 Nd6 6. Bxc6 dxc6 7. Nxe5 Be7 8. d4 0-0 9. Qf3"] = "Be6";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. Re1 Nd6 6. Bxc6 dxc6 7. Nxe5 Be7 8. Qe2"] = "Nf5";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. Re1 Nd6 6. Bxc6 dxc6 7. Nxe5 Be7 8. Nc3"] = "0-0";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. Re1 Nd6 6. Bxc6 dxc6 7. Nxe5 Be7 8. d3"] = "0-0";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. Re1 Nd6 6. Bxc6 dxc6 7. Nxe5 Be7 8. h3"] = "0-0";

        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. Qe2"] = "Nd6";

        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. d4"] = "Nd6";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. d4 Nd6 6. Bxc6"] = "dxc6";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. d4 Nd6 6. Bxc6 dxc6 7. dxe5"] = "Nf5";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. d4 Nd6 6. Bxc6 dxc6 7. dxe5 Nf5 8. Qxd8+"] = "Kxd8";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. d4 Nd6 6. Bxc6 dxc6 7. dxe5 Nf5 8. Qxd8+ Kxd8 9. Nc3"] = "Ke8";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. d4 Nd6 6. Bxc6 dxc6 7. dxe5 Nf5 8. Qxd8+ Kxd8 9. b3"] = "Be7";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. d4 Nd6 6. Bxc6 dxc6 7. dxe5 Nf5 8. Qxd8+ Kxd8 9. b3 Be7 10. Bb2"] = "Be6";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. d4 Nd6 6. Bxc6 dxc6 7. dxe5 Nf5 8. Qxd8+ Kxd8 9. b3 Be7 10. Rd1+"] = "Bd7";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. d4 Nd6 6. Bxc6 dxc6 7. dxe5 Nf5 8. Qxd8+ Kxd8 9. b3 Be7 10. Nc3"] = "Be6";

        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. d4 Nd6 6. Bxc6 dxc6 7. dxe5 Nf5 8. Qxd8+ Kxd8 9. Rd1+"] = "Ke8";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. d4 Nd6 6. Bxc6 dxc6 7. dxe5 Nf5 8. Qxd8+ Kxd8 9. Rd1+ Ke8 10. b3"] = "Be7";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. d4 Nd6 6. Bxc6 dxc6 7. dxe5 Nf5 8. Qxd8+ Kxd8 9. Rd1+ Ke8 10. b3 Be7 11. Bb2"] = "Nh4";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. d4 Nd6 6. Bxc6 dxc6 7. dxe5 Nf5 8. Qxd8+ Kxd8 9. Rd1+ Ke8 10. b3 Be7 11. Nc3"] = "Nh4";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. d4 Nd6 6. Bxc6 dxc6 7. dxe5 Nf5 8. Qxd8+ Kxd8 9. Rd1+ Ke8 10. b3 Be7 11. Nbd2"] = "Nh4";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. d4 Nd6 6. Bxc6 dxc6 7. dxe5 Nf5 8. Qxd8+ Kxd8 9. Rd1+ Ke8 10. Nc3"] = "Be7";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. d4 Nd6 6. Bxc6 dxc6 7. dxe5 Nf5 8. Qxd8+ Kxd8 9. Rd1+ Ke8 10. Nc3 Be7 11. Ne2"] = "b6";


        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. d3"] = "Nd6";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. Bxc6"] = "dxc6";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. Bxc6 dxc6 6. Re1"] = "Nd6";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. Bxc6 dxc6 6. Re1 Nd6 7. Nxe5"] = "Be7";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. Bxc6 dxc6 6. Re1 Nd6 7. Rxe5"] = "Be7";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. Bxc6 dxc6 6. Nxe5"] = "Qf6";

        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. d3"] = "Bc5";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. Qe2"] = "Bc5";

        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. Nc3"] = "Nd4";

        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. Nc3 Nd4 5. Nxd4"] = "exd4";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. Nc3 Nd4 5. Nxd4 exd4 6. e5"] = "dxc3";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. Nc3 Nd4 5. Nxd4 exd4 6. e5 dxc3 7. exf6"] = "Qxf6";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. Nc3 Nd4 5. Nxd4 exd4 6. e5 dxc3 7. exf6 Qxf6 8. bxc3"] = "c6";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. Nc3 Nd4 5. Nxd4 exd4 6. e5 dxc3 7. exf6 Qxf6 8. dxc3"] = "Bc5";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. Nc3 Nd4 5. Nxd4 exd4 6. e5 dxc3 7. exf6 Qxf6 8. dxc3 Bc5 9. 0-0"] = "0-0";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. Nc3 Nd4 5. Nxd4 exd4 6. e5 dxc3 7. exf6 Qxf6 8. dxc3 Bc5 9. Qe2+"] = "Qe7";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. Nc3 Nd4 5. Nxd4 exd4 6. Nd5"] = "Nxd5";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. Nc3 Nd4 5. Nxd4 exd4 6. Nd5 Nxd5 7. exd5"] = "Qe7+";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. Nc3 Nd4 5. Nxd4 exd4 6. Nd5 Nxd5 7. exd5 Qe7+ 8. Be2"] = "d3";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. Nc3 Nd4 5. Nxd4 exd4 6. Nd5 Nxd5 7. exd5 Qe7+ 8. Be2 d3 9. cxd3"] = "Qf6";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. Nc3 Nd4 5. Nxd4 exd4 6. Nd5 Nxd5 7. exd5 Qe7+ 8. Qe2"] = "a6";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. Nc3 Nd4 5. Nxd4 exd4 6. Nd5 Nxd5 7. exd5 Qe7+ 8. Qe2 a6 9. Bd3"] = "c5";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. Nc3 Nd4 5. Nxd4 exd4 6. Nd5 Nxd5 7. exd5 Qe7+ 8. Qe2 a6 9. Ba4"] = "Qxe2+";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. Nc3 Nd4 5. Nxd4 exd4 6. Nd5 Nxd5 7. exd5 Qe7+ 8. Qe2 a6 9. Ba4 Qxe2+ 10. Kxe2"] = "Bd6";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. Nc3 Nd4 5. Nxd4 exd4 6. Nd5 Nxd5 7. exd5 Qe7+ 8. Qe2 a6 9. Bc4"] = "Qxe2+";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. Nc3 Nd4 5. Nxd4 exd4 6. Nd5 Nxd5 7. exd5 Qe7+ 8. Qe2 a6 9. Bc4 Qxe2+ 10. Bxe2"] = "f6";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. Nc3 Nd4 5. Nxd4 exd4 6. Nd5 Nxd5 7. exd5 Qe7+ 8. Qe2 a6 9. Bc4 Qxe2+ 10. Kxe2"] = "Bd6";

        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. Nc3 Nd4 5. Nxe5"] = "Qe7";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. Nc3 Nd4 5. Bc4"] = "Bc5";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. Nc3 Nd4 5. 0-0"] = "c6";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. Nc3 Nd4 5. 0-0 c6 6. Bc4"] = "d6";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. Nc3 Nd4 5. 0-0 c6 6. Be2"] = "Bd6";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. Nc3 Nd4 5. 0-0 c6 6. Ba4"] = "a5";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. Nc3 Nd4 5. 0-0 c6 6. Ba4 a5 7. Bb3"] = "d6";

        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. Nc3 Nd4 5. Ba4"] = "c6";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. Nc3 Nd4 5. Ba4 c6 6. d3"] = "Bc5";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. Nc3 Nd4 5. Ba4 c6 6. Nxe5"] = "d6";
        book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. Nc3 Nd4 5. Ba4 c6 6. 0-0"] = "a5";


        // C46 Four knights game -- BLACK
        book["1. e4 e5 2. Nc3"] = "Nc6";

        book["1. e4 e5 2. Nc3 Nc6 3. d3"] = "Bb4";
        book["1. e4 e5 2. Nc3 Nc6 3. d3 Bb4 4. Be2"] = "Nge7";
        book["1. e4 e5 2. Nc3 Nc6 3. d3 Bb4 4. a3"] = "Bxc3+";
        book["1. e4 e5 2. Nc3 Nc6 3. d3 Bb4 4. a3 Bxc3+ 5. bxc3"] = "Nge7";
        book["1. e4 e5 2. Nc3 Nc6 3. d3 Bb4 4. Nf3"] = "Nf6";
        book["1. e4 e5 2. Nc3 Nc6 3. d3 Bb4 4. Bd2"] = "Nf6";

        book["1. e4 e5 2. Nc3 Nc6 3. Nf3"] = "Nf6";

        book["1. e4 e5 2. Nc3 Nc6 3. Nf3 Nf6 4. Bb5"] = "Nd4";
        book["1. e4 e5 2. Nc3 Nc6 3. Nf3 Nf6 4. Bb5 Nd4 5. Nxd4"] = "exd4";
        book["1. e4 e5 2. Nc3 Nc6 3. Nf3 Nf6 4. Bb5 Nd4 5. Nxd4 exd4 6. e5"] = "dxc3";
        book["1. e4 e5 2. Nc3 Nc6 3. Nf3 Nf6 4. Bb5 Nd4 5. Nxd4 exd4 6. e5 dxc3 7. exf6"] = "Qxf6";
        book["1. e4 e5 2. Nc3 Nc6 3. Nf3 Nf6 4. Bb5 Nd4 5. Nxd4 exd4 6. e5 dxc3 7. exf6 Qxf6 8. dxc3"] = "Bc5";
        book["1. e4 e5 2. Nc3 Nc6 3. Nf3 Nf6 4. Bb5 Nd4 5. Nxd4 exd4 6. e5 dxc3 7. exf6 Qxf6 8. dxc3 Bc5 9. Qe2+"] = "Qe7";
        book["1. e4 e5 2. Nc3 Nc6 3. Nf3 Nf6 4. Bb5 Nd4 5. Nxd4 exd4 6. e5 dxc3 7. exf6 Qxf6 8. dxc3 Bc5 9. 0-0"] = "0-0";
        book["1. e4 e5 2. Nc3 Nc6 3. Nf3 Nf6 4. Bb5 Nd4 5. Nxd4 exd4 6. Ne2"] = "c6";
        book["1. e4 e5 2. Nc3 Nc6 3. Nf3 Nf6 4. Bb5 Nd4 5. Nxd4 exd4 6. Nd5"] = "Nxd5";
        book["1. e4 e5 2. Nc3 Nc6 3. Nf3 Nf6 4. Bb5 Nd4 5. Nxd4 exd4 6. Nd5 Nxd5 7. exd5"] = "Qe7+";
        book["1. e4 e5 2. Nc3 Nc6 3. Nf3 Nf6 4. Bb5 Nd4 5. Nxd4 exd4 6. Nd5 Nxd5 7. exd5 Qe7+ 8. Be2"] = "d3";
        book["1. e4 e5 2. Nc3 Nc6 3. Nf3 Nf6 4. Bb5 Nd4 5. Nxd4 exd4 6. Nd5 Nxd5 7. exd5 Qe7+ 8. Be2 d3 9. cxd3"] = "Qf6";
        book["1. e4 e5 2. Nc3 Nc6 3. Nf3 Nf6 4. Bb5 Nd4 5. Nxd4 exd4 6. Nd5 Nxd5 7. exd5 Qe7+ 8. Qe2"] = "b6";

        book["1. e4 e5 2. Nc3 Nc6 3. Nf3 Nf6 4. Bb5 Nd4 5. Ba4"] = "c6";
        book["1. e4 e5 2. Nc3 Nc6 3. Nf3 Nf6 4. Bb5 Nd4 5. Bc4"] = "Bc5";
        book["1. e4 e5 2. Nc3 Nc6 3. Nf3 Nf6 4. Bb5 Nd4 5. Bc4 Bc5 6. Nxe5"] = "Qe7";

        book["1. e4 e5 2. Nc3 Nc6 3. Nf3 Nf6 4. d4"] = "exd4";
        book["1. e4 e5 2. Nc3 Nc6 3. Nf3 Nf6 4. g3"] = "Bc5";
        book["1. e4 e5 2. Nc3 Nc6 3. Nf3 Nf6 4. a3"] = "d5";
        book["1. e4 e5 2. Nc3 Nc6 3. Nf3 Nf6 4. Be2"] = "d5";
        book["1. e4 e5 2. Nc3 Nc6 3. Nf3 Nf6 4. Bc4"] = "Nxe4";
        book["1. e4 e5 2. Nc3 Nc6 3. Nf3 Nf6 4. h3"] = "Bb4";


        book["1. e4 e5 2. Nc3 Nc6 3. g3"] = "Bc5";
        book["1. e4 e5 2. Nc3 Nc6 3. Bc4"] = "Nf6";
        book["1. e4 e5 2. Nc3 Nc6 3. f4"] = "exf4";
        book["1. e4 e5 2. Nc3 Nc6 3. f4 exf4 4. Nf3"] = "g5";
        book["1. e4 e5 2. Nc3 Nc6 3. f4 exf4 4. Nf3 g5 5. d4"] = "g4";
        book["1. e4 e5 2. Nc3 Nc6 3. f4 exf4 4. Nf3 g5 5. h4"] = "g4";
        book["1. e4 e5 2. Nc3 Nc6 3. f4 exf4 4. Nf3 g5 5. h3"] = "h6";
        book["1. e4 e5 2. Nc3 Nc6 3. f4 exf4 4. Nf3 g5 5. Bc4"] = "g4";
        book["1. e4 e5 2. Nc3 Nc6 3. f4 exf4 4. d4"] = "Qh4+";
        book["1. e4 e5 2. Nc3 Nc6 3. f4 exf4 4. d4 Qh4+ 5. Ke2"] = "b6";


        // A46 Queen's pawn game -- BLACK
        book["1. d4 Nf6 2. Nf3"] = "e6";
        book["1. d4 Nf6 2. Nf3 e6 3. c4"] = "d5";
        book["1. d4 Nf6 2. Nf3 e6 3. c4 d5 4. g3"] = "dxc4";
        book["1. d4 Nf6 2. Nf3 e6 3. c4 d5 4. g3 dxc4 5. Bg2"] = "Nc6";
        book["1. d4 Nf6 2. Nf3 e6 3. c4 d5 4. g3 dxc4 5. Qa4"] = "Nbd7";
        book["1. d4 Nf6 2. Nf3 e6 3. c4 d5 4. g3 dxc4 5. Qa4 Nbd7 6. Nc3"] = "a6";
        book["1. d4 Nf6 2. Nf3 e6 3. c4 d5 4. g3 dxc4 5. Qa4 Nbd7 6. Bg2"] = "a6";

        book["1. d4 Nf6 2. Nf3 e6 3. c4 d5 4. c5"] = "b6";
        book["1. d4 Nf6 2. Nf3 e6 3. c4 d5 4. c5 b6 5. cxb6"] = "axb6";
        book["1. d4 Nf6 2. Nf3 e6 3. c4 d5 4. c5 b6 5. Be3"] = "bxc5";
        book["1. d4 Nf6 2. Nf3 e6 3. c4 d5 4. c5 b6 5. Be3 bxc5 6. dxc5"] = "Nfd7";
        book["1. d4 Nf6 2. Nf3 e6 3. c4 d5 4. c5 b6 5. b4"] = "a5";
        book["1. d4 Nf6 2. Nf3 e6 3. c4 d5 4. c5 b6 5. Nc3"] = "bxc5";
        book["1. d4 Nf6 2. Nf3 e6 3. c4 d5 4. c5 b6 5. Nc3 bxc5 6. e3"] = "Nbd7";
        book["1. d4 Nf6 2. Nf3 e6 3. c4 d5 4. c5 b6 5. e3"] = "bxc5";
        book["1. d4 Nf6 2. Nf3 e6 3. c4 d5 4. c5 b6 5. e3 bxc5 6. Be2"] = "Bd6";
        book["1. d4 Nf6 2. Nf3 e6 3. c4 d5 4. c5 b6 5. e3 bxc5 6. Nc3"] = "Bd6";
        book["1. d4 Nf6 2. Nf3 e6 3. c4 d5 4. c5 b6 5. e3 bxc5 6. dxc5"] = "Bxc5";

        book["1. d4 Nf6 2. Nf3 e6 3. c4 d5 4. Nc3"] = "Bb4";
        book["1. d4 Nf6 2. Nf3 e6 3. c4 d5 4. Nc3 Bb4 5. Bg5"] = "h6";
        book["1. d4 Nf6 2. Nf3 e6 3. c4 d5 4. Nc3 Bb4 5. Bg5 h6 6. Bxf6"] = "Qxf6";
        book["1. d4 Nf6 2. Nf3 e6 3. c4 d5 4. Nc3 Bb4 5. Bg5 h6 6. Bh4"] = "dxc4";
        book["1. d4 Nf6 2. Nf3 e6 3. c4 d5 4. Nc3 Bb4 5. Bg5 h6 6. Bf4"] = "dxc4";
        book["1. d4 Nf6 2. Nf3 e6 3. c4 d5 4. Nc3 Bb4 5. Bg5 h6 6. Qa4+"] = "Nc3";
        book["1. d4 Nf6 2. Nf3 e6 3. c4 d5 4. Nc3 Bb4 5. Qb3"] = "c5";
        book["1. d4 Nf6 2. Nf3 e6 3. c4 d5 4. Nc3 Bb4 5. e3"] = "0-0";
        book["1. d4 Nf6 2. Nf3 e6 3. c4 d5 4. Nc3 Bb4 5. Qa4+"] = "Nc6";
        book["1. d4 Nf6 2. Nf3 e6 3. c4 d5 4. Nc3 Bb4 5. cxd5"] = "exd5";
        book["1. d4 Nf6 2. Nf3 e6 3. c4 d5 4. Nc3 Bb4 5. cxd5 exd5 6. Qa4+"] = "Nc6";
        book["1. d4 Nf6 2. Nf3 e6 3. c4 d5 4. Nc3 Bb4 5. cxd5 exd5 6. Bf4"] = "Ne4";
        book["1. d4 Nf6 2. Nf3 e6 3. c4 d5 4. Nc3 Bb4 5. cxd5 exd5 6. Qc2"] = "c5";
        book["1. d4 Nf6 2. Nf3 e6 3. c4 d5 4. Nc3 Bb4 5. cxd5 exd5 6. Qb3"] = "c5";
        book["1. d4 Nf6 2. Nf3 e6 3. c4 d5 4. Nc3 Bb4 5. cxd5 exd5 6. Bg5"] = "h6";
        book["1. d4 Nf6 2. Nf3 e6 3. c4 d5 4. Nc3 Bb4 5. cxd5 exd5 6. Bg5 h6 7. Bh4"] = "c6";
        book["1. d4 Nf6 2. Nf3 e6 3. c4 d5 4. Nc3 Bb4 5. cxd5 exd5 6. Bg5 h6 7. Bf4"] = "Ne4";
        book["1. d4 Nf6 2. Nf3 e6 3. c4 d5 4. Nc3 Bb4 5. cxd5 exd5 6. Bg5 h6 7. Qa4+"] = "Nc6";
        book["1. d4 Nf6 2. Nf3 e6 3. c4 d5 4. Nc3 Bb4 5. cxd5 exd5 6. Bg5 h6 7. Bxf6"] = "Qxf6";

        book["1. d4 Nf6 2. Nf3 e6 3. c4 d5 4. Bg5"] = "dxc4";
        book["1. d4 Nf6 2. Nf3 e6 3. c4 d5 4. e3"] = "c5";
        book["1. d4 Nf6 2. Nf3 e6 3. c4 d5 4. e3 c5 5. Nc3"] = "Nc6";
        book["1. d4 Nf6 2. Nf3 e6 3. c4 d5 4. e3 c5 5. Nc3 Nc6 6. a3"] = "a6";
        book["1. d4 Nf6 2. Nf3 e6 3. c4 d5 4. e3 c5 5. Nc3 Nc6 6. cxd5"] = "exd5";
        book["1. d4 Nf6 2. Nf3 e6 3. c4 d5 4. e3 c5 5. Nc3 Nc6 6. Be2"] = "cxd4";
        book["1. d4 Nf6 2. Nf3 e6 3. c4 d5 4. e3 c5 5. Nc3 Nc6 6. Be2 cxd4 7. exd4"] = "Be7";
        book["1. d4 Nf6 2. Nf3 e6 3. c4 d5 4. e3 c5 5. Nc3 Nc6 6. Be2 cxd4 7. Nxd4"] = "Bb4";
        book["1. d4 Nf6 2. Nf3 e6 3. c4 d5 4. e3 c5 5. Nc3 Nc6 6. Bd3"] = "dxc4";
        book["1. d4 Nf6 2. Nf3 e6 3. c4 d5 4. e3 c5 5. Nc3 Nc6 6. Bd3 dxc4 7. Bxc4"] = "cxd4";
        book["1. d4 Nf6 2. Nf3 e6 3. c4 d5 4. e3 c5 5. Nc3 Nc6 6. Bd3 dxc4 7. Bxc4 cxd4 8. exd4"] = "Be7";
        book["1. d4 Nf6 2. Nf3 e6 3. c4 d5 4. e3 c5 5. Nc3 Nc6 6. Bd3 dxc4 7. Bxc4 cxd4 8. Nxd4"] = "Bd7";
        book["1. d4 Nf6 2. Nf3 e6 3. c4 d5 4. e3 c5 5. Nc3 Nc6 6. dxc5"] = "Bxc5";
        book["1. d4 Nf6 2. Nf3 e6 3. c4 d5 4. e3 c5 5. Nc3 Nc6 6. Ne5"] = "cxd4";
        book["1. d4 Nf6 2. Nf3 e6 3. c4 d5 4. e3 c5 5. Nc3 Nc6 6. Ne5 cxd4 7. exd4"] = "Bd6";
        book["1. d4 Nf6 2. Nf3 e6 3. c4 d5 4. e3 c5 5. Nc3 Nc6 6. Ne5 cxd4 7. Nxc6"] = "bxc6";
        book["1. d4 Nf6 2. Nf3 e6 3. c4 d5 4. e3 c5 5. Nc3 Nc6 6. Ne5 cxd4 7. Nxc6 bxc6 8. exd4"] = "Bd6";
        book["1. d4 Nf6 2. Nf3 e6 3. c4 d5 4. e3 c5 5. Nc3 Nc6 6. Ne5 cxd4 7. Nxc6 bxc6 8. Qxd4"] = "Bd6";
        book["1. d4 Nf6 2. Nf3 e6 3. c4 d5 4. e3 c5 5. Nc3 Nc6 6. h3"] = "a6";
        book["1. d4 Nf6 2. Nf3 e6 3. c4 d5 4. e3 c5 5. Nc3 Nc6 6. b3"] = "cxd4";
        book["1. d4 Nf6 2. Nf3 e6 3. c4 d5 4. e3 c5 5. Nc3 Nc6 6. b3 cxd4 7. exd4"] = "Ne4";
        book["1. d4 Nf6 2. Nf3 e6 3. c4 d5 4. e3 c5 5. Nc3 Nc6 6. b3 cxd4 7. Nxd4"] = "Bb4";
        book["1. d4 Nf6 2. Nf3 e6 3. c4 d5 4. e3 c5 5. cxd5"] = "exd5";
        book["1. d4 Nf6 2. Nf3 e6 3. c4 d5 4. e3 c5 5. cxd5 exd5 6. Bb5+"] = "Nc6";
        book["1. d4 Nf6 2. Nf3 e6 3. c4 d5 4. e3 c5 5. cxd5 exd5 6. Bb5+ Nc6 7. Bxc6+"] = "bxc6";
        book["1. d4 Nf6 2. Nf3 e6 3. c4 d5 4. e3 c5 5. cxd5 exd5 6. Bd3"] = "c4";
        book["1. d4 Nf6 2. Nf3 e6 3. c4 d5 4. e3 c5 5. cxd5 exd5 6. Bd3 c4 7. Be2"] = "b5";
        book["1. d4 Nf6 2. Nf3 e6 3. c4 d5 4. e3 c5 5. cxd5 exd5 6. Bd3 c4 7. Bc2"] = "Bg4";
        book["1. d4 Nf6 2. Nf3 e6 3. c4 d5 4. e3 c5 5. cxd5 exd5 6. Be2"] = "cxd4";
        book["1. d4 Nf6 2. Nf3 e6 3. c4 d5 4. e3 c5 5. cxd5 exd5 6. Be2 cxd4 7. exd4"] = "Nc6";
        book["1. d4 Nf6 2. Nf3 e6 3. c4 d5 4. e3 c5 5. cxd5 exd5 6. Be2 cxd4 7. Nxd4"] = "Bc5";
        book["1. d4 Nf6 2. Nf3 e6 3. c4 d5 4. e3 c5 5. cxd5 exd5 6. Be2 cxd4 7. Qxd4"] = "Nc6";
        book["1. d4 Nf6 2. Nf3 e6 3. c4 d5 4. e3 c5 5. cxd5 exd5 6. Nc3"] = "c4";
        book["1. d4 Nf6 2. Nf3 e6 3. c4 d5 4. e3 c5 5. a3"] = "h6";
        book["1. d4 Nf6 2. Nf3 e6 3. c4 d5 4. e3 c5 5. dxc5"] = "Bxc5";
        book["1. d4 Nf6 2. Nf3 e6 3. c4 d5 4. e3 c5 5. Bd3"] = "dxc4";
        book["1. d4 Nf6 2. Nf3 e6 3. c4 d5 4. e3 c5 5. Bd3 dxc4 6. Bxc4"] = "Be7";
        book["1. d4 Nf6 2. Nf3 e6 3. c4 d5 4. e3 c5 5. Be2"] = "cxd4";
        book["1. d4 Nf6 2. Nf3 e6 3. c4 d5 4. e3 c5 5. Be2 cxd4 6. exd4"] = "dxc4";
        book["1. d4 Nf6 2. Nf3 e6 3. c4 d5 4. e3 c5 5. Be2 cxd4 6. exd4 dxc4 7. Bxc4"] = "Be7";
        book["1. d4 Nf6 2. Nf3 e6 3. c4 d5 4. e3 c5 5. Be2 cxd4 6. Nxd4"] = "dxc4";
        book["1. d4 Nf6 2. Nf3 e6 3. c4 d5 4. e3 c5 5. Be2 cxd4 6. Nxd4 dxc4 7. 0-0"] = "Be7";
        book["1. d4 Nf6 2. Nf3 e6 3. c4 d5 4. e3 c5 5. Be2 cxd4 6. Nxd4 dxc4 7. Bxc4"] = "e5";
        book["1. d4 Nf6 2. Nf3 e6 3. c4 d5 4. e3 c5 5. Be2 cxd4 6. Qxd4"] = "Nc6";
        book["1. d4 Nf6 2. Nf3 e6 3. c4 d5 4. e3 c5 5. Nbd2"] = "Nc6";
        book["1. d4 Nf6 2. Nf3 e6 3. c4 d5 4. e3 c5 5. b3"] = "cxd4";
        book["1. d4 Nf6 2. Nf3 e6 3. c4 d5 4. e3 c5 5. b3 cxd4 6. exd4"] = "Nc6";
        book["1. d4 Nf6 2. Nf3 e6 3. c4 d5 4. e3 c5 5. b3 cxd4 6. Nxd4"] = "e5";
        book["1. d4 Nf6 2. Nf3 e6 3. c4 d5 4. e3 c5 5. b3 cxd4 6. Qxd4"] = "Nc6";

        book["1. d4 Nf6 2. Nf3 e6 3. g3"] = "c5";
        book["1. d4 Nf6 2. Nf3 e6 3. g3 c5 4. c3"] = "Nc6";
        book["1. d4 Nf6 2. Nf3 e6 3. g3 c5 4. c3 Nc6 5. Bg2"] = "Be7";
        book["1. d4 Nf6 2. Nf3 e6 3. g3 c5 4. c3 Nc6 5. dxc5"] = "Bxc5";
        book["1. d4 Nf6 2. Nf3 e6 3. g3 c5 4. c4"] = "cxd4";
        book["1. d4 Nf6 2. Nf3 e6 3. g3 c5 4. c4 cxd4 5. Qxd4"] = "Nc6";
        book["1. d4 Nf6 2. Nf3 e6 3. g3 c5 4. c4 cxd4 5. Nxd4"] = "d5";
        book["1. d4 Nf6 2. Nf3 e6 3. g3 c5 4. c4 cxd4 5. Nxd4 d5 6. Bg2"] = "e5";
        book["1. d4 Nf6 2. Nf3 e6 3. g3 c5 4. c4 cxd4 5. Bg2"] = "e5";
        book["1. d4 Nf6 2. Nf3 e6 3. g3 c5 4. e3"] = "d5";
        book["1. d4 Nf6 2. Nf3 e6 3. g3 c5 4. e3 d5 5. Bg2"] = "b5";
        book["1. d4 Nf6 2. Nf3 e6 3. g3 c5 4. Bg2"] = "cxd4";
        book["1. d4 Nf6 2. Nf3 e6 3. g3 c5 4. Bg2 cxd4 5. Nxd4"] = "d5";
        book["1. d4 Nf6 2. Nf3 e6 3. g3 c5 4. Bg2 cxd4 5. Nxd4 d5 6. 0-0"] = "e5";
        book["1. d4 Nf6 2. Nf3 e6 3. g3 c5 4. Bg2 cxd4 5. 0-0"] = "d5";
        book["1. d4 Nf6 2. Nf3 e6 3. g3 c5 4. Bg2 cxd4 5. 0-0 d5 6. Nxd4"] = "e5";
        book["1. d4 Nf6 2. Nf3 e6 3. g3 c5 4. Bg2 cxd4 5. 0-0 d5 6. Qxd4"] = "Nc6";
        book["1. d4 Nf6 2. Nf3 e6 3. g3 c5 4. Bg2 cxd4 5. Qxd4"] = "Nc6";
        book["1. d4 Nf6 2. Nf3 e6 3. g3 c5 4. Bg2 cxd4 5. Qxd4 Nc6 6. Qa4"] = "d5";
        book["1. d4 Nf6 2. Nf3 e6 3. g3 c5 4. Bg2 cxd4 5. Qxd4 Nc6 6. Qd1"] = "Bb4+";
        book["1. d4 Nf6 2. Nf3 e6 3. g3 c5 4. Bg2 cxd4 5. Qxd4 Nc6 6. Qd1 Bb4+ 7. Bd2"] = "Qb6";
        book["1. d4 Nf6 2. Nf3 e6 3. g3 c5 4. Bg2 cxd4 5. Qxd4 Nc6 6. Qd1 Bb4+ 7. c3"] = "Bc5";
        book["1. d4 Nf6 2. Nf3 e6 3. g3 c5 4. Bg2 cxd4 5. Qxd4 Nc6 6. Qd1 Bb4+ 7. c3 Bc5 8. 0-0"] = "0-0";
        book["1. d4 Nf6 2. Nf3 e6 3. g3 c5 4. Bg2 cxd4 5. Qxd4 Nc6 6. Qd1 Bb4+ 7. c3 Bc5 8. c4"] = "0-0";
        book["1. d4 Nf6 2. Nf3 e6 3. g3 c5 4. Bg2 cxd4 5. Qxd4 Nc6 6. Qd1 Bb4+ 7. c3 Bc5 8. Bg5"] = "Bxf2+";

        book["1. d4 Nf6 2. Nf3 e6 3. e3"] = "d5";
        book["1. d4 Nf6 2. Nf3 e6 3. e3 d5 4. c4"] = "Be7";
        book["1. d4 Nf6 2. Nf3 e6 3. e3 d5 4. Nbd2"] = "b6";
        book["1. d4 Nf6 2. Nf3 e6 3. e3 d5 4. Bd3"] = "c5";
        book["1. d4 Nf6 2. Nf3 e6 3. e3 d5 4. Bd3 c5 5. b3"] = "Nc6";

        book["1. d4 Nf6 2. Nf3 e6 3. e3 d5 4. Bd3 c5 5. c3"] = "Nc6";
        book["1. d4 Nf6 2. Nf3 e6 3. e3 d5 4. Bd3 c5 5. c3 Nc6 6. Nbd2"] = "b6";
        book["1. d4 Nf6 2. Nf3 e6 3. e3 d5 4. Bd3 c5 5. c3 Nc6 6. Nbd2 b6 7. Ne5"] = "Nxe5";
        book["1. d4 Nf6 2. Nf3 e6 3. e3 d5 4. Bd3 c5 5. c3 Nc6 6. Nbd2 b6 7. Ne5 Nxe5 8. dxe5"] = "c4";
        book["1. d4 Nf6 2. Nf3 e6 3. e3 d5 4. Bd3 c5 5. c3 Nc6 6. Nbd2 b6 7. 0-0"] = "Bb7";
        book["1. d4 Nf6 2. Nf3 e6 3. e3 d5 4. Bd3 c5 5. c3 Nc6 6. Ne5"] = "Nxe5";
        book["1. d4 Nf6 2. Nf3 e6 3. e3 d5 4. Bd3 c5 5. c3 Nc6 6. Ne5 Nxe5 7. dxe5"] = "Nd7";
        book["1. d4 Nf6 2. Nf3 e6 3. e3 d5 4. Bd3 c5 5. c3 Nc6 6. b3"] = "Bd6";
        book["1. d4 Nf6 2. Nf3 e6 3. e3 d5 4. Bd3 c5 5. c3 Nc6 6. Qe2"] = "b6";
        book["1. d4 Nf6 2. Nf3 e6 3. e3 d5 4. Bd3 c5 5. c3 Nc6 6. 0-0"] = "Bd6";
        book["1. d4 Nf6 2. Nf3 e6 3. e3 d5 4. Bd3 c5 5. c3 Nc6 6. 0-0 Bd6 7. Nbd2"] = "0-0";
        book["1. d4 Nf6 2. Nf3 e6 3. e3 d5 4. Bd3 c5 5. c3 Nc6 6. 0-0 Bd6 7. dxc5"] = "Bxc5";
        book["1. d4 Nf6 2. Nf3 e6 3. e3 d5 4. Bd3 c5 5. c3 Nc6 6. 0-0 Bd6 7. dxc5 Bxc5 8. Nbd2"] = "0-0";
        book["1. d4 Nf6 2. Nf3 e6 3. e3 d5 4. Bd3 c5 5. c3 Nc6 6. 0-0 Bd6 7. dxc5 Bxc5 8. b4"] = "Be7";

        book["1. d4 Nf6 2. Nf3 e6 3. e3 d5 4. Bd3 c5 5. 0-0"] = "b6";
        book["1. d4 Nf6 2. Nf3 e6 3. e3 d5 4. Bd3 c5 5. c4"] = "dxc4";
        book["1. d4 Nf6 2. Nf3 e6 3. e3 d5 4. Bd3 c5 5. c4 dxc4 6. Bxc4"] = "Be7";

        book["1. d4 Nf6 2. Nf3 e6 3. Bg5"] = "c5";

        book["1. d4 Nf6 2. Nf3 e6 3. Bf4"] = "d5";
        book["1. d4 Nf6 2. Nf3 e6 3. Bf4 d5 4. Nbd2"] = "c5";
        book["1. d4 Nf6 2. Nf3 e6 3. Bf4 d5 4. Nbd2 c5 5. e3"] = "Qb6";
        book["1. d4 Nf6 2. Nf3 e6 3. Bf4 d5 4. c3"] = "c5";
        book["1. d4 Nf6 2. Nf3 e6 3. Bf4 d5 4. c4"] = "dxc4";
        book["1. d4 Nf6 2. Nf3 e6 3. Bf4 d5 4. c4 dxc4 5. Qa4+"] = "Nb7";
        book["1. d4 Nf6 2. Nf3 e6 3. Bf4 d5 4. h3"] = "Bd6";
        book["1. d4 Nf6 2. Nf3 e6 3. Bf4 d5 4. Nc3"] = "Bb4";
        book["1. d4 Nf6 2. Nf3 e6 3. Bf4 d5 4. e3"] = "c5";
        book["1. d4 Nf6 2. Nf3 e6 3. Bf4 d5 4. e3 c5 5. c3"] = "Nc6";
        book["1. d4 Nf6 2. Nf3 e6 3. Bf4 d5 4. e3 c5 5. Nbd2"] = "Nc6";
        book["1. d4 Nf6 2. Nf3 e6 3. Bf4 d5 4. e3 c5 5. Be2"] = "Qb6";
        book["1. d4 Nf6 2. Nf3 e6 3. Bf4 d5 4. e3 c5 5. Be2 Qb6 6. b3"] = "Nc6";
        book["1. d4 Nf6 2. Nf3 e6 3. Bf4 d5 4. e3 c5 5. Nc3"] = "a6";
        book["1. d4 Nf6 2. Nf3 e6 3. Bf4 d5 4. e3 c5 5. c4"] = "cxd4";
        book["1. d4 Nf6 2. Nf3 e6 3. Bf4 d5 4. e3 c5 5. c4 cxd4 6. exd4"] = "Bb4+";
        book["1. d4 Nf6 2. Nf3 e6 3. Bf4 d5 4. e3 c5 5. c4 cxd4 6. Nxd4"] = "Nbd7";
        book["1. d4 Nf6 2. Nf3 e6 3. Bf4 d5 4. e3 c5 5. Bd3"] = "Qb6";
        book["1. d4 Nf6 2. Nf3 e6 3. Bf4 d5 4. e3 c5 5. Bb5+"] = "Bd7";
        book["1. d4 Nf6 2. Nf3 e6 3. Bf4 d5 4. e3 c5 5. a3"] = "Nc6";
        book["1. d4 Nf6 2. Nf3 e6 3. Bf4 d5 4. e3 c5 5. h3"] = "Nc6";
        book["1. d4 Nf6 2. Nf3 e6 3. Bf4 d5 4. e3 c5 5. dxc5"] = "Nc6";


        // A05 Reti opening -- BLACK
        book["1. Nf3 Nf6 2. d3"] = "d5";
        book["1. Nf3 Nf6 2. d3 d5 3. Nbd2"] = "c5";
        book["1. Nf3 Nf6 2. d3 d5 3. Bg5"] = "c5";
        book["1. Nf3 Nf6 2. d3 d5 3. Bf4"] = "c5";
        book["1. Nf3 Nf6 2. d3 d5 3. b3"] = "g6";
        book["1. Nf3 Nf6 2. d3 d5 3. g3"] = "c5";
        book["1. Nf3 Nf6 2. d3 d5 3. g3 c5 4. Bg2"] = "Nc6";

        book["1. Nf3 Nf6 2. e3"] = "d5";
        book["1. Nf3 Nf6 2. e3 d5 3. c4"] = "e6";
        book["1. Nf3 Nf6 2. e3 d5 3. b3"] = "Bg4";
        book["1. Nf3 Nf6 2. e3 d5 3. d4"] = "c5";

        book["1. Nf3 Nf6 2. b3"] = "d5";
        book["1. Nf3 Nf6 2. b3 d5 3. Bb2"] = "Bg4";
        book["1. Nf3 Nf6 2. b3 d5 3. e3"] = "Bf5";
        book["1. Nf3 Nf6 2. b3 d5 3. g3"] = "c5";
        book["1. Nf3 Nf6 2. b3 d5 3. g3 c5 4. Bg2"] = "Nc6";
        book["1. Nf3 Nf6 2. b3 d5 3. g3 c5 4. Bg2 Nc6 5. 0-0"] = "e5";
        book["1. Nf3 Nf6 2. b3 d5 3. g3 c5 4. Bg2 Nc6 5. 0-0 e5 6. Bb2"] = "Bd6";
        book["1. Nf3 Nf6 2. b3 d5 3. g3 c5 4. Bg2 Nc6 5. Bb2"] = "Qc7";
        book["1. Nf3 Nf6 2. b3 d5 3. g3 c5 4. Bg2 Nc6 5. Bb2 Qc7 6. 0-0"] = "e5";
        book["1. Nf3 Nf6 2. b3 d5 3. g3 c5 4. Bb2"] = "Qc7";
        book["1. Nf3 Nf6 2. b3 d5 3. g3 c5 4. Bb2 Qc7 5. Bg2"] = "Nc6";
        book["1. Nf3 Nf6 2. b3 d5 3. g3 c5 4. Bb2 Qc7 5. Bg2 Nc6 6. 0-0"] = "e5";


        // A15 English opening -- BLACK
        book["1. Nf3 Nf6 2. c4"] = "e6";
        book["1. Nf3 Nf6 2. c4 e6 3. g3"] = "d5";
        book["1. Nf3 Nf6 2. c4 e6 3. g3 d5 4. Bg2"] = "d4";
        book["1. Nf3 Nf6 2. c4 e6 3. g3 d5 4. Nc3"] = "d4";
        book["1. Nf3 Nf6 2. c4 e6 3. g3 d5 4. d4"] = "Bb4+";
        book["1. Nf3 Nf6 2. c4 e6 3. g3 d5 4. d4 Bb4+ 5. Bd2"] = "Be7";
        book["1. Nf3 Nf6 2. c4 e6 3. g3 d5 4. d4 Bb4+ 5. Bd2 Be7 6. Bg2"] = "0-0";
        book["1. Nf3 Nf6 2. c4 e6 3. g3 d5 4. d4 Bb4+ 5. Bd2 Be7 6. Bg2 0-0 7. 0-0"] = "Nbd7";
        book["1. Nf3 Nf6 2. c4 e6 3. g3 d5 4. d4 Bb4+ 5. Nbd2"] = "dxc4";
        book["1. Nf3 Nf6 2. c4 e6 3. g3 d5 4. d4 Bb4+ 5. Nbd2 dxc4 6. Bg2"] = "b5";
        book["1. Nf3 Nf6 2. c4 e6 3. g3 d5 4. d4 Bb4+ 5. Nbd2 dxc4 6. a3"] = "Bxd2+";
        book["1. Nf3 Nf6 2. c4 e6 3. g3 d5 4. d4 Bb4+ 5. Nc3"] = "0-0";
        book["1. Nf3 Nf6 2. c4 e6 3. g3 d5 4. d4 Bb4+ 5. Nc3 0-0 6. Bg2"] = "dxc4";

        book["1. Nf3 Nf6 2. c4 e6 3. Nc3"] = "Bb4";
        book["1. Nf3 Nf6 2. c4 e6 3. Nc3 Bb4 4. d4"] = "b6";
        book["1. Nf3 Nf6 2. c4 e6 3. Nc3 Bb4 4. Qc2"] = "0-0";
        book["1. Nf3 Nf6 2. c4 e6 3. Nc3 Bb4 4. a3"] = "Bxc3";
        book["1. Nf3 Nf6 2. c4 e6 3. Nc3 Bb4 4. a3 Bxc3 5. dxc3"] = "0-0";
        book["1. Nf3 Nf6 2. c4 e6 3. Nc3 Bb4 4. a3 Bxc3 5. bxc3"] = "0-0";

        book["1. Nf3 Nf6 2. c4 e6 3. d4"] = "d5";
        book["1. Nf3 Nf6 2. c4 e6 3. d4 d5 4. Nc3"] = "Bb4";
        book["1. Nf3 Nf6 2. c4 e6 3. d4 d5 4. Nc3 Bb4 5. cxd5"] = "exd5";
        book["1. Nf3 Nf6 2. c4 e6 3. d4 d5 4. Nc3 Bb4 5. Bg5"] = "0-0";
        book["1. Nf3 Nf6 2. c4 e6 3. d4 d5 4. Nc3 Bb4 5. Qa4+"] = "Nc6";
        book["1. Nf3 Nf6 2. c4 e6 3. d4 d5 4. Nc3 Bb4 5. e3"] = "0-0";
        book["1. Nf3 Nf6 2. c4 e6 3. d4 d5 4. Nc3 Bb4 5. Qb3"] = "c5";
        book["1. Nf3 Nf6 2. c4 e6 3. d4 d5 4. g3"] = "Bb4+";
        book["1. Nf3 Nf6 2. c4 e6 3. d4 d5 4. Bg5"] = "dxc4";
        book["1. Nf3 Nf6 2. c4 e6 3. d4 d5 4. Bg5 dxc4 5. e4"] = "b5";
        book["1. Nf3 Nf6 2. c4 e6 3. d4 d5 4. Bg5 dxc4 5. Nc3"] = "a6";
        book["1. Nf3 Nf6 2. c4 e6 3. d4 d5 4. e3"] = "b6";

        book["1. Nf3 Nf6 2. c4 e6 3. b3"] = "d5";


        // B12 Caro-Kann defence -- WHITE
        book["1. e4 c6 2. d4 g6"] = "Nc3";
        book["1. e4 c6 2. d4 g6 3. Nc3 Bg7"] = "Nf3";
        book["1. e4 c6 2. d4 g6 3. Nc3 d5"] = "Nf3";

        book["1. e4 c6 2. d4 d5"] = "Nc3";

        book["1. e4 c6 2. d4 d5 3. Nc3 Nf6"] = "e5";
        book["1. e4 c6 2. d4 d5 3. Nc3 Nf6 4. e5 Ng8"] = "Bd3";
        book["1. e4 c6 2. d4 d5 3. Nc3 Nf6 4. e5 Nfd7"] = "Bd3";
        book["1. e4 c6 2. d4 d5 3. Nc3 Nf6 4. e5 Nfd7 5. Bd3 e6"] = "Nce2";
        book["1. e4 c6 2. d4 d5 3. Nc3 Nf6 4. e5 Nfd7 5. Bd3 e6 6. Nce2 c5"] = "c3";
        book["1. e4 c6 2. d4 d5 3. Nc3 Nf6 4. e5 Nfd7 5. Bd3 e6 6. Nce2 c5 7. c3 Nc6"] = "a3";
        book["1. e4 c6 2. d4 d5 3. Nc3 Nf6 4. e5 Nfd7 5. Bd3 e6 6. Nce2 c5 7. c3 c4"] = "Bc2";
        book["1. e4 c6 2. d4 d5 3. Nc3 Nf6 4. e5 Nfd7 5. Bd3 e6 6. Nce2 c5 7. c3 c4 8. Bc2 Nc6"] = "Nf4";
        book["1. e4 c6 2. d4 d5 3. Nc3 Nf6 4. e5 Nfd7 5. Bd3 e6 6. Nce2 c5 7. c3 c4 8. Bc2 b5"] = "Nf4";
        book["1. e4 c6 2. d4 d5 3. Nc3 Nf6 4. e5 Nfd7 5. Bd3 e6 6. Nce2 c5 7. c3 c4 8. Bc2 Be7"] = "Ng3";

        book["1. e4 c6 2. d4 d5 3. Nc3 Nd7"] = "exd5";
        book["1. e4 c6 2. d4 d5 3. Nc3 Nd7 4. exd5 Ngf6"] = "dxc6";
        book["1. e4 c6 2. d4 d5 3. Nc3 Nd7 4. exd5 Ngf6 5. dxc6 bxc6"] = "Bd3";
        book["1. e4 c6 2. d4 d5 3. Nc3 Nd7 4. exd5 cxd5"] = "Nxd5";
        book["1. e4 c6 2. d4 d5 3. Nc3 Nd7 4. exd5 cxd5 5. Nxd5 e6"] = "Ne3";

        book["1. e4 c6 2. d4 d5 3. Nc3 dxe4"] = "Nxe4";
        book["1. e4 c6 2. d4 d5 3. Nc3 dxe4 4. Nxe4 Nf6"] = "Nxf6+";
        book["1. e4 c6 2. d4 d5 3. Nc3 dxe4 4. Nxe4 Nf6 5. Nxf6+ gxf6"] = "c3";
        book["1. e4 c6 2. d4 d5 3. Nc3 dxe4 4. Nxe4 Nf6 5. Nxf6+ gxf6 6. c3 e5"] = "Nf3";
        book["1. e4 c6 2. d4 d5 3. Nc3 dxe4 4. Nxe4 Nf6 5. Nxf6+ exf6"] = "c3";
        book["1. e4 c6 2. d4 d5 3. Nc3 dxe4 4. Nxe4 Nf6 5. Nxf6+ exf6 6. c3 Bd6"] = "Bd3";

        book["1. e4 c6 2. d4 d5 3. Nc3 dxe4 4. Nxe4 Bf5"] = "Ng3";
        book["1. e4 c6 2. d4 d5 3. Nc3 dxe4 4. Nxe4 Bf5 5. Ng3 Bg6"] = "Nf3";
        book["1. e4 c6 2. d4 d5 3. Nc3 dxe4 4. Nxe4 Bf5 5. Ng3 Bg6 6. Nf3 Nd7"] = "Bd3";
        book["1. e4 c6 2. d4 d5 3. Nc3 dxe4 4. Nxe4 Bf5 5. Ng3 Bg6 6. Nf3 Nd7 7. Bd3 Bxd3"] = "Qxd3";
        book["1. e4 c6 2. d4 d5 3. Nc3 dxe4 4. Nxe4 Bf5 5. Ng3 Bg6 6. Nf3 Nd7 7. Bd3 Bxd3 8. Qxd3 Ngf6"] = "0-0";
        book["1. e4 c6 2. d4 d5 3. Nc3 dxe4 4. Nxe4 Bf5 5. Ng3 Bg6 6. Nf3 Nd7 7. Bd3 Bxd3 8. Qxd3 e6"] = "0-0";
        book["1. e4 c6 2. d4 d5 3. Nc3 dxe4 4. Nxe4 Bf5 5. Ng3 Bg6 6. Nf3 Nd7 7. Bd3 e6"] = "0-0";
        book["1. e4 c6 2. d4 d5 3. Nc3 dxe4 4. Nxe4 Bf5 5. Ng3 Bg6 6. Nf3 Nd7 7. Bd3 Ngf6"] = "Bxg6";
        book["1. e4 c6 2. d4 d5 3. Nc3 dxe4 4. Nxe4 Bf5 5. Ng3 Bg6 6. Nf3 Nd7 7. Bd3 Ngf6 8. Bxg6 hxg6"] = "0-0";
        book["1. e4 c6 2. d4 d5 3. Nc3 dxe4 4. Nxe4 Bf5 5. Ng3 Bg6 6. Nf3 Nd7 7. Bd3 Ngf6 8. Bxg6 fxg6"] = "0-0";
        book["1. e4 c6 2. d4 d5 3. Nc3 dxe4 4. Nxe4 Bf5 5. Ng3 Bg6 6. Nf3 Nd7 7. Bd3 Qc7"] = "0-0";
        book["1. e4 c6 2. d4 d5 3. Nc3 dxe4 4. Nxe4 Bf5 5. Ng3 Bg6 6. Nf3 Nf6"] = "h4";
        book["1. e4 c6 2. d4 d5 3. Nc3 dxe4 4. Nxe4 Bf5 5. Ng3 Bg6 6. Nf3 e6"] = "h4";

        book["1. e4 c6 2. d4 d5 3. Nc3 dxe4 4. Nxe4 h6"] = "Nf3";

        book["1. e4 c6 2. d4 d5 3. Nc3 dxe4 4. Nxe4 Nd7"] = "Nf3";
        book["1. e4 c6 2. d4 d5 3. Nc3 dxe4 4. Nxe4 Nd7 5. Nf3 Ngf6"] = "Nxf6+";
        book["1. e4 c6 2. d4 d5 3. Nc3 dxe4 4. Nxe4 Nd7 5. Nf3 Ngf6 6. Nxf6+ Nxf6"] = "c3";
        book["1. e4 c6 2. d4 d5 3. Nc3 dxe4 4. Nxe4 Nd7 5. Nf3 Ngf6 6. Nxf6+ Nxf6 7. c3 Bg4"] = "h3";



        // Rare -- WHITE
        book["1. e4 b6"] = "d4";
        book["1. e4 b6 2. d4 Nf6"] = "e5";
        book["1. e4 b6 2. d4 Nf6 3. e5 Ne4"] = "Qe2";
        book["1. e4 b6 2. d4 Nf6 3. e5 Nd5"] = "c4";
        book["1. e4 b6 2. d4 Nf6 3. e5 Ng8"] = "Nf3";
        book["1. e4 b6 2. d4 Nf6 3. e5 Ng8 4. Nf3 Bb7"] = "Bd3";
        book["1. e4 b6 2. d4 Nf6 3. e5 Ng8 4. Nf3 e6"] = "Bd3";
        book["1. e4 b6 2. d4 e6"] = "Nf3";
        book["1. e4 b6 2. d4 e6 3. Nf3 Bb7"] = "Bd3";

        book["1. e4 Nc6"] = "Nf3";
        book["1. e4 Nc6 2. Nf3 d6"] = "d4";
        book["1. e4 Nc6 2. Nf3 e5"] = "Bb5";
        book["1. e4 Nc6 2. Nf3 d5"] = "exd5";
        book["1. e4 Nc6 2. Nf3 d5 3. exd5 Qxd5"] = "Nc3";

        book["1. e4 b6 2. d4 Bb7"] = "Bd3";
        book["1. e4 b6 2. d4 Bb7 3. Bd3 Nf6"] = "Qe2";
        book["1. e4 b6 2. d4 Bb7 3. Bd3 e6"] = "Nf3";
        book["1. e4 b6 2. d4 Bb7 3. Bd3 g6"] = "Nf3";
        book["1. e4 b6 2. d4 Bb7 3. Bd3 g6 4. Nf3 Bg7"] = "c4";
        book["1. e4 b6 2. d4 Bb7 3. Bd3 g6 4. Nf3 Bg7 5. c4 e5"] = "d5";
        book["1. e4 b6 2. d4 Bb7 3. Bd3 g6 4. Nf3 Bg7 5. c4 e6"] = "Nc3";
        book["1. e4 b6 2. d4 Bb7 3. Bd3 g6 4. Nf3 Bg7 5. c4 d6"] = "Nc3";

        book["1. e4 e6 2. d4 Nf6"] = "e5";
        book["1. e4 e6 2. d4 Nf6 3. e5 Ng8"] = "Nf3";
        book["1. e4 e6 2. d4 Nf6 3. e5 Ne4"] = "Ne2";
        book["1. e4 e6 2. d4 Nf6 3. e5 Nd5"] = "Nf3";
        book["1. e4 e6 2. d4 Nf6 3. e5 Nd5 4. Nf3 d6"] = "c4";


        // Rare -- BLACK
        book["1. g4"] = "d5";
        book["1. g4 d5 2. Bg2"] = "Bxg4";
        book["1. g4 d5 2. Bg2 Bxg4 3. c4"] = "c6";
        book["1. g4 d5 2. h3"] = "e5";
        book["1. g4 d5 2. e3"] = "e5";

        book["1. e4 e5 2. Qf3"] = "Nf6";
        book["1. e4 e5 2. Qf3 Nf6 3. Bc4"] = "c6";
        book["1. e4 e5 2. Qf3 Nf6 3. Bc4 c6 4. Ne2"] = "d5";
        book["1. e4 e5 2. Qf3 Nf6 3. Bc4 c6 4. Nc3"] = "b5";
        book["1. e4 e5 2. Qf3 Nf6 3. Bc4 c6 4. Nc3 b5 5. Bb3"] = "a5";

        book["1. e4 e5 2. Bb5"] = "c6";
        book["1. e4 e5 2. Bb5 c6 3. Ba4"] = "d5";
        book["1. e4 e5 2. Bb5 c6 3. Ba4 d5 4. exd5"] = "Qxd5";
        book["1. e4 e5 2. Bb5 c6 3. Bc4"] = "d5";
        book["1. e4 e5 2. Bb5 c6 3. Bc4 d5 4. exd5"] = "cxd5";
        book["1. e4 e5 2. Bb5 c6 3. Bc4 d5 4. exd5 cxd5 5. Bb5+"] = "Nc6";
        book["1. e4 e5 2. Bb5 c6 3. Bc4 d5 4. exd5 cxd5 5. Bb3"] = "Nc6";
        book["1. e4 e5 2. Bb5 c6 3. Bc4 d5 4. exd5 cxd5 5. Be2"] = "Nc6";
        book["1. e4 e5 2. Bb5 c6 3. Be2"] = "Nf6";

        book["1. e4 g6"] = "d4";
        book["1. e4 g6 2. d4 d6"] = "Nf3";
        book["1. e4 g6 2. d4 d6 3. Nf3 Bg7"] = "c4";
        book["1. e4 g6 2. d4 Bg7"] = "Nf3";
        book["1. e4 g6 2. d4 Bg7 Nf3 3. d6"] = "Bd3";
        book["1. e4 g6 2. d4 Bg7 Nf3 3. c6"] = "c4";
        book["1. e4 g6 2. d4 Bg7 Nf3 3. Nf6"] = "e5";
        book["1. e4 g6 2. d4 Bg7 Nf3 3. Nf6 e5 4. Ne4"] = "Bd3";
        book["1. e4 g6 2. d4 Bg7 Nf3 3. Nf6 e5 4. Ng4"] = "h3";
        book["1. e4 g6 2. d4 Bg7 Nf3 3. Nf6 e5 4. Ng4 h3 5. Nh6"] = "Bf4";
        book["1. e4 g6 2. d4 Bg7 Nf3 3. Nf6 e5 4. Nd5"] = "c4";
        book["1. e4 g6 2. d4 Bg7 Nf3 3. c5"] = "dxc5";
        book["1. e4 g6 2. d4 Bg7 Nf3 3. c5 dxc5 4. Qa5+"] = "c3";
        book["1. e4 g6 2. d4 Bg7 Nf3 3. c5 dxc5 4. Qa5+ c3 5. Qxc5"] = "Na3";

        book["1. e4 e5 2. g3"] = "d5";
        book["1. e4 e5 2. g3 d5 3. Bg2"] = "dxe4";
        book["1. e4 e5 2. g3 d5 3. Bg2 dxe4 4. Nc3"] = "f5";
        book["1. e4 e5 2. g3 d5 3. Bg2 dxe4 4. Bxe4"] = "Nf6";
        book["1. e4 e5 2. g3 d5 3. Bg2 dxe4 4. Bxe4 Nf6 5. Bg2"] = "Nc6";
        book["1. e4 e5 2. g3 d5 3. exd5"] = "Qxd5";
        book["1. e4 e5 2. g3 d5 3. exd5 Qxd5 4. Nf3"] = "Bg4";
        book["1. e4 e5 2. g3 d5 3. exd5 Qxd5 4. Nf3 Bg4 5. Be2"] = "Nc6";
        book["1. e4 e5 2. g3 d5 3. exd5 Qxd5 4. Nf3 Bg4 5. Be2 Nc6 6. Nc3"] = "Qd7";
        book["1. e4 e5 2. g3 d5 3. exd5 Qxd5 4. Nf3 Bg4 5. Be2 Nc6 6. Nc3 Qd7 7. d4"] = "Bxf3";
        book["1. e4 e5 2. g3 d5 3. exd5 Qxd5 4. Nf3 Bg4 5. Be2 Nc6 6. Nc3 Qd7 7. d4 Bxf3 8. Bxf3"] = "exd4";
        book["1. e4 e5 2. g3 d5 3. exd5 Qxd5 4. Nf3 Bg4 5. Be2 Nc6 6. Nc3 Qd7 7. 0-0"] = "0-0-0";
        book["1. e4 e5 2. g3 d5 3. exd5 Qxd5 4. Nf3 Bg4 5. Be2 Nc6 6. Nc3 Qd7 7. 0-0 0-0-0 8. d3"] = "Nf6";
        book["1. e4 e5 2. g3 d5 3. exd5 Qxd5 4. Nf3 Bg4 5. Be2 Nc6 6. Nc3 Qd7 7. 0-0 0-0-0 8. a3"] = "f5";
        book["1. e4 e5 2. g3 d5 3. exd5 Qxd5 4. Nf3 Bg4 5. Be2 Nc6 6. Nc3 Qd7 7. 0-0 0-0-0 8. Qe1"] = "e4";
        book["1. e4 e5 2. g3 d5 3. exd5 Qxd5 4. Nf3 Bg4 5. Be2 Nc6 6. Nc3 Qd7 7. 0-0 0-0-0 8. Qe1 e4 9. Ng5"] = "Bxe2";
        book["1. e4 e5 2. g3 d5 3. exd5 Qxd5 4. Nf3 Bg4 5. Be2 Nc6 6. Nc3 Qd7 7. 0-0 0-0-0 8. Qe1 e4 9. Ng5 Bxe2 10. Qxe2"] = "h6";
        book["1. e4 e5 2. g3 d5 3. exd5 Qxd5 4. Nf3 Bg4 5. Be2 Nc6 6. Nc3 Qd7 7. 0-0 0-0-0 8. Qe1 e4 9. Ng5 Bxe2 10. Nxe2"] = "Qf5";
        book["1. e4 e5 2. g3 d5 3. exd5 Qxd5 4. Nf3 Bg4 5. Be2 Nc6 6. Nc3 Qd7 7. 0-0 0-0-0 8. Qe1 e4 9. Nxe4"] = "Re8";
        book["1. e4 e5 2. g3 d5 3. exd5 Qxd5 4. Nf3 Bg4 5. Be2 Nc6 6. Nc3 Qd7 7. 0-0 0-0-0 8. Qe1 e4 9. Nxe4 Re8 10. d3"] = "f5";
}



/*!
 * Find a reply move to a given sequence.
 *
 * This function searches the book file for a given sequence and returns a
 * random move out of the list of replies. If the sequence wasn't found, it
 * returns NULL.
 *
 * @return a string containing the randomly selected move from the replies.
 */
string getReplyTo(string sequence)
{
    string replies_buf;
    char delimiter = '|';
    vector<string> replies;
    string tok;

    // get the list of replies for a given sequence
    if (usePersonalBook)
        replies_buf = book[sequence];
    else
        replies_buf = book[sequence];

    // if no replies, return
    if (replies_buf == "")
        return "";

    // if there are replies, parse them and return them
    stringstream ss(replies_buf);

    // tokenize the line and get a vector of strings with the
    // possible replies 
    while (getline(ss, tok, delimiter))
    {
        tok.erase(std::remove(tok.begin(), tok.end(),' '), tok.end());
        replies.push_back(tok);
    }

    // select a random reply and return it
    srand(time(NULL));
    int randomIndex = rand() % replies.size();
    return replies[randomIndex];
}
