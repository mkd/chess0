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
 * @file src/game/board/board.cpp
 */
#include <iomanip>
#include <sstream>
#include <iostream>
#include <algorithm>
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
 * Default constructor
 *
 * @param p pointer to the MoveParser of the current game.
 */
Board::Board()
{
    Square *sq;

    // Bitboards containing initial positions for all and various pieces: these
    // bitboards will be updated during the game as pieces are moved around
    whitePieces      = 0x000000000000FFFF;
    blackPieces      = 0xFFFF000000000000;

    // Masks are useful bitboards used for comparison purposes and never changed
    // their value during the game (they are 'static')
    whitePiecesMask  = 0x000000000000FFFF;
    blackPiecesMask  = 0xFFFF000000000000;

    whitePawns   = whitePawnMask   = 0x000000000000FF00;
    whiteKnights = whiteKnightMask = 0x0000000000000042;
    whiteBishops = whiteBishopMask = 0x0000000000000024;
    whiteRooks   = whiteRookMask   = 0x0000000000000081;
    whiteQueens  = whiteQueenMask  = 0x0000000000000008;
    whiteKing    = whiteKingMask   = 0x0000000000000010;

    blackPawns   = blackPawnMask   = 0x00FF000000000000;
    blackKnights = blackKnightMask = 0x4200000000000000;
    blackBishops = blackBishopMask = 0x2400000000000000;
    blackRooks   = blackRookMask   = 0x8100000000000000;
    blackQueens  = blackQueenMask  = 0x0800000000000000;
    blackKing    = blackKingMask   = 0x1000000000000000;

    // column masks to find isolated and doubled pawns
    columnMask['a']                = 0x0101010101010101;
    columnMask['b']                = 0x0202020202020202;
    columnMask['c']                = 0x0404040404040404; 
    columnMask['d']                = 0x0808080808080808; 
    columnMask['e']                = 0x1010101010101010;
    columnMask['f']                = 0x2020202020202020; 
    columnMask['g']                = 0x4040404040404040;  
    columnMask['h']                = 0x8080808080808080;  

    // masks for "left" and "right" side of the board
    shortCastleMask                = 0xF0F0F0F0F0F0F0F0;
    longCastleMask                 = 0x0F0F0F0F0F0F0F0F;

    // short (s) and long (l) castle safety masks
    wKingSafeMask["s1"]            = 0x0000000000E00000;
    wKingSafeMask["sx"]            = 0x000000000000E000;
    wKingSafeMask["l1"]            = 0x0000000000070000;
    wKingSafeMask["lx"]            = 0x0000000000000700;

    bKingSafeMask["s1"]            = 0x0000E00000000000;
    bKingSafeMask["sx"]            = 0x00E0000000000000;
    bKingSafeMask["l1"]            = 0x0000070000000000;
    bKingSafeMask["lx"]            = 0x0007000000000000;

    // create 64 squares and initialize them
    for (int i = 0; i < 64; i++)
    {
        sq = new Square();
        squares.push_back(sq);
    }

    // phase status
    cursor = 0;
    phase  = PHASE_TYPE_OPENING;
    check  = COLOR_TYPE_NONE;
    mate   = COLOR_TYPE_NONE;
    end    = END_TYPE_NOEND;
    indent = 0;

    // 50-moves repetition flag
    fifty = 0;
    oldfifty.push_back(0);

    // initial number of pieces
    empassant = 0;

    // logging is disabled by default
    log_file = "";
    log = false;

    // display flipped or not
    flipped = false;

    // finally, initialize the squares with the pieces
    init();
}


/*!
 * Auxiliar function similar to the constructor, but it can be used at any
 * moment, when the Board has already been created, and it will reset the
 * position of the board to the initial position.
 */
