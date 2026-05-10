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

// vim:et:ts=4:sw=4

/*!
 * @file src/game/board/action.cpp
 */
#include <sstream>
#include "definitions"
#include "utils"
#include "game/board/board"
#include "game/board/piece"
#include "game/board/pawn"
#include "game/board/knight"
#include "game/board/bishop"
#include "game/board/rook"
#include "game/board/queen"
#include "game/board/king"



/*!
 * Set the piece at a certain square.
 *
 * Please note that the piece position is not updated here. This means that the
 * piece position and new moves/attacks should be recalculated separately. For
 * instance, a piece of code my set a piece on the board, but after using this
 * function, the function Piece::update() should be called, to update the status
 * of that piece.
 *
 * @param p   Piece to be set on the position.
 * @param pos Square where the piece must be.
 */
void Board::setPiece(Piece *p, int pos)
{
    // delete previous piece, if any
    Piece *piece = getPieceAt(pos);
    if (piece != 0)
        removePiece(piece);

    // now set the moving piece to the given position
    int oldpos = p->getPosition();
    empty(oldpos);
    squares[pos]->setPiece(p);
    p->setSquare(squares[pos]);
    p->setPosition(pos);
    updateBitboards(p, oldpos);
}


/*!
 * Update all the positional Bitboards that are affected by the given piece.
 *
 * @param p           Pointer to the piece which may affect any of the
 *                    bitboards.
 * @param oldPosition Integer number telling at which position was the
 *                    recently-moved piece.
 */
void Board::updateBitboards(Piece *p, int oldPosition)
{
    switch (p->getColor())
    {
        case COLOR_TYPE_WHITE:
            resetBit(&whitePieces, oldPosition);
            resetBit(&blackPieces, p->getPosition());
            setBit(&whitePieces, p->getPosition());
            break;

        case COLOR_TYPE_BLACK:
            resetBit(&blackPieces, oldPosition);
            resetBit(&whitePieces, p->getPosition());
            setBit(&blackPieces, p->getPosition());
            break;

        default:
            break;
    }
}


/*!
 * Apply a move to the current board.
 *
 * @param mv Move to be performed on the board.
 */
void Board::doMove(Move mv)
{
    // log operation
    if (log)
    {
        indent++;

        for (int i = 0; i < indent; i++)
            log_fd << ".";
        log_fd << "BEGIN doMove(" << mv.getAlgebraic() << ")" << endl;
    }

    Piece *p = getPieceAt(mv.getOrigin());

    // promotion_simple
    if (mv.isPromotion())
    {
        doPromotion(mv);
    }
    // killer move
    else if (mv.isCapture())
    {
        doCapture(mv);
    }
    // special moves: CastleShort, CastleLong
    else if (mv.isCastle())
    {
        doCastle(mv);
    }
    // any move in general
    else
    {
        p->increaseMoves();
        setPiece(p, mv.getDestination());
    }

    // update data structures
    updatePieces();
    updateEmpassants(mv, false);
    updateKings();

    // check the 50-moves repetition rule
    oldfifty.push_back(fifty);
    if (mv.isCapture() || (simplePiece(mv.getPiece()) == PIECE_TYPE_PAWN))
        fifty = 0;
    else
        fifty++;
    if (fifty >= 50)
        end = END_TYPE_DRAW_50RULE;

    // store the serialized version of the board
    serials.push_back(toSerial(mv.getColor(), 0, 0, 0));

    // check the rule of threefold
    //checkThreeRepetitions();

    // increment the number of moves
    cursor++;

    // log operation
    if (log)
    {
        for (int i = 0; i < indent; i++)
            log_fd << ".";
        log_fd << "END doMove(" << mv.getAlgebraic() << ")" << endl;
    }
}


/*!
 * Undo a move from the current board.
 *
 * @param mv Move to be undone.
 *
 * Please notice that this function should be used with a parameter that
 * correleates with its previous move. This means that the board will become
 * inconsistent if another method tries to undo a move that it is not the
 * previous move.
 */
