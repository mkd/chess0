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



// initBook()
//
// Fill in the openings book with all the theory lines.
void initBook()
{
    ////////////////
    // WHITE 
    //
    // OPENINGS
    /////////////////
   
   
    //  Initial openings
    book["%"] = "e4";



    // Open openings
    book["1. e4 e5"] = "Nf3";
    book["1. e4 e5 2. Nf3 Nc6"] = "Bb5";
    book["1. e4 e5 2. Nf3 Nf6"] = "Nxe5";
    book["1. e4 e5 2. Nf3 d6"] = "d4";
    book["1. e4 e5 2. Nf3 f5"] = "Nxe5";
    book["1. e4 e5 2. Nf3 d5"] = "exd5";
    book["1. e4 e5 2. Nf3 Qe7"] = "Bc4";
    book["1. e4 e5 2. Nf3 Bc5"] = "Nxe5";

    book["1. e4 e5 2. Nf3 Bc5 3. Nxe5 d6"] = "Nf3";
    book["1. e4 e5 2. Nf3 Bc5 3. Nxe5 Qe7"] = "d4";
    book["1. e4 e5 2. Nf3 Bc5 3. Nxe5 Qe7 4. d4 Nf6"] = "Bc4";
    book["1. e4 e5 2. Nf3 Bc5 3. Nxe5 Qe7 4. d4 Bb6"] = "Bc4";
    book["1. e4 e5 2. Nf3 Bc5 3. Nxe5 Qe7 4. d4 Bb4+"] = "c3";
    book["1. e4 e5 2. Nf3 Bc5 3. Nxe5 Qe7 4. d4 Bd6"] = "Nf3";
    book["1. e4 e5 2. Nf3 Bc5 3. Nxe5 Qe7 4. d4 Bd6 5. Nf3 Qxe4+"] = "Be2";

    book["1. e4 e5 2. Nf3 d6 3. d4 exd4"] = "Nxd4";
    book["1. e4 e5 2. Nf3 d6 3. d4 Nf6"] = "Nc3";
    book["1. e4 e5 2. Nf3 d6 3. d4 Nf6 4. Nc3 Nbd7"] = "Bc4";
    book["1. e4 e5 2. Nf3 d6 3. d4 Nf6 4. Nc3 exd4"] = "Nxd4";



    // Petrov Defense -- BLACK
    book["1. e4 e5 2. Nf3 Nf6 3. Nxe5 d6"] = "Nf3";
    book["1. e4 e5 2. Nf3 Nf6 3. Nxe5 d6 4. Nf3 Nxe4"] = "d4";
    book["1. e4 e5 2. Nf3 Nf6 3. Nxe5 d6 4. Nf3 Nxe4 5. d4 d5"] = "Bd3";
    book["1. e4 e5 2. Nf3 Nf6 3. Nxe5 d6 4. Nf3 Nxe4 5. d4 Be7"] = "Bd3";
    book["1. e4 e5 2. Nf3 Nf6 3. Nxe5 d6 4. Nf3 Nxe4 5. d4 Bg4"] = "Bd3";
    book["1. e4 e5 2. Nf3 Nf6 3. Nxe5 d6 4. Nf3 Nxe4 5. d4 Nc6"] = "Bd3";



    // C42 Petrov, classical attack -- BLACK
    book["1. e4 e5 2. Nf3 Nf6 3. Nxe5 d6 4. Nf3 Nxe4 5. d4 d5 6. Bd3 Nc6"] = "0-0";
    book["1. e4 e5 2. Nf3 Nf6 3. Nxe5 d6 4. Nf3 Nxe4 5. d4 d5 6. Bd3 Be7"] = "0-0";
    book["1. e4 e5 2. Nf3 Nf6 3. Nxe5 d6 4. Nf3 Nxe4 5. d4 d5 6. Bd3 Bd6"] = "0-0";
    book["1. e4 e5 2. Nf3 Nf6 3. Nxe5 d6 4. Nf3 Nxe4 5. d4 d5 6. Bd3 Bg4"] = "h3";
    book["1. e4 e5 2. Nf3 Nf6 3. Nxe5 d6 4. Nf3 Nxe4 5. d4 d5 6. Bd3 Bg4 7. h3 Bh5"] = "0-0";
    book["1. e4 e5 2. Nf3 Nf6 3. Nxe5 d6 4. Nf3 Nxe4 5. d4 d5 6. Bd3 Bg4 7. h3 Bxf3"] = "Qxf3";

    book["1. e4 e5 2. Nf3 Nf6 3. Nxe5 d6 4. Nf3 Nxe4 5. d4 Be7 6. Bd3 Nf6"] = "0-0";
    book["1. e4 e5 2. Nf3 Nf6 3. Nxe5 d6 4. Nf3 Nxe4 5. d4 Be7 6. Bd3 d5"] = "0-0";
    book["1. e4 e5 2. Nf3 Nf6 3. Nxe5 d6 4. Nf3 Nxe4 5. d4 Be7 6. Bd3 d5 7. 0-0 Nc6"] = "c4";

    book["1. e4 e5 2. Nf3 Nf6 3. Nxe5 d6 4. Nf3 Bg4"] = "Nc3";
    book["1. e4 e5 2. Nf3 Nf6 3. Nxe5 d6 4. Nf3 Nc6"] = "Nc3";
    book["1. e4 e5 2. Nf3 Nf6 3. Nxe5 d6 4. Nf3 Qe7"] = "d3";

    book["1. e4 e5 2. Nf3 Nf6 3. Nxe5 Qe7"] = "Nf3";
    book["1. e4 e5 2. Nf3 Nf6 3. Nxe5 Nxe4"] = "Qe2";
    book["1. e4 e5 2. Nf3 Nf6 3. Nxe5 Nc6"] = "Nxc6";
    book["1. e4 e5 2. Nf3 Nf6 3. Nxe5 Bd6"] = "Nc4";
    book["1. e4 e5 2. Nf3 Nf6 3. Nxe5 Bc5"] = "d4";



    // Alekhine Defense (WHITE)
    book["1. e4 Nf6"] = "e5";
    book["1. e4 Nf6 2. e5 Nd5"] = "d4";
    book["1. e4 Nf6 2. e5 Nd5 3. d4 d6"] = "Nf3";
    book["1. e4 Nf6 2. e5 Nd5 3. d4 Nb6"] = "Nf3";
    book["1. e4 Nf6 2. e5 Nd5 3. d4 e6"] = "Nf3";




    // French Defense (XX) -- WHITE
    book["1. e4 e6"] = "d4";
    book["1. e4 e6 2. d4 d5"] = "Nc3";
    book["1. e4 e6 2. d4 d5 3. Nc3 Bb4"] = "e5";
    book["1. e4 e6 2. d4 d5 3. Nc3 Nf6"] = "Bg5";
    book["1. e4 e6 2. d4 d5 3. Nc3 dxe4"] = "Nxe4";
    book["1. e4 e6 2. d4 d5 3. Nc3 c5"] = "exd5";

    book["1. e4 e6 2. d4 d5 3. Nc3 c5 4. exd5 exd5"] = "dxc4";
    book["1. e4 e6 2. d4 d5 3. Nc3 c5 4. exd5 cxd4"] = "Bb5+";
    book["1. e4 e6 2. d4 d5 3. Nc3 c5 4. exd5 cxd4 5.Bb5+ Bd7"] = "Qxd4";

    book["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. e5 c5"] = "Bd2";
    book["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. e5 c5 5. Bd2 Ne7"] = "a3";
    book["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. e5 c5 5. Bd2 cxd4"] = "Nb5";
    book["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. e5 c5 5. Bd2 Nc6"] = "Nb5";
    book["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. e5 c5 5. Bd2 Nh6"] = "Nb5";
    book["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. e5 c5 5. Bd2 Bxc3"] = "Bxc3";


    // C17 French, Winawer, advance, Bogolyubov variation -- BLACK
    book["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. e5 c5 5. Bd2 Bxc3 6. Bxc3 cxd4"] = "Qxd4";
    book["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. e5 c5 5. Bd2 Bxc3 6. Bxc3 cxd4 7. Qxd4 Ne7"] = "Nf3";
    book["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. e5 c5 5. Bd2 Bxc3 6. Bxc3 cxd4 7. Qxd4 Nc6"] = "Qg4";


    book["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. e5 c5 5. Bd2 cxd4 6. Nb5 Bc5"] = "Qg4";
    book["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. e5 c5 5. Bd2 cxd4 6. Nb5 Bxd2+"] = "Qxd2";
    book["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. e5 c5 5. Bd2 cxd4 6. Nb5 Bf8"] = "Nf3";
    book["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. e5 c5 5. Bd2 cxd4 6. Nb5 Be7"] = "Qg4";
    book["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. e5 c5 5. Bd2 cxd4 6. Nb5 Nc6"] = "Bxb4";
    book["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. e5 c5 5. Bd2 cxd4 6. Nb5 Nc6 7. Bxb4 Nxb4"] = "Qd2";
    book["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. e5 c5 5. Bd2 cxd4 6. Nb5 Nc6 7. Bxb4 Nxb4 8. Qd2 Qa5"] = "Nxd4";
    book["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. e5 c5 5. Bd2 cxd4 6. Nb5 Nc6 7. Bxb4 Nxb4 8. Qd2 Nc6"] = "Nd6+";
    book["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. e5 c5 5. Bd2 cxd4 6. Nb5 Nc6 7. Bxb4 Nxb4 8. Qd2 Nc6 9. Nd6+ Kf8"] = "f4";
    book["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. e5 c5 5. Bd2 cxd4 6. Nb5 Nc6 7. Bxb4 Nxb4 8. Qd2 Nc6 9. Nd6+ Ke7"] = "f4";
    book["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. e5 c5 5. Bd2 cxd4 6. Nb5 Nc6 7. Bxb4 Nxb4 8. Qd2 Nc6 9. Nd6+ Ke7 10. f4 g5"] = "Bb5";

    book["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. e5 c5 5. Bd2 Ne7 6. a3 Bxc3"] = "Bxc3";
    book["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. e5 c5 5. Bd2 Ne7 6. a3 Ba5"] = "dxc5";

    book["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. e5 c5 5. Bd2 cxd4 6. Nb5 Bxd2+ 7. Qxd2 Nc6"] = "f4";

    book["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. e5 Ne7"] = "a3";
    book["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. e5 Bf8"] = "Nf3";
    book["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. e5 Bf8 5. Nf3 b6"] = "Bd3";
    book["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. e5 Bf8 5. Nf3 a6"] = "Be3";

    book["1. e4 e6 2. d4 d5 3. Nc3 Nf6 4. Bg5 Be7"] = "e5";
    book["1. e4 e6 2. d4 d5 3. Nc3 Nf6 4. Bg5 Be7 5. e5 Nfd7"] = "Bxe7";
    book["1. e4 e6 2. d4 d5 3. Nc3 Nf6 4. Bg5 Be7 5. e5 Nfd7 6. Bxe7 Qxe7"] = "f4";

    // C12 French, MacCutcheon variation
    book["1. e4 e6 2. d4 d5 3. Nc3 Nf6 4. Bg5 Bb4"] = "e5";
    book["1. e4 e6 2. d4 d5 3. Nc3 Nf6 4. Bg5 Bb4 5. e5 h6"] = "Bd2";
    book["1. e4 e6 2. d4 d5 3. Nc3 Nf6 4. Bg5 Bb4 5. e5 h6 6. Bd2 Bxc3+"] = "Bxc3";
    book["1. e4 e6 2. d4 d5 3. Nc3 Nf6 4. Bg5 Bb4 5. e5 Bxc3+"] = "bxc3";

    book["1. e4 e6 2. d4 d5 3. Nc3 Nf6 4. Bg5 h6"] = "Bxf6";
    book["1. e4 e6 2. d4 d5 3. Nc3 Nf6 4. Bg5 h6 5. Bxf6 Qxf6"] = "exd5";
    book["1. e4 e6 2. d4 d5 3. Nc3 Nf6 4. Bg5 h6 5. Bxf6 Qxf6 6. exd5 Bb4"] = "Bb5+";
    book["1. e4 e6 2. d4 d5 3. Nc3 Nf6 4. Bg5 h6 5. Bxf6 Qxf6 6. exd5 Bb4 7. Bb5+ Bd7"] = "Bxd7";
    book["1. e4 e6 2. d4 d5 3. Nc3 Nf6 4. Bg5 h6 5. Bxf6 Qxf6 6. exd5 Bb4 7. Bb5+ Bd7 8. Bxd7+ Nxd7"] = "dxe6";
    book["1. e4 e6 2. d4 d5 3. Nc3 Nf6 4. Bg5 h6 5. Bxf6 Qxf6 6. exd5 Bb4 7. Bb5+ Bd7 8. Bxd7+ Nxd7 9. dxe6 fxe6"] = "Nf3";

    book["1. e4 e6 2. d4 d5 3. Nc3 Nf6 4. Bg5 h6 5. Bxf6 Qxf6 6. exd5 Bb4 7. Bb5+ c6"] = "dxc6";
    book["1. e4 e6 2. d4 d5 3. Nc3 Nf6 4. Bg5 h6 5. Bxf6 Qxf6 6. exd5 Bb4 7. Bb5+ c6 8. dxc6 bxc6"] = "Be2";
    book["1. e4 e6 2. d4 d5 3. Nc3 Nf6 4. Bg5 h6 5. Bxf6 Qxf6 6. exd5 Bb4 7. Bb5+ c6 8. dxc6 Nxc6"] = "Nf3";

    book["1. e4 e6 2. d4 d5 3. Nc3 dxe4"] = "Nxe4";
    book["1. e4 e6 2. d4 d5 3. Nc3 dxe4 4. Nxe4 Nf6"] = "Nxf6+";
    book["1. e4 e6 2. d4 d5 3. Nc3 dxe4 4. Nxe4 Nf6 5. Nxf6+ Qxf6"] = "Nf3";
    book["1. e4 e6 2. d4 d5 3. Nc3 dxe4 4. Nxe4 Nf6 5. Nxf6+ Qxf6 6. Nf3 h6"] = "Bd3";


    // Caro-Kann Defense 
    book["1. e4 c6"] = "d4";
    book["1. e4 c6 2. d4 d5"] = "Nc3";
    book["1. e4 c6 2. d4 d5 3. Nc3 dxe4"] = "Nxe4";
    book["1. e4 c6 2. d4 d5 3. Nc3 Nf6"] = "e5";
    book["1. e4 c6 2. d4 d5 3. Nc3 g6"] = "Nf3";

    book["1. e4 c6 2. d4 d5 3. Nc3 dxe4 4. Nxe4 Nf6"] = "Nxf6+";
    book["1. e4 c6 2. d4 d5 3. Nc3 dxe4 4. Nxe4 Nf6 5. Nxf6+ gxf6"] = "Nf3";
    book["1. e4 c6 2. d4 d5 3. Nc3 dxe4 4. Nxe4 Nf6 5. Nxf6+ gxf6 6. Nf3 Bg4"] = "Be2";
    book["1. e4 c6 2. d4 d5 3. Nc3 dxe4 4. Nxe4 Nf6 5. Nxf6+ gxf6 6. Nf3 Bg4 7. Be2 Qc7"] = "Be3";
    book["1. e4 c6 2. d4 d5 3. Nc3 dxe4 4. Nxe4 Nf6 5. Nxf6+ exf6"] = "c3";

    book["1. e4 c6 2. d4 d5 3. Nc3 g6 4. Nf3 Bg7"] = "h3";
    book["1. e4 c6 2. d4 d5 3. Nc3 g6 4. Nf3 Bg4"] = "Be2";
    book["1. e4 c6 2. d4 d5 3. Nc3 g6 4. Nf3 dxc4"] = "Nxe4";
    book["1. e4 c6 2. d4 d5 3. Nc3 g6 4. Nf3 e6"] = "Bg5";

    book["1. e4 c6 2. d4 d6"] = "Nc3";
    book["1. e4 c6 2. d4 d6 3. Nc3 Nf6"] = "f4";
    book["1. e4 c6 2. d4 d6 3. Nc3 g6"] = "Be3";
    book["1. e4 c6 2. d4 d6 3. Nc3 Qc7"] = "f4";

    


    // Danish Defense (WHITE)
    book["1. e4 d5"] = "exd5";
    book["1. e4 d5 2. exd5 Qxd5"] = "Nc3";
    book["1. e4 d5 2. exd5 Qxd5 3. Nc3 Qa5"] = "Nf3";
    book["1. e4 d5 2. exd5 Qxd5 3. Nc3 Qd6"] = "d4";
    book["1. e4 d5 2. exd5 Qxd5 3. Nc3 Qd8"] = "d4";
    book["1. e4 d5 2. exd5 Qxd5 3. Nc3 Qe5+"] = "Be2";
    book["1. e4 d5 2. exd5 Qxd5 3. Nc3 Qe6+"] = "Be2";

    book["1. e4 d5 2. exd5 Nf6"] = "d4";
    book["1. e4 d5 2. exd5 Nf6 3. d4 Nxd5"] = "Nf3";
    book["1. e4 d5 2. exd5 Nf6 3. d4 Bg4"] = "Bb5+";

    book["1. e4 d5 2. exd5 Qxd5 3. Nc3 Qa5 4. Nf3 Nf6"] = "d4";
    book["1. e4 d5 2. exd5 Qxd5 3. Nc3 Qa5 4. Nf3 Bg4"] = "Be2";
    book["1. e4 d5 2. exd5 Qxd5 3. Nc3 Qa5 4. Nf3 c6"] = "d4";
    book["1. e4 d5 2. exd5 Qxd5 3. Nc3 Qa5 4. Nf3 c6 5. d4 Nf6"] = "Bc4";
    book["1. e4 d5 2. exd5 Qxd5 3. Nc3 Qa5 4. Nf3 Bf5"] = "Bc4";

    book["1. e4 d5 2. exd5 Qxd5 3. Nc3 Qd8 4. d4 Nf6"] = "Nf3";
    book["1. e4 d5 2. exd5 Qxd5 3. Nc3 Qd8 4. d4 c6"] = "Bc4";
    book["1. e4 d5 2. exd5 Qxd5 3. Nc3 Qd8 4. d4 g6"] = "Nf3";
    book["1. e4 d5 2. exd5 Qxd5 3. Nc3 Qd8 4. d4 e6"] = "Nf3";
    book["1. e4 d5 2. exd5 Qxd5 3. Nc3 Qd8 4. d4 Bf5"] = "Nf3";

    book["1. e4 d5 2. exd5 Qxd5 3. Nc3 Qe6+ 4. Be2 Qg6"] = "Nf3";
    book["1. e4 d5 2. exd5 Qxd5 3. Nc3 Qe6+ 4. Be2 Nf6"] = "Nf3";
    book["1. e4 d5 2. exd5 Qxd5 3. Nc3 Qe6+ 4. Be2 Nc6"] = "d4";
    book["1. e4 d5 2. exd5 Qxd5 3. Nc3 Qe6+ 4. Be2 Qc6"] = "Nf3";

    book["1. e4 d5 2. exd5 c6"] = "dxc6";
    book["1. e4 d5 2. exd5 c6 3. dxc6 Nxc6"] = "Nf3";
    book["1. e4 d5 2. exd5 c6 3. dxc6 Nxc6 4. Nf3 e5"] = "Nc3";
    book["1. e4 d5 2. exd5 c6 3. dxc6 Nxc6 4. Nf3 Bg4"] = "Be2";
    book["1. e4 d5 2. exd5 c6 3. dxc6 Nxc6 4. Nf3 Nf6"] = "Bb5";


    // Sicilian Defense (WHITE)
    book["1. e4 c5"] = "Nf3";
    book["1. e4 c5 2. Nf3 d6"] = "d4";
    book["1. e4 c5 2. Nf3 Nc6"] = "d4";
    book["1. e4 c5 2. Nf3 e6"] = "d4";
    book["1. e4 c5 2. Nf3 g6"] = "d4";
    book["1. e4 c5 2. Nf3 a6"] = "c3";
    book["1. e4 c5 2. Nf3 Nf6"] = "e5";

    book["1. e4 c5 2. Nf3 e6 3. d4 cxd4"] = "Nxd4";
    book["1. e4 c5 2. Nf3 e6 3. d4 cxd4 4. Nxd4 a6"] = "Bd3";
    book["1. e4 c5 2. Nf3 e6 3. d4 cxd4 4. Nxd4 Nf6"] = "Nc3";
    book["1. e4 c5 2. Nf3 e6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 d6"] = "Be2";
    book["1. e4 c5 2. Nf3 e6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 Nc6"] = "Ndb5";
    book["1. e4 c5 2. Nf3 e6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 Nc6 6. Ndb5 d6"] = "Bf4";
    book["1. e4 c5 2. Nf3 e6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 Nc6 6. Ndb5 d6 7. Bf4 e5"] = "Bg5";
    book["1. e4 c5 2. Nf3 e6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 Nc6 6. Ndb5 d6 7. Bf4 e5 8. Bg5 a6"] = "Na3";

    book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4"] = "Nxd4";
    book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 Nf6"] = "Nc3";
    book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 g6"] = "Nc3";
    book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 e5"] = "Nb5";
    book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 e6"] = "Nc3";
    book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 Qc7"] = "Nc3";
    book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 Qb6"] = "Nb3";
    book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 d6"] = "Nc3";
    book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 a6"] = "Nc3";

    book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 Nxd4"] = "Qxd4";
    book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 Nxd4 5. Qxd4 d6"] = "Nc3";
    book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 Nxd4 5. Qxd4 e6"] = "Nc3";

    book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 e6"] = "Ndb5";
    book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 e6 6. Ndb5 d6"] = "Bf4";
    book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 e6 6. Ndb5 Bb4"] = "a3";

    book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 e5 5. Nb5 d6"] = "N1c3";
    book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 e5 5. Nb5 a6"] = "Nd6+";
    book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 e5 5. Nb5 Nf6"] = "N1c3";
    book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 e5 5. Nb5 Qa5+"] = "N1c3";

    book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 e5 5. Nb5 a6 6. Nd6+ Bxd6"] = "Qxd6";
    book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 e5 5. Nb5 a6 6. Nd6+ Bxd6 7. Qxd6 Qf6"] = "Qxf6";
    book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 e5 5. Nb5 a6 6. Nd6+ Bxd6 7. Qxd6 Qe7"] = "Qd1";
    book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 e5 5. Nb5 a6 6. Nd6+ Bxd6 7. Qxd6 f5"] = "Nc3";
    book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 e5 5. Nb5 a6 6. Nd6+ Bxd6 7. Qxd6 Nf6"] = "Nc3";
    book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 e5 5. Nb5 a6 6. Nd6+ Bxd6 7. Qxd6 Nf6 8. Nc3 Qe7"] = "Qxe7+";
    book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 e5 5. Nb5 a6 6. Nd6+ Bxd6 7. Qxd6 Nf6 8. Nc3 h6"] = "Be3";
    book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 e5 5. Nb5 a6 6. Nd6+ Bxd6 7. Qxd6 Nf6 8. Nc3 Qb6"] = "Bd2";

    book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 e5 5. Nb5 a6 6. Nd6+ Bxd6 7. Qxd6 Nf6 8. Nc3 b5"] = "Bg5";
    book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 e5 5. Nb5 a6 6. Nd6+ Bxd6 7. Qxd6 Nf6 8. Nc3 b5 9. Bg5 Qe7"] = "Qd2";
    book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 e5 5. Nb5 a6 6. Nd6+ Bxd6 7. Qxd6 Nf6 8. Nc3 b5 9. Bg5 h6"] = "Nd5";
    book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 e5 5. Nb5 a6 6. Nd6+ Bxd6 7. Qxd6 Nf6 8. Nc3 b5 9. Bg5 Ra7"] = "0-0-0";

    book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 e5 5. Nb5 Qa5+ 6. N1c3 a6"] = "Nd6+";
    book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 e5 5. Nb5 Qa5+ 6. N1c3 a6 7. Nd6+ Bxd6"] = "Qxd6";

    book["1. e4 c5 2. Nf3 d6 3. d4 cxd4"] = "Nxd4";
    book["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 Nf6"] = "Nc3";
    book["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 Nc6"] = "Nc3";
    book["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 a6"] = "Nc3";
    book["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 g6"] = "Nc3";
    book["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 e5"] = "Nb3";
    book["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 e6"] = "Nc3";
    book["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 Bd7"] = "Nc3";

    book["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 Nc6 5. Nc3 g6"] = "Be3";
    book["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 Nc6 5. Nc3 Nf6"] = "Bg5";

    book["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 Nc6 5. Nc3 Nf6 6. Bg5 e6"] = "Qd2";
    book["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 Nc6 5. Nc3 Nf6 6. Bg5 Bd7"] = "Qd2";
    book["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 Nc6 5. Nc3 Nf6 6. Bg5 Qb6"] = "Nb3";
    book["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 Nc6 5. Nc3 Nf6 6. Bg5 a6"] = "Qd2";

    book["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 e6 5. Nc3 Qc7"] = "Be3";
    book["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 e6 5. Nc3 a6"] = "Be2";
    book["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 e6 5. Nc3 d6"] = "Be3";
    book["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 e6 5. Nc3 Nf6"] = "Ndb5";
    book["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 e6 5. Nc3 Bb4"] = "Ndb5";
    book["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 e6 5. Nc3 Bc5"] = "Nb3";

    book["1. e4 c5 2. Nf3 d6 3. d4 e6"] = "dxc5";
    book["1. e4 c5 2. Nf3 d6 3. d4 e6 4. dxc5 Qa5+"] = "Nc3";

    book["1. e4 c5 2. Nf3 Nc6 3. d4 d5"] = "exd5";
    book["1. e4 c5 2. Nf3 Nc6 3. d4 d5 4. exd5 Qxd5"] = "Nc3";
    book["1. e4 c5 2. Nf3 Nc6 3. d4 d5 4. exd5 Nxd4"] = "Nxd4";
    book["1. e4 c5 2. Nf3 Nc6 3. d4 d5 4. exd5 Nxd4 5. Nxd4 cxd4"] = "Qxd4";

    // Sicilian, accelerated fianchetto (B34)
    book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 g6 5. Nc3 Bg7"] = "Be3";
    book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 g6 5. Nc3 Bg7 6. Be3 Nf6"] = "Bc4";
    book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 g6 5. Nc3 Bg7 6. Be3 d6"] = "Qd2";
    book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 g6 5. Nc3 Bg7 6. Be3 a6"] = "Qd2";
    book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 g6 5. Nc3 Bg7 6. Be3 e6"] = "Ndb5";



    // Spanish Opening (XX) -- WHITE
    book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6"] = "0-0";
    book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4"] = "d4";
    book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. d4 Nd6"] = "Bxc6";
    book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. d4 Be7"] = "Qe2";
    book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. d4 a6"] = "Ba4";
    book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. d4 exd4"] = "Re1";
    book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. d4 exd4 6. Re1 d5"] = "Nxd4";
    book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. d4 exd4 6. Re1 f5"] = "Nxd4";
    book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. d4 exd4 6. Re1 Be7"] = "Rxe4";
    book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. d4 exd4 6. Re1 Qe7 7. Nxd4 Nxd4"] = "Qxd4";


    book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6"] = "Ba4";
    book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nf6"] = "0-0";
    book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 d6"] = "c3";
    book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 b5"] = "Bb3";
    book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Bc5"] = "0-0";

    book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 d6 5. c3 Bd7"] = "d4";
    book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 d6 5. c3 f5"] = "exf5";
    book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 d6 5. c3 Nf6"] = "d4";
    book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 d6 5. c3 b5"] = "Bc2";
    book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 d6 5. c3 b5 6. Bc2 Bg4"] = "h3";
    book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 d6 5. c3 b5 6. Bc2 h6"] = "d4";

    book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nf6 5. 0-0 Be7"] = "Re1";
    book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nf6 5. 0-0 b5"] = "Bb3";
    book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nf6 5. 0-0 Nxe4"] = "d4";
    book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nf6 5. 0-0 d6"] = "Re1";
    book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nf6 5. 0-0 Bc5"] = "c3";

    book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nf6 5. 0-0 b5 6. Bb3 Be7"] = "Re1";
    book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nf6 5. 0-0 b5 6. Bb3 Bc5"] = "c3";
    book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nf6 5. 0-0 b5 6. Bb3 Bb7"] = "d3";
    book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nf6 5. 0-0 b5 6. Bb3 d6"] = "c3";
    book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nf6 5. 0-0 b5 6. Bb3 Nxe4"] = "d4";

    book["1. e4 e5 2. Nf3 Nc6 3. Bb5 d6"] = "d4";
    book["1. e4 e5 2. Nf3 Nc6 3. Bb5 d6 4. d4 Bd7"] = "Nc3";
    book["1. e4 e5 2. Nf3 Nc6 3. Bb5 d6 4. d4 exd4"] = "Nxd4";
    book["1. e4 e5 2. Nf3 Nc6 3. Bb5 d6 4. d4 a6"] = "Bxc6+";
    book["1. e4 e5 2. Nf3 Nc6 3. Bb5 d6 4. d4 a6 5. Bxc6+ bxc6"] = "dxe5";

    book["1. e4 e5 2. Nf3 Nc6 3. Bb5 d6 4. d4 Bd7 5. Nc3 Nf6"] = "0-0";
    book["1. e4 e5 2. Nf3 Nc6 3. Bb5 d6 4. d4 Bd7 5. Nc3 exd4"] = "Nxd4";
    book["1. e4 e5 2. Nf3 Nc6 3. Bb5 d6 4. d4 Bd7 5. Nc3 Nge7"] = "d5";
    book["1. e4 e5 2. Nf3 Nc6 3. Bb5 d6 4. d4 Bd7 5. Nc3 a6"] = "Bxc6";
    book["1. e4 e5 2. Nf3 Nc6 3. Bb5 d6 4. d4 Bd7 5. Nc3 a6 6. Bxc6 Bxc6"] = "dxe5";
    book["1. e4 e5 2. Nf3 Nc6 3. Bb5 d6 4. d4 Bd7 5. Nc3 a6 6. Bxc6 Bxc6 7. dxe5 dxe5"] = "Qxd8";
    book["1. e4 e5 2. Nf3 Nc6 3. Bb5 d6 4. d4 Bd7 5. Nc3 a6 6. Bxc6 Bxc6 7. dxe5 dxe5 8. Qxd8 Rxd8"] ="Nxe5";
    book["1. e4 e5 2. Nf3 Nc6 3. Bb5 d6 4. d4 Bd7 5. Nc3 Nxd4"] = "Nxd4";
    book["1. e4 e5 2. Nf3 Nc6 3. Bb5 d6 4. d4 Bd7 5. Nc3 Nxd4 6. Nxd4 exd4"] = "Qxd4";
    book["1. e4 e5 2. Nf3 Nc6 3. Bb5 d6 4. d4 Bd7 5. Nc3 Nxd4 6. Nxd4 exd4 7. Qxd4 Bxb5"] = "Nxb5";
    book["1. e4 e5 2. Nf3 Nc6 3. Bb5 d6 4. d4 Bd7 5. Nc3 Nxd4 6. Nxd4 exd4 7. Qxd4 Nf6"] = "Bxd7+";
    book["1. e4 e5 2. Nf3 Nc6 3. Bb5 d6 4. d4 Bd7 5. Nc3 Nxd4 6. Nxd4 exd4 7. Qxd4 Nf6 8. Bxd7+ Qxd7"] = "Bg5";
    book["1. e4 e5 2. Nf3 Nc6 3. Bb5 d6 4. d4 Bd7 5. Nc3 Nxd4 6. Nxd4 exd4 7. Qxd4 Ne7"] = "Bxd7+";
    book["1. e4 e5 2. Nf3 Nc6 3. Bb5 d6 4. d4 Bd7 5. Nc3 Nxd4 6. Nxd4 exd4 7. Qxd4 Ne7 8. Bxd7+ Qxd7"] = "Be3";

    book["1. e4 e5 2. Nf3 Nc6 3. Bb5 d6 4. d4 exd4 5. Nxd4 Bd7"] = "Nc3";
    book["1. e4 e5 2. Nf3 Nc6 3. Bb5 d6 4. d4 exd4 5. Nxd4 Bd7 6. Nc3 Nf6"] = "0-0";
    book["1. e4 e5 2. Nf3 Nc6 3. Bb5 d6 4. d4 exd4 5. Nxd4 Bd7 6. Nc3 Nf6 7. 0-0 Be7"] = "Re1";



    // Rare openings (WHITE)
    book["1. e4 d6"] = "d4";
    book["1. e4 d6 2. d4 c6"] = "Nc3";

    book["1. e4 d6 2. d4 Nf6"] = "Nc3";
    book["1. e4 d6 2. d4 Nf6 3. Nc3 g6"] = "Nf3";
    book["1. e4 d6 2. d4 Nf6 3. Nc3 e5"] = "Nf3";

    book["1. e4 a6"] = "d4";
    book["1. e4 a6 2. d4 h6"] = "Nf3";






    ////////////////
    // BLACK
    //
    // OPENINGS
    ////////////////


    // Initial openings
    book["1. e4"] = "e5";
    book["1. d4"] = "Nf6";
    book["1. Nf3"] = "d5";
    book["1. c4"] = "e5";
    book["1. c4"] = "e5";



    // Open openings
    book["1. e4 e5 2. Nf3"] = "Nc6";
    book["1. e4 e5 2. Bc4"] = "Nf6";
    book["1. e4 e5 2. f4"] = "exf4";
    book["1. e4 e5 2. Nc3"] = "Nf6";
    book["1. e4 e5 2. d3"] = "Nc6";



    // Nimzovich-Larsen attack (A01) -- BLACK
    book["1. b3"] = "e5";
    book["1. b3 e5 2. Bb2"] = "Nc6";



    // Bird's opening (A02) -- BLACK
    book["1. f4"] = "d5";

    book["1. f4 d5 2. e3"] = "Nf6";
    book["1. f4 d5 2. Nf3"] = "Nf6";
    book["1. f4 d5 2. b3"] = "Nf6";
    book["1. f4 d5 2. g3"] = "Nf6";

    book["1. f4 d5 2. Nf3 Nf6 3. e3"] = "g6";
    book["1. f4 d5 2. Nf3 Nf6 3. e3 g6 4. b3"] = "Bg7";
    book["1. f4 d5 2. Nf3 Nf6 3. e3 g6 4. b3 Bg7 5. Bb2"] = "0-0";
    book["1. f4 d5 2. Nf3 Nf6 3. e3 g6 4. d4"] = "Bg7";
    book["1. f4 d5 2. Nf3 Nf6 3. e3 g6 4. d4 Bg7 5. Bd3"] = "0-0";

    book["1. f4 d5 2. Nf3 Nf6 3. g3"] = "Bf5";



    // English opening (A10) -- BLACK
    book["1. c4 e5 2. g3"] = "Nf6";
    book["1. c4 e5 2. g3 Nf6 3. Bg2"] = "d5";
    book["1. c4 e5 2. g3 Nf6 3. Bg2 d5 4. cxd5"] = "Nxd5";
    book["1. c4 e5 2. g3 Nf6 3. Bg2 d5 4. d3"] = "d4";

    book["1. c4 e5 2. Nc3"] = "Nf6";
    book["1. c4 e5 2. Nc3 Nf6 3. Nf3"] = "Nc6";
    book["1. c4 e5 2. Nc3 Nf6 3. g3"] = "Bb4";
    book["1. c4 e5 2. Nc3 Nf6 3. g3 Bb4 4. Bg2"] = "0-0";
    book["1. c4 e5 2. Nc3 Nf6 3. d3"] = "Nc6";
    book["1. c4 e5 2. Nc3 Nf6 3. e4"] = "Bc5";
    book["1. c4 e5 2. Nc3 Nf6 3. e3"] = "Bb4";

    book["1. c4 e5 2. Nc3 Nf6 3. d3 Nc6 4. g3"] = "Bb4";
    book["1. c4 e5 2. Nc3 Nf6 3. d3 Nc6 4. Nf3"] = "Bb4";
    book["1. c4 e5 2. Nc3 Nf6 3. d3 Nc6 4. e4"] = "Bc5";

    book["1. c4 e5 2. b3"] = "Nf6";
    book["1. c4 e5 2. b3 Nf6 3. Bb2"] = "Nc6";


    // Indian opening (C21)
    book["1. e4 e5 2. d3 Nc6 3. Nf3"] = "Nf6";
    book["1. e4 e5 2. d3 Nc6 3. Nc3"] = "Nf6";
    book["1. e4 e5 2. d3 Nc6 3. g3"] = "Nf6";
    book["1. e4 e5 2. d3 Nc6 3. g3 Nf6 4. Bg2"] = "Bc5";
    book["1. e4 e5 2. d3 Nc6 3. c3"] = "Nf6";


    // Centre game (C21)
    book["1. e4 e5 2. d4"] = "exd4";
    book["1. e4 e5 2. d4 exd4 3. Qxd4"] = "Nc6";
    book["1. e4 e5 2. d4 exd4 3. c3"] = "dxc3";
    book["1. e4 e5 2. d4 exd4 3. c3 dxc3 4. Bc4"] = "cxb2";
    book["1. e4 e5 2. d4 exd4 3. c3 dxc3 4. Bc4 cxb2 5. Bxb2"] = "d5";
    book["1. e4 e5 2. d4 exd4 3. c3 dxc3 4. Nxc3"] = "Nc6";
    book["1. e4 e5 2. d4 exd4 3. Nf3"] = "Nc6";
    book["1. e4 e5 2. d4 exd4 3. Bc4"] = "Nf6";



    // XXX
    book["1. e4 e5 2. Nf3 Nc6 3. Nc3"] = "Nf6";
    book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. Bc4"] = "Nxe4";
    book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. Bc4 Nxe4 5. Nxe4"] = "d5";
    book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. Bc4 Nxe4 5. Nxe4 d5 6. Bxd5"] = "Qxd5";
    book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. Bc4 Nxe4 5. Nxe4 d5 6. Bxd5 Qxd5 7. Nc3"] = "Qd6";
    book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. Bc4 Nxe4 5. Nxe4 d5 6. Bxd5 Qxd5 7. Nc3 d6 8. d3"] = "Bg4";
    book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. Bc4 Nxe4 5. Nxe4 d5 6. Bd3"] = "dxe4";
    book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. Bc4 Nxe4 5. Nxe4 d5 6. Bd3 dxe4 7. Bxe4"] = "Bd6";

    book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. Bc4 Nxe4 5. Bxf7+"] = "Kxf7";
    book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. Bc4 Nxe4 5. Bxf7+ Kxf7 6. Nxe4"] = "d5";
    book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. Bc4 Nxe4 5. Bxf7+ Kxf7 6. Nxe5+"] = "Nxe5";
    book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. Bc4 Nxe4 5. Bxf7+ Kxf7 6. Nxe5+ Nxe5 7. Nxe4"] = "d5";
    book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. Bc4 Nxe4 5. Bxf7+ Kxf7 6. Nxe5+ Nxe5 7. Qh5+"] = "g6";
    book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. Bc4 Nxe4 5. Bxf7+ Kxf7 6. Nxe5+ Nxe5 7. Qh5+ g6 8. Qxe5"] = "Nxc3";

    book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. d4"] = "exd4";
    book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. d4 exd4 5. Nxd4"] = "Bb4";
    book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. d4 exd4 5. Nxd4 Bb4 6. Nxc6"] = "bxc6";
    book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. d4 exd4 5. Nxd4 Bb4 6. Nxc6 bxc6 7. Bd3"] = "d5";
    book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. d4 exd4 5. Nxd4 Bb4 6. Nxc6 bxc6 7. Bd3 d5 8. exd5"] = "cxd5";
    book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. d4 exd4 5. Nxd4 Bb4 6. Nxc6 bxc6 7. Bd3 d5 8. e5"] = "Ng4";
    book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. d4 exd4 5. Nxd4 Bb4 6. Nxc6 bxc6 7. Bd3 d5 8. 0-0"] = "Bxc3";

    book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Nc3"] = "Nxe4";
    book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Nc3 Nxe4 5. Nxe4"] = "d5";
    book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Nc3 Nxe4 5. Nxe4 d5 6. Bxd5"] = "Qxd5";
    book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Nc3 Nxe4 5. Nxe4 d5 6. Bxd5 Qxd5 7. Nc3"] = "Qd6";
    book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Nc3 Nxe4 5. Nxe4 d5 6. Bxd5 Qxd5 7. Nc3 d6 8. d3"] = "Bg4";
    book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Nc3 Nxe4 5. Nxe4 d5 6. Bd3"] = "dxe4";
    book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Nc3 Nxe4 5. Nxe4 d5 6. Bd3 dxe4 7. Bxe4"] = "Bd6";

    book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Nc3 Nxe4 5. Bxf7+"] = "Kxf7";
    book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Nc3 Nxe4 5. Bxf7+ Kxf7 6. Nxe4"] = "d5";
    book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Nc3 Nxe4 5. Bxf7+ Kxf7 6. Nxe5+"] = "Nxe5";
    book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Nc3 Nxe4 5. Bxf7+ Kxf7 6. Nxe5+ Nxe5 7. Nxe4"] = "d5";
    book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Nc3 Nxe4 5. Bxf7+ Kxf7 6. Nxe5+ Nxe5 7. Qh5+"] = "g6";
    book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Nc3 Nxe4 5. Bxf7+ Kxf7 6. Nxe5+ Nxe5 7. Qh5+ g6 8. Qxe5"] = "Nxc3";

    book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. d3"] = "Bc5";
    book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. d3 Bc5 5. c3"] = "d6";
    book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. d3 Bc5 5. 0-0"] = "d6";
    book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. d3 Bc5 5. Nc3"] = "d6";
    book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. d3 Bc5 5. Bg5"] = "d6";

    book["1. e4 e5 2. Nf3 Nc6 3. b3"] = "Nf6";
    book["1. e4 e5 2. Nf3 Nc6 3. b3 Nf6 4. Bb2"] = "Bc3";
    book["1. e4 e5 2. Nf3 Nc6 3. b3 Nf6 4. Bb2 Bc5 5. h3"] = "Nxe4";
    book["1. e4 e5 2. Nf3 Nc6 3. b3 Nf6 4. Bb2 Bc5 5. Nc3"] = "0-0";
    book["1. e4 e5 2. Nf3 Nc6 3. b3 Nf6 4. Bb2 Bc5 5. Nxe5"] = "Nxe5";
    book["1. e4 e5 2. Nf3 Nc6 3. b3 Nf6 4. Bb2 Bc5 5. Nxe5 Nxe5 6. Bxe5"] = "Qe7";

    book["1. e4 e5 2. Nf3 Nc6 3. Bc4"] = "Nf6";
    book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. c3"] = "Nxe4";

    book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. 0-0"] = "Nxe4";
    book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. 0-0 Nxe4 5. Re1"] = "d5";
    book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. 0-0 Nxe4 5. Nc3"] = "Nxc3";
    book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. 0-0 Nxe4 5. d4"] = "d5";
    book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. 0-0 Nxe4 5. Bb5"] = "Bc5";
    book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. 0-0 Nxe4 5. Bb5 Bc5 6. Qe1"] = "Nf6";
    book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. 0-0 Nxe4 5. Bb5 Bc5 6. Qe1 Nf6 7. Bxc6"] = "dxc6";
    book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. 0-0 Nxe4 5. Bb5 Bc5 6. Qe1 Nf6 7. Bxc6 dxc6 8. Qxe5"] = "Qe7";
    book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. 0-0 Nxe4 5. Bb5 Bc5 6. Qe1 Nf6 7. Bxc6 dxc6 8. d3"] = "0-0";

    book["1. e4 e5 2. Nf3 Nc6 3. d3"] = "Nf6";
    book["1. e4 e5 2. Nf3 Nc6 3. d3 Nf6 4. Be2"] = "d5";
    book["1. e4 e5 2. Nf3 Nc6 3. d3 Nf6 4. g3"] = "Bc5";
    book["1. e4 e5 2. Nf3 Nc6 3. d3 Nf6 4. c3"] = "d5";
    book["1. e4 e5 2. Nf3 Nc6 3. d3 Nf6 4. Nc3"] = "Bb4";
    book["1. e4 e5 2. Nf3 Nc6 3. d3 Nf6 4. Bg5"] = "Be7";
    book["1. e4 e5 2. Nf3 Nc6 3. d3 Nf6 4. Nbd2"] = "Bc5";
    book["1. e4 e5 2. Nf3 Nc6 3. d3 Nf6 4. c4"] = "Bc5";
    book["1. e4 e5 2. Nf3 Nc6 3. d3 Nf6 4. Be3"] = "d5";

    book["1. e4 e5 2. Nf3 Nc6 3. b3"] = "Nf6";
    book["1. e4 e5 2. Nf3 Nc6 3. b3 Nf6 4. Nc3"] = "Bc5";
    book["1. e4 e5 2. Nf3 Nc6 3. b3 Nf6 4. d3"] = "Bc5";
    book["1. e4 e5 2. Nf3 Nc6 3. b3 Nf6 4. Bb2"] = "Bc5";

    book["1. e4 e5 2. Nc3 Nf6 3. Bc4"] = "Bc5";
    book["1. e4 e5 2. Nc3 Nf6 3. Bc4 Bc5 4. d3"] = "d6";
    book["1. e4 e5 2. Nc3 Nf6 3. Bc4 Bc5 4. Nf3"] = "d6";

    book["1. e4 e5 2. Nc3 Nf6 3. Nf3"] = "Nc6";



    // Scotch (BLACK)
    book["1. e4 e5 2. Nf3 Nc6 3. d4"] = "exd4";
    book["1. e4 e5 2. Nf3 Nc6 3. d4 exd4 4. Nxd4"] = "Nf6";
    book["1. e4 e5 2. Nf3 Nc6 3. d4 exd4 4. Nxd4 Nf6 5. Nxc6"] = "bxc6";
    book["1. e4 e5 2. Nf3 Nc6 3. d4 exd4 4. Nxd4 Nf6 5. Nc3"] = "Bb4";
    book["1. e4 e5 2. Nf3 Nc6 3. d4 exd4 4. Nxd4 Nf6 5. Bg5"] = "h6";

    book["1. e4 e5 2. Nf3 Nc6 3. d4 exd4 4. Bc4"] = "Nf6";
    book["1. e4 e5 2. Nf3 Nc6 3. d4 exd4 4. c3"] = "dxc3";
    book["1. e4 e5 2. Nf3 Nc6 3. d4 exd4 4. c3 dxc3 5. Bc4"] = "cxb2";
    book["1. e4 e5 2. Nf3 Nc6 3. d4 exd4 4. c3 dxc3 5. Bc4 cxb2 6. Bxb2"] = "Bb4+";
    book["1. e4 e5 2. Nf3 Nc6 3. d4 exd4 4. c3 dxc3 5. Nxc3"] = "Bb4";




    // King's Gambit
    book["1. e4 e5 2. f4 exf4 3. Nf3"] = "g5";
    book["1. e4 e5 2. f4 exf4 3. Nf3 g5 4. h4"] = "g4";
    book["1. e4 e5 2. f4 exf4 3. Nf3 g5 4. Bc4"] = "g4";
    book["1. e4 e5 2. f4 exf4 3. Nf3 g5 4. d4"] = "g4";
    book["1. e4 e5 2. f4 exf4 3. Nf3 g5 4. Nc3"] = "g4";
    book["1. e4 e5 2. f4 exf4 3. Nf3 g5 4. h3"] = "Bg7";

    book["1. e4 e5 2. f4 exf4 3. Nf3 g5 4. h4 g4 5. Ne5"] = "d6";
    book["1. e4 e5 2. f4 exf4 3. Nf3 g5 4. h4 g4 5. Ng5"] = "h6";

    book["1. e4 e5 2. f4 exf4 3. Nf3 g5 4. h4 g4 5. Ne5 d6 6. Nxg4"] = "Be7";
    book["1. e4 e5 2. f4 exf4 3. Nf3 g5 4. h4 g4 5. Ne5 d6 6. Nxg4 Be7 7. d4"] = "Bxh4+";
    book["1. e4 e5 2. f4 exf4 3. Nf3 g5 4. h4 g4 5. Ne5 d6 6. Nxg4 Be7 7. Bc4"] = "Bxh4+";
    book["1. e4 e5 2. f4 exf4 3. Nf3 g5 4. h4 g4 5. Ne5 d6 6. Nxg4 Be7 7. Qf3"] = "Bxh4+";

    book["1. e4 e5 2. f4 exf4 3. Nf3 g5 4. Bc4 g4 5. 0-0"] = "gxf3";
    book["1. e4 e5 2. f4 exf4 3. Nf3 g5 4. Bc4 g4 5. 0-0 gxf3 6. Qxf3"] = "Qf6";
    book["1. e4 e5 2. f4 exf4 3. Nf3 g5 4. Bc4 g4 5. 0-0 gxf3 6. Qxf3 Qf6 7. e5"] = "Qxe5";
    book["1. e4 e5 2. f4 exf4 3. Nf3 g5 4. Bc4 g4 5. 0-0 gxf3 6. Qxf3 Qf6 7. e5 Qxe5 8. d3"] = "Bh6";
    book["1. e4 e5 2. f4 exf4 3. Nf3 g5 4. Bc4 g4 5. 0-0 gxf3 6. Qxf3 Qf6 7. d3"] = "Nc6";

    book["1. e4 e5 2. f4 exf4 3. Nf3 g5 4. h3 Bg7 5. d4"] = "h6";
    book["1. e4 e5 2. f4 exf4 3. Nf3 g5 4. h3 Bg7 5. Bc4"] = "h6";


    // Fried Liver Attack (C58)
    book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Ng5"] = "d5";
    book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Ng5 d5 5. Nxf7"] = "Kxf7";
    book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Ng5 d5 5. Nxf7 Kxf7 6. exd5"] = "b5";

    book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Ng5 d5 5. exd5"] = "Na5";
    book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Ng5 d5 5. exd5 Na5 6. Bb5+"] = "c6";
    book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Ng5 d5 5. exd5 Na5 6. Bb5+ c6 7. dxc6"] = "bxc6";
    book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Ng5 d5 5. exd5 Na5 6. Bb5+ c6 7. dxc6 bxc6 8. Bd3"] = "Nd5";
    book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Ng5 d5 5. exd5 Na5 6. Bb5+ c6 7. dxc6 bxc6 8. Be2"] = "h6";
    book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Ng5 d5 5. exd5 Na5 6. Bb5+ c6 7. dxc6 bxc6 8. Ba4"] = "h6";

    book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Ng5 d5 5. exd5 Na5 6. Bb5+ c6 7. dxc6 bxc6 8. Bd3 Nd5 9. Nf3"] = "Bd6";
    book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Ng5 d5 5. exd5 Na5 6. Bb5+ c6 7. dxc6 bxc6 8. Bd3 Nd5 9. h4"] = "Nf4";
    book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Ng5 d5 5. exd5 Na5 6. Bb5+ c6 7. dxc6 bxc6 8. Be2 h6 9. Nf3"] = "e4";
    book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Ng5 d5 5. exd5 Na5 6. Bb5+ c6 7. dxc6 bxc6 8. Ba4 h6 9. Nf3"] = "e4";

    book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Ng5 d5 5. exd5 Na5 6. Bb5+ c6 7. dxc6 bxc6 8. Be2 h6 9. Nf3 e4 10. 0-0"] = "exf3";
    book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Ng5 d5 5. exd5 Na5 6. Bb5+ c6 7. dxc6 bxc6 8. Be2 h6 9. Nf3 e4 10. 0-0 exf3 11. Bxf3"] = "Bd6";
    book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Ng5 d5 5. exd5 Na5 6. Bb5+ c6 7. dxc6 bxc6 8. Be2 h6 9. Nf3 e4 10. 0-0 exf3 11. Bxf3 Bd6 12. Re1+"] = "Be6";



    // Spanish Defense (BLACK)
    book["1. e4 e5 2. Nf3 Nc6 3. Bb5"]= "Nf6";
    book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0"] = "Nxe4";
    book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. d4"] = "Nd6";
    book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. d4 Nd6 6. Bxc6"] = "dxc6";
    book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. d4 Nd6 6. Bxc6 dxc6 7. dxe5"] = "Nf5";

    book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. d4 Nd6 6. Bxc6 dxc6 7. dxe5 Nf5 8. Qxd8+"] = "Kxd8";
    book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. d4 Nd6 6. Bxc6 dxc6 7. dxe5 Nf5 8. Qxd8+ Kxd8 9. Nc3"] = "Ke8";
    book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. d4 Nd6 6. Bxc6 dxc6 7. dxe5 Nf5 8. Qxd8+ Kxd8 9. Rd1+"] = "Ke8";


    // C67 Ruy Lopez, Berlin defence, open variation -- BLACK
    book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. Bxc6"] = "dxc6";
    book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. Bxc6 dxc6 6. Re1"] = "Nd6";
    book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. Bxc6 dxc6 6. Nxe5"] = "Nd6";
    book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. Bxc6 dxc6 6. Qe2"] = "Ng5";
    book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. Bxc6 dxc6 6. d3"] = "Nd6";


    // C67 Ruy Lopez, Berlin defence, open variation -- BLACK
    book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. Bxc6 dxc6 6. Nxe5 Nd6 7. d3"] = "Be7";
    book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. Bxc6 dxc6 6. Nxe5 Nd6 7. d4"] = "Be7";


    book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. Re1"] = "Nd6";
    book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. Re1 Nd6 6. Nxe5"] = "Be7";
    book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. Re1 Nd6 6. Nxe5 Be7 7. Bf1"] = "Nxe5";
    book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. Re1 Nd6 6. Nxe5 Be7 7. Bd3"] = "Nxe5";
    book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. Re1 Nd6 6. Nxe5 Be7 7. Ba4"] = "Nxe5";
    book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. Re1 Nd6 6. Nxe5 Be7 7. Nxc6"] = "dxc6";
    book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. Re1 Nd6 6. Nxe5 Be7 7. Bxc6"] = "dxc6";

    book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. d3"] = "Bc5";
    book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. d3 Bc5 5. c3"] = "0-0";
    book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. d3 Bc5 5. Bxc6"] = "dxc6";
    book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. d3 Bc5 5. 0-0"] = "d6";
    book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. d3 Bc5 5. Nc3"] = "d6";

    book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. Nc3"] = "Bb4";
    book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. Nc3 Bb4 5. 0-0"] = "0-0";
    book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. Nc3 Bb4 5. d3"] = "d6";
    book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. Nc3 Bb4 5. Bxc6"] = "dxc6";
    book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. Nc3 Bb4 5. a3"] = "Bxc3";
    book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. Nc3 Bb4 5. Nd5"] = "Nxd5";
    book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. Nc3 Bb4 5. Qe2"] = "0-0";

    // C49 Four knights, Nimzovich (Paulsen) variation -- BLACK
    book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. Nc3 Bb4 5. 0-0 0-0 6. d3"] = "d6";
    book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. Nc3 Bb4 5. 0-0 0-0 6. Bxc6"] = "dxc6";
    book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. Nc3 Bb4 5. 0-0 0-0 6. Bxc6 dxc6 7. d3"] = "Re8";
    book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. Nc3 Bb4 5. 0-0 0-0 6. Bxc6 dxc6 7. Nxe5"] = "Re8";

    book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. Nc3 Bb4 5. 0-0 0-0 6. d3 d6 7. Bg5"] = "Bxc3";
    book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. Nc3 Bb4 5. 0-0 0-0 6. d3 d6 7. Bg5 Bxc3 8. bxc3"] = "Qe7";
    book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. Nc3 Bb4 5. 0-0 0-0 6. d3 d6 7. Bg5 Bxc3 8. bxc3 Qe7 9. Re1"] = "Nd8";
    book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. Nc3 Bb4 5. 0-0 0-0 6. d3 d6 7. Bg5 Bxc3 8. bxc3 Qe7 9. Bxc6"] = "bxc6";
    book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. Nc3 Bb4 5. 0-0 0-0 6. d3 d6 7. Bg5 Bxc3 8. bxc3 Qe7 9. Bxc6 bxc6 10. Rb1"] = "h6";
    book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. Nc3 Bb4 5. 0-0 0-0 6. d3 d6 7. Bg5 Bxc3 8. bxc3 Qe7 9. Bxc6 bxc6 10. Rb1 h6 11. Be3"] = "Bd7";
    book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. Nc3 Bb4 5. 0-0 0-0 6. d3 d6 7. Bg5 Bxc3 8. bxc3 Qe7 9. Bxc6 bxc6 10. Rb1 h6 11. Be3 Bd7 12. Rb7"] = "Ng4";
    book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. Nc3 Bb4 5. 0-0 0-0 6. d3 d6 7. Bg5 Bxc3 8. bxc3 Qe7 9. Bxc6 bxc6 10. Rb1 h6 11. Be3 Bd7 12. Rb7 Ng4 18. Bxa7"] = "Bc8";

    book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. Bxc6"] = "dxc6";
    book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. Bxc6 dxc6 5. d3"] = "Bd6";
    book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. Bxc6 dxc6 5. Nxe5"] = "Qd4";
    book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. Bxc6 dxc6 5. 0-0"] = "Bd6";
    book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. Bxc6 dxc6 5. Nc3"] = "Bd6";
    book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. Bxc6 dxc6 5. Qe2"] = "Bd6";
    book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. Bxc6 dxc6 5. d4"] = "Bg4";



    // Grünfeld Defense (BLACK)
    book["1. d4 Nf6 2. c4"] = "g6";
    book["1. d4 Nf6 2. c4 g6 3. Nc3"] = "d5";
    book["1. d4 Nf6 2. c4 g6 3. Nc3 d5 4. cxd5"] = "Nxd5";
    book["1. d4 Nf6 2. c4 g6 3. Nc3 d5 4. cxd5 Nxd5 5. e4"] = "Nxc3";
    book["1. d4 Nf6 2. c4 g6 3. Nc3 d5 4. cxd5 Nxd5 5. e4 Nxc3 6. bxc3"] = "Bg7";
    book["1. d4 Nf6 2. c4 g6 3. Nc3 d5 4. cxd5 Nxd5 5. e4 Nxc3 6. bxc3 Bg7 7. Nf3"] = "c5";
    book["1. d4 Nf6 2. c4 g6 3. Nc3 d5 4. cxd5 Nxd5 5. e4 Nxc3 6. bxc3 Bg7 7. Nf3 c5 8. Rb1"] = "0-0";
    book["1. d4 Nf6 2. c4 g6 3. Nc3 d5 4. cxd5 Nxd5 5. e4 Nxc3 6. bxc3 Bg7 7. Nf3 c5 8. Rb1 0-0 9. Be2"] = "Nc6";

    book["1. d4 Nf6 2. c4 g6 3. Nc3 d5 4. cxd5 Nxd5 5. e4 Nxc3 6. bxc3 Bg7 7. Nf3 c5 8. Rb1 0-0 9. Be2 Nc6 10. d5"] = "Ne5";
    book["1. d4 Nf6 2. c4 g6 3. Nc3 d5 4. cxd5 Nxd5 5. e4 Nxc3 6. bxc3 Bg7 7. Nf3 c5 8. Rb1 0-0 9. Be2 Nc6 10. d5 Ne5 11. Nxe5"] = "Bxe5";

    book["1. d4 Nf6 2. c4 g6 3. Nc3 d5 4. e3"] = "Bg7";
    book["1. d4 Nf6 2. c4 g6 3. Nc3 d5 4. e3 Bg7 5. Nf3"] = "0-0";
    book["1. d4 Nf6 2. c4 g6 3. Nc3 d5 4. e3 Bg7 5. Qb3"] = "e6";
    book["1. d4 Nf6 2. c4 g6 3. Nc3 d5 4. e3 Bg7 5. cxd5"] = "Nxd5";
    book["1. d4 Nf6 2. c4 g6 3. Nc3 d5 4. e3 Bg7 5. Bd3"] = "0-0";


    
    // Trompovsky attack (A45)
    book["1. d4 Nf6 2. Bg5"] = "d5";
    book["1. d4 Nf6 2. Bg5 d5 3. Bxf6"] = "exf6";
    book["1. d4 Nf6 2. Bg5 d5 3. e3"] = "c5";
    book["1. d4 Nf6 2. Bg5 d5 3. Nd2"] = "c5";
    book["1. d4 Nf6 2. Bg5 d5 3. Nf3"] = "Ne4";
    book["1. d4 Nf6 2. Bg5 d5 3. Nc3"] = "Nbd7";
    book["1. d4 Nf6 2. Bg5 d5 3. c4"] = "Ne4";


    // D01 Richter-Veresov attack
    book["1. d4 Nf6 2. Bg5 d5 3. Nc3 Nbd7 4. f3"] = "c6";
    book["1. d4 Nf6 2. Bg5 d5 3. Nc3 Nbd7 4. f3 c6 5. e4"] = "dxe4";
    book["1. d4 Nf6 2. Bg5 d5 3. Nc3 Nbd7 4. f3 c6 5. e4 dxe4 6. fxe4"] = "e5";
    book["1. d4 Nf6 2. Bg5 d5 3. Nc3 Nbd7 4. f3 c6 5. Bxf6"] = "Nxf6";


    book["1. d4 Nf6 2. Bg5 d5 3. e3 c5 4. Bxf6"] = "gxf6";
    book["1. d4 Nf6 2. Bg5 d5 3. e3 c5 4. c3"] = "Nc6";
    book["1. d4 Nf6 2. Bg5 d5 3. e3 c5 4. Nc3"] = "Nc6";
    book["1. d4 Nf6 2. Bg5 d5 3. e3 c5 4. Nd2"] = "cxd4";
    book["1. d4 Nf6 2. Bg5 d5 3. e3 c5 4. Nf3"] = "Ne4";
    book["1. d4 Nf6 2. Bg5 d5 3. e3 c5 4. dxc5"] = "Ne4";


    // Reti opening (A07)
    book["1. Nf3 d5 2. g3"] = "Nf6";
    book["1. Nf3 d5 2. g3 Nf6 3. Bg2"] = "c5";

    book["1. Nf3 d5 2. d4"] = "Nf6";
    book["1. Nf3 d5 2. c4"] = "d4";
    book["1. Nf3 d5 2. e3"] = "Nf6";
    book["1. Nf3 d5 2. b3"] = "Nf6";



    // Queen opening (BLACK)
    book["1. d4 Nf6 2. e3"] = "d5";
    book["1. d4 Nf6 2. e3 d5 3. Bd3"] = "c5";
    book["1. d4 Nf6 2. e3 d5 3. c4"] = "c6";
    book["1. d4 Nf6 2. e3 d5 3. Nf3"] = "Bf5";
    book["1. d4 Nf6 2. e3 d5 3. f4"] = "Bf5";
    book["1. d4 Nf6 2. e3 d5 3. Nd2"] = "Bf5";
    book["1. d4 Nf6 2. e3 d5 3. Nc3"] = "Bf5";
    book["1. d4 Nf6 2. e3 d5 3. Bd2"] = "Bf5";

    book["1. d4 Nf6 2. Nf3"] = "d5";
    book["1. d4 Nf6 2. Nf3 d5 3. c4"] = "e6";
    book["1. d4 Nf6 2. Nf3 d5 3. e3"] = "e6";
    book["1. d4 Nf6 2. Nf3 d5 3. Bf4"] = "c5";
    book["1. d4 Nf6 2. Nf3 d5 3. g3"] = "c5";
    book["1. d4 Nf6 2. Nf3 d5 3. g3 c5 4. Bg2"] = "Nc6";
    book["1. d4 Nf6 2. Nf3 d5 3. Bg5"] = "Ne4";
    book["1. d4 Nf6 2. Nf3 d5 3. c3"] = "Bf5";
    book["1. d4 Nf6 2. Nf3 d5 3. Nc3"] = "e6";
    book["1. d4 Nf6 2. Nf3 d5 3. Nbd2"] = "Bf5";

    book["1. d4 Nf6 2. Nf3 d5 3. c3 Bf5 4. Bf4"] = "e6";
    book["1. d4 Nf6 2. Nf3 d5 3. c3 Bf5 4. Bf4 e6 5. e3"] = "Bd6";

    book["1. d4 Nf6 2. e3 d5 3. Bd3 c5 4. c3"] = "Nc6";
    book["1. d4 Nf6 2. e3 d5 3. Bd3 c5 4. c3 Nc6 5. f4"] = "Bg4";
    book["1. d4 Nf6 2. e3 d5 3. Bd3 c5 4. c3 Nc6 5. Nd2"] = "e5";
    book["1. d4 Nf6 2. e3 d5 3. Bd3 c5 4. c3 Nc6 5. Nf3"] = "Bg4";
    book["1. d4 Nf6 2. e3 d5 3. Bd3 c5 4. c3 Nc6 5. dxc5"] = "e5";

    book["1. d4 Nf6 2. e3 d5 3. c4 c6 4. Nc3"] = "e6";
    book["1. d4 Nf6 2. e3 d5 3. c4 c6 4. Nc3 e6 5. Bd2"] = "Nbd7";

    book["1. d4 Nf6 2. Nd2"] = "d5";
    book["1. d4 Nf6 2. Nd2 d5 3. e3"] = "Bf5";
    book["1. d4 Nf6 2. Nd2 d5 3. e3 Bf5 4. Ngf3"] = "e6";
    book["1. d4 Nf6 2. Nd2 d5 3. e3 Bf5 4. c4"] = "e6";
    book["1. d4 Nf6 2. Nd2 d5 3. e3 Bf5 4. Bd3"] = "Bxd3";
    book["1. d4 Nf6 2. Nd2 d5 3. e3 Bf5 4. Bd3 Bxd3 5. cxd3"] = "e6";

    book["1. d4 Nf6 2. c4 g6 3. e3"] = "Bg7";
    book["1. d4 Nf6 2. c4 g6 3. e3 Bg7 4. Nc3"] = "0-0";
    book["1. d4 Nf6 2. c4 g6 3. e3 Bg7 4. Nf3"] = "0-0";
    book["1. d4 Nf6 2. c4 g6 3. e3 Bg7 4. Bd3"] = "0-0";

    book["1. d4 Nf6 2. c4 g6 3. Bf4"] = "Bg7";
    book["1. d4 Nf6 2. c4 g6 3. Bf4 Bg7 4. Nc3"] = "d6";
    book["1. d4 Nf6 2. c4 g6 3. Bf4 Bg7 4. e3"] = "d6";

    book["1. d4 Nf6 2. Bf4"] = "d5";
    book["1. d4 Nf6 2. Bf4 d5 3. e3"] = "c5";
    book["1. d4 Nf6 2. Bf4 d5 3. e3 c5 4. c3"] = "Nc6";
    book["1. d4 Nf6 2. Bf4 d5 3. e3 c5 4. Nc3"] = "cxd4";
    book["1. d4 Nf6 2. Bf4 d5 3. e3 c5 4. Nf3"] = "Nc6";
    book["1. d4 Nf6 2. Bf4 d5 3. e3 c5 4. dxc5"] = "Nc6";

    book["1. d4 Nf6 2. Bf4 d5 3. e3 c5 4. c3 Nc6 5. Nf3"] = "e6";
    book["1. d4 Nf6 2. Bf4 d5 3. e3 c5 4. c3 Nc6 5. Nf3 e6 6. Nbd2"] = "Bd6";
    book["1. d4 Nf6 2. Bf4 d5 3. e3 c5 4. c3 Nc6 5. Nf3 e6 6. Nbd2 Bd6 7. Bg3"] = "0-0";

    book["1. d4 Nf6 2. Bf4 d5 3. Nf3"] = "c5";
    book["1. d4 Nf6 2. Bf4 d5 3. Nf3 c5 4. e3"] = "Nc6";
    book["1. d4 Nf6 2. Bf4 d5 3. Nf3 c5 4. c3"] = "Nc6";
    book["1. d4 Nf6 2. Bf4 d5 3. Nf3 c5 4. dxc5"] = "e6";



    // Rare openings
    book["1. e4 e5 2. Nf3 Nc6 3. g4"] = "Nf6";
    book["1. e4 e5 2. Nf3 Nc6 3. g4 Nf6 4. Ng5"] = "Bc4";
    book["1. e4 e5 2. Bc4"] = "Nf6";
    book["1. e4 e5 2. Bc4 Nf6 3. d3"] = "Nc6";
    book["1. e4 e5 2. Bc4 Nf6 3. d3 Nc6 4. a3"] = "Bc5";
    book["1. e4 e5 2. Bc4 Nf6 3. d3 Nc6 4. a3 Bc5 5. h3"] = "0-0";

    book["1. e4 b6"] = "d4";
    book["1. e4 b6 2. d4 g6"] = "Nf3";
    book["1. e4 b6 2. d4 g6 3. Nf3 Bg7"] = "Nc3";

    book["1. e4 e5 2. Qh5"] = "Nc6";
    book["1. e4 e5 2. Qh5 Nc6 3. Bc4"] = "g6";
    book["1. e4 e5 2. Qh5 Nc6 3. Bc4 g6 4. Qd1"] = "Bg7";
    book["1. e4 e5 2. Qh5 Nc6 3. Bc4 g6 4. Qf3"] = "Nf6";
    book["1. e4 e5 2. Qh5 Nc6 3. Bc4 g6 4. Qf3 Nf6 5. Ne2"] = "Bg7";
    book["1. e4 e5 2. Qh5 Nc6 3. Bc4 g6 4. Qf3 Nf6 5. d3"] = "Nd4";
    book["1. e4 e5 2. Qh5 Nc6 3. Bc4 g6 4. Qf3 Nf6 5. Nc3"] = "Nd4";

    book["1. e4 b6 2. d4 Bb7"] = "Nc3";

    book["1. Nc3"] = "d5";
    book["1. Nc3 d5 2. Nf3"] = "Nf6";

    book["1. e4 e5 2. h4"] = "Nf6";

    book["1. e4 e5 2. Ne2"] = "Nf6";
    book["1. e4 e5 2. Ne2 Nf6 3. Ng3"] = "Nc6";

    book["1. d3"] = "d5";
    book["1. d3 d5 2. e3"] = "e5";
    book["1. d3 d5 2. e3 e5 3. Nf3"] = "Nc6";
    book["1. d3 d5 2. e3 e5 3. Nc3"] = "Nc6";

    book["1. g4"] = "d5";
    book["1. g4 d5 2. Bg2"] = "c6";

    book["1. e3"] = "e5";
    book["1. e3 e5 2. Nc3"] = "Nf6";



    ////////////////
    // END OF BOOK
    ////////////////
}



// getReplyTo()
//
// Find a reply move to a given sequence.
//
// This function searches the book file for a given sequence and returns a
// random move out of the list of replies. If the sequence wasn't found, it
// returns NULL.
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