void Board::init()
{
    Piece *p;
    ColorType c;

    // initialize clean squares
    for (int i = 0; i < 64; i++)
        squares[i]->setPiece(0);

    // go through all the squares and add its initial-position piece
    for (int i = 0; i < 64; i++)
    {
        // create white pawns
        if ((i >= 8) && (i <= 15))
            p = new Pawn(PIECE_TYPE_PAWN_WHITE);
        // create black pawns
        else if ((i >= 48) && (i <= 55))
            p = new Pawn(PIECE_TYPE_PAWN_BLACK);
        // create white rooks
        else if ((i == 0) || (i == 7))
            p = new Rook(PIECE_TYPE_ROOK_WHITE);
        // create black rooks
        else if ((i == 56) || (i == 63))
            p = new Rook(PIECE_TYPE_ROOK_BLACK);
        // create white knights
        else if ((i == 1) || (i == 6))
            p = new Knight(PIECE_TYPE_KNIGHT_WHITE);
        // create black knights
        else if ((i == 57) || (i == 62))
            p = new Knight(PIECE_TYPE_KNIGHT_BLACK);
        // create white bishops
        else if ((i == 2) || (i == 5))
            p = new Bishop(PIECE_TYPE_BISHOP_WHITE);
        // create black bishops
        else if ((i == 58) || (i == 61))
            p = new Bishop(PIECE_TYPE_BISHOP_BLACK);
        // create white queen
        else if (i == 3)
            p = new Queen(PIECE_TYPE_QUEEN_WHITE);
        // create black queen
        else if (i == 59)
            p = new Queen(PIECE_TYPE_QUEEN_BLACK);
        // create white king
        else if (i == 4)
        {
            p = new King(PIECE_TYPE_KING_WHITE);
            whiteKingPiece = (King *) p;
        }
        // create black king
        else if (i == 60)
        {
            p = new King(PIECE_TYPE_KING_BLACK);
            blackKingPiece = (King *) p;
        }
        // leave empty
        else
            continue;

        // add piece to the list of pieces
        ((i % 2) == 0) ? c = COLOR_TYPE_BLACK : c = COLOR_TYPE_WHITE;
        squares[i]->setColor(c);
        squares[i]->setPosition(i);
        squares[i]->setPiece(p);
        p->setPosition(i);
        p->setSquare(squares[i]);
        pieces.push_back(p);
    }

    // initialize pre-computed moves for non-sliding pieces
    initKnightMoves();
    initKingMoves();
    initSlidingMoves();
    initPawnAttacks();

    // piece updates must be performed once the board is full, since they must
    // check the squares looking for free places where to move
    updatePieces();
}


/*!
 * Reset the board with the help of the init() function.
 */
void Board::reset()
{
    clear();
    init();
}


/*!
 * Clear a board.
 *
 * This is a reset where the starting position is not restored, thus wiping the
 * pieces from the board.
 */
void Board::clear()
{
    // re-initialize bitboards
    whitePieces = 0xFFFFULL;
    blackPieces = 0xFFFF000000000000ULL;

    // clean-up piece objects
    pieces.clear();
    removedPieces.clear();

    // display orientation (default: white)
    flipped = false;

    // re-create the board
    serials.clear();
    cursor = 0;
    phase  = PHASE_TYPE_OPENING;
    check  = COLOR_TYPE_NONE;
    mate   = COLOR_TYPE_NONE;
    end    = END_TYPE_NOEND;

    // reset the 50-moves repetition flag
    fifty = 0;
    oldfifty.clear();
    oldfifty.push_back(0);

    // initial number of pieces
    empassant = 0;
    empassants.clear();
}


/*!
 * Return a list with the pieces that are enabled (on the board).
 *
 * @return a vector of pointers to Piece.
 */
vector<Piece *> Board::getPieces()
{
    vector<Piece *> mypieces;

    for (unsigned int i = 0; i < pieces.size(); i++)
        if (pieces[i]->isEnabled())
            mypieces.push_back(pieces[i]);

    return mypieces;
}


/*!
 * Return a list with the pieces that are enabled (on the board).
 *
 * @return a vector of pointers to Piece.
 */
