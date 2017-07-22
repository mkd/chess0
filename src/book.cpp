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
unordered_map<string, string> po;



/*!
 * Fill in the openings book with all the theory lines.
 */
void initBook()
{
    ////////////////
    // WHITE 
    /////////////////
    
    po["%"] = "e4";



    // Open openings
    po["1. e4 e5"] = "Nf3";
    po["1. e4 e5 2. Nf3 Nc6"] = "Bb5";
    po["1. e4 e5 2. Nf3 Nf6"] = "Nxe5";
    po["1. e4 e5 2. Nf3 d6"] = "d4";
    po["1. e4 e5 2. Nf3 f5"] = "Nxe5";
    po["1. e4 e5 2. Nf3 d5"] = "exd5";
    po["1. e4 e5 2. Nf3 Qe7"] = "Bc4";
    po["1. e4 e5 2. Nf3 Bc5"] = "Nxe5";


    // Alekhine Defense (WHITE)
    po["1. e4 Nf6"] = "e5";
    po["1. e4 Nf6 2. e5 Nd5"] = "d4";
    po["1. e4 Nf6 2. e5 Nd5 3. d4 d6"] = "Nf3";
    po["1. e4 Nf6 2. e5 Nd5 3. d4 Nb6"] = "Nf3";
    po["1. e4 Nf6 2. e5 Nd5 3. d4 e6"] = "Nf3";




    // French Defense (WHITE)
    po["1. e4 e6"] = "d4";
    po["1. e4 e6 2. d4 d5"] = "Nc3";
    po["1. e4 e6 2. d4 d5 3. Nc3 Bb4"] = "e5";
    po["1. e4 e6 2. d4 d5 3. Nc3 Nf6"] = "Bg5";
    po["1. e4 e6 2. d4 d5 3. Nc3 dxe4"] = "Nxe4";
    po["1. e4 e6 2. d4 d5 3. Nc3 c5"] = "exd5";

    po["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. e5 c5"] = "Bd2";
    po["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. e5 c5 5. Bd2 Ne7"] = "a3";
    po["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. e5 c5 5. Bd2 cxd4"] = "Nb5";
    po["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. e5 c5 5. Bd2 Nc6"] = "Nb5";
    po["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. e5 c5 5. Bd2 Nh6"] = "Nb5";
    po["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. e5 c5 5. Bd2 Bxc3"] = "Bxc3";

    po["1. e4 e6 2. d4 d5 3. Nc3 Nf6 4. Bg5 Be7"] = "e5";
    po["1. e4 e6 2. d4 d5 3. Nc3 Nf6 4. Bg5 Be7 5. e5 Nfd7"] = "Bxe7";
    po["1. e4 e6 2. d4 d5 3. Nc3 Nf6 4. Bg5 Be7 5. e5 Nfd7 6. Bxe7 Qxe7"] = "f4";

    po["1. e4 e6 2. d4 d5 3. Nc3 Nf6 4. Bg5 h6"] = "Bxf6";
    po["1. e4 e6 2. d4 d5 3. Nc3 Nf6 4. Bg5 h6 5. Bxf6 Qxf6"] = "exd5";
    po["1. e4 e6 2. d4 d5 3. Nc3 Nf6 4. Bg5 h6 5. Bxf6 Qxf6 6. exd5 Bb4"] = "Bb5+";
    po["1. e4 e6 2. d4 d5 3. Nc3 Nf6 4. Bg5 h6 5. Bxf6 Qxf6 6. exd5 Bb4 7. Bb5+ Bd7"] = "Bxd7";
    po["1. e4 e6 2. d4 d5 3. Nc3 Nf6 4. Bg5 h6 5. Bxf6 Qxf6 6. exd5 Bb4 7. Bb5+ Bd7 8. Bxd7+ Nxd7"] = "dxe6";
    po["1. e4 e6 2. d4 d5 3. Nc3 Nf6 4. Bg5 h6 5. Bxf6 Qxf6 6. exd5 Bb4 7. Bb5+ Bd7 8. Bxd7+ Nxd7 9. dxe6 fxe6"] = "Nf3";

    po["1. e4 e6 2. d4 d5 3. Nc3 Nf6 4. Bg5 h6 5. Bxf6 Qxf6 6. exd5 Bb4 7. Bb5+ c6"] = "dxc6";
    po["1. e4 e6 2. d4 d5 3. Nc3 Nf6 4. Bg5 h6 5. Bxf6 Qxf6 6. exd5 Bb4 7. Bb5+ c6 8. dxc6 bxc6"] = "Be2";
    po["1. e4 e6 2. d4 d5 3. Nc3 Nf6 4. Bg5 h6 5. Bxf6 Qxf6 6. exd5 Bb4 7. Bb5+ c6 8. dxc6 Nxc6"] = "Nf3";

    po["1. e4 e6 2. d4 d5 3. Nc3 dxe4"] = "Nxe4";
    po["1. e4 e6 2. d4 d5 3. Nc3 dxe4 4. Nxe4 Nf6"] = "Nxf6+";
    po["1. e4 e6 2. d4 d5 3. Nc3 dxe4 4. Nxe4 Nf6 5. Nxf6+ Qxf6"] = "Nf3";
    po["1. e4 e6 2. d4 d5 3. Nc3 dxe4 4. Nxe4 Nf6 5. Nxf6+ Qxf6 6. Nf3 h6"] = "Bd3";


    // Caro-Kann Defense 
    po["1. e4 c6"] = "d4";
    po["1. e4 c6 2. d4 d5"] = "Nc3";
    po["1. e4 c6 2. d4 d5 3. Nc3 dxe4"] = "Nxe4";
    po["1. e4 c6 2. d4 d5 3. Nc3 Nf6"] = "e5";
    po["1. e4 c6 2. d4 d5 3. Nc3 g6"] = "Nf3";

    po["1. e4 c6 2. d4 d5 3. Nc3 dxe4 4. Nxe4 Nf6"] = "Nxf6+";
    po["1. e4 c6 2. d4 d5 3. Nc3 dxe4 4. Nxe4 Nf6 5. Nxf6+ gxf6"] = "Nf3";
    po["1. e4 c6 2. d4 d5 3. Nc3 dxe4 4. Nxe4 Nf6 5. Nxf6+ gxf6 6. Nf3 Bg4"] = "Be2";
    po["1. e4 c6 2. d4 d5 3. Nc3 dxe4 4. Nxe4 Nf6 5. Nxf6+ gxf6 6. Nf3 Bg4 7. Be2 Qc7"] = "Be3";
    po["1. e4 c6 2. d4 d5 3. Nc3 dxe4 4. Nxe4 Nf6 5. Nxf6+ exf6"] = "c3";

    


    // Danish Defense (WHITE)
    po["1. e4 d5"] = "exd5";
    po["1. e4 d5 2. exd5 Qxd5"] = "Nc3";
    po["1. e4 d5 2. exd5 Qxd5 3. Nc3 Qa5"] = "Nf3";
    po["1. e4 d5 2. exd5 Qxd5 3. Nc3 Qd6"] = "d4";
    po["1. e4 d5 2. exd5 Qxd5 3. Nc3 Qd8"] = "d4";
    po["1. e4 d5 2. exd5 Qxd5 3. Nc3 Qe5+"] = "Be2";
    po["1. e4 d5 2. exd5 Qxd5 3. Nc3 Qe6+"] = "Be2";

    po["1. e4 d5 2. exd5 Qxd5 3. Nc3 Qa5 4. Nf3 Nf6"] = "d4";
    po["1. e4 d5 2. exd5 Qxd5 3. Nc3 Qa5 4. Nf3 Bg4"] = "Be2";
    po["1. e4 d5 2. exd5 Qxd5 3. Nc3 Qa5 4. Nf3 c6"] = "d4";
    po["1. e4 d5 2. exd5 Qxd5 3. Nc3 Qa5 4. Nf3 c6 5. d4 Nf6"] = "Bc4";

    po["1. e4 d5 2. exd5 Qxd5 3. Nc3 Qd8 4. d4 Nf6"] = "Nf3";
    po["1. e4 d5 2. exd5 Qxd5 3. Nc3 Qd8 4. d4 c6"] = "Bc4";
    po["1. e4 d5 2. exd5 Qxd5 3. Nc3 Qd8 4. d4 g6"] = "Nf3";
    po["1. e4 d5 2. exd5 Qxd5 3. Nc3 Qd8 4. d4 e6"] = "Nf3";
    po["1. e4 d5 2. exd5 Qxd5 3. Nc3 Qd8 4. d4 Bf5"] = "Nf3";

    po["1. e4 d5 2. exd5 Qxd5 3. Nc3 Qe6+ 4. Be2 Qg6"] = "Nf3";
    po["1. e4 d5 2. exd5 Qxd5 3. Nc3 Qe6+ 4. Be2 Nf6"] = "Nf3";
    po["1. e4 d5 2. exd5 Qxd5 3. Nc3 Qe6+ 4. Be2 Nc6"] = "d4";
    po["1. e4 d5 2. exd5 Qxd5 3. Nc3 Qe6+ 4. Be2 Qc6"] = "Nf3";



    // Sicilian Defense (WHITE)
    po["1. e4 c5"] = "Nf3";
    po["1. e4 c5 2. Nf3 d6"] = "d4";
    po["1. e4 c5 2. Nf3 Nc6"] = "d4";
    po["1. e4 c5 2. Nf3 e6"] = "d4";
    po["1. e4 c5 2. Nf3 g6"] = "d4";
    po["1. e4 c5 2. Nf3 a6"] = "c3";
    po["1. e4 c5 2. Nf3 Nf6"] = "e5";

    po["1. e4 c5 2. Nf3 e6 3. d4 cxd4"] = "Nxd4";
    po["1. e4 c5 2. Nf3 e6 3. d4 cxd4 4. Nxd4 a6"] = "Bd3";
    po["1. e4 c5 2. Nf3 e6 3. d4 cxd4 4. Nxd4 Nf6"] = "Nc3";
    po["1. e4 c5 2. Nf3 e6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 d6"] = "Be2";
    po["1. e4 c5 2. Nf3 e6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 Nc6"] = "Ndb5";
    po["1. e4 c5 2. Nf3 e6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 Nc6 6. Ndb5 d6"] = "Bf4";
    po["1. e4 c5 2. Nf3 e6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 Nc6 6. Ndb5 d6 7. Bf4 e5"] = "Bg5";
    po["1. e4 c5 2. Nf3 e6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 Nc6 6. Ndb5 d6 7. Bf4 e5 8. Bg5 a6"] = "Na3";

    po["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4"] = "Nxd4";
    po["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 Nf6"] = "Nc3";
    po["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 g6"] = "Nc3";
    po["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 e5"] = "Nb5";
    po["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 e6"] = "Nc3";
    po["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 Qc7"] = "Nc3";
    po["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 Qb6"] = "Nb3";
    po["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 d6"] = "Nc3";
    po["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 a6"] = "Nc3";

    po["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 e5 5. Nb5 d6"] = "N1c3";
    po["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 e5 5. Nb5 a6"] = "Nd6+";
    po["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 e5 5. Nb5 Nf6"] = "N1c3";
    po["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 e5 5. Nb5 Qa5+"] = "N1c3";

    po["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 e5 5. Nb5 a6 6. Nd6+ Bxd6"] = "Qxd6";
    po["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 e5 5. Nb5 a6 6. Nd6+ Bxd6 7. Qxd6 Qf6"] = "Qxf6";
    po["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 e5 5. Nb5 a6 6. Nd6+ Bxd6 7. Qxd6 Qe7"] = "Qd1";
    po["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 e5 5. Nb5 a6 6. Nd6+ Bxd6 7. Qxd6 f5"] = "Nc3";
    po["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 e5 5. Nb5 a6 6. Nd6+ Bxd6 7. Qxd6 Nf6"] = "Nc3";
    po["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 e5 5. Nb5 a6 6. Nd6+ Bxd6 7. Qxd6 Nf6 8. Nc3 Qe7"] = "Qxe7+";
    po["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 e5 5. Nb5 a6 6. Nd6+ Bxd6 7. Qxd6 Nf6 8. Nc3 h6"] = "Be3";
    po["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 e5 5. Nb5 a6 6. Nd6+ Bxd6 7. Qxd6 Nf6 8. Nc3 Qb6"] = "Bd2";

    po["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 e5 5. Nb5 a6 6. Nd6+ Bxd6 7. Qxd6 Nf6 8. Nc3 b5"] = "Bg5";
    po["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 e5 5. Nb5 a6 6. Nd6+ Bxd6 7. Qxd6 Nf6 8. Nc3 b5 9. Bg5 Qe7"] = "Qd2";
    po["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 e5 5. Nb5 a6 6. Nd6+ Bxd6 7. Qxd6 Nf6 8. Nc3 b5 9. Bg5 h6"] = "Nd5";
    po["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 e5 5. Nb5 a6 6. Nd6+ Bxd6 7. Qxd6 Nf6 8. Nc3 b5 9. Bg5 Ra7"] = "0-0-0";

    po["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 e5 5. Nb5 Qa5+ 6. N1c3 a6"] = "Nd6+";
    po["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 e5 5. Nb5 Qa5+ 6. N1c3 a6 7. Nd6+ Bxd6"] = "Qxd6";

    po["1. e4 c5 2. Nf3 d6 3. d4 cxd4"] = "Nxd4";
    po["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 Nf6"] = "Nc3";
    po["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 Nc6"] = "Nc3";
    po["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 a6"] = "Nc3";
    po["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 g6"] = "Nc3";
    po["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 e5"] = "Nb3";
    po["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 e6"] = "Nc3";
    po["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 Bd7"] = "Nc3";

    po["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 Nc6 5. Nc3 g6"] = "Be3";
    po["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 Nc6 5. Nc3 Nf6"] = "Bg5";

    po["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 Nc6 5. Nc3 Nf6 6. Bg5 e6"] = "Qd2";
    po["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 Nc6 5. Nc3 Nf6 6. Bg5 Bd7"] = "Qd2";
    po["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 Nc6 5. Nc3 Nf6 6. Bg5 Qb6"] = "Nb3";
    po["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 Nc6 5. Nc3 Nf6 6. Bg5 a6"] = "Qd2";

    po["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 e6 5. Nc3 Qc7"] = "Be3";
    po["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 e6 5. Nc3 a6"] = "Be2";
    po["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 e6 5. Nc3 d6"] = "Be3";
    po["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 e6 5. Nc3 Nf6"] = "Ndb5";
    po["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 e6 5. Nc3 Bb4"] = "Ndb5";
    po["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 e6 5. Nc3 Bc5"] = "Nb3";

    po["1. e4 c5 2. Nf3 d6 3. d4 e6"] = "dxc5";
    po["1. e4 c5 2. Nf3 d6 3. d4 e6 4. dxc5 Qa5+"] = "Nc3";

    po["1. e4 c5 2. Nf3 Nc6 3. d4 d5"] = "exd5";
    po["1. e4 c5 2. Nf3 Nc6 3. d4 d5 4. exd5 Qxd5"] = "Nc3";
    po["1. e4 c5 2. Nf3 Nc6 3. d4 d5 4. exd5 Nxd4"] = "Nxd4";
    po["1. e4 c5 2. Nf3 Nc6 3. d4 d5 4. exd5 Nxd4 5. Nxd4 cxd4"] = "Qxd4";

    // Sicilian, accelerated fianchetto (B34)
    po["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 g6 5. Nc3 Bg7"] = "Be3";
    po["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 g6 5. Nc3 Bg7 6. Be3 Nf6"] = "Bc4";
    po["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 g6 5. Nc3 Bg7 6. Be3 d6"] = "Qd2";
    po["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 g6 5. Nc3 Bg7 6. Be3 a6"] = "Qd2";
    po["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 g6 5. Nc3 Bg7 6. Be3 e6"] = "Ndb5";



    // Spanish Opening (WHITE)
    po["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6"] = "0-0";
    po["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4"] = "d4";
    po["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. d4 Nd6"] = "Bxc6";
    po["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. d4 Be7"] = "Qe2";
    po["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. d4 a6"] = "Ba4";
    po["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. d4 exd4"] = "Re1";
    po["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. d4 exd4 6. Re1 d5"] = "Nxd4";
    po["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. d4 exd4 6. Re1 f5"] = "Nxd4";
    po["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. d4 exd4 6. Re1 Be7"] = "Rxe4";
    po["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. d4 exd4 6. Re1 Qe7 7. Nxd4 Nxd4"] = "Qxd4";

    po["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6"] = "Ba4";
    po["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nf6"] = "0-0";
    po["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 d6"] = "c3";
    po["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 b5"] = "Bb3";
    po["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Bc5"] = "0-0";

    po["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nf6 5. 0-0 Be7"] = "Re1";
    po["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nf6 5. 0-0 b5"] = "Bb3";
    po["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nf6 5. 0-0 Nxe4"] = "d4";
    po["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nf6 5. 0-0 d6"] = "Re1";
    po["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nf6 5. 0-0 Bc5"] = "c3";

    po["1. e4 e5 2. Nf3 Nc6 3. Bb5 d6"] = "d4";
    po["1. e4 e5 2. Nf3 Nc6 3. Bb5 d6 4. d4 Bd7"] = "Nc3";
    po["1. e4 e5 2. Nf3 Nc6 3. Bb5 d6 4. d4 exd4"] = "Nxd4";
    po["1. e4 e5 2. Nf3 Nc6 3. Bb5 d6 4. d4 a6"] = "Bxc6+";
    po["1. e4 e5 2. Nf3 Nc6 3. Bb5 d6 4. d4 a6 5. Bxc6+ bxc6"] = "dxe5";



    // Rare openings (WHITE)
    po["1. e4 d6"] = "d4";
    po["1. e4 d6 2. d4 c6"] = "Nc3";





    ////////////////
    // BLACK
    ////////////////

    po["1. e4"] = "e5";
    po["1. d4"] = "Nf6";
    po["1. Nf3"] = "d5";
    po["1. c4"] = "e5";
    po["1. f4"] = "Nf3";



    // Open openings
    po["1. e4 e5 2. Nf3"] = "Nc6";
    po["1. e4 e5 2. Bc4"] = "Nf6";
    po["1. e4 e5 2. f4"] = "exf4";
    po["1. e4 e5 2. Nc3"] = "Nf6";
    po["1. e4 e5 2. d3"] = "Nc6";

    po["1. e4 e5 2. Nf3 Nc6 3. Bc4"] = "Nf6";
    po["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. c3"] = "Nxe4";

    po["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. 0-0"] = "Nxe4";
    po["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. 0-0 Nxe4 5. Re1"] = "d5";
    po["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. 0-0 Nxe4 5. Nc3"] = "Nxc3";
    po["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. 0-0 Nxe4 5. d4"] = "d5";
    po["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. 0-0 Nxe4 5. Bb5"] = "Bc5";
    po["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. 0-0 Nxe4 5. Bb5 Bc5 6. Qe1"] = "Nf6";
    po["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. 0-0 Nxe4 5. Bb5 Bc5 6. Qe1 Nf6 7. Bxc6"] = "dxc6";
    po["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. 0-0 Nxe4 5. Bb5 Bc5 6. Qe1 Nf6 7. Bxc6 dxc6 8. Qxe5"] = "Qe7";
    po["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. 0-0 Nxe4 5. Bb5 Bc5 6. Qe1 Nf6 7. Bxc6 dxc6 8. d3"] = "0-0";

    po["1. e4 e5 2. Nf3 Nc6 3. d3"] = "Nf6";
    po["1. e4 e5 2. Nf3 Nc6 3. d3 Nf6 4. Be2"] = "d5";
    po["1. e4 e5 2. Nf3 Nc6 3. d3 Nf6 4. g3"] = "Bc5";
    po["1. e4 e5 2. Nf3 Nc6 3. d3 Nf6 4. c3"] = "d5";
    po["1. e4 e5 2. Nf3 Nc6 3. d3 Nf6 4. Nc3"] = "Bb4";
    po["1. e4 e5 2. Nf3 Nc6 3. d3 Nf6 4. Bg5"] = "Be7";
    po["1. e4 e5 2. Nf3 Nc6 3. d3 Nf6 4. Nbd2"] = "Bc5";
    po["1. e4 e5 2. Nf3 Nc6 3. d3 Nf6 4. c4"] = "Bc5";
    po["1. e4 e5 2. Nf3 Nc6 3. d3 Nf6 4. Be3"] = "d5";

    po["1. e4 e5 2. Nf3 Nc6 3. b3"] = "Nf6";
    po["1. e4 e5 2. Nf3 Nc6 3. b3 Nf6 4. Nc3"] = "Bc5";
    po["1. e4 e5 2. Nf3 Nc6 3. b3 Nf6 4. d3"] = "Bc5";
    po["1. e4 e5 2. Nf3 Nc6 3. b3 Nf6 4. Bb2"] = "Bc5";

    po["1. e4 e5 2. Nc3 Nf6 3. Bc4"] = "Bc5";
    po["1. e4 e5 2. Nc3 Nf6 3. Bc4 Bc5 4. d3"] = "d6";
    po["1. e4 e5 2. Nc3 Nf6 3. Bc4 Bc5 4. Nf3"] = "d6";



    // Scotch (BLACK)
    po["1. e4 e5 2. Nf3 Nc6 3. d4"] = "exd4";
    po["1. e4 e5 2. Nf3 Nc6 3. d4 exd4 4. Nxd4"] = "Nf6";
    po["1. e4 e5 2. Nf3 Nc6 3. d4 exd4 4. Nxd4 Nf6 5. Nxc6"] = "bxc6";
    po["1. e4 e5 2. Nf3 Nc6 3. d4 exd4 4. Nxd4 Nf6 5. Nc3"] = "Bb4";
    po["1. e4 e5 2. Nf3 Nc6 3. d4 exd4 4. Nxd4 Nf6 5. Bg5"] = "h6";


    // King's Gambit
    po["1. e4 e5 2. f4 exf4 3. Nf3"] = "g5";
    po["1. e4 e5 2. f4 exf4 3. Nf3 g5 4. h4"] = "g4";
    po["1. e4 e5 2. f4 exf4 3. Nf3 g5 4. Bc4"] = "g4";
    po["1. e4 e5 2. f4 exf4 3. Nf3 g5 4. d4"] = "g4";
    po["1. e4 e5 2. f4 exf4 3. Nf3 g5 4. Nc3"] = "g4";
    po["1. e4 e5 2. f4 exf4 3. Nf3 g5 4. h3"] = "Bg7";

    po["1. e4 e5 2. f4 exf4 3. Nf3 g5 4. Bc4 g4 5. 0-0"] = "gxf3";
    po["1. e4 e5 2. f4 exf4 3. Nf3 g5 4. Bc4 g4 5. 0-0 gxf3 6. Qxf3"] = "Qf6";
    po["1. e4 e5 2. f4 exf4 3. Nf3 g5 4. Bc4 g4 5. 0-0 gxf3 6. Qxf3 Qf6 7. e5"] = "Qxe5";
    po["1. e4 e5 2. f4 exf4 3. Nf3 g5 4. Bc4 g4 5. 0-0 gxf3 6. Qxf3 Qf6 7. e5 Qxe5 8. d3"] = "Bh6";
    po["1. e4 e5 2. f4 exf4 3. Nf3 g5 4. Bc4 g4 5. 0-0 gxf3 6. Qxf3 Qf6 7. d3"] = "Nc6";

    po["1. e4 e5 2. f4 exf4 3. Nf3 g5 4. h3 Bg7 5. d4"] = "h6";
    po["1. e4 e5 2. f4 exf4 3. Nf3 g5 4. h3 Bg7 5. Bc4"] = "h6";


    // Fried Liver Attack (C58)
    po["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Ng5"] = "d5";
    po["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Ng5 d5 5. Nxf7"] = "Kxf7";
    po["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Ng5 d5 5. Nxf7 Kxf7 6. exd5"] = "b5";

    po["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Ng5 d5 5. exd5"] = "Na5";
    po["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Ng5 d5 5. exd5 Na5 6. Bb5+"] = "c6";
    po["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Ng5 d5 5. exd5 Na5 6. Bb5+ c6 7. dxc6"] = "bxc6";
    po["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Ng5 d5 5. exd5 Na5 6. Bb5+ c6 7. dxc6 bxc6 8. Bd3"] = "Nd5";
    po["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Ng5 d5 5. exd5 Na5 6. Bb5+ c6 7. dxc6 bxc6 8. Be2"] = "h6";
    po["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Ng5 d5 5. exd5 Na5 6. Bb5+ c6 7. dxc6 bxc6 8. Ba4"] = "h6";

    po["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Ng5 d5 5. exd5 Na5 6. Bb5+ c6 7. dxc6 bxc6 8. Bd3 Nd5 9. Nf3"] = "Bd6";
    po["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Ng5 d5 5. exd5 Na5 6. Bb5+ c6 7. dxc6 bxc6 8. Bd3 Nd5 9. h4"] = "Nf4";
    po["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Ng5 d5 5. exd5 Na5 6. Bb5+ c6 7. dxc6 bxc6 8. Be2 h6 9. Nf3"] = "e4";
    po["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Ng5 d5 5. exd5 Na5 6. Bb5+ c6 7. dxc6 bxc6 8. Ba4 h6 9. Nf3"] = "e4";



    // Spanish Defense
    po["1. e4 e5 2. Nf3 Nc6 3. Bb5"]= "Nf6";
    po["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0"] = "Nxe4";
    po["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. d4"] = "Nd6";
    po["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. d4 Nd6 6. Bxc6"] = "dxc6";
    po["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. d4 Nd6 6. Bxc6 dxc6 7. dxe5"] = "Nf5";


    po["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. Re1"] = "Nd6";
    po["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. Re1 Nd6 6. Nxe5"] = "Be7";
    po["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. Re1 Nd6 6. Nxe5 Be7 7. Bf1"] = "Nxe5";
    po["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. Re1 Nd6 6. Nxe5 Be7 7. Bd3"] = "Nxe5";
    po["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. Re1 Nd6 6. Nxe5 Be7 7. Ba4"] = "Nxe5";
    po["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. Re1 Nd6 6. Nxe5 Be7 7. Nxc6"] = "dxc6";
    po["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. Re1 Nd6 6. Nxe5 Be7 7. Bxc6"] = "dxc6";

    po["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. d3"] = "Bc5";
    po["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. d3 Bc5 5. c3"] = "0-0";
    po["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. d3 Bc5 5. Bxc6"] = "dxc6";
    po["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. d3 Bc5 5. 0-0"] = "d6";
    po["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. d3 Bc5 5. Nc3"] = "d6";



    // Grünfeld Defense (BLACK)
    po["1. d4 Nf6 2. c4"] = "g6";
    po["1. d4 Nf6 2. c4 g6 3. Nc3"] = "d5";
    po["1. d4 Nf6 2. c4 g6 3. Nc3 d5 4. cxd5"] = "Nxd5";
    po["1. d4 Nf6 2. c4 g6 3. Nc3 d5 4. cxd5 Nxd5 5. e4"] = "Nxc3";
    po["1. d4 Nf6 2. c4 g6 3. Nc3 d5 4. cxd5 Nxd5 5. e4 Nxc3 6. bxc3"] = "Bg7";
    po["1. d4 Nf6 2. c4 g6 3. Nc3 d5 4. cxd5 Nxd5 5. e4 Nxc3 6. bxc3 Bg7 7. Nf3"] = "c5";
    po["1. d4 Nf6 2. c4 g6 3. Nc3 d5 4. cxd5 Nxd5 5. e4 Nxc3 6. bxc3 Bg7 7. Nf3 c5 8. Rb1"] = "0-0";
    po["1. d4 Nf6 2. c4 g6 3. Nc3 d5 4. cxd5 Nxd5 5. e4 Nxc3 6. bxc3 Bg7 7. Nf3 c5 8. Rb1 0-0 9. Be2"] = "Nc6";

    po["1. d4 Nf6 2. c4 g6 3. Nc3 d5 4. e3"] = "Bg7";
    po["1. d4 Nf6 2. c4 g6 3. Nc3 d5 4. e3 Bg7 5. Nf3"] = "0-0";
    po["1. d4 Nf6 2. c4 g6 3. Nc3 d5 4. e3 Bg7 5. Qb3"] = "e6";
    po["1. d4 Nf6 2. c4 g6 3. Nc3 d5 4. e3 Bg7 5. cxd5"] = "Nxd5";
    po["1. d4 Nf6 2. c4 g6 3. Nc3 d5 4. e3 Bg7 5. Bd3"] = "0-0";


    // Queen opening (BLACK)
    po["1. d4 Nf6 2. e3"] = "d5";
    po["1. d4 Nf6 2. e3 d5 3. Bd3"] = "c5";
    po["1. d4 Nf6 2. e3 d5 3. c4"] = "c6";
    po["1. d4 Nf6 2. e3 d5 3. Nf3"] = "Bf5";
    po["1. d4 Nf6 2. e3 d5 3. f4"] = "Bf5";
    po["1. d4 Nf6 2. e3 d5 3. Nd2"] = "Bf5";
    po["1. d4 Nf6 2. e3 d5 3. Nc3"] = "Bf5";
    po["1. d4 Nf6 2. e3 d5 3. Bd2"] = "Bf5";

    po["1. d4 Nf6 2. e3 d5 3. c4 c6 4. Nc3"] = "e6";
    po["1. d4 Nf6 2. e3 d5 3. c4 c6 4. Nc3 e6 5. Bd2"] = "Nbd7";

    po["1. d4 Nf6 2. Nd2"] = "d5";
    po["1. d4 Nf6 2. Nd2 d5 3. e3"] = "Bf5";
    po["1. d4 Nf6 2. Nd2 d5 3. e3 Bf5 4. Ngf3"] = "e6";
    po["1. d4 Nf6 2. Nd2 d5 3. e3 Bf5 4. c4"] = "e6";
    po["1. d4 Nf6 2. Nd2 d5 3. e3 Bf5 4. Bd3"] = "Bxd3";
    po["1. d4 Nf6 2. Nd2 d5 3. e3 Bf5 4. Bd3 Bxd3 5. cxd3"] = "e6";

    po["1. d4 Nf6 2. c4 g6 3. e3"] = "Bg7";
    po["1. d4 Nf6 2. c4 g6 3. e3 Bg7 4. Nc3"] = "0-0";
    po["1. d4 Nf6 2. c4 g6 3. e3 Bg7 4. Nf3"] = "0-0";
    po["1. d4 Nf6 2. c4 g6 3. e3 Bg7 4. Bd3"] = "0-0";

    po["1. d4 Nf6 2. c4 g6 3. Bf4"] = "Bg7";
    po["1. d4 Nf6 2. c4 g6 3. Bf4 Bg7 4. Nc3"] = "d6";
    po["1. d4 Nf6 2. c4 g6 3. Bf4 Bg7 4. e3"] = "d6";

    po["1. d4 Nf6 2. Bf4"] = "d5";
    po["1. d4 Nf6 2. Bf4 d5 3. e3"] = "c5";
    po["1. d4 Nf6 2. Bf4 d5 3. e3 c5 4. c3"] = "Nc6";
    po["1. d4 Nf6 2. Bf4 d5 3. e3 c5 4. Nc3"] = "cxd4";
    po["1. d4 Nf6 2. Bf4 d5 3. e3 c5 4. Nf3"] = "Nc6";
    po["1. d4 Nf6 2. Bf4 d5 3. e3 c5 4. dxc5"] = "Nc6";

    po["1. d4 Nf6 2. Bf4 d5 3. Nf3"] = "c5";
    po["1. d4 Nf6 2. Bf4 d5 3. Nf3 c5 4. e3"] = "Nc6";
    po["1. d4 Nf6 2. Bf4 d5 3. Nf3 c5 4. c3"] = "Nc6";
    po["1. d4 Nf6 2. Bf4 d5 3. Nf3 c5 4. dxc5"] = "e6";



    // Rare openings
    po["1. e4 e5 2. Nf3 Nc6 3. g4"] = "Nf6";
    po["1. e4 e5 2. Nf3 Nc6 3. g4 Nf6 4. Ng5"] = "Bc4";
    po["1. e4 e5 2. Bc4"] = "Nf6";
    po["1. e4 e5 2. Bc4 Nf6 3. d3"] = "Nc6";

    po["1. e4 b6"] = "d4";
    po["1. e4 b6 2. d4 g6"] = "Nf3";
    po["1. e4 b6 2. d4 g6 3. Nf3 Bg7"] = "Nc3";

    po["1. e4 b6 2. d4 Bb7"] = "Nc3";

    po["1. Nc3"] = "d5";
    po["1. Nc3 d5 2. Nf3"] = "Nf6";



    ////////////////
    // END OF BOOK
    ////////////////
    
    book = po;
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
        replies_buf = po[sequence];
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
