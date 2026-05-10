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
 * @file src/game/board/edit.cpp
 */
#include <stdio.h>
#include <ctype.h>
#include <fstream>
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
 * Interactively guide the user in the process of creating a manual position on
 * the board.
 *
 * Note: this function does not care about the validity of such position on the
 *       board.
 *
 * @see checkIntegerity
 */
void Board::edit()
{
    string input;
    char piece = '\0';
    char col;
    char row;
    int pos = -1;
    Piece *p = 0;

    // wipe out the whole board
    clear();
    whitePieces = 0;
    blackPieces = 0;

    // initialize clean squares
    for (int i = 0; i < 64; i++)
    {
        p = squares[i]->getPiece();
        squares[i]->setPiece(0);
    }

    // enter white pieces
    cout << "Enter white pieces and black pieces followed by '#':" << endl;
    while ((piece != '#') && (piece != '.'))
    {
        cin >> input;
        piece = input[0];
        col   = input[1];
        row   = input[2];

        // add piece
        if ((isPiece(piece) || (piece == 'p') || (piece == 'P')) &&
            isColumn(col) && isRow(row))
        {
            pos = bmap(input.substr(1, 2));

            // check that this new piece does not remove a king
            if (squares[pos]->getPiece() && (squares[pos]->getPiece()->getValue() == VALUE_KING))
                continue;

            resetBit(&blackPieces, pos);
            setBit(&whitePieces, pos);
            switch (piece)
            {
                case 'p':
                case 'P':
                    p = new Pawn(PIECE_TYPE_PAWN_WHITE);
                    break;
                case 'n':
                case 'N':
                    p = new Knight(PIECE_TYPE_KNIGHT_WHITE);
                    break;
                case 'b':
                case 'B':
                    p = new Bishop(PIECE_TYPE_BISHOP_WHITE);
                    break;
                case 'r':
                case 'R':
                    p = new Rook(PIECE_TYPE_ROOK_WHITE);
                    break;
                case 'q':
                case 'Q':
                    p = new Queen(PIECE_TYPE_QUEEN_WHITE);
                    break;
                case 'k':
                case 'K':
                    p = new King(PIECE_TYPE_KING_WHITE);
                    whiteKingPiece = (King *) p;
                    break;
                default:
                    continue;
            }

            // delete a previous piece, if any
            squares[pos]->setPiece(0);
            for (unsigned int j = 0; j < pieces.size(); j++)
                if (pieces[j]->getPosition() == pos)
                    pieces.erase(pieces.begin() + j);

            // set the new piece
            squares[pos]->setPiece(p);
            p->setPosition(pos);
            p->setSquare(squares[pos]);
            pieces.push_back(p);

            // if minor piece, pawn, rook or king at their starting point, act
            // like they have been never moved (thus allowing empassant,
            // castling, etc)
            if ((piece == 'p') || (piece == 'P'))
                if (!(p->getBB() & whitePawnMask))
                    p->increaseMoves();
            if ((piece == 'n') || (piece == 'N'))
                if (!(p->getBB() & whiteKnightMask))
                    p->increaseMoves();
            if ((piece == 'b') || (piece == 'B'))
                if (!(p->getBB() & whiteBishopMask))
                    p->increaseMoves();
            if ((piece == 'r') || (piece == 'R'))
                if (!(p->getBB() & whiteRookMask))
                    p->increaseMoves();
            if ((piece == 'k') || (piece == 'K'))
                if (!(p->getBB() & whiteKingMask))
                    p->increaseMoves();
        }
    }

    // enter black pieces
    piece = '\0';
    cout << "Enter black pieces followed by '#':" << endl;
    while ((piece != '#') && (piece != '.'))
    {
        cin >> input;
        piece = input[0];
        col   = input[1];
        row   = input[2];

        // add piece
        if ((isPiece(piece) || (piece == 'p') || (piece == 'P')) &&
            isColumn(col) && isRow(row))
        {
            pos = bmap(input.substr(1, 2));

            // check that this new piece does not remove a king
            if (squares[pos]->getPiece() && (squares[pos]->getPiece()->getValue() == -VALUE_KING))
                continue;

            resetBit(&whitePieces, pos);
            setBit(&blackPieces, pos);
            switch (piece)
            {
                case 'p':
                case 'P':
                    p = new Pawn(PIECE_TYPE_PAWN_BLACK);
                    break;
                case 'n':
                case 'N':
                    p = new Knight(PIECE_TYPE_KNIGHT_BLACK);
                    break;
                case 'b':
                case 'B':
                    p = new Bishop(PIECE_TYPE_BISHOP_BLACK);
                    break;
                case 'r':
                case 'R':
                    p = new Rook(PIECE_TYPE_ROOK_BLACK);
                    break;
                case 'q':
                case 'Q':
                    p = new Queen(PIECE_TYPE_QUEEN_BLACK);
                    break;
                case 'k':
                case 'K':
                    p = new King(PIECE_TYPE_KING_BLACK);
                    blackKingPiece = (King *) p;
                    break;
                default:
                    continue;
            }

            // set the new piece
            squares[pos]->setPiece(p);
            p->setPosition(pos);
            p->setSquare(squares[pos]);
            pieces.push_back(p);

            // if minor piece, pawn, rook or king at their starting point, act
            // like they have been never moved (thus allowing empassant,
            // castling, etc)
            if ((piece == 'p') || (piece == 'P'))
                if (!(p->getBB() & blackPawnMask))
                    p->increaseMoves();
            if ((piece == 'n') || (piece == 'N'))
                if (!(p->getBB() & blackKnightMask))
                    p->increaseMoves();
            if ((piece == 'b') || (piece == 'B'))
                if (!(p->getBB() & blackBishopMask))
                    p->increaseMoves();
            if ((piece == 'r') || (piece == 'R'))
                if (!(p->getBB() & blackRookMask))
                    p->increaseMoves();
            if ((piece == 'k') || (piece == 'K'))
                if (!(p->getBB() & blackKingMask))
                    p->increaseMoves();
        }
    }

    // update empassants and king
    updatePieces();
    updateKings();
    updatePhase();
}