void Board::undoMove(Move mv)
{
    // null move
    if (mv.getType() == MOVE_TYPE_NULL)
        return;

    // log operation
    if (log)
    {
        for (int i = 0; i < indent; i++)
            log_fd << ".";
        log_fd << "BEGIN undoMove(" << mv.getAlgebraic() << ")" << endl;
    }

    // promotion_simple
    if (mv.isPromotion())
    {
        undoPromotion(mv);
    }
    // if the move was a killer move, then restore the previous piece
    else if (mv.isCapture())
    {
        undoCapture(mv);
    }
    // check for castling
    else if (mv.isCastle())
    {
        undoCastle(mv);
    }
    // normal move (no capture)
    else
    {
        Piece *p = getPieceAt(mv.getDestination());
        p->decreaseMoves();
        setPiece(p, mv.getOrigin());
    }

    // update data structures
    updatePieces();
    updateEmpassants(mv, true);
    updateKings();

    // check the 50-moves repetition rule
    fifty = oldfifty.back();
    oldfifty.pop_back();

    // if the move could be performed, there was no end
    end  = END_TYPE_NOEND;
    mate = COLOR_TYPE_NONE;

    // restore the serialized version of the board
    serials.pop_back();

    // decrement the number of moves
    cursor--;

    // log operation
    if (log)
    {
        for (int i = 0; i < indent; i++)
            log_fd << ".";
        log_fd << "END undoMove(" << mv.getAlgebraic() << ")" << endl;

        indent--;
    }
}


/*!
 * Update all the pawns and their empassant status.
 *
 * @param undo Tell if we are undoing or not a move.
 *
 * This 'undo' parameter tries to deal with the complexity of empassants and
 * remembering each empassant position, as we can do and undo moves seamlessly.
 *
 * @param mv a Move object contained the last move.
 */
void Board::updateEmpassants(Move mv, bool undo)
{
    Pawn *p;
    BitBoard cur_emp = 0;
    
    // doMove
    if (!undo)
    {
        // save the current empassant
        empassants.push_back(empassant);

        // calculate the new empassant
        if (simplePiece(mv.getPiece()) == PIECE_TYPE_PAWN)
        {
            p = static_cast<Pawn *>(getPieceAt(mv.getDestination()));
            int distance = mv.getOrigin() - mv.getDestination();
            distance *= distance;
            if (distance == (16 * 16))
                cur_emp = p->getBB();
        }

        // update the new empassant
        empassant = cur_emp;
    }
    // undoMove
    else
    {
        // enable the last empassant
        empassant = empassants.back();
        empassants.pop_back();
    }
}


/*!
 * Internal method for performing a promotion.
 *
 * @param mv Move object containg the promotion move.
 */
void Board::doPromotion(Move mv)
{
    PieceType pt;
    Piece *pr = 0;
    char promo;
    string input;

    // check which type of promotion
    input = mv.getAlgebraic();
    if (mv.getType() == MOVE_TYPE_PROMOTION_SIMPLE)
        promo = input[3];
    else if (mv.getType() == MOVE_TYPE_PROMOTION_CAPTURE)
        promo = input[5];
    else if (mv.getType() == MOVE_TYPE_PROMOTION_CAPTURE_SHORT)
        promo = input[4];
    else
        promo = 'q';

    // perform the promotion
    switch (promo)
    {
        case 'n':
        case 'N':
            if (mv.getColor() == COLOR_TYPE_WHITE)
                pt = PIECE_TYPE_KNIGHT_WHITE;
            else
                pt = PIECE_TYPE_KNIGHT_BLACK;
            pr = new Knight(pt);
            break;
        case 'b':
        case 'B':
            if (mv.getColor() == COLOR_TYPE_WHITE)
                pt = PIECE_TYPE_BISHOP_WHITE;
            else
                pt = PIECE_TYPE_BISHOP_BLACK;
            pr = new Bishop(pt);
            break;
        case 'r':
        case 'R':
            if (mv.getColor() == COLOR_TYPE_WHITE)
                pt = PIECE_TYPE_ROOK_WHITE;
            else
                pt = PIECE_TYPE_ROOK_BLACK;
            pr = new Rook(pt);
            break;
        case 'q':
        case 'Q':
            if (mv.getColor() == COLOR_TYPE_WHITE)
                pt = PIECE_TYPE_QUEEN_WHITE;
            else
                pt = PIECE_TYPE_QUEEN_BLACK;
            pr = new Queen(pt);
            break;
        default:
            cerr << mv.toString() << endl;
            cerr << "Promotion error!" << endl;
            return;       
    }

    // configure the promotion piece
    Piece *pawn = getPieceAt(mv.getOrigin());
    pawn->increaseMoves();
    removePiece(pawn);
    setPiece(pr, mv.getDestination());
    pieces.push_back(pr);
}


