// Copyright: 2008-2016  Claudio M. Camacho                                       
                                                                           
// This file is part of Chess0.                                              
                                                                            
// Chess0 is free software; you can redistribute it and/or modify            
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.

// Chess0 is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with Chess0; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
// 

// vim:et:ts=4:sw=4

/*!
 * @file src/ai/adaptive_position.cpp
 */
#include <unordered_map>
#include "utils"
#include "ai/adaptive"
#include "game/board/board"
#include "game/board/square"
#include "game/board/piece"
#include "game/board/king"
#include "game/board/queen"
#include "game/board/knight"
#include "game/board/bishop"
#include "game/board/rook"



/*!
 * Evaluate the current board taking in account only the position.
 *
 * @return a float with a positive number for white leading, negative number for
 *         black leading and 0.0 for an equal situation.
 */
float Adaptive::evalPosition()
{
    float est = 0;
    
    // obtain the list of pieces
    vector<Piece *> pieces = board->getPieces();
    PhaseType phase = board->getPhase();
    BitBoard wPawns = board->getPositions(PIECE_TYPE_PAWN_WHITE);
    BitBoard bPawns = board->getPositions(PIECE_TYPE_PAWN_BLACK);

    // positional evaluation for each piece
    // * remember that black pieces have a negative value ;-)
    for (unsigned int i = 0; i < pieces.size(); i++)
    {
        // EVERY PIECE
        // positional values to each piece (depending on the square)
        switch (pieces[i]->getType())
        {
            case PIECE_TYPE_PAWN_WHITE:   est += quanta_WP[pieces[i]->getPosition()];
                                          break;
            case PIECE_TYPE_PAWN_BLACK:   est += quanta_BP[pieces[i]->getPosition()];
                                          break;
            case PIECE_TYPE_KNIGHT_WHITE: est += quanta_WN[pieces[i]->getPosition()];
                                          break;
            case PIECE_TYPE_KNIGHT_BLACK: est += quanta_BN[pieces[i]->getPosition()];
                                          break;
            case PIECE_TYPE_BISHOP_WHITE: est += quanta_WB[pieces[i]->getPosition()];
                                          break;
            case PIECE_TYPE_BISHOP_BLACK: est += quanta_BB[pieces[i]->getPosition()];
                                          break;
            case PIECE_TYPE_ROOK_WHITE:   est += quanta_WR[pieces[i]->getPosition()];
                                          break;
            case PIECE_TYPE_ROOK_BLACK:   est += quanta_BR[pieces[i]->getPosition()];
                                          break;
            case PIECE_TYPE_QUEEN_WHITE:  est += quanta_WQ[pieces[i]->getPosition()];
                                          break;
            case PIECE_TYPE_QUEEN_BLACK:  est += quanta_BQ[pieces[i]->getPosition()];
                                          break;
            case PIECE_TYPE_KING_WHITE:   if (board->getPhase() == PHASE_TYPE_END)
                                              est += quanta_WZ[pieces[i]->getPosition()];
                                          else
                                              est += quanta_WK[pieces[i]->getPosition()];
                                          break;
            case PIECE_TYPE_KING_BLACK:   if (board->getPhase() == PHASE_TYPE_END)
                                              est += quanta_BZ[pieces[i]->getPosition()];
                                          else
                                              est += quanta_BK[pieces[i]->getPosition()];
            default: est += 0;
        }

        // mobility bonus to each piece (according to their number of moves)
        est += pieces[i]->getNMoves() * pieces[i]->getColor() / 2;

        // KINGS
        if ((pieces[i]->getType() == PIECE_TYPE_KING_WHITE) || (pieces[i]->getType() == PIECE_TYPE_KING_BLACK))
        {
            King *k = (King *) pieces[i];


            // KING SAFETY
            if (phase != PHASE_TYPE_END)
            {
                BitBoard tPawns;
                unordered_map<string, BitBoard> tKingSafeMask;

                // king shield, -0.10 for 1-square pawn move, -0.40 farther
                if (k->hasCastled())
                {
                    BitBoard kSide = k->getBB();
                    if (k->getColor() == COLOR_TYPE_WHITE)
                    {
                        tPawns = wPawns;
                        tKingSafeMask = board->wKingSafeMask;
                    }
                    else
                    {
                        tPawns = bPawns;
                        tKingSafeMask = board->bKingSafeMask;
                    }

                    unsigned short s1Pawns = 0;
                    unsigned short sxPawns = 0;
                    unsigned short l1Pawns = 0;
                    unsigned short lxPawns = 0;

                    // short castle
                    if (kSide & board->shortCastleMask)
                    {
                        if (tPawns & tKingSafeMask["s1"])
                        {
                            s1Pawns = countBits(tPawns & tKingSafeMask["s1"]);
                            est -= 10 * s1Pawns * k->getColor();
                        }

                        sxPawns = countBits(tPawns & tKingSafeMask["sx"]);
                        if (sxPawns < 3)
                        {
                            est -= 40 * (3 - sxPawns - s1Pawns) * k->getColor();
                        }
                    }
                    
                    // long castle
                    else
                    {
                        if (tPawns & tKingSafeMask["l1"])
                        {
                            l1Pawns = countBits(tPawns & tKingSafeMask["l1"]);
                            est -= 10 * l1Pawns * k->getColor();
                        }

                        lxPawns = countBits(tPawns & tKingSafeMask["lx"]);
                        if (lxPawns < 3)
                        {
                            est -= 40 * (3- lxPawns - l1Pawns) * k->getColor();
                        }
                    }
                }
            }

            // penalty for king on open file: -0.10
            if (!(board->columnMask[k->getColumn()] & (wPawns | bPawns)))
                est += 10 * k->getColor();

            // king with very low mobility: -0.10
            if (k->getNMoves() == 0)
                est -= 10 * k->getColor();

            // castled kings: +0.40
            if (k->hasCastled())
                est += 40 * k->getColor();           

            // king has moved without castling: -0.30
            else if (k->isMoved())
                est -= 30 * k->getColor();

            // king under check (midgame / endgame): -0.75 / -0.10
            else if (k->isChecked())
            {
                if (phase == PHASE_TYPE_END)
                    est -= 10 * k->getColor();
                else
                    est -= 75 * k->getColor();
            }
        }


        // QUEENS
        else if ((pieces[i]->getType() == PIECE_TYPE_QUEEN_WHITE) || (pieces[i]->getType() == PIECE_TYPE_QUEEN_BLACK))
        {
            // moved queen in opening: -0.10
            Queen *q = (Queen *) pieces[i];
            if ((phase == PHASE_TYPE_OPENING) && (q->isMoved()))
            {
                est -= 10 * q->getColor();
            }
        }


        // ROOKS
        else if ((pieces[i]->getType() == PIECE_TYPE_ROOK_WHITE) || (pieces[i]->getType() == PIECE_TYPE_ROOK_BLACK))
        {
            Rook *r = (Rook *) pieces[i];

            // reward for rooks on open file: +0.20
            if (!(board->columnMask[r->getColumn()] & (wPawns | bPawns)))
                est += 20 * r->getColor();

            // penaly for rooks which move before castling: -0.10
            if (r->getColor() == COLOR_TYPE_WHITE)
            {
                if (r->isMoved() && !board->whiteKingPiece->hasCastled())
                    est -= 10;
            }
            else if (r->getColor() == COLOR_TYPE_BLACK)
            {
                if (r->isMoved() & !board->blackKingPiece->hasCastled())
                    est += 10;
            }
        }

     
        // BISHOPS
        else if ((pieces[i]->getType() == PIECE_TYPE_BISHOP_WHITE) || (pieces[i]->getType() == PIECE_TYPE_BISHOP_BLACK))
        {
            Bishop *b = (Bishop *) pieces[i];

            // bisohps at the end are more worthy: +0.10
            if (phase == PHASE_TYPE_END)
            {
                est += 10 * b->getColor();
            }
        }
        
        
        // KNIGHTS
        else if ((pieces[i]->getType() == PIECE_TYPE_KNIGHT_WHITE) || (pieces[i]->getType() == PIECE_TYPE_KNIGHT_BLACK))
        {
            // knights at the end are less worthy: -0.10
            Knight *n = (Knight *) pieces[i];
            if (phase == PHASE_TYPE_END)
            {
                est -= 10 * n->getColor();
            }
        }
    }


    // PAWNS
    vector<Piece *> wPawnPieces = board->getPieces(PIECE_TYPE_PAWN_WHITE);
    vector<Piece *> bPawnPieces = board->getPieces(PIECE_TYPE_PAWN_BLACK);

    // White's pawn structures
    // doubled pawns: -0.16
    for (char i = 'a'; i < 'i'; i++)
        if (countBits(wPawns & board->columnMask[i]) > 1)
            est -= 16;

    // isolated pawns: -0.20
    // passed pawns: +0.50
    // rook pawns: -0.15
    for (unsigned i = 0; i < wPawnPieces.size(); i++)
    {
        char column = wPawnPieces[i]->getColumn();

        // rook pawns
        if (column == 'a')
        {
            est -= 15;

            // isolated pawn
            if ((board->columnMask['b'] & wPawns) == 0)
                est -= 20;

            // passed pawn
            if (((board->columnMask['a'] & bPawns) == 0) &&
                ((board->columnMask['b'] & bPawns) == 0))
                est += 50;
        }
        else if (column == 'h')
        {
            est -= 15;

            // isolated pawn
            if ((board->columnMask['g'] & wPawns) == 0)
                est -= 20;

            // passed pawn
            if (((board->columnMask['h'] & bPawns) == 0) &&
                ((board->columnMask['g'] & bPawns) == 0))
                est += 50;
        }

        // rest of columns
        else
        {
            // isolated pawn
            if (((board->columnMask[column - 1] & wPawns) == 0) &&
                ((board->columnMask[column + 1] & wPawns) == 0))
                est -= 20;

            // passed pawn
            if (((board->columnMask[column] & bPawns) == 0) &&
                ((board->columnMask[column - 1] & bPawns) == 0) &&
                ((board->columnMask[column + 1] & bPawns) == 0))
                est += 50;
        }
    }

    // Black's pawn structures
    // doubled pawns: -0.16
    for (char i = 'a'; i < 'i'; i++)
        if (countBits(bPawns & board->columnMask[i]) > 1)
            est += 16;

    // isolated pawns: -0.20
    // passed pawns: +0.50
    // rook pawns: -0.15
    for (unsigned i = 0; i < bPawnPieces.size(); i++)
    {
        char column = bPawnPieces[i]->getColumn();

        // rook pawns
        if (column == 'a')
        {
            est += 15;

            // isolated pawn
            if ((board->columnMask['b'] & bPawns) == 0)
                est += 20;

            // passed pawn
            if (((board->columnMask['a'] & wPawns) == 0) &&
                ((board->columnMask['b'] & wPawns) == 0))
                est -= 50;
        }
        else if (column == 'h')
        {
            est += 15;

            // isolated pawn
            if ((board->columnMask['g'] & bPawns) == 0)
                est += 20;

            // passed pawn
            if (((board->columnMask['h'] & wPawns) == 0) &&
                ((board->columnMask['g'] & wPawns) == 0))
                est -= 50;
        }

        // rest of columns
        else
        {
            // isolated pawn
            if (((board->columnMask[column - 1] & bPawns) == 0) &&
                ((board->columnMask[column + 1] & bPawns) == 0))
                est += 20;

            // passed pawn
            if (((board->columnMask[column] & wPawns) == 0) &&
                ((board->columnMask[column - 1] & wPawns) == 0) &&
                ((board->columnMask[column + 1] & wPawns) == 0))
                est -= 50;
        }
    }

    // other bonuses and penalties
    // add bonus to moving player (tempo bonus): +0.10
    est += 10 * game->getPlayer();

    // pair of bishops is more worthy: +0.10
    if ((board->getPieces(PIECE_TYPE_BISHOP_WHITE)).size() > 1)
        est += 10;
    if ((board->getPieces(PIECE_TYPE_BISHOP_BLACK)).size() > 1)
        est -= 10;


    // default: position doesn't count
    return (est / 100);
}