vector<Piece *> Board::getRemovedPieces()
{
    vector<Piece *> mypieces;

    for (unsigned int i = 0; i < pieces.size(); i++)
        if (!pieces[i]->isEnabled())
            mypieces.push_back(pieces[i]);

    return mypieces;
}


/*!
 * Convert the internal representation of the board into a human-readable string
 * (capable of being shown and represented as a Board in ASCII).
 *
 * @return a string containing the whole human-readable representation of the
 *         board.
 */
string Board::toString()
{
    int i = 0;
    int j = 0;
    ostringstream board(ostringstream::out);
    char p = ' ';

    board << "\n       +----+----+----+----+----+----+----+----+\n";

    // display black front
    if (flipped)
    {
        for (i = 0; i <= 7; i++)
        {
            board << "  " << i + 1 << "    ";
            for (j = 7; j >= 0; j--)
            {
                // put the squares into the string
                p = getPieceCharAt((i * 8) + j);
                if ((p >= 'b') && (p <= 'r'))
                    board << "| *" << p << " ";
                else
                    board << "|  " << p << " ";

            }
            board << "|";
            board << "\n       +----+----+----+----+----+----+----+----+\n";
        }

        board << "\n         h    g    f    e    d    c    b    a\n\n";
    }

    // display white front
    else 
    {
        for (i = 7; i >= 0; i--)
        {
            board << "  " << i + 1 << "    ";
            for (j = 0; j < 8; j++)
            {
                // put the squares into the string
                p = getPieceCharAt((i * 8) + j);
                if ((p >= 'b') && (p <= 'r'))
                    board << "| *" << p << " ";
                else
                    board << "|  " << p << " ";

            }
            board << "|";
            board << "\n       +----+----+----+----+----+----+----+----+\n";
        }

        board << "\n         a    b    c    d    e    f    g    h\n\n";
    }

    return board.str();
}


/*!
 * Retrieve the piece at a certain square and return its character
 * representation.
 *
 * @param pos Square where the piece must be.
 *
 * @return a char containing the representation of the piece or the status of
 *         the square at this moment.
 */
char Board::getPieceCharAt(int pos)
{
    Piece *p = squares[pos]->getPiece();

    if (p == 0)
        return ' ';

    switch (p->getType())
    {
        case PIECE_TYPE_PAWN_BLACK  :  return 'p';
        case PIECE_TYPE_KNIGHT_BLACK:  return 'n';
        case PIECE_TYPE_BISHOP_BLACK:  return 'b';
        case PIECE_TYPE_ROOK_BLACK  :  return 'r';
        case PIECE_TYPE_QUEEN_BLACK :  return 'q';
        case PIECE_TYPE_KING_BLACK  :  return 'k';
        case PIECE_TYPE_PAWN_WHITE  :  return 'P';
        case PIECE_TYPE_KNIGHT_WHITE:  return 'N';
        case PIECE_TYPE_BISHOP_WHITE:  return 'B';
        case PIECE_TYPE_ROOK_WHITE  :  return 'R';
        case PIECE_TYPE_QUEEN_WHITE :  return 'Q';
        case PIECE_TYPE_KING_WHITE  :  return 'K';
        default:  ;
    }

    return 'X';
}


/*!
 * Retrieve the piece at a certain square and return its type.
 *
 * @param pos Square where the piece must be.
 *
 * @return a piece type or the status of the square at this moment.
 */
PieceType Board::getPiece(int pos)
{
    return squares[pos]->getPiece()->getType();
}


/*!
 * Retrieve the piece at a certain square and return its object.
 *
 * @param pos Square where the piece must be.
 *
 * @return a pointer to the piece object on that square.
 */
Piece* Board::getPieceAt(int pos)
{
    return squares[pos]->getPiece();
}


/*!
 * Retrieve all the pieces of a type on the board.
 *
 * @param pt Piece type to look for (including its color).
 *
 * @return a list of pointers to the piece objects created and associated to
 *         this board.
 */
