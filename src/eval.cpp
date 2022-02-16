// This file is part of Chess0, a computer chess program based on Winglet chess
// by Stef Luijten.
//
// Copyright (C) 2022 Claudio M. Camacho
//
// Chess0 is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Chess0 is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Foobar. If not, see <http://www.gnu.org/licenses/>.



// @file eval.cpp
//
// This file contains the necessary functions to evaluate the current board
// position (i.e., static evaluation) taking into account both material and
// position.
#include <iostream>
#include "definitions.h"
#include "functions.h"
#include "extglobals.h"
#include "board.h"



// Board::eval
//
// This is Chess0's evaluation function, including both material and positional
// evaluation.
int Board::eval()
{

    int score, square;
    int whitepawns, whiteknights, whitebishops, whiterooks, whitequeens;
    int blackpawns, blackknights, blackbishops, blackrooks, blackqueens;
    int whitekingsquare, blackkingsquare;
    int whitetotalmat, blacktotalmat;
    int whitetotal, blacktotal;
    bool endgame;
    Bitboard temp, whitepassedpawns, blackpassedpawns, allpieces;


    // 1. count material
    score = board.Material;


    // 2. check where kings and pieces are
    // 2.1 Kings
    whitekingsquare = firstOne(board.whiteKing);
    blackkingsquare = firstOne(board.blackKing);


    // 2.2 Pieces
    whitepawns = bitCnt(board.whitePawns);
    whiteknights = bitCnt(board.whiteKnights);
    whitebishops = bitCnt(board.whiteBishops);
    whiterooks = bitCnt(board.whiteRooks);
    whitequeens = bitCnt(board.whiteQueens);
    whitetotalmat = 3 * whiteknights + 3 * whitebishops + 5 * whiterooks + 10 * whitequeens;
    whitetotal = whitepawns + whiteknights + whitebishops + whiterooks + whitequeens;
    blackpawns = bitCnt(board.blackPawns);
    blackknights = bitCnt(board.blackKnights);
    blackbishops = bitCnt(board.blackBishops);
    blackrooks = bitCnt(board.blackRooks);
    blackqueens = bitCnt(board.blackQueens);
    blacktotalmat = 3 * blackknights + 3 * blackbishops + 5 * blackrooks + 10 * blackqueens;
    blacktotal = blackpawns + blackknights + blackbishops + blackrooks + blackqueens;
    allpieces = board.whitePawns | board.whiteKnights | board.whiteBishops |
                board.whiteRooks | board.whiteQueens | board.whiteKing |
                board.blackPawns | board.blackKnights | board.blackBishops |
                board.blackRooks | board.blackQueens | board.blackKing;


    // 3. check if we are at the endgame: anything less than a
    //                                    queen + rook (=15), excluding pawns,
    //                                    is considered endgame
    endgame = (whitetotalmat < 15 || blacktotalmat < 15);
   

    // 4. draw evaluation due to insufficient material
    if (!whitepawns && !blackpawns)
    {
        // 4.1 K-K
        if ((whitetotalmat == 0) && (blacktotalmat == 0)) 
        {
            if (board.nextMove)
                return -DRAWSCORE;
            else
                return DRAWSCORE;
        }


        // 4.2 KN-K
        if (((whitetotalmat == 3) && (whiteknights == 1) && (blacktotalmat == 0)) ||
                ((blacktotalmat == 3) && (blackknights == 1) && (whitetotalmat == 0))) 
        {
            if (board.nextMove)
                return -DRAWSCORE;
            else
                return DRAWSCORE;
        }


        // 4.3 KNN-K (not forced mate)
        if (((whitetotalmat == 6) && (whiteknights == 2) && (blacktotalmat == 0)) ||
                ((blacktotalmat == 6) && (blackknights == 2) && (whitetotalmat == 0))) 
        {
            if (board.nextMove)
                return -DRAWSCORE;
            else
                return DRAWSCORE;
        }


        // 4.4 KB-KB (all bishops on the same color squares)
        if ((whitebishops + blackbishops) > 0)
        {
            if ((whiteknights == 0) && (whiterooks == 0) && (whitequeens == 0) &&
                (blackknights == 0) && (blackrooks == 0) && (blackqueens == 0))
            {
                if (!((board.whiteBishops | board.blackBishops) & WHITE_SQUARES) ||
                        !((board.whiteBishops | board.blackBishops) & BLACK_SQUARES))
                {
                    if (board.nextMove)
                        return -DRAWSCORE;
                    else
                        return DRAWSCORE;
                }
            }
        }


        // 4.5 Kminor-Kminor
        if ((whitetotalmat == 3) && (blacktotalmat == 3))
        {
            if (board.nextMove)
                return -DRAWSCORE;
            else
                return DRAWSCORE;
        }


        // 4.6 KNN-Kminor
        if (((whitetotalmat == 6) && (whiteknights == 2) && (blacktotalmat == 3)) ||
            ((blacktotalmat == 6) && (blackknights == 2) && (whitetotalmat == 3)))
        {
            if (board.nextMove)
                return -DRAWSCORE;
            else
                return DRAWSCORE;
        }


        // 4.7 KBB-KB
        if (((whitetotalmat == 6) && (whitebishops == 2) && (blacktotalmat == 3)) ||
            ((blacktotalmat == 6) && (blackbishops == 2) && (whitetotalmat == 3)))
        {
            if (board.nextMove)
                return -DRAWSCORE;
            else
                return DRAWSCORE;
        }


        // 4.8 KBN-Kminor
        if (((whitetotalmat == 6) && (whitebishops == 1) && (blacktotalmat == 3)) ||
            ((blacktotalmat == 6) && (blackbishops == 1) && (whitetotalmat == 3)))
        {
            if (board.nextMove)
                return -DRAWSCORE;
            else
                return DRAWSCORE;
        }
    }


    // 5. evaluate material heuristics

    // 5.1 the winning side prefers to exchange pieces
    // (every exchange with unequal material adds 8 centipawns to the score)
    if (whitetotalmat + whitepawns > blacktotalmat + blackpawns)
        score +=  45 + 3 * whitetotal - 8 * blacktotal;
    else if (whitetotalmat + whitepawns < blacktotalmat + blackpawns)
        score += -45 - 3 * blacktotal + 8 * whitetotal;


    // 5.2 evaluate White pieces

    // 5.2.1 white pawns, including:
    //       - position on the board
    //       - distance from opponent king
    //       - distance from own king
    //       - passed, doubled, isolated or backward pawns
    whitepassedpawns = 0;
    temp = board.whitePawns;
    while (temp)
    {
        square = firstOne(temp);

        if (endgame)
        {
            score += PAWNPOS_W_EG[square];
        }
        else
        {
            score += PAWNPOS_W_MG[square];
        }

        score += PAWN_OPPONENT_DISTANCE[DISTANCE[square][blackkingsquare]];


        if (endgame)
        {
            score += PAWN_OWN_DISTANCE[DISTANCE[square][whitekingsquare]];
        }

        if (!(PASSED_WHITE[square] & board.blackPawns))
        {
            score += BONUS_PASSED_PAWN;

            // remember its location, we need it later when evaluating the white rooks
            whitepassedpawns ^= BITSET[square];
        }

        if ((board.whitePawns ^ BITSET[square]) & FILEMASK[square])
        {
            if (endgame)
            {
                score -= PENALTY_DOUBLED_PAWN_EG;
            }
            else
            {
                score -= PENALTY_DOUBLED_PAWN_MG;
            }
        }

        if (!(ISOLATED_WHITE[square] & board.whitePawns))
        {
            if (endgame)
            {
                score -= PENALTY_ISOLATED_PAWN_EG;
            }
            else
            {
                score -= PENALTY_ISOLATED_PAWN_MG;
            }
        }


        // if inot isolated, then it might be backward. Two conditions must be true:
        //  1) if the next square is controlled by an enemy pawn - we use the PAWN_ATTACKS Bitboards to check this
        //  2) if there are no pawns left that could defend this pawn
        else
        {
            if ((WHITE_PAWN_ATTACKS[square + 8] & board.blackPawns))
                if (!(BACKWARD_WHITE[square] & board.whitePawns))
                {
                    if (endgame)
                    {
                        score -= PENALTY_BACKWARD_PAWN_EG;
                    }
                    else
                    {
                        score -= PENALTY_BACKWARD_PAWN_MG;
                    }
                }
        }

        temp ^= BITSET[square];
    }


    // 5.2.2 white knights
    //       - position on the board
    //       - distance from opponent king
    temp = board.whiteKnights;
    while (temp)
    {
        square = firstOne(temp);

        if (endgame)
        {
            score += KNIGHTPOS_W_EG[square];
        }
        else
        {
            score += KNIGHTPOS_W_MG[square];
        }


        score += KNIGHT_DISTANCE[DISTANCE[square][blackkingsquare]];

        temp ^= BITSET[square];
    }


    // 5.2.3 white bishops
    //       - having the pair
    //       - position on the board
    //       - distance from opponent king
    if (board.whiteBishops)
        if ((board.whiteBishops & WHITE_SQUARES) && (board.whiteBishops & BLACK_SQUARES))
        {
            if (endgame)
            {
                score += BONUS_BISHOP_PAIR_EG;
            }
            else
            {
                score += BONUS_BISHOP_PAIR_MG;
            }
        }

    temp = board.whiteBishops;

    while (temp)
    {
        square = firstOne(temp);

        if (endgame)
        {
            score += BISHOPPOS_W_EG[square];
        }
        else
        {
            score += BISHOPPOS_W_MG[square];
        }

        score += BISHOP_DISTANCE[DISTANCE[square][blackkingsquare]];

        temp ^= BITSET[square];
    }


    // 5.2.4 white rooks
    //       - position on the board
    //       - distance from opponent king
    //       - behind a passed pawn
    //       - on semi-open file
    //       - on open file
    //       - on the 7th rank
    //       - two rooks connected on the 7th
    temp = board.whiteRooks;
    while (temp)
    {
        square = firstOne(temp);
        score += ROOKPOS_W[square];

        if (!board.castleWhite)
        {
            score += ROOK_DISTANCE[DISTANCE[square][blackkingsquare]];
        }

        // rook behind passed pawn
        if (FILEMASK[square] & whitepassedpawns)
            if ((unsigned int) square < lastOne(FILEMASK[square] & whitepassedpawns))
            {
                if (endgame)
                {
                    score += BONUS_ROOK_BEHIND_PASSED_PAWN_EG;
                }
                else
                {
                    score += BONUS_ROOK_BEHIND_PASSED_PAWN_MG;
                }
            }


        // rook on semi-open file
        if (bitCnt(FILEMASK[square] & (board.whitePawns | board.blackPawns)) == 1)
        {
            if (endgame)
                score += BONUS_ROOK_ON_SEMIOPEN_FILE_EG;
            else
                score += BONUS_ROOK_ON_SEMIOPEN_FILE_MG;
        }

        // rook on open file
        if (!(FILEMASK[square] & (board.whitePawns | board.blackPawns)))
        {
            if (endgame)
                score += BONUS_ROOK_ON_OPEN_FILE_EG;
            else
                score += BONUS_ROOK_ON_OPEN_FILE_MG;
        }

        temp ^= BITSET[square];
    }


    // 5.2.5 white queens
    //       - position on the board
    //       - distance from opponent king
    temp = board.whiteQueens;
    while (temp)
    {
        square = firstOne(temp);

        if (endgame)
        {
            score += QUEENPOS_W_EG[square];
        }
        else
        {
            score += QUEENPOS_W_MG[square];
        }

        score += QUEEN_DISTANCE[DISTANCE[square][blackkingsquare]];

        temp ^= BITSET[square];
    }


    // 5.2.6 white king
    //       - position on the board
    //       - proximity to the pawns
    //       - pawn shield (not in the endgame)
    if (endgame)
    {
        score += KINGPOS_W_EG[whitekingsquare];
    }
    else if (board.whiteKing & KINGCASTLED_MASK_W)
    {
        // basic bonus just because we're castled
        score += BONUS_KING_IS_CASTLED;

        score += KINGPOS_W_MG[whitekingsquare];

        // add pawn shield bonus if we're not in the endgame:
        // strong pawn shield bonus if the pawns are near the king:
        score += BONUS_PAWN_SHIELD_STRONG * bitCnt(KINGSHIELD_STRONG_W[whitekingsquare] & board.whitePawns);

        // weaker pawn shield bonus if the pawns are not so near the king:
        score += BONUS_PAWN_SHIELD_WEAK * bitCnt(KINGSHIELD_WEAK_W[whitekingsquare] & board.whitePawns);
    }

    // king on semi-open file
    if (bitCnt(FILEMASK[whitekingsquare] & (board.whitePawns | board.blackPawns)) == 1)
    {
        if ((FILES[whitekingsquare] <= 2) || (FILES[whitekingsquare] >= 7))
            score -= PENALTY_KING_ON_SEMIOPEN_ABGH;
        else
            score -= PENALTY_KING_ON_SEMIOPEN_CDEF;
    }

    // king on open file
    if (!(FILEMASK[whitekingsquare] & (board.whitePawns | board.blackPawns)))
    {
        if ((FILES[whitekingsquare] == 1) || (FILES[whitekingsquare] == 8))
            score -= PENALTY_KING_ON_OPEN_FILE_AH;
        else if ((FILES[whitekingsquare] == 2) || (FILES[whitekingsquare] == 7))
            score -= PENALTY_KING_ON_OPEN_FILE_BG;
        else
            score -= PENALTY_KING_ON_OPEN_FILE_CDEF;
    }



    // 5.3 evaluate black pieces

    // 5.3.1 black pawns
    //       - position on the board
    //       - distance from opponent king
    //       - distance from own king
    //       - passed, doubled, isolated or backward pawns
    blackpassedpawns = 0;
    temp = board.blackPawns;
    while (temp)
    {
        square = firstOne(temp);

        if (endgame)
        {
            score -= PAWNPOS_B_EG[square];
        }
        else
        {
            score -= PAWNPOS_B_MG[square];
        }

        score -= PAWN_OPPONENT_DISTANCE[DISTANCE[square][whitekingsquare]];

        if (endgame)
        {
            score -= PAWN_OWN_DISTANCE[DISTANCE[square][blackkingsquare]];
        }

        if (!(PASSED_BLACK[square] & board.whitePawns))
        {
            score -= BONUS_PASSED_PAWN;

            // remember its location, we need it later when evaluating the black rooks:
            blackpassedpawns ^= BITSET[square];
        }

        if ((board.blackPawns ^ BITSET[square]) & FILEMASK[square])
        {
            if (endgame)
            {
                score += PENALTY_DOUBLED_PAWN_EG;
            }
            else
            {
                score += PENALTY_DOUBLED_PAWN_MG;
            }
        }

        if (!(ISOLATED_BLACK[square] & board.blackPawns))
        {
            if (endgame)
            {
                score += PENALTY_ISOLATED_PAWN_EG;
            }
            else
            {
                score += PENALTY_ISOLATED_PAWN_MG;
            }
        }


        // if not isolated, then it might be backward. Two conditions must be true:
        //  1) if the next square is controlled by an enemy pawn - we use the PAWN_ATTACKS Bitboards to check this
        //  2) if there are no pawns left that could defend this pawn
        else
        {
            if ((BLACK_PAWN_ATTACKS[square - 8] & board.whitePawns))
                if (!(BACKWARD_BLACK[square] & board.blackPawns))
                {
                    if (endgame)
                    {
                        score += PENALTY_BACKWARD_PAWN_EG;
                    }
                    else
                    {
                        score += PENALTY_BACKWARD_PAWN_MG;
                    }
                }
        }

        temp ^= BITSET[square];
    }


    // 5.3.2 black knights
    //       - position on the board
    //       - distance from opponent king
    temp = board.blackKnights;
    while (temp)
    {
        square = firstOne(temp);

        if (endgame)
        {
            score -= KNIGHTPOS_B_EG[square];
        }
        else
        {
            score -= KNIGHTPOS_B_MG[square];
        }

        score -= KNIGHT_DISTANCE[DISTANCE[square][whitekingsquare]];

        temp ^= BITSET[square];
    }


    // 5.3.3 black bishops
    //       - having the pair
    //       - position on the board
    //       - distance from opponent king
    if (board.blackBishops)
        if ((board.blackBishops & WHITE_SQUARES) && (board.blackBishops & BLACK_SQUARES))
        {
            if (endgame)
            {
                score -= BONUS_BISHOP_PAIR_EG;
            }
            else
            {
                score -= BONUS_BISHOP_PAIR_MG;
            }
        }

    temp = board.blackBishops;
    while (temp)
    {
        square = firstOne(temp);

        if (endgame)
        {
            score -= BISHOPPOS_B_EG[square];
        }
        else
        {
            score -= BISHOPPOS_B_MG[square];
        }

        score -= BISHOP_DISTANCE[DISTANCE[square][whitekingsquare]];

        temp ^= BITSET[square];
    }


    // 5.3.4 black rooks
    //       - position on the board
    //       - distance from opponent king
    //       - behind a passed pawn
    //       - on semi-open file
    //       - on open file
    //       - on the 7th rank
    //       - two rooks connected on the 7th
    temp = board.blackRooks;
    while (temp)
    {
        square = firstOne(temp);
        score -= ROOKPOS_B[square];

        if (!board.castleBlack)
        {
            score -= ROOK_DISTANCE[DISTANCE[square][whitekingsquare]];
        }

        // rook behind passed pawn
        if (FILEMASK[square] & blackpassedpawns)
        {
            if ((unsigned int) square > firstOne(FILEMASK[square] & blackpassedpawns))
            {
                if (endgame)
                {
                    score -= BONUS_ROOK_BEHIND_PASSED_PAWN_EG;
                }
                else
                {
                    score -= BONUS_ROOK_BEHIND_PASSED_PAWN_MG;
                }
            }
        }


        // rook on semi-open file
        if (bitCnt(FILEMASK[square] & (board.whitePawns | board.blackPawns)) == 1)
        {
            if (endgame)
                score -= BONUS_ROOK_ON_SEMIOPEN_FILE_EG;
            else
                score -= BONUS_ROOK_ON_SEMIOPEN_FILE_MG;
        }

        // rook on open file
        if (!(FILEMASK[square] & (board.whitePawns | board.blackPawns)))
        {
            if (endgame)
                score -= BONUS_ROOK_ON_OPEN_FILE_EG;
            else
                score -= BONUS_ROOK_ON_OPEN_FILE_MG;
        }

        temp ^= BITSET[square];
    }


    // 5.3.5 black queens
    //       - position on the board
    //       - distance from opponent king
    temp = board.blackQueens;
    while (temp)
    {
        square = firstOne(temp);

        if (endgame)
        {
            score -= QUEENPOS_B_EG[square];
        }
        else
        {
            score -= QUEENPOS_B_MG[square];
        }

        score -= QUEEN_DISTANCE[DISTANCE[square][whitekingsquare]];

        temp ^= BITSET[square];
    }


    // 5.3.6 black king
    //       - position on the board
    //       - proximity to the pawns
    //       - pawn shield (not in the endgame)
    if (endgame)
    {
        score -= KINGPOS_B_EG[blackkingsquare];
    }
    else if (board.blackKing & KINGCASTLED_MASK_B)
    {
        // basic bonus just because we're castled
        score -= BONUS_KING_IS_CASTLED;

        score -= KINGPOS_B_MG[blackkingsquare];

        // add pawn shield bonus if we're not in the endgame:
        // strong pawn shield bonus if the pawns are near the king:
        score -= BONUS_PAWN_SHIELD_STRONG * bitCnt(KINGSHIELD_STRONG_B[blackkingsquare] & board.blackPawns);

        // weaker pawn shield bonus if the pawns are not so near the king:
        score -= BONUS_PAWN_SHIELD_WEAK * bitCnt(KINGSHIELD_WEAK_B[blackkingsquare] & board.blackPawns);
    }

    // king on semi-open file
    if (bitCnt(FILEMASK[blackkingsquare] & (board.whitePawns | board.blackPawns)) == 1)
    {
        if ((FILES[blackkingsquare] <= 2) || (FILES[blackkingsquare] >= 7))
            score += PENALTY_KING_ON_SEMIOPEN_ABGH;
        else
            score += PENALTY_KING_ON_SEMIOPEN_CDEF;
    }

    // king on open file
    if (!(FILEMASK[blackkingsquare] & (board.whitePawns | board.blackPawns)))
    {
        if ((FILES[blackkingsquare] == 1) || (FILES[blackkingsquare] == 8))
            score += PENALTY_KING_ON_OPEN_FILE_AH;
        else if ((FILES[blackkingsquare] == 2) || (FILES[blackkingsquare] == 7))
            score += PENALTY_KING_ON_OPEN_FILE_BG;
        else
            score += PENALTY_KING_ON_OPEN_FILE_CDEF;
    }


    // 6. bonus for tempo
    int tempoBonus = 0;
    if (endgame)
        tempoBonus = BONUS_TEMPO_ENDGAME;
    else
        tempoBonus = BONUS_TEMPO_MIDGAME;
    if (board.nextMove)
        score -= tempoBonus;
    else
        score += tempoBonus;


    // return the score
    if (board.nextMove)
        return -score;
    else
        return score;
}



