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
unordered_map<string, string> po;



/*!
 * Fill in the openings book with all the theory lines.
 */
void initBook()
{
        ////// PERSONAL OPENINGS ///////

        // White opening
        po["%"] = "e4";


        // first-move replies for Black
        po["1. e4"] = "e5";
        po["1. d4"] = "Nf6";
        po["1. Nf3"] = "Nf6";
        po["1. c4"] = "Nf6";
        po["1. g3"] = "d5";
        po["1. b3"] = "e5";
        po["1. f4"] = "d5";
        po["1. Nc3"] = "d5";
        po["1. b4"] = "e5";


        // 2-ply move for White
        po["1. e4 e5"] = "Nf3";
        po["1. e4 c5"] = "Nf3";
        po["1. e4 c6"] = "d4";
        po["1. e4 e6"] = "d4";
        po["1. e4 Nf6"] = "e5";
        po["1. e4 d6"] = "d4";
        po["1. e4 d5"] = "exd5";


        // B02 Alekhine's defence -- WHITE
        po["1. e4 Nf6 2. e5 Ng8"] = "d4";
        po["1. e4 Nf6 2. e5 Ne4"] = "d3";
        po["1. e4 Nf6 2. e5 Ne4 3. d3 Nc5"] = "d4";
        po["1. e4 Nf6 2. e5 Nd5"] = "d4";
        po["1. e4 Nf6 2. e5 Nd5 3. d4 d6"] = "Nf3";
        po["1. e4 Nf6 2. e5 Nd5 3. d4 d6 4. Nf3 Bg4"] = "Be2";
        po["1. e4 Nf6 2. e5 Nd5 3. d4 d6 4. Nf3 dxe5"] = "Nxe5";
        po["1. e4 Nf6 2. e5 Nd5 3. d4 Nb6"] = "a4";
        po["1. e4 Nf6 2. e5 Nd5 3. d4 Nb6 4. a4 a5"] = "Nf3";


        // B01 Scandinavian (centre counter) defence -- WHITE
        po["1. e4 d5 2. exd5 Nf6"] = "Nf3";
        po["1. e4 d5 2. exd5 Nf6 3. Nf3 Nxd5"] = "d4";
        po["1. e4 d5 2. exd5 Nf6 3. Nf3 Bg4"] = "Bb5+";
        po["1. e4 d5 2. exd5 Nf6 3. Nf3 Bg4 4. Bb5+ c6"] = "dxc6";
        po["1. e4 d5 2. exd5 Nf6 3. Nf3 Qxd5"] = "d4";
        po["1. e4 d5 2. exd5 Nf6 3. Nf3 Qxd5 4. d4 Qd8"] = "Bd3";
        po["1. e4 d5 2. exd5 Nf6 3. Nf3 Qxd5 4. d4 Bg4"] = "Be2";

        po["1. e4 d5 2. exd5 Qxd5"] = "Nc3";
        po["1. e4 d5 2. exd5 Qxd5 3. Nc3 Qa5"] = "d4";
        po["1. e4 d5 2. exd5 Qxd5 3. Nc3 Qd6"] = "d4";
        po["1. e4 d5 2. exd5 Qxd5 3. Nc3 Qd8"] = "d4";
        po["1. e4 d5 2. exd5 Qxd5 3. Nc3 Qe5+"] = "Be2";


        // C23 Bishop's opening -- BLACK
        po["1. e4 e5 2. Bc4"] = "Nf6";
        po["1. e4 e5 2. Bc4 Nf6 3. d3"] = "c6";
        po["1. e4 e5 2. Bc4 Nf6 3. Nc3"] = "Bc5";
        po["1. e4 e5 2. Bc4 Nf6 3. Nc3 Bc5 4. d3"] = "d6";
        po["1. e4 e5 2. Bc4 Nf6 3. Nc3 Bc5 4. f4"] = "d6";
        po["1. e4 e5 2. Bc4 Nf6 3. Nc3 Bc5 4. Nf3"] = "d6";


        // C42 Petrov's defence -- WHITE
        po["1. e4 e5 2. Nf3 Nf6"] = "Nxe5";
        po["1. e4 e5 2. Nf3 Nf6 3. Nxe5 Nxe4"] = "Qe2";
        po["1. e4 e5 2. Nf3 Nf6 3. Nxe5 Qe7"] = "d4";
        po["1. e4 e5 2. Nf3 Nf6 3. Nxe5 Qe7 4. d4 Nc6"] = "Nc3";
        po["1. e4 e5 2. Nf3 Nf6 3. Nxe5 Qe7 4. d4 d6"] = "Nf3";
        po["1. e4 e5 2. Nf3 Nf6 3. Nxe5 Qe7 4. d4 d6 5. Nf3 Nxe4"] = "Be2";
        po["1. e4 e5 2. Nf3 Nf6 3. Nxe5 Qe7 4. d4 d6 5. Nf3 Qxe4+"] = "Be2";
        po["1. e4 e5 2. Nf3 Nf6 3. Nxe5 Qe7 4. d4 d6 5. Nf3 Qxe4+ 6. Be2 Bf5"] = "Na3";

        po["1. e4 e5 2. Nf3 Nf6 3. Nxe5 d6"] = "Nf3";
        po["1. e4 e5 2. Nf3 Nf6 3. Nxe5 d6 4. Nf3 Nxe4"] = "d4";
        po["1. e4 e5 2. Nf3 Nf6 3. Nxe5 d6 4. Nf3 Nxe4 5. d4 d5"] = "Bd3";
        po["1. e4 e5 2. Nf3 Nf6 3. Nxe5 d6 4. Nf3 Nxe4 5. d4 Nc6"] = "Bd3";
        po["1. e4 e5 2. Nf3 Nf6 3. Nxe5 d6 4. Nf3 Nxe4 5. d4 Be7"] = "Bd3";
        po["1. e4 e5 2. Nf3 Nf6 3. Nxe5 d6 4. Nf3 Nxe4 5. d4 Be7 6. Bd3 d5"] = "0-0";
        po["1. e4 e5 2. Nf3 Nf6 3. Nxe5 d6 4. Nf3 Nxe4 5. d4 Be7 6. Bd3 d5 7. 0-0 Nc6"] = "Nbd2";
        po["1. e4 e5 2. Nf3 Nf6 3. Nxe5 d6 4. Nf3 Nxe4 5. d4 Be7 6. Bd3 d5 7. 0-0 Nf6"] = "Re1";


        // C41 Philidor's defence -- WHITE
        po["1. e4 e5 2. Nf3 d6"] = "d4";
        po["1. e4 e5 2. Nf3 d6 3. d4 exd4"] = "Nxd4";
        po["1. e4 e5 2. Nf3 d6 3. d4 Nf6"] = "dxe5";
        po["1. e4 e5 2. Nf3 d6 3. d4 Nf6 4. dxe5 Nxe4"] = "Bc4";
        po["1. e4 e5 2. Nf3 d6 3. d4 Nd7"] = "Bc4";


        // C41 B00 King's pawn opening -- WHITE
        po["1. e4 d6 2. d4 Nf6"] = "Nc3";
        po["1. e4 d6 2. d4 Nf6 3. Nc3 g6"] = "f4";
        po["1. e4 d6 2. d4 Nf6 3. Nc3 e5"] = "Nf3";
        po["1. e4 d6 2. d4 Nf6 3. Nc3 c6"] = "f4";

        po["1. e4 d6 2. d4 g6"] = "Nc3";
        po["1. e4 d6 2. d4 g6 3. Nc3 Bg7"] = "Be3";


        // C60 Ruy Lopez (Spanish opening) -- WHITE
        po["1. e4 e5 2. Nf3 Nc6"] = "Bb5";
        po["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6"] = "Ba4";
        po["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6"] = "0-0";
        po["1. e4 e5 2. Nf3 Nc6 3. Bb5 g6"] = "c3";
        po["1. e4 e5 2. Nf3 Nc6 3. Bb5 f5"] = "Nc3";
        po["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nge7"] = "Nc3";
        po["1. e4 e5 2. Nf3 Nc6 3. Bb5 Bc5"] = "c3";
        po["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nd4"] = "Nxd4";

        po["1. e4 e5 2. Nf3 Nc6 3. Bb5 d6"] = "d4";
        po["1. e4 e5 2. Nf3 Nc6 3. Bb5 d6 4. d4 exd4"] = "Nxd4";
        po["1. e4 e5 2. Nf3 Nc6 3. Bb5 d6 4. d4 exd4 5. Nxd4 Bd7"] = "Nc3";
        po["1. e4 e5 2. Nf3 Nc6 3. Bb5 d6 4. d4 Bg4"] = "dxe5";
        po["1. e4 e5 2. Nf3 Nc6 3. Bb5 d6 4. d4 Bg4 5. dxe5 dxe5"] = "Qd5";
        po["1. e4 e5 2. Nf3 Nc6 3. Bb5 d6 4. d4 Bd7"] = "d5";
        po["1. e4 e5 2. Nf3 Nc6 3. Bb5 d6 4. d4 Bd7 5. d5 Nce7"] = "Bxd7+";
        po["1. e4 e5 2. Nf3 Nc6 3. Bb5 d6 4. d4 Bd7 5. d5 Nce7 6. Bxd7+ Qxd7"] = "c4";
        po["1. e4 e5 2. Nf3 Nc6 3. Bb5 d6 4. d4 Bd7 5. d5 Nce7 6. Bxd7+ Qxd7 7. c4 Ng6"] = "Nc3";
        po["1. e4 e5 2. Nf3 Nc6 3. Bb5 d6 4. d4 Bd7 5. d5 Nce7 6. Bxd7+ Qxd7 7. c4 Ng6 8. Nc3 Be7"] = "h4";
        po["1. e4 e5 2. Nf3 Nc6 3. Bb5 d6 4. d4 Bd7 5. d5 Nce7 6. Bxd7+ Qxd7 7. c4 Ng6 8. Nc3 Nf6"] = "Bg5";
        po["1. e4 e5 2. Nf3 Nc6 3. Bb5 d6 4. d4 Bd7 5. d5 Nce7 6. Bxd7+ Qxd7 7. c4 Ng6 8. Nc3 Nf6 9. Bg5 Be7"] = "Bxf6";
        po["1. e4 e5 2. Nf3 Nc6 3. Bb5 d6 4. d4 Bd7 5. d5 Nce7 6. Bxd7+ Qxd7 7. c4 Ng6 8. Nc3 Nf6 9. Bg5 Be7 10. Bxf6 Bxf6"] = "g3";

        po["1. e4 e5 2. Nf3 Nc6 3. Bb5 Bd6"] = "0-0";

        po["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nd4 4. Nxd4 exd4"] = "0-0";
        po["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nd4 4. Nxd4 exd4 5. 0-0 c6"] = "Bc4";
        po["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nd4 4. Nxd4 exd4 5. 0-0 c6 6. Bc4 Nf6"] = "d3";
        po["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nd4 4. Nxd4 exd4 5. 0-0 c6 6. Bc4 Nf6 7. d3 d5"] = "exd5";
        po["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nd4 4. Nxd4 exd4 5. 0-0 c6 6. Bc4 Nf6 7. d3 d5 8. exd5 Nxd5"] = "Re1+";


        // C70 Ruy Lopez -- WHITE
        po["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nf6"] = "0-0";
        po["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nf6 5. 0-0 Bc5"] = "c3";
        po["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nf6 5. 0-0 d6"] = "d4";
        po["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nf6 5. 0-0 Be7"] = "Re1";
        po["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nf6 5. 0-0 a6"] = "Bxc6";

        po["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nf6 5. 0-0 b5"] = "Bb3";
        po["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nf6 5. 0-0 b5 6. Bb3 Bb7"] = "d3";
        po["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nf6 5. 0-0 b5 6. Bb3 Be7"] = "d4";

        po["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 d6"] = "0-0";
        po["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nge7"] = "c3";
        po["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 b5"] = "Bb3";

        po["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nf6 5. 0-0 Nxe4"] = "d4";
        po["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nf6 5. 0-0 Nxe4 6. d4 exd4"] = "Re1";
        po["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nf6 5. 0-0 Nxe4 6. d4 b5"] = "Bb3";
        po["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nf6 5. 0-0 Nxe4 6. d4 b5 7. Bb3 d5"] = "dxe5";


        // B27 Sicilian defence -- WHITE
        po["1. e4 c5 2. Nf3 d6"] = "d4";
        po["1. e4 c5 2. Nf3 d6 3. d4 Nf6"] = "Nc3";
        po["1. e4 c5 2. Nf3 d6 3. d4 cxd4"] = "Nxd4";
        po["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 Nf6"] = "Nc3";
        po["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 Nc6"] = "c4";
        po["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 a6"] = "c4";
        po["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 e6"] = "c4";
        po["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 e5"] = "Bb5+";
        po["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 g6"] = "c4";

        po["1. e4 c5 2. Nf3 e6"] = "d4";
        po["1. e4 c5 2. Nf3 g6"] = "d4";
        po["1. e4 c5 2. Nf3 a6"] = "c3";
        po["1. e4 c5 2. Nf3 Nf6"] = "e5";
        po["1. e4 c5 2. Nf3 Nf6 3. e5 Nd5"] = "Nc3";


        // B32 Sicilian defence -- WHITE
        po["1. e4 c5 2. Nf3 Nc6"] = "d4";
        po["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4"] = "Nxd4";
        po["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 g6"] = "c4";
        po["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 e5"] = "Nb5";
        po["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 e6"] = "Nc3";
        po["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 Qc7"] = "Nc3";
        po["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 Qb6"] = "Nb3";
        po["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 d5"] = "exd5";

        po["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 Nf6"] = "Nc3";
        po["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 e6"] = "Nxc6";
        po["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 e6 6. Nxc6 bxc6"] = "e5";
        po["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 e5"] = "Ndb5";
        po["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 e5 6. Ndb5 a6"] = "Nd6+";
        po["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 e5 6. Ndb5 d6"] = "Bg5";
        po["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 d5"] = "Bb5";


        // A01 Nimzovich-Larsen attack, modern variation -- BLACK
        po["1. b3 e5 2. e3"] = "d5";
        po["1. b3 e5 2. Bb2"] = "Nc6";
        po["1. b3 e5 2. Bb2 Nc6 3. e3"] = "Nf6";
        po["1. b3 e5 2. Bb2 Nc6 3. e3 Nf6 4. c4"] = "d5";
        po["1. b3 e5 2. Bb2 Nc6 3. c4"] = "Nf6";
        po["1. b3 e5 2. Bb2 Nc6 3. c4 Nf6 4. e3"] = "d5";


        // A15 English, 1...Nf6 (Anglo-Indian defense) -- BLACK
        po["1. c4 Nf6 2. Nf3"] = "e6";
        po["1. c4 Nf6 2. g3"] = "e5";
        po["1. c4 Nf6 2. g3 e5 3. Bg2"] = "d5";
        po["1. c4 Nf6 2. d4"] = "e6";
        po["1. c4 Nf6 2. b3"] = "g6";

        po["1. c4 Nf6 2. Nc3"] = "e5";
        po["1. c4 Nf6 2. Nc3 e5 3. Nf3"] = "Nc6";
        po["1. c4 Nf6 2. Nc3 e5 3. Nf3 Nc6 4. e3"] = "Bb4";
        po["1. c4 Nf6 2. Nc3 e5 3. Nf3 Nc6 4. g3"] = "d5";
        po["1. c4 Nf6 2. Nc3 e5 3. Nf3 Nc6 4. g3 d5 5. d4"] = "exd4";
        po["1. c4 Nf6 2. Nc3 e5 3. Nf3 Nc6 4. g3 d5 5. d4 exd4 6. Nxd4"] = "dxc4";
        po["1. c4 Nf6 2. Nc3 e5 3. Nf3 Nc6 4. g3 d5 5. Bg2"] = "d4";
        po["1. c4 Nf6 2. Nc3 e5 3. Nf3 Nc6 4. g3 d5 5. cxd5"] = "Nxd5";
        po["1. c4 Nf6 2. Nc3 e5 3. Nf3 Nc6 4. g3 d5 5. cxd5 Nxd5 6. d3"] = "Bb4";
        po["1. c4 Nf6 2. Nc3 e5 3. Nf3 Nc6 4. g3 d5 5. cxd5 Nxd5 6. Bg2"] = "Nb6";

        po["1. c4 Nf6 2. Nc3 e5 3. g3"] = "Bb4";
        po["1. c4 Nf6 2. Nc3 e5 3. e3"] = "Bb4";
        po["1. c4 Nf6 2. Nc3 e5 3. d3"] = "Bb4";
        po["1. c4 Nf6 2. Nc3 e5 3. a3"] = "c6";
        po["1. c4 Nf6 2. Nc3 e5 3. a3 c6 4. Nf3"] = "e4";
        po["1. c4 Nf6 2. Nc3 e5 3. a3 c6 4. d4"] = "exd4";
        po["1. c4 Nf6 2. Nc3 e5 3. a3 c6 4. d4 exd4 5. Qxd4"] = "d5";
        po["1. c4 Nf6 2. Nc3 e5 3. a3 c6 4. e3"] = "d5";
        po["1. c4 Nf6 2. Nc3 e5 3. a3 c6 4. e3 d5 5. d4"] = "e4";


        // C45 Scotch, Schmidt variation -- BLACK
        po["1. e4 e5 2. Nf3 Nc6 3. d4"] = "exd4";
        po["1. e4 e5 2. Nf3 Nc6 3. d4 exd4 4. Bc4"] = "Nf6";
        po["1. e4 e5 2. Nf3 Nc6 3. d4 exd4 4. c3"] = "dxc3";
        po["1. e4 e5 2. Nf3 Nc6 3. d4 exd4 4. Nxd4"] = "Nf6";
        po["1. e4 e5 2. Nf3 Nc6 3. d4 exd4 4. Nxd4 Nf6 5. Nxc6"] = "bxc6";
        po["1. e4 e5 2. Nf3 Nc6 3. d4 exd4 4. Nxd4 Nf6 5. Nxc6 bxc6 6. e5"] = "Qe7";
        po["1. e4 e5 2. Nf3 Nc6 3. d4 exd4 4. Nxd4 Nf6 5. Nxc6 bxc6 6. Nc3"] = "Bb4";
        po["1. e4 e5 2. Nf3 Nc6 3. d4 exd4 4. Nxd4 Nf6 5. Nxc6 bxc6 6. Bd3"] = "d5";
        po["1. e4 e5 2. Nf3 Nc6 3. d4 exd4 4. Nxd4 Nf6 5. Nc3"] = "Bb4";
        po["1. e4 e5 2. Nf3 Nc6 3. d4 exd4 4. Nxd4 Nf6 5. Nc3 Bb4 6. Bd3"] = "0-0";


        // C21 Centre game -- BLACK
        po["1. e4 e5 2. d4"] = "exd4";
        po["1. e4 e5 2. d4 exd4 3. Qxd4"] = "Nc6";
        po["1. e4 e5 2. d4 exd4 3. c3"] = "dxc3";
        po["1. e4 e5 2. d4 exd4 3. c3 dxc3 4. Bc4"] = "cxb2";
        po["1. e4 e5 2. d4 exd4 3. c3 dxc3 4. Bc4 cxb2 5. Bxb2"] = "Bb4+";
        po["1. e4 e5 2. d4 exd4 3. c3 dxc3 4. Bc4 cxb2 5. Bxb2 Bb4+ 6. Bc3"] = "Bxc3+";
        po["1. e4 e5 2. d4 exd4 3. c3 dxc3 4. Bc4 cxb2 5. Bxb2 Bb4+ 6. Bc3 Bxc3+ 7. Nxc3"] = "Nc6";
        po["1. e4 e5 2. d4 exd4 3. c3 dxc3 4. Bc4 cxb2 5. Bxb2 Bb4+ 6. Nc3"] = "Nf6";
        po["1. e4 e5 2. d4 exd4 3. c3 dxc3 4. Bc4 cxb2 5. Bxb2 Bb4+ 6. Nd2"] = "Nf6";

        po["1. e4 e5 2. d4 exd4 3. c3 dxc3 4. Nxc3"] = "Bc5";
        po["1. e4 e5 2. d4 exd4 3. Bc4"] = "Nf6";
        po["1. e4 e5 2. d4 exd4 3. Nf3"] = "Nc6";
        po["1. e4 e5 2. d4 exd4 3. Nf3 Nc6 4. Nxd4"] = "Nf6";
        po["1. e4 e5 2. d4 exd4 3. Nf3 Nc6 4. Nxd4 Nf6 5. Nc3"] = "Bb4";
        po["1. e4 e5 2. d4 exd4 3. Nf3 Nc6 4. Nxd4 Nf6 5. Nxc6"] = "bxc6";


        // C00 French defence -- WHITE
        po["1. e4 e6 2. d4 d5"] = "Nc3";
        po["1. e4 e6 2. d4 d5 3. Nc3 Bb4"] = "exd5";
        po["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. exd5 exd5"] = "Bd3";
        po["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. exd5 Qxd5"] = "Nf3";
        po["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. exd5 Bxc3+"] = "bxc3";
        po["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. exd5 Bxc3+ 5. bxc3 exd5"] = "Bb5+";
        po["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. exd5 Bxc3+ 5. bxc3 exd5 6. Bb5+ c6"] = "Bd3";
        po["1. e4 e6 2. d4 d5 3. Nc3 Nf6"] = "Bg5";
        po["1. e4 e6 2. d4 d5 3. Nc3 Nf6 4. Bg5 Be7"] = "e5";
        po["1. e4 e6 2. d4 d5 3. Nc3 Nf6 4. Bg5 Be7 5. e5 Nfd7"] = "Bxe7";
        po["1. e4 e6 2. d4 d5 3. Nc3 Nf6 4. Bg5 Be7 5. e5 Nfd7 6. Bxe7 Qxe7"] = "f4";
        po["1. e4 e6 2. d4 d5 3. Nc3 Nf6 4. Bg5 Be7 5. e5 Nfd7 6. Bxe7 Qxe7 7. f4 0-0"] = "Nf3";
        po["1. e4 e6 2. d4 d5 3. Nc3 Nf6 4. Bg5 Be7 5. e5 Nfd7 6. Bxe7 Qxe7 7. f4 a6"] = "Qg5";
        po["1. e4 e6 2. d4 d5 3. Nc3 Nf6 4. Bg5 Be7 5. e5 Nfd7 6. Bxe7 Qxe7 7. f4 a6 8. Qg5 f6"] = "Nf3";
        po["1. e4 e6 2. d4 d5 3. Nc3 Nf6 4. Bg5 Be7 5. e5 Nfd7 6. Bxe7 Qxe7 7. f4 a6 8. Qg5 0-0"] = "Bd3";

        po["1. e4 e6 2. d4 d5 3. Nc3 dxe4"] = "Nxe4";
        po["1. e4 e6 2. d4 d5 3. Nc3 dxe4 4. Nxe4 Nd7"] = "Nf3";
        po["1. e4 e6 2. d4 d5 3. Nc3 dxe4 4. Nxe4 Bd7"] = "Nf3";
        po["1. e4 e6 2. d4 d5 3. Nc3 dxe4 4. Nxe4 Be7"] = "Nf3";
        po["1. e4 e6 2. d4 d5 3. Nc3 dxe4 4. Nxe4 Qd5"] = "Bd3";
        po["1. e4 e6 2. d4 d5 3. Nc3 dxe4 4. Nxe4 Nf6"] = "Nxf6+";
        po["1. e4 e6 2. d4 d5 3. Nc3 dxe4 4. Nxe4 Nf6 5. Nxf6+ gxf6"] = "Be3";
        po["1. e4 e6 2. d4 d5 3. Nc3 dxe4 4. Nxe4 Nf6 5. Nxf6+ Qxf6"] = "Nf3";
        po["1. e4 e6 2. d4 d5 3. Nc3 dxe4 4. Nxe4 Nf6 5. Nxf6+ Qxf6 6. Nf3 h6"] = "Bd3";
        po["1. e4 e6 2. d4 d5 3. Nc3 dxe4 4. Nxe4 Nf6 5. Nxf6+ Qxf6 6. Nf3 Bd6"] = "Bd3";
        po["1. e4 e6 2. d4 d5 3. Nc3 dxe4 4. Nxe4 Nf6 5. Nxf6+ Qxf6 6. Nf3 Nc6"] = "Bd3";

        po["1. e4 e6 2. d4 d5 3. Nc3 Nc6"] = "e5";
        po["1. e4 e6 2. d4 d5 3. Nc3 Be7"] = "Bd3";
        po["1. e4 e6 2. d4 d5 3. Nc3 c5"] = "exd5";
        po["1. e4 e6 2. d4 d5 3. Nc3 c5 4. exd5 cxd4"] = "Bb5+";
        po["1. e4 e6 2. d4 d5 3. Nc3 c5 4. exd5 exd5"] = "Bb5+";


        po["1. e4 e6 2. d4 c5"] = "d5";

        po["1. e4 e6 2. d4 b6"] = "Bd3";
        po["1. e4 e6 2. d4 b6 3. Bd3 Bg7"] = "Nf3";
        po["1. e4 e6 2. d4 b6 3. Bd3 Bg7 4. Nf3 c5"] = "c3";
        po["1. e4 e6 2. d4 b6 3. Bd3 Bg7 4. Nf3 d6"] = "0-0";
        po["1. e4 e6 2. d4 b6 3. Bd3 Bg7 4. Nf3 g6"] = "Bg5";
        po["1. e4 e6 2. d4 b6 3. Bd3 Bg7 4. Nf3 d5"] = "exd5";
        po["1. e4 e6 2. d4 b6 3. Bd3 Bg7 4. Nf3 Nf6"] = "e5";


        // A45 Queen's pawn game -- BLACK
        po["1. d4 Nf6 2. c4"] = "e6";
        po["1. d4 Nf6 2. Nf3"] = "e6";
        po["1. d4 Nf6 2. Bg5"] = "Ne4";
        po["1. d4 Nf6 2. Bf4"] = "e6";
        po["1. d4 Nf6 2. Nc3"] = "d5";
        po["1. d4 Nf6 2. g3"] = "d5";
        po["1. d4 Nf6 2. g3 d5 3. Bg2"] = "c5";
        po["1. d4 Nf6 2. e3"] = "e6";

        po["1. d4 Nf6 2. f4"] = "d5";
        po["1. d4 Nf6 2. f4 d5 3. e3"] = "c5";
        po["1. d4 Nf6 2. f4 d5 3. Nf3"] = "Bf5";


        // E20 Nimzo-Indian defence -- BLACK
        po["1. d4 Nf6 2. c4 e6 3. Nc3"] = "Bb4";
        po["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. e3"] = "0-0";
        po["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. Qc2"] = "0-0";
        po["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. Nf3"] = "c5";
        po["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. f3"] = "d5";
        po["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. g3"] = "c5";

        po["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. Bg5"] = "c5";
        po["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. Bg5 c5 5. a3"] = "Bxc3+";
        po["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. Bg5 c5 5. a3 Bxc3+ 6. bxc3"] = "Qa5";
        po["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. Bg5 c5 5. Nf3"] = "h6";
        po["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. Bg5 c5 5. Nf3 h6 6. Bh4"] = "g5";
        po["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. Bg5 c5 5. Nf3 h6 6. Bh4 g5 7. Bg3"] = "g4";
        po["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. Bg5 c5 5. Nf3 h6 6. Bf4"] = "cxd4";
        po["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. Bg5 c5 5. Nf3 h6 6. Bf4 cxd4 7. Nxd4"] = "0-0";
        po["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. Bg5 c5 5. Nf3 h6 6. Bf4 cxd4 7. Qxd4"] = "d6";
        po["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. Bg5 c5 5. Nf3 h6 6. Bxf6"] = "Qxf6";
        po["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. Bg5 c5 5. d5"] = "h6";
        po["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. Bg5 c5 5. d5 h6 6. Bh4"] = "b6";
        po["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. Bg5 c5 5. d5 h6 6. Bf4"] = "0-0";
        po["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. Bg5 c5 5. d5 h6 6. Bxf6"] = "Qxf6";
        po["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. Bg5 c5 5. Rc1"] = "h6";
        po["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. Bg5 c5 5. Rc1 h6 6. Bh4"] = "cxd4";
        po["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. Bg5 c5 5. Rc1 h6 6. Bf4"] = "cxd4";
        po["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. Bg5 c5 5. Rc1 h6 6. Bxf6"] = "Qxf6";
        po["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. Bg5 c5 5. dxc5"] = "Na6";

        po["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. a3"] = "Bxc3+";
        po["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. a3 Bxc3+ 5. bxc3"] = "c5";
        po["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. Qb3"] = "c5";
        po["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. Bd2"] = "0-0";
        po["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. d5"] = "Bxc3+";
        po["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. d5 Bxc3+ 5. bxc3"] = "d6";


        // E12 Queen's Indian defence -- BLACK
        po["1. d4 Nf6 2. c4 e6 3. Nf3"] = "b6";
        po["1. d4 Nf6 2. c4 e6 3. Nf3 b6 4. g3"] = "Bb7";
        po["1. d4 Nf6 2. c4 e6 3. Nf3 b6 4. g3 Bb7 5. Bg2"] = "Bb4+";
        po["1. d4 Nf6 2. c4 e6 3. Nf3 b6 4. a3"] = "Bb7";
        po["1. d4 Nf6 2. c4 e6 3. Nf3 b6 4. Nc3"] = "Bb4";
        po["1. d4 Nf6 2. c4 e6 3. Nf3 b6 4. e3"] = "Bb7";
        po["1. d4 Nf6 2. c4 e6 3. Nf3 b6 4. Bf4"] = "Bb7";
        po["1. d4 Nf6 2. c4 e6 3. Nf3 b6 4. Bg5"] = "Bb7";
        po["1. d4 Nf6 2. c4 e6 3. Nf3 b6 4. e3"] = "Bb7";


        // A45 Trompovsky attack (Ruth, Opovcensky opening) -- BLACK
        po["1. d4 Nf6 2. Bg5 Ne4 3. Bh4"] = "g5";
        po["1. d4 Nf6 2. Bg5 Ne4 3. Bh4 g5 4. f3"] = "c5";
        po["1. d4 Nf6 2. Bg5 Ne4 3. Bh4 g5 4. Bg3"] = "c5";
        po["1. d4 Nf6 2. Bg5 Ne4 3. Bh4 g5 4. Bg3 c5 5. dxc5"] = "Bg7";
        po["1. d4 Nf6 2. Bg5 Ne4 3. Bh4 g5 4. Bg3 c5 5. e3"] = "Nc6";
        po["1. d4 Nf6 2. Bg5 Ne4 3. Bh4 g5 4. Bg3 c5 5. c3"] = "Qb6";
        po["1. d4 Nf6 2. Bg5 Ne4 3. Bh4 g5 4. Bg3 c5 5. Nd2"] = "Nxg3";
        po["1. d4 Nf6 2. Bg5 Ne4 3. Bh4 g5 4. Bg3 c5 5. Nd2 Nxg3 6. hxg3"] = "cxd4";
        po["1. d4 Nf6 2. Bg5 Ne4 3. Bh4 g5 4. Bg3 c5 5. Nd2 Nxg3 6. fxg3"] = "cxd4";

        po["1. d4 Nf6 2. Bg5 Ne4 3. Bf4"] = "c5";
        po["1. d4 Nf6 2. Bg5 Ne4 3. Bf4 c5 4. f3"] = "Qa5+";
        po["1. d4 Nf6 2. Bg5 Ne4 3. Bf4 c5 4. d5"] = "Qb6";
        po["1. d4 Nf6 2. Bg5 Ne4 3. Bf4 c5 4. dxc5"] = "d5";
        po["1. d4 Nf6 2. Bg5 Ne4 3. Bf4 c5 4. e3"] = "Qb6";
        po["1. d4 Nf6 2. Bg5 Ne4 3. Bf4 c5 4. Nd2"] = "Nxd2";
        po["1. d4 Nf6 2. Bg5 Ne4 3. Bf4 c5 4. Nd2 Nxd2 5. Bxd2"] = "cxd4";
        po["1. d4 Nf6 2. Bg5 Ne4 3. Bf4 c5 4. Nd2 Nxd2 5. Qxd2"] = "cxd4";


        // C55 Two knights defence -- BLACK
        po["1. e4 e5 2. Nf3"] = "Nc6";
        po["1. e4 e5 2. Nf3 Nc6 3. Bc4"] = "Nf6";
        po["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. d3"] = "Bc5";
        po["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Ng5"] = "d5";
        po["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. d4"] = "exd4";
        po["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Nc3"] = "Nxe4";


        // C46 Four knights game -- BLACK
        po["1. e4 e5 2. Nf3 Nc6 3. Nc3"] = "Nf6";
        po["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. Bc4"] = "Nxe4";
        po["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. Bb4"] = "Nd4";

        po["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. Bb5 Nd4 5. Ba4"] = "c6";
        po["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. Bb5 Nd4 5. Nxd4"] = "exd4";
        po["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. Bb5 Nd4 5. Nxd4 exd4 6. e5"] = "dxc3";
        po["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. Bb5 Nd4 5. Nxd4 exd4 6. e5 dxc3 7. exf6"] = "Qxf6";
        po["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. Bb5 Nd4 5. Nxd4 exd4 6. e5 dxc3 7. exf6 Qxf6 8. dxc3"] = "Bc5";
        po["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. Bb5 Nd4 5. Nxd4 exd4 6. e5 dxc3 7. exf6 Qxf6 8. dxc3 Bc5 9. Qe2+"] = "Qe7";
        po["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. Bb5 Nd4 5. Nxd4 exd4 6. e5 dxc3 7.  exf6 Qxf6 8. dxc3 Bc5 9. 0-0"] = "0-0";
        po["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. Bb5 Nd4 5. Nxd4 exd4 6. Ne2"] = "c6";
        po["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. Bb5 Nd4 5. Nxd4 exd4 6. Nd5"] = "Nxd5";
        po["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. Bb5 Nd4 5. Nxd4 exd4 6. Nd5 Nxd5 7. exd5"] = "Qe7+";
        po["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. Bb5 Nd4 5. Bc4"] = "Bc5";
        po["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. Bb5 Nd4 5. Bc4 Bc5 6. Nxe5"] = "Qe7";


        // C58 Fried Liver Attack -- BLACK
        po["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Ng5"] = "d5";
        po["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Ng5 d5 5. Nxf7"] = "Kxf7";
        po["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Ng5 d5 5. Nxf7 Kxf7 6. exd5"] = "b5";

        po["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Ng5 d5 5. exd5"] = "Na5";
        po["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Ng5 d5 5. exd5 Na5 6. Bb5+"] = "c6";
        po["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Ng5 d5 5. exd5 Na5 6. Bb5+ c6 7. dxc6"] = "bxc6";
        po["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Ng5 d5 5. exd5 Na5 6. Bb5+ c6 7. dxc6 bxc6 8. Bd3"] = "Nd5";
        po["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Ng5 d5 5. exd5 Na5 6. Bb5+ c6 7. dxc6 bxc6 8. Be2"] = "h6";
        po["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Ng5 d5 5. exd5 Na5 6. Bb5+ c6 7. dxc6 bxc6 8. Ba4"] = "h6";
        po["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Ng5 d5 5. exd5 Na5 6. Bb5+ c6 7. dxc6 bxc6 8. Qf3"] = "Be7";

        po["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Ng5 d5 5. exd5 Na5 6. Bb5+ c6 7. dxc6 bxc6 8. Bd3 Nd5 9. Nxh7"] = "Nf4";
        po["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Ng5 d5 5. exd5 Na5 6. Bb5+ c6 7. dxc6 bxc6 8. Bd3 Nd5 9. Nxh7 Nf4 10. Nxf8"] = "Nxg2+";
        po["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Ng5 d5 5. exd5 Na5 6. Bb5+ c6 7. dxc6 bxc6 8. Bd3 Nd5 9. Nxh7 Nf4 10. Nxf8 Nxg2+ 11. Kf1"] = "Bh3";
        po["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Ng5 d5 5. exd5 Na5 6. Bb5+ c6 7. dxc6 bxc6 8. Bd3 Nd5 9. Nxh7 Nf4 10. Nxf8 Nxg2+ 11. Ke2"] = "Bg4+";
        po["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Ng5 d5 5. exd5 Na5 6. Bb5+ c6 7. dxc6 bxc6 8. Bd3 Nd5 9. Nxh7 Nf4 10. Nxf8 Nxg2+ 11. Ke2 Bg4+ 12. f3"] = "Nf4+";

        po["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Ng5 d5 5. exd5 Na5 6. Bb5+ c6 7. dxc6 bxc6 8. Bd3 Nd5 9. Nf3"] = "Bd6";
        po["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Ng5 d5 5. exd5 Na5 6. Bb5+ c6 7. dxc6 bxc6 8. Bd3 Nd5 9. h4"] = "Nf4";
        po["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Ng5 d5 5. exd5 Na5 6. Bb5+ c6 7. dxc6 bxc6 8. Be2 h6 9. Nf3"] = "e4";
        po["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Ng5 d5 5. exd5 Na5 6. Bb5+ c6 7. dxc6 bxc6 8. Ba4 h6 9. Nf3"] = "e4";
        po["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Ng5 d5 5. exd5 Na5 6. Bb5+ c6 7. dxc6 bxc6 8. Ba4 h6 9. Nf3 e4 10. Qe2"] = "Bc5";
        po["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Ng5 d5 5. exd5 Na5 6. Bb5+ c6 7. dxc6 bxc6 8. Ba4 h6 9. Nf3 e4 10. Ne5"] = "Qd4";

        po["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Ng5 d5 5. exd5 Na5 6. Bb5+ c6 7. dxc6 bxc6 8. Be2 h6 9. Nf3 e4 10. 0-0"] = "exf3";
        po["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Ng5 d5 5. exd5 Na5 6. Bb5+ c6 7. dxc6 bxc6 8. Be2 h6 9. Nf3 e4 10. 0-0 exf3 11. Bxf3"] = "Bd6";
        po["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Ng5 d5 5. exd5 Na5 6. Bb5+ c6 7. dxc6 bxc6 8. Be2 h6 9. Nf3 e4 10. 0-0 exf3 11. Bxf3 Bd6 12. Re1+"] = "Be6";


        // C65 Ruy Lopez, Berlin defence -- BLACK
        po["1. e4 e5 2. Nf3 Nc6 3. Bb5"] = "Nf6";

        po["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0"] = "Nxe4";
        po["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. Re1"] = "Nd6";
        po["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. Qe2"] = "Ng5";
        po["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. d4"] = "Nd6";
        po["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. d3"] = "Nd6";
        po["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. Bxc6"] = "dxc6";
        po["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. Bxc6 dxc6 6. Re1"] = "Nd6";
        po["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. Bxc6 dxc6 6. Re1 Nd6 7. Nxe5"] = "Be7";
        po["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. Bxc6 dxc6 6. Re1 Nd6 7. Rxe5"] = "Be7";
        po["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4 5. Bxc6 dxc6 6. Nxe5"] = "Qf6";

        po["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. d3"] = "Bc5";
        po["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. Qe2"] = "Bc5";

        po["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. Nc3"] = "Nd4";
        po["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. Nc3 Nd4 5. Nxd4"] = "exd4";
        po["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. Nc3 Nd4 5. Nxe5"] = "Qe7";
        po["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. Nc3 Nd4 5. Bc4"] = "Bc5";
        po["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. Nc3 Nd4 5. 0-0"] = "c6";
        po["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. Nc3 Nd4 5. Ba4"] = "c6";
        po["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. Nc3 Nd4 5. Ba4 c6 6. d3"] = "Bc5";
        po["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. Nc3 Nd4 5. Ba4 c6 6. Nxe5"] = "d6";
        po["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. Nc3 Nd4 5. Ba4 c6 6. 0-0"] = "a5";


        // C46 Four knights game -- BLACK
        po["1. e4 e5 2. Nc3"] = "Nc6";
        po["1. e4 e5 2. Nc3 Nc6 3. Nf3"] = "Nf6";
        po["1. e4 e5 2. Nc3 Nc6 3. Nf3 Nf6 4. Bb5"] = "Nd4";
        po["1. e4 e5 2. Nc3 Nc6 3. Nf3 Nf6 4. Bb5 Nd4 5. Nxd4"] = "exd4";
        po["1. e4 e5 2. Nc3 Nc6 3. Nf3 Nf6 4. Bb5 Nd4 5. Nxd4 exd4 6. e5"] = "dxc3";
        po["1. e4 e5 2. Nc3 Nc6 3. Nf3 Nf6 4. Bb5 Nd4 5. Nxd4 exd4 6. e5 dxc3 7. exf6"] = "Qxf6";
        po["1. e4 e5 2. Nc3 Nc6 3. Nf3 Nf6 4. Bb5 Nd4 5. Nxd4 exd4 6. e5 dxc3 7. exf6 Qxf6 8. dxc3"] = "Bc5";
        po["1. e4 e5 2. Nc3 Nc6 3. Nf3 Nf6 4. Bb5 Nd4 5. Nxd4 exd4 6. e5 dxc3 7. exf6 Qxf6 8. dxc3 Bc5 9. Qe2+"] = "Qe7";
        po["1. e4 e5 2. Nc3 Nc6 3. Nf3 Nf6 4. Bb5 Nd4 5. Nxd4 exd4 6. e5 dxc3 7.  exf6 Qxf6 8. dxc3 Bc5 9. 0-0"] = "0-0";
        po["1. e4 e5 2. Nc3 Nc6 3. Nf3 Nf6 4. Bb5 Nd4 5. Nxd4 exd4 6. Ne2"] = "c6";
        po["1. e4 e5 2. Nc3 Nc6 3. Nf3 Nf6 4. Bb5 Nd4 5. Nxd4 exd4 6. Nd5"] = "Nxd5";
        po["1. e4 e5 2. Nc3 Nc6 3. Nf3 Nf6 4. Bb5 Nd4 5. Nxd4 exd4 6. Nd5 Nxd5 7. exd5"] = "Qe7+";
        po["1. e4 e5 2. Nc3 Nc6 3. Nf3 Nf6 4. Bb5 Nd4 5. Ba4"] = "c6";
        po["1. e4 e5 2. Nc3 Nc6 3. Nf3 Nf6 4. Bb5 Nd4 5. Bc4"] = "Bc5";
        po["1. e4 e5 2. Nc3 Nc6 3. Nf3 Nf6 4. Bb5 Nd4 5. Bc4 Bc5 6. Nxe5"] = "Qe7";

        po["1. e4 e5 2. Nc3 Nc6 3. Nf3 Nf6 4. d4"] = "exd4";
        po["1. e4 e5 2. Nc3 Nc6 3. Nf3 Nf6 4. g3"] = "Bc5";
        po["1. e4 e5 2. Nc3 Nc6 3. Nf3 Nf6 4. a3"] = "d5";
        po["1. e4 e5 2. Nc3 Nc6 3. Nf3 Nf6 4. Be2"] = "d5";
        po["1. e4 e5 2. Nc3 Nc6 3. Nf3 Nf6 4. Bc4"] = "Nxe4";
        po["1. e4 e5 2. Nc3 Nc6 3. Nf3 Nf6 4. h3"] = "Bb4";


        po["1. e4 e5 2. Nc3 Nc6 3. g3"] = "Bc5";
        po["1. e4 e5 2. Nc3 Nc6 3. Bc4"] = "Nf6";
        po["1. e4 e5 2. Nc3 Nc6 3. f4"] = "exf4";
        po["1. e4 e5 2. Nc3 Nc6 3. f4 exf4 4. Nf3"] = "g5";
        po["1. e4 e5 2. Nc3 Nc6 3. f4 exf4 4. Nf3 g5 5. d4"] = "g4";
        po["1. e4 e5 2. Nc3 Nc6 3. f4 exf4 4. Nf3 g5 5. h4"] = "g4";
        po["1. e4 e5 2. Nc3 Nc6 3. f4 exf4 4. Nf3 g5 5. h3"] = "h6";
        po["1. e4 e5 2. Nc3 Nc6 3. f4 exf4 4. Nf3 g5 5. Bc4"] = "g4";
        po["1. e4 e5 2. Nc3 Nc6 3. f4 exf4 4. d4"] = "Qh4+";
        po["1. e4 e5 2. Nc3 Nc6 3. f4 exf4 4. d4 Qh4+ 5. Ke2"] = "b6";


        // A46 Queen's pawn game -- BLACK
        po["1. d4 Nf6 2. Nf3"] = "e6";
        po["1. d4 Nf6 2. Nf3 e6 3. c4"] = "d5";
        po["1. d4 Nf6 2. Nf3 e6 3. g3"] = "c5";
        po["1. d4 Nf6 2. Nf3 e6 3. e3"] = "d5";
        po["1. d4 Nf6 2. Nf3 e6 3. Bg5"] = "c5";
        po["1. d4 Nf6 2. Nf3 e6 3. Bf4"] = "d5";


        // A05 Reti opening -- BLACK
        po["1. Nf3 Nf6 2. d3"] = "d5";
        po["1. Nf3 Nf6 2. d3 d5 3. Nbd2"] = "c5";
        po["1. Nf3 Nf6 2. d3 d5 3. Bg5"] = "c5";
        po["1. Nf3 Nf6 2. d3 d5 3. Bf4"] = "c5";
        po["1. Nf3 Nf6 2. d3 d5 3. b3"] = "g6";
        po["1. Nf3 Nf6 2. d3 d5 3. g3"] = "c5";
        po["1. Nf3 Nf6 2. d3 d5 3. g3 c5 4. Bg2"] = "Nc6";


        // A15 English opening -- BLACK
        po["1. Nf3 Nf6 2. c4"] = "e6";
        po["1. Nf3 Nf6 2. c4 e6 3. g3"] = "d5";
        po["1. Nf3 Nf6 2. c4 e6 3. g3 d5 4. Bg2"] = "d4";
        po["1. Nf3 Nf6 2. c4 e6 3. g3 d5 4. Nc3"] = "d4";
        po["1. Nf3 Nf6 2. c4 e6 3. Nc3"] = "Bb4";
        po["1. Nf3 Nf6 2. c4 e6 3. d4"] = "d5";
        po["1. Nf3 Nf6 2. c4 e6 3. b3"] = "d5";


        // B12 Caro-Kann defence -- WHITE
        po["1. e4 c6 2. d4 g6"] = "Nc3";
        po["1. e4 c6 2. d4 g6 3. Nc3 Bg7"] = "Nf3";
        po["1. e4 c6 2. d4 g6 3. Nc3 d5"] = "Nf3";
        po["1. e4 c6 2. d4 d5"] = "Nc3";
        po["1. e4 c6 2. d4 d5 3. Nc3 dxe4"] = "Nxe4";
        po["1. e4 c6 2. d4 d5 3. Nc3 dxe4 4. Nxe4 Nf6"] = "Nxf6+";
        po["1. e4 c6 2. d4 d5 3. Nc3 dxe4 4. Nxe4 Bf5"] = "Ng3";
        po["1. e4 c6 2. d4 d5 3. Nc3 dxe4 4. Nxe4 Bf5 5. Ng3 Bg6"] = "Nf3";



        // Rare -- WHITE
        po["1. e4 b6"] = "d4";
        po["1. e4 b6 2. d4 Nf6"] = "e5";
        po["1. e4 b6 2. d4 Nf6 3. e5 Ne4"] = "Qe2";
        po["1. e4 b6 2. d4 Nf6 3. e5 Nd5"] = "c4";
        po["1. e4 b6 2. d4 Nf6 3. e5 Ng8"] = "Nf3";
        po["1. e4 b6 2. d4 Nf6 3. e5 Ng8 4. Nf3 Bb7"] = "Bd3";
        po["1. e4 b6 2. d4 Nf6 3. e5 Ng8 4. Nf3 e6"] = "Bd3";
        po["1. e4 b6 2. d4 e6"] = "Nf3";
        po["1. e4 b6 2. d4 e6 3. Nf3 Bb7"] = "Bd3";

        po["1. e4 b6 2. d4 Bb7"] = "Bd3";
        po["1. e4 b6 2. d4 Bb7 3. Bd3 Nf6"] = "Qe2";
        po["1. e4 b6 2. d4 Bb7 3. Bd3 e6"] = "Nf3";
        po["1. e4 b6 2. d4 Bb7 3. Bd3 g6"] = "Nf3";
        po["1. e4 b6 2. d4 Bb7 3. Bd3 g6 4. Nf3 Bg7"] = "c4";
        po["1. e4 b6 2. d4 Bb7 3. Bd3 g6 4. Nf3 Bg7 5. c4 e5"] = "d5";
        po["1. e4 b6 2. d4 Bb7 3. Bd3 g6 4. Nf3 Bg7 5. c4 e6"] = "Nc3";
        po["1. e4 b6 2. d4 Bb7 3. Bd3 g6 4. Nf3 Bg7 5. c4 d6"] = "Nc3";


        // Rare -- BLACK
        po["1. e4 e5 2. g3"] = "d5";
        po["1. e4 e5 2. g3 d5 3. Bg2"] = "dxe4";
        po["1. e4 e5 2. g3 d5 3. Bg2 dxe4 4. Nc3"] = "f5";
        po["1. e4 e5 2. g3 d5 3. Bg2 dxe4 4. Bxe4"] = "Nf6";
        po["1. e4 e5 2. g3 d5 3. Bg2 dxe4 4. Bxe4 Nf6 5. Bg2"] = "Nc6";
        po["1. e4 e5 2. g3 d5 3. exd5"] = "Qxd5";
        po["1. e4 e5 2. g3 d5 3. exd5 Qxd5 4. Nf3"] = "Bg4";
        po["1. e4 e5 2. g3 d5 3. exd5 Qxd5 4. Nf3 Bg4 5. Be2"] = "Nc6";
        po["1. e4 e5 2. g3 d5 3. exd5 Qxd5 4. Nf3 Bg4 5. Be2 Nc6 6. Nc3"] = "Qd7";
        po["1. e4 e5 2. g3 d5 3. exd5 Qxd5 4. Nf3 Bg4 5. Be2 Nc6 6. Nc3 Qd7 7. d4"] = "Bxf3";
        po["1. e4 e5 2. g3 d5 3. exd5 Qxd5 4. Nf3 Bg4 5. Be2 Nc6 6. Nc3 Qd7 7. d4 Bxf3 8. Bxf3"] = "exd4";
        po["1. e4 e5 2. g3 d5 3. exd5 Qxd5 4. Nf3 Bg4 5. Be2 Nc6 6. Nc3 Qd7 7. 0-0"] = "0-0-0";
        po["1. e4 e5 2. g3 d5 3. exd5 Qxd5 4. Nf3 Bg4 5. Be2 Nc6 6. Nc3 Qd7 7. 0-0 0-0-0 8. d3"] = "Nf6";
        po["1. e4 e5 2. g3 d5 3. exd5 Qxd5 4. Nf3 Bg4 5. Be2 Nc6 6. Nc3 Qd7 7. 0-0 0-0-0 8. a3"] = "f5";
        po["1. e4 e5 2. g3 d5 3. exd5 Qxd5 4. Nf3 Bg4 5. Be2 Nc6 6. Nc3 Qd7 7. 0-0 0-0-0 8. Qe1"] = "e4";
        po["1. e4 e5 2. g3 d5 3. exd5 Qxd5 4. Nf3 Bg4 5. Be2 Nc6 6. Nc3 Qd7 7. 0-0 0-0-0 8. Qe1 e4 9. Ng5"] = "Bxe2";
        po["1. e4 e5 2. g3 d5 3. exd5 Qxd5 4. Nf3 Bg4 5. Be2 Nc6 6. Nc3 Qd7 7. 0-0 0-0-0 8. Qe1 e4 9. Ng5 Bxe2 10. Qxe2"] = "h6";
        po["1. e4 e5 2. g3 d5 3. exd5 Qxd5 4. Nf3 Bg4 5. Be2 Nc6 6. Nc3 Qd7 7. 0-0 0-0-0 8. Qe1 e4 9. Ng5 Bxe2 10. Nxe2"] = "Qf5";
        po["1. e4 e5 2. g3 d5 3. exd5 Qxd5 4. Nf3 Bg4 5. Be2 Nc6 6. Nc3 Qd7 7. 0-0 0-0-0 8. Qe1 e4 9. Nxe4"] = "Re8";
        po["1. e4 e5 2. g3 d5 3. exd5 Qxd5 4. Nf3 Bg4 5. Be2 Nc6 6. Nc3 Qd7 7. 0-0 0-0-0 8. Qe1 e4 9. Nxe4 Re8 10. d3"] = "f5";




        // Use personal openings, instead of full book
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