vector<Piece *> Board::getPieces(PieceType pt)
{
    vector<Piece *> mypieces;

    for (unsigned int i = 0; i < pieces.size(); i++)
    {
        if ((pt == pieces[i]->getType()) && (pieces[i]->isEnabled()))
            mypieces.push_back(pieces[i]);
    }

    return mypieces;
}


/*!
 * Retrieve all the pieces of a type on the board.
 *
 * @param bb Bitboard with the bits set where the pieces are.
 *
 * @return a list of pointers to the piece objects created and associated to
 *         this board on their respective positions in the BitBoard.
 */
vector<Piece *> Board::getPieces(BitBoard bb)
{
    vector<Piece *> mypieces;
    vector<int> positions = positionsFromBitboard(bb);

    for (unsigned int i = 0; i < positions.size(); i++)
        mypieces.push_back(getPieceAt(positions[i]));

    return mypieces;
}


/*!
 * Retrieve all the positions in the board where a certain type of piece is
 * found.
 *
 * @param pt Piece type to look for.
 *
 * @return a BitBoard containing 1s where the given type of piece can be found.
 */
BitBoard Board::getPositions(PieceType pt)
{
    BitBoard bb = 0;
    BitBoard tb = 1;
    Piece *p;

    for (int i = 0; i < 64; i++)
    {
        tb = 1;

        p = squares[i]->getPiece();
        if (p && (p->getType() == pt))
        {
            tb <<= i;
            bb  += tb;
        }
    }

    return bb;
}


/*!
 * Retrieve the piece color at a certain square.
 *
 * @param pos Square where the piece must be.
 *
 * @return a color type, including empty if the square is not occupied.
 */
ColorType Board::getPieceColor(int pos)
{
    Piece *p = squares[pos]->getPiece();

    if (p == 0)
        return COLOR_TYPE_EMPTY;

    return p->getColor();
}


/*!
 * Empty a given square in the board.
 *
 * @param pos Integer representing the square in the internal format.
 */
void Board::empty(int pos)
{
    if ((pos >= 0) && (pos <= 63))
    {
        squares[pos]->setPiece(0);

        // update lists internally
        resetBit(&whitePieces, pos);
        resetBit(&blackPieces, pos);
    }
}


/*!
 * Retrieve the position of the pieces structure in the board.
 *
 * @param ct Color of the side whose pieces structure must be retrieved.
 *
 * @return a BitBoard containing the structure of the pieces swith bitsets.
 */
BitBoard Board::getPieces(ColorType ct)
{
    switch (ct)
    {
        case COLOR_TYPE_WHITE:
            return whitePieces;
        case COLOR_TYPE_BLACK:
            return blackPieces;
        default:
            return 0;
    }
}


/*!
 * Set the position of the pieces structure in the board.
 *
 * @param ct ColorType defining the color of the pieces to be set.
 * @param bb BitBoard containing the positions of the pieces.
 */
void Board::setPieces(ColorType ct, BitBoard bb)
{
    switch (ct)
    {
        case COLOR_TYPE_WHITE:
            whitePieces = bb;
            break;
        case COLOR_TYPE_BLACK:
            blackPieces = bb;
            break;
        default:
            return;
    }
}


/*!
 * Retrieve a list with all the possible moves that can be done by one side.
 *
 * @param c specify the color of the side to be checked for moves.
 *
 * @return a list containing all the moves that the side can perform.
 */
vector<Move> Board::getAllMoves(ColorType c)
{
    vector<Move> moves;
    vector<Move> tmp;
    vector<Piece *> ps = getPieces(getPieces(c));

    for (unsigned int i = 0; i < ps.size(); i++)
    {
        tmp = ps[i]->getAllMoves();
        for (unsigned int j = 0; j < tmp.size(); j++)
            moves.push_back(tmp[j]);
    }

    return moves;
}