/*!
 * Internal method for performing a capture.
 *
 * @param mv Move object which contains the castling move.
 */
void Board::doCapture(Move mv)
{
    Piece *p = getPieceAt(mv.getOrigin());
    Piece *victim;

    // check for empassants
    if (mv.isEmpassant())
    {
        if (mv.getColor() == COLOR_TYPE_WHITE)
            victim = getPieceAt(mv.getDestination() - 8);
        else
            victim = getPieceAt(mv.getDestination() + 8);

        // with empassant, victim removal is special
        removePiece(victim);
    }
    else
    {
        victim = getPieceAt(mv.getDestination());
    }

    p->increaseMoves();
    setPiece(p, mv.getDestination());
}


/*!
 * Internal method for performing a castling.
 *
 * @param mv Move object which contains the castling move.
 */
void Board::doCastle(Move mv)
{
    int kingat, rookat;
    Piece *king, *rook;

    if (mv.getColor() == COLOR_TYPE_WHITE)
    {
        if (mv.getType() == MOVE_TYPE_CASTLE_SHORT)
        {
            kingat = 4;
            rookat = 7;
        }
        else
        {
            kingat = 4;
            rookat = 0;
        }
    }
    else
    {
        if (mv.getType() == MOVE_TYPE_CASTLE_SHORT)
        {
            kingat = 60;
            rookat = 63;
        }
        else
        {
            kingat = 60;
            rookat = 56;
        }
    }

    king = getPieceAt(kingat);
    rook = getPieceAt(rookat);

    if (mv.getType() == MOVE_TYPE_CASTLE_SHORT)
    {
        setPiece(king, kingat+2);
        setPiece(rook, kingat+1);
    }
    else
    {
        setPiece(king, kingat-2);
        setPiece(rook, kingat-1);
    }

    // update the king and rook status
    King *k = static_cast<King *>(king);
    k->setCastled(true);
    king->increaseMoves();
    rook->increaseMoves();
}


/*!
 * Internal method for undoing a promotion.
 *
 * @param mv Move object containg the promotion move.
 */
void Board::undoPromotion(Move mv)
{
    Piece *pawn = 0;
    Piece *last = 0;

    // check if the promotion also captured another piece
    if (mv.isCapture())
    {
        last = removedPieces.back();
        removedPieces.pop_back();
        pawn = removedPieces.back();
    }
    else
    {
        pawn = removedPieces.back(),
        removedPieces.pop_back();
    }

    // delete the created promotion piece
    for (unsigned int i = 0; i < pieces.size(); i++)
    {
        if (!pieces[i]->isEnabled())
            continue;

        if (pieces[i]->getPosition() == mv.getDestination())
        {
            pieces.erase(pieces.begin() + i);
            break;
        }
    }

    // restore pawn
    pawn->decreaseMoves();
    pawn->enable();
    setPiece(pawn, mv.getOrigin());
    empty(mv.getDestination());

    // restore also a captured piece if it was there
    if (last)
    {
        if ((last->getColor() != pawn->getColor()) &&
            (last->getType() != PIECE_TYPE_PAWN_WHITE) &&
            (last->getType() != PIECE_TYPE_PAWN_BLACK) &&
            (last->getPosition() == mv.getDestination()))
        {
            last->enable();
            setPiece(last, mv.getDestination());
            removedPieces.pop_back();
        }
    }
}


/*!
 * Internal method for undoing a castling.
 *
 * @param mv Move object which contains the castling move.
 */