/*!
 * Load a board position from a disk file.
 *
 * @param stream File stream from where to read the position setup.
 *
 * Note: this function does not care about the validity of such position on the
 *       board.
 *
 * @see checkIntegerity
 */
void Board::load(ifstream *fin)
{
    string input;
    char piece = '\0';
    char col;
    char row;
    int pos = -1;
    Piece *p = 0;

    // wipe out the whole board
    clear();
    whitePieces = 0;
    blackPieces = 0;

    // initialize clean squares
    for (int i = 0; i < 64; i++)
    {
        p = squares[i]->getPiece();
        squares[i]->setPiece(0);
    }

    // enter white pieces
    while ((piece != '#') && (piece != '.'))
    {
        (*fin) >> input;
        piece = input[0];
        col   = input[1];
        row   = input[2];

        // add piece
        if ((isPiece(piece) || (piece == 'p') || (piece == 'P')) &&
            isColumn(col) && isRow(row))
        {
            pos = bmap(input.substr(1, 2));

            // check that this new piece does not remove a king
            if (squares[pos]->getPiece() && (squares[pos]->getPiece()->getValue() == VALUE_KING))
                continue;

            resetBit(&blackPieces, pos);
            setBit(&whitePieces, pos);
            switch (piece)
            {
                case 'p':
                case 'P':
                    p = new Pawn(PIECE_TYPE_PAWN_WHITE);
                    break;
                case 'n':
                case 'N':
                    p = new Knight(PIECE_TYPE_KNIGHT_WHITE);
                    break;
                case 'b':
                case 'B':
                    p = new Bishop(PIECE_TYPE_BISHOP_WHITE);
                    break;
                case 'r':
                case 'R':
                    p = new Rook(PIECE_TYPE_ROOK_WHITE);
                    break;
                case 'q':
                case 'Q':
                    p = new Queen(PIECE_TYPE_QUEEN_WHITE);
                    break;
                case 'k':
                case 'K':
                    p = new King(PIECE_TYPE_KING_WHITE);
                    whiteKingPiece = (King *) p;
                    break;
                default:
                    continue;
            }

            // delete a previous piece, if any
            squares[pos]->setPiece(0);
            for (unsigned int j = 0; j < pieces.size(); j++)
                if (pieces[j]->getPosition() == pos)
                    pieces.erase(pieces.begin() + j);

            // set the new piece
            squares[pos]->setPiece(p);
            p->setPosition(pos);
            p->setSquare(squares[pos]);
            pieces.push_back(p);

            // if minor piece, pawn, rook or king at their starting point, act
            // like they have been never moved (thus allowing empassant,
            // castling, etc)
            if ((piece == 'p') || (piece == 'P'))
                if (!(p->getBB() & whitePawnMask))
                    p->increaseMoves();
            if ((piece == 'n') || (piece == 'N'))
                if (!(p->getBB() & whiteKnightMask))
                    p->increaseMoves();
            if ((piece == 'b') || (piece == 'B'))
                if (!(p->getBB() & whiteBishopMask))
                    p->increaseMoves();
            if ((piece == 'r') || (piece == 'R'))
                if (!(p->getBB() & whiteRookMask))
                    p->increaseMoves();
            if ((piece == 'k') || (piece == 'K'))
                if (!(p->getBB() & whiteKingMask))
                    p->increaseMoves();
        }
    }

    // enter black pieces
    piece = '\0';
    while ((piece != '#') && (piece != '.'))
    {
        (*fin) >> input;
        piece = input[0];
        col   = input[1];
        row   = input[2];

        // add piece
        if ((isPiece(piece) || (piece == 'p') || (piece == 'P')) &&
            isColumn(col) && isRow(row))
        {
            pos = bmap(input.substr(1, 2));

            // check that this new piece does not remove a king
            if (squares[pos]->getPiece() && (squares[pos]->getPiece()->getValue() == -VALUE_KING))
                continue;

            resetBit(&whitePieces, pos);
            setBit(&blackPieces, pos);
            switch (piece)
            {
                case 'p':
                case 'P':
                    p = new Pawn(PIECE_TYPE_PAWN_BLACK);
                    break;
                case 'n':
                case 'N':
                    p = new Knight(PIECE_TYPE_KNIGHT_BLACK);
                    break;
                case 'b':
                case 'B':
                    p = new Bishop(PIECE_TYPE_BISHOP_BLACK);
                    break;
                case 'r':
                case 'R':
                    p = new Rook(PIECE_TYPE_ROOK_BLACK);
                    break;
                case 'q':
                case 'Q':
                    p = new Queen(PIECE_TYPE_QUEEN_BLACK);
                    break;
                case 'k':
                case 'K':
                    p = new King(PIECE_TYPE_KING_BLACK);
                    blackKingPiece = (King *) p;
                    break;
                default:
                    continue;
            }

            // set the new piece
            squares[pos]->setPiece(p);
            p->setPosition(pos);
            p->setSquare(squares[pos]);
            pieces.push_back(p);

            // if minor piece, pawn, rook or king at their starting point, act
            // like they have been never moved (thus allowing empassant,
            // castling, etc)
            if ((piece == 'p') || (piece == 'P'))
                if (!(p->getBB() & blackPawns))
                    p->increaseMoves();
            if ((piece == 'n') || (piece == 'N'))
                if (!(p->getBB() & blackKnights))
                    p->increaseMoves();
            if ((piece == 'b') || (piece == 'B'))
                if (!(p->getBB() & blackBishops))
                    p->increaseMoves();
            if ((piece == 'r') || (piece == 'R'))
                if (!(p->getBB() & blackRooks))
                    p->increaseMoves();
            if ((piece == 'k') || (piece == 'K'))
                if (!(p->getBB() & blackKing))
                    p->increaseMoves();
        }
    }

    // update empassants and king
    updatePieces();
    updateKings();
    updatePhase();
}