/*!
 * Check the amount of possible moves for one side.
 *
 * @param c specify the color of the side to be checked for moves.
 *
 * @return the number of possible moves, 0 if none.
 */
int Board::getNMoves(ColorType c)
{
    int moves = 0;

    vector<Piece *> ps = getPieces(getPieces(c));

    for (unsigned int i = 0; i < ps.size(); i++)
        moves += ps[i]->getNMoves();

    return moves;
}


/*!
*   Copied from Crafty-Chess (phase.c)
*   
*   updatePhase() is used to determine the phase of the game: opening,
*   middlegame or endgame. The three phases are identified by the following
*   criteria:
*                                                                              
*   (a) opening:  if any minor pieces are still on their original squares, or  
*       the king has not yet castled nor given up the right to castle, then    
*       opening development rules still apply.                                 
*
*   (b) middle-game:  if the opening criteria are not met, and the end-game    
*       criteria are not met, then all that's left is a middle-game.          
*
*   (c) end-game:  if both sides have less than 17 points of material, not     
*       counting pawns, (Q=9, R=5, BN=3) then we are in an end-game.           
*/                                                                              
void Board::updatePhase()
{
    bool canCastle = false;

    // if one of the sides can castle, we are still in the opening
    vector<Piece *> white_rk = getPieces(PIECE_TYPE_ROOK_WHITE);
    vector<Piece *> black_rk = getPieces(PIECE_TYPE_ROOK_BLACK);
    Rook *white_rook;
    Rook *black_rook;
    
    // white king can still castle?
    if (!whiteKingPiece->isMoved())
    {
        for (unsigned i = 0; i < white_rk.size(); i++)
        {
            white_rook = (Rook *)white_rk[i];
            if (!white_rook->isMoved())
            {
                canCastle = true;
                break;
            }
        }
    }

    // black king can still castle?
    if (!blackKingPiece->isMoved())
    {
        for (unsigned i = 0; i < black_rk.size(); i++)
        {
            black_rook = (Rook *)black_rk[i];
            if (!black_rook->isMoved())
            {
                canCastle = true;
                break;
            }
        }
    }

    // if castling is still possible, we are at the opening
    if (canCastle)
    {
        phase = PHASE_TYPE_OPENING;
        return;
    }

    // if not, check if the minor pieces are in their original squares
    else
    {
        vector<Piece *> white_kn = getPieces(PIECE_TYPE_KNIGHT_WHITE);
        vector<Piece *> black_kn = getPieces(PIECE_TYPE_KNIGHT_BLACK);
        vector<Piece *> white_bp = getPieces(PIECE_TYPE_BISHOP_WHITE);
        vector<Piece *> black_bp = getPieces(PIECE_TYPE_BISHOP_BLACK);

        // create a vector called minorPieces with all the minor pieces
        vector<Piece *> minorPieces = white_kn;
        minorPieces.insert(minorPieces.begin(), black_kn.begin(), black_kn.end());
        minorPieces.insert(minorPieces.begin(), white_bp.begin(), white_bp.end());
        minorPieces.insert(minorPieces.begin(), black_bp.begin(), black_bp.end());

        // as soon as we find a minorPiece which has not moved (!isMoved()), we
        // can assure we are still at the opening
        for (unsigned i = 0; i < minorPieces.size(); i++)
        {
            if (!minorPieces[i]->isMoved())
            {
                phase = PHASE_TYPE_OPENING;
                return;
            }
        }
    }


    // if the piece point count drops below 20 (2000cp, e.g., two rooks and
    // three minor pieces) then this is an end-game
    vector<Piece *> remainingPieces = getPieces();
    float curValue = 0;
    float accValue = 0;
    for (unsigned i = 0; i < remainingPieces.size(); i++)
    {
        curValue = Abs(remainingPieces[i]->getValue());

        // don't count King nor Pawns
        if ((curValue == VALUE_PAWN) || (curValue == VALUE_KING))
            continue;

        accValue += curValue;
    }

    // if value of pieces below 20 points, we are at the end
    if (accValue < PIECE_POINT_COUNT_END)
    {
        phase = PHASE_TYPE_END;
    }

    // if not opening and not end game, it has to be middle game
    else
    {
        phase = PHASE_TYPE_MIDDLE;
    }
}