void Board::undoCastle(Move mv)
{
    int kingat, rookat;
    Piece *king, *rook;

    // depending on which side and type of castle, fix the positions for the
    // rook and the king, where to find them and from where to move them
    if (mv.getColor() == COLOR_TYPE_WHITE)
    {
        if (mv.getType() == MOVE_TYPE_CASTLE_SHORT)
        {
            kingat = 6;
            rookat = 5;
        }
        else
        {
            kingat = 2;
            rookat = 3;
        }
    }
    else
    {
        if (mv.getType() == MOVE_TYPE_CASTLE_SHORT)
        {
            kingat = 62;
            rookat = 61;
        }
        else
        {
            kingat = 58;
            rookat = 59;
        }
    }

    // pick the king and the rook of the corresponding castle
    king = getPieceAt(kingat);
    rook = getPieceAt(rookat);

    // set the king and the rook to their new squares
    if (mv.getType() == MOVE_TYPE_CASTLE_SHORT)
    {
        setPiece(king, kingat-2);
        setPiece(rook, kingat+1);
    }
    else
    {
        setPiece(king, kingat+2);
        setPiece(rook, kingat-2);
    }

    // update the king and rook status
    King *k = static_cast<King *>(king);
    k->setCastled(false);
    king->decreaseMoves();
    rook->decreaseMoves();
}


/*!
 *
 * Internal method for undoing a capture.
 *
 * @param mv Move object which contains the capturing move.
 */
void Board::undoCapture(Move mv)
{
    Piece *restored = removedPieces.back();
    removedPieces.pop_back();

    Piece *p = getPieceAt(mv.getDestination());
    setPiece(p, mv.getOrigin());

    if (mv.isEmpassant())
    {
        if (mv.getColor() == COLOR_TYPE_WHITE)
            setPiece(restored, mv.getDestination() - 8);
        else
            setPiece(restored, mv.getDestination() + 8);

    }
    else
    {
        setPiece(restored, mv.getDestination());
    }

    restored->enable();
    p->decreaseMoves();
}


/*!
 * Remove a piece from the board.
 *
 * @param p Piece to be removed from the board.
 */
void Board::removePiece(Piece *p)
{
    // if there is no piece, don't do anything
    if (p == 0)
        return;

    // p is disabled, but it remains in the pieces list
    p->disable();

    // p is also copied to the list of removed pieces (for restore)
    removedPieces.push_back(p);

    // always set to 0 the piece on that square
    empty(p->getPosition());
}


/*!
 * Update the status of each piece.
 */
void Board::updatePieces()
{
    // update each piece's moves and attacks
    for (unsigned int i = 0; i < pieces.size(); i++)
        if (pieces[i]->isEnabled())
            pieces[i]->update(this);
}


/*!
 * Update the status of the kings (both of them).
 *
 * Check every piece against the king's position and update the check and mate
 * status variables.
 */
void Board::updateKings()
{
    vector<Piece *> whites = getPieces(whitePieces);
    vector<Piece *> blacks = getPieces(blackPieces);

    // if no mate, continue
    bool white_checked = false;
    bool black_checked = false;

    // check against the white king
    for (unsigned int i = 0; i < blacks.size(); i++)
    {
        if (blacks[i] == 0)
            continue;

        if (blacks[i]->getAttacks() & whiteKingPiece->getBB())
        {
            white_checked = true;
            break;
        }
    }

    // check against the black king
    for (unsigned int i = 0; i < whites.size(); i++)
    {
        if (whites[i] == 0)
            continue;

        if (whites[i]->getAttacks() & blackKingPiece->getBB())
        {
            black_checked = true;
            break;
        }
    }

    // update the kings' status
    whiteKingPiece->setChecked(white_checked);
    blackKingPiece->setChecked(black_checked);

    if (white_checked && black_checked)
        check = COLOR_TYPE_BOTH;
    else if (white_checked)
        check = COLOR_TYPE_WHITE;
    else if (black_checked)
        check = COLOR_TYPE_BLACK;
    else
        check = COLOR_TYPE_NONE; 
}