// convert BBC piece code to Stockfish piece codes
int nnue_pieces[12] = { 6, 5, 4, 3, 2, 1, 12, 11, 10, 9, 8, 7 };

// convert BBC square indices to Stockfish indices
int nnue_squares[64] = {
    A1, B1, C1, D1, E1, F1, G1, H1,
	A2, B2, C2, D2, E2, F2, G2, H2,
	A3, B3, C3, D3, E3, F3, G3, H3,
	A4, B4, C4, D4, E4, F4, G4, H4,
	A5, B5, C5, D5, E5, F5, G5, H5,
	A6, B6, C6, D6, E6, F6, G6, H6,
	A7, B7, C7, D7, E7, F7, G7, H7,
	A8, B8, C8, D8, E8, F8, G8, H8
};




/*
int Board::evalNNUE()
{    
    // current pieces bitboard copy
    Bitboard bb;
    
    // init piece & square
    int piece, square;
    
    // array of piece codes converted to Stockfish piece codes
    int pieces[33];
    
    // array of square indices converted to Stockfish square indices
    int squares[33];
    
    // pieces and squares current index to write next piece square pair at
    int index = 2;
    
    // loop over piece bitboards
    for (int bb_piece = P; bb_piece <= k; bb_piece++)
    {
        // init piece bitboard copy
        bb = bitboards[bb_piece];
        
        // loop over pieces within a bitboard
        while (bitboard)
        {
            // init piece
            piece = bb_piece;
            
            // init square
            square = get_ls1b_index(bitboard);
            
            // Code to initialize pieces and squares arrays to serve the purpose of direct probing of NNUE
            
            // case white king
            if (piece == K)
            {
                // convert white king piece code to stockfish piece code and store it at the first index of pieces array
                pieces[0] = nnue_pieces[piece];
                
                // convert white king square index to stockfish square index and store it at the first index of pieces array
                squares[0] = nnue_squares[square];
            }
            
            // case black king
            else if (piece == k)
            {
                // convert black king piece code to stockfish piece code and store it at the second index of pieces array
                pieces[1] = nnue_pieces[piece];
                
                // convert black king square index to stockfish square index and store it at the second index of pieces array
                squares[1] = nnue_squares[square];
            }
            
            // all the rest pieces
            else
            {
                // convert all the rest of piece code with corresponding square codes to stockfish piece codes and square indices respectively
                pieces[index] = nnue_pieces[piece];
                squares[index] = nnue_squares[square];
                index++;    
            }

            // pop ls1b
            pop_bit(bitboard, square);
        }
    }
    
    // set zero terminating characters at the end of pieces & squares arrays
    pieces[index] = 0;
    squares[index] = 0;
    
    //
    //    We need to make sure that fifty rule move counter gives a penalty
    //    to the evaluation, otherwise it won't be capable of mating in
    //    simple endgames like KQK or KRK! This expression is used:
    //                    nnue_score * (100 - fifty) / 100
    
    // get NNUE score (final score! No need to adjust by the side!)
    return (evaluate_nnue(side, pieces, squares) * (100 - fifty) / 100);
}*/