/*
 * Retrieve the list of pseudo-legal attacks of a side's king.
 *
 * @param c ColorType specifying which color are we examining.
 *
 * @return a BitBoard with the bits set to the attacked squares.
 */
BitBoard Board::getKingAttacks(ColorType c)
{
    vector<Piece *> ps;

    if (c == COLOR_TYPE_WHITE)
        return whiteKingPiece->getAttacks();
    else
        return blackKingPiece->getAttacks();
}


/*!
 * Create a serial stream of characters representing an unique position.
 *
 * @param c     ColorType (side) for which the board is being stored, for fairness.
 * @param d     Depth at which the board serial was created.
 * @param alpha Alpha-bound at which the board serial was created.
 * @param beta  Beta-bound at which the board serial was created.
 *
 * Example: negamax() may use this function to store boards with some evaluation
 *          attached to them, and use the extra parameter to tell the depth of
 *          the search.
 *
 * @return a string containing the list of representing characters.
 */
string Board::toSerial(ColorType c, float alpha, float beta, int d)
{
    string serial = "";
    ostringstream extra(ostringstream::out);

    // serialize the whole board into a 64-chars string
    for (int i = 0; i < 64; i++)
        serial.append(1, getPieceCharAt(i));

    // append the moving side ('w' or 'b')
    char moving = c2c(c);
    serial.append(&moving);

    // append castling rights
    string wc = "0";
    string bc = "0";
    if (whiteKingPiece->hasCastled())
        wc = "1";
    if (blackKingPiece->hasCastled())
        bc = "1";
    serial.append("|");
    serial.append(wc);
    serial.append("|");
    serial.append(bc);
    serial.append("|");

    // add empassants
    serial.append(to_string(getEmpassant()));

    // append the alpha and beta bounds
    serial.append("|");
    serial.append(to_string(alpha));
    serial.append("|");
    serial.append(to_string(beta));
    serial.append("|");

    // append the depth as well
    extra.fill('0');
    extra << setw(3) << d;
    serial.append(extra.str());

    return serial;
}


/*!
 * Change the current log file.
 *
 * @param fn String containing the filename.
 */
void Board::setLogFile(string fn)
{
    // if the filename is the same as the previous one, don't do anything
    if (fn == log_file)
        return;

    // test opening the new log file
    ofstream test(fn.c_str());
    if (!test.is_open())
        return;

    // if it is successful, then use fn as the new log file
    log_file = fn;
    test.close();
    log_fd.close();
    log_fd.open(log_file.c_str());
}


/*!
 * Check the rule of three repetitions.
 */
void Board::checkThreeRepetitions()
{
    if (serials.size() < 10)
        return;

    int found = 0;
    unsigned int last = serials.size() - 1;

    // find repeated positions
    for (unsigned int i = 1; i < 10; i++)
    {
        if (serials[last] == serials[last -i])
            found++;
    }

    // if three boards are repeated, at least, then it is draw by threefold
    if (found >= 2)
    {
        mate = COLOR_TYPE_NONE;
        end  = END_TYPE_DRAW_3RULE;
    }
}


/*!
 * Initialize Knight's pre-computed moves (using bitboards).
 *
 * Note: this code has been borrowed from Crafty (init.c).
 */