/*!
 * Create a serializable string from the current board position.
 *
 * @return a string object with the list of commands to restore the position
 * (e.g. using the edit() functionality.
 */
string Board::toEdited()
{
    Piece *p = 0;
    char pc = '\0';
    string col_row;
    ostringstream board(ostringstream::out);

    // white pieces
    for (unsigned int i = 0; i < 64; i++)
    {
        p = squares[i]->getPiece();
        if ((p == 0) || (p->getColor() != COLOR_TYPE_WHITE))
            continue;

        pc = getPieceCharAt(i);
        col_row = bunmap(i);
        board << pc << col_row << endl;   
    }

    // black pieces
    board << "#" << endl;
    for (unsigned int i = 0; i < 64; i++)
    {
        p = squares[i]->getPiece();
        if ((p == 0) || (p->getColor() != COLOR_TYPE_BLACK))
            continue;

        pc = toupper(getPieceCharAt(i));
        col_row = bunmap(i);
        board << pc << col_row << endl;   
    }

    return board.str();
}


/*!
 * Check the integrity of a given position.
 *
 * This includes:
 * a) two, and only two, kings, of opposite color must be on the board
 * b) only one or none kings can be in check at a time, not two
 * c) no more than eight pawns of a same color can exist at the same time
 * d) no pawns on row 1 nor row 8 (either promotion or invalid)
 *
 * @return true if the board is proper, false otherwise.
 */
bool Board::checkIntegrity()
{
    // 1) two, and only two, kings, of opposite color must be on the board
    vector<Piece *> white_ks = getPieces(PIECE_TYPE_KING_WHITE);
    vector<Piece *> black_ks = getPieces(PIECE_TYPE_KING_BLACK);
    if ((white_ks.size() != 1) || (black_ks.size() != 1))
        return false;

    // 2) only one or none kings can be in check at a time, not two
    updateKings();
    if (check == COLOR_TYPE_BOTH)
        return false;

    // 3) no more than eight pawns of a same color can exist at the same time
    vector<Piece *> white_ps = getPieces(PIECE_TYPE_PAWN_WHITE);
    vector<Piece *> black_ps = getPieces(PIECE_TYPE_PAWN_BLACK);
    if ((white_ps.size() > 8) || (black_ps.size() > 8))
        return false;

    // 4) no pawns on row 1 nor row 8 (either promotion or invalid)
    for (unsigned int i = 0; i < white_ps.size(); i++)
        if ((white_ps[i]->getPosition() < 8) ||
            (white_ps[i]->getPosition() > 55))
            return false;
    for (unsigned int i = 0; i < black_ps.size(); i++)
        if ((black_ps[i]->getPosition() < 8) ||
            (black_ps[i]->getPosition() > 55))
            return false;

    return true;
}