void Board::initKnightMoves()
{
    short sq;
    short i, j;
    short frank, ffile, trank, tfile;
    short knightsq[8] = { -17, -15, -10, -6, 6, 10, 15, 17 };
    for (i = 0; i < 64; i++)
    {
        knightMoves[i] = 0;

        frank = posToRowInt(i);
        ffile = posToColumnInt(i);

        for (j = 0; j < 8; j++)
        {
            sq = i + knightsq[j];
            if (sq < 0 || sq > 63)
                continue;

            trank = posToRowInt(sq);
            tfile = posToColumnInt(sq);

            if (Abs(frank - trank) > 2 || Abs(ffile - tfile) > 2)
            continue;

            knightMoves[i] = knightMoves[i] | (uint64_t) 1 << sq;
        }
    }
}


/*!
 * Initialize King's pre-computed moves (using bitboards).
 *
 * Note: this code has been borrowed from Crafty (init.c).
 */
void Board::initKingMoves()
{
    short i, j;

    for (i = 0; i < 64; i++)
    {
        kingMoves[i] = 0;

        for (j = 0; j < 64; j++)
            if (Distance(i, j) == 1)
                setBit(&kingMoves[i], j);
    }

}

/*!
 * Initialize Pawn's pre-computed attacks (using bitboards).
 */
void Board::initPawnAttacks()
{
    short i, j;
    int sq;
    int bishopsq[4] = { -9, -7, 7, 9 };

    for (i = 0; i < 64; i++)
    {
        whitePawnAttacks[i] = 0;

        if (i < 56)
            for (j = 2; j < 4; j++)
            {
                sq = i + bishopsq[j];
                if (Abs(Rank(sq) - Rank(i)) == 1 && Abs(File(sq) - File(i)) == 1 && sq < 64 && sq > -1)
                    whitePawnAttacks[i] = whitePawnAttacks[i] | (uint64_t) 1 << sq;
            }

        blackPawnAttacks[i] = 0;

        if (i > 7)
            for (j = 0; j < 2; j++)
            {
                sq = i + bishopsq[j];
                if (Abs(Rank(sq) - Rank(i)) == 1 && Abs(File(sq) - File(i)) == 1 && sq < 64 && sq > -1)
                    blackPawnAttacks[i] = blackPawnAttacks[i] | (uint64_t) 1 << sq;
            }
    }
}


/*!
 * Initialize moves for sliding pieces using magic bitboards.
 *
 * Note: this code has been borrowed from Rival chess:
 * http://www.afewmorelines.com/understanding-magic-bitboards-in-chess-programming/
 */
void Board::initSlidingMoves()
{
    //initOccupancyMasks();
    //initOccupancyVariations();
}


/*!
 * Initialize occupancy masks for sliding pieces (with magic bitboards).
 *
 * Note: The occupancyMask arrays can be calculated easily enough, but here they
 * are along with the code to calculate them… you’ll notice in the code that we
 * avoid marking edge squares in the mask. This is because an edge square is
 * always a blocker so does not need to be defined as such – a slider will
 * always stop on top of the first blocker it encounters (captures of friendly
 * pieces are filtered out at the end as you can see above.) -- From Rival
 * chess:
 * http://www.afewmorelines.com/understanding-magic-bitboards-in-chess-programming/
 */
/*
void Board::initOccupancyMasks()
{
    int i, bitRef;
    uint64_t mask;

    for (bitRef=0; bitRef<=63; bitRef++)
    {
        mask = 0;
        for (i=bitRef+8; i<=55; i+=8) mask |= (1L << i);
        for (i=bitRef-8; i>=8; i-=8) mask |= (1L << i);
        for (i=bitRef+1; i%8!=7 && i%8!=0 ; i++) mask |= (1L << i);
        for (i=bitRef-1; i%8!=7 && i%8!=0 && i>=0; i--) mask |= (1L << i);
        occupancyMaskRook[bitRef] = mask;

        mask = 0;
        for (i=bitRef+9; i%8!=7 && i%8!=0 && i<=55; i+=9) mask |= (1L << i);
        for (i=bitRef-9; i%8!=7 && i%8!=0 && i>=8; i-=9) mask |= (1L << i);
        for (i=bitRef+7; i%8!=7 && i%8!=0 && i<=55; i+=7) mask |= (1L << i);
        for (i=bitRef-7; i%8!=7 && i%8!=0 && i>=8; i-=7) mask |= (1L << i);
        occupancyMaskBishop[bitRef] = mask;
    }
}
*/


/*!
 * Calculte the occupancy variations.
 *
 * Note: To generate the magic numbers, we first need to populate a
 * occupancyVariation and atttackSet array. The occupancyVariation array will
 * contain all the occupancy variations for a piece on a given square.
 *
 * This code was borrowed from Rival chess:
 * http://www.afewmorelines.com/understanding-magic-bitboards-in-chess-programming/
 */
/*
void Board::initOccupancyVariations(boolean isRook)
{
    int i, j, bitRef;
    long mask;
    int variationCount;
    int[] setBitsInMask, setBitsInIndex;
    int bitCount[] = new int[64];

    for (bitRef=0; bitRef<=63; bitRef++)
    {
        mask = isRook ? occupancyMaskRook[bitRef] : occupancyMaskBishop[bitRef];
        setBitsInMask = Bitboards.getSetBits(mask);
        bitCount[bitRef] = Bitboards.countSetBits(mask);
        variationCount = (int)(1L << bitCount[bitRef]);
        for (i=0; i<variationCount; i++)
        {
            occupancyVariation[bitRef][i] = 0; 

            // find bits set in index "i" and map them to bits in the 64 bit "occupancyVariation"
            setBitsInIndex = Bitboards.getSetBits(i); // an array of integers showing which bits are set
            for (j=0; setBitsInIndex[j] != -1; j++)
            {
                occupancyVariation[bitRef][i] |= (1L << setBitsInMask[setBitsInIndex[j]]);
            }

            if (isRook)
            {
                for (j=bitRef+8; j<=55 && (occupancyVariation[bitRef][i] & (1L << j)) == 0; j+=8);
                if (j>=0 && j<=63) occupancyAttackSet[bitRef][i] |= (1L << j);
                for (j=bitRef-8; j>=8 && (occupancyVariation[bitRef][i] & (1L << j)) == 0; j-=8);
                if (j>=0 && j<=63) occupancyAttackSet[bitRef][i] |= (1L << j);
                for (j=bitRef+1; j%8!=7 && j%8!=0 && (occupancyVariation[bitRef][i] & (1L << j)) == 0; j++);
                if (j>=0 && j<=63) occupancyAttackSet[bitRef][i] |= (1L << j);
                for (j=bitRef-1; j%8!=7 && j%8!=0 && j>=0 && (occupancyVariation[bitRef][i] & (1L << j)) == 0; j--);
                if (j>=0 && j<=63) occupancyAttackSet[bitRef][i] |= (1L << j);
            }
            else
            {
                for (j=bitRef+9; j%8!=7 && j%8!=0 && j<=55 && (occupancyVariation[bitRef][i] & (1L << j)) == 0; j+=9);
                if (j>=0 && j<=63) occupancyAttackSet[bitRef][i] |= (1L << j);
                for (j=bitRef-9; j%8!=7 && j%8!=0 && j>=8 && (occupancyVariation[bitRef][i] & (1L << j)) == 0; j-=9);
                if (j>=0 && j<=63) occupancyAttackSet[bitRef][i] |= (1L << j);
                for (j=bitRef+7; j%8!=7 && j%8!=0 && j<=55 && (occupancyVariation[bitRef][i] & (1L << j)) == 0; j+=7);
                if (j>=0 && j<=63) occupancyAttackSet[bitRef][i] |= (1L << j);
                for (j=bitRef-7; j%8!=7 && j%8!=0 && j>=8 && (occupancyVariation[bitRef][i] & (1L << j)) == 0; j-=7);
                if (j>=0 && j<=63) occupancyAttackSet[bitRef][i] |= (1L << j);
            }
        }
    }
}
*/
