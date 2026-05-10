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
 * @file src/game/moveparser.cpp
 */
#include "utils"
#include "game/moveparser"



/*!
 * Convert a given input into an internal move specification, consisting of the
 * origin square and the destiny square (e.g. 2233), and the type of movement,
 * which is also embedded in the Move object.
 *
 * @param input Input string that the user enter as the move.
 * @param mtype Type of move that is expeced to be parsed.
 * @param g     Pointer to the current game's object.
 *
 * @return a Move object with the internal move representation for the program.
 */
Move MoveParser::translate(string input, MoveType mtype, Game *g)
{
    // remember the last game, for default translations
    lastGame = g;

    // reset move to empty (defaults)
    move.reset();

    // common operations for any move
    move.setTurn(g->getTurn());

    // set move destination
    switch (mtype)
    {
        case MOVE_TYPE_PAWN:
            return translatePawn(input, g);

        case MOVE_TYPE_PROMOTION_SIMPLE:
            return translatePromotionSimple(input, g);

        case MOVE_TYPE_PROMOTION_CAPTURE:
            return translatePromotionCapture(input, g);
     
        case MOVE_TYPE_PROMOTION_CAPTURE_SHORT:
            return translatePromotionCaptureShort(input, g);
     
        case  MOVE_TYPE_SIMPLE:
            return translateSimple(input, g);

        case MOVE_TYPE_CASTLE_SHORT:
            return translateCastleShort(input, g);

        case MOVE_TYPE_XY:
            return translateXY(input, g);

        case MOVE_TYPE_CAPTURE_PAWN:
            return translateCapturePawn(input, g);
        
        case MOVE_TYPE_CAPTURE_PAWN_SHORT:
            return translateCapturePawnShort(input, g);
        
        case MOVE_TYPE_CAPTURE_SIMPLE:
            return translateCaptureSimple(input, g);

        case MOVE_TYPE_CAPTURE_SIMPLE_SHORT:
            return translateCaptureShort(input, g);
        
        case MOVE_TYPE_AMBIGUOUS:
            return translateAmbiguous(input, g);
        
        case MOVE_TYPE_CASTLE_LONG:
            return translateCastleLong(input, g);

        case MOVE_TYPE_CAPTURE_LONG:
            return translateCaptureLong(input, g);
        
        default:
            return move;
    }
}


/*!
 * Convert a descriptive move into SAN notation.
 *
 * Note: only XY moves will be decodified to SAN notation, as castlings, pawn
 * captures and promotions are already set in SAN notation.
 *
 * This function modifies the field 'human' of the move, thus adding the SAN
 * notation to it. The rest of the fields are not modified.
 *
 * Moreover, this function should be usually called if a move has been
 * automatically generated and the SAN notation ('human' field) is not filled in
 * or if it does not include a proper SAN notation.
 *
 * By default, if no move translation is found, the algebraic field is used as
 * the SAN notation.
 *
 * @param m Pointer to the Move object to be converted.
 */
void MoveParser::pretty(Move *m)
{
    SimplePieceType piece = simplePiece(m->getPiece());
    string san = "";

    // only translate XY moves
    if (m->getType() != MOVE_TYPE_XY)
    {
        m->setHuman(m->getAlgebraic());
        return;
    }

    // now check which type inside the XY and translate it
    // pawn moves
    if (piece == PIECE_TYPE_PAWN)
    {
        m->setHuman(m->getAlgebraic().substr(2, 2));
    }

    // piece moves that are not captures
    else if (!m->isCapture())
    {
        // first try simple move, without ambiguity
        san += pieceToChar(piece);
        san += m->getAlgebraic().substr(2, 2);
        Move test = translate(san, MOVE_TYPE_SIMPLE, lastGame);
        if (test.isValid() && !test.isAmbiguous())
        {
            m->setHuman(san);
        }

        // if ambiguous, then try adding the column
        if (test.isAmbiguous())
        {
            san = "";
            san += pieceToChar(piece);
            san += m->getAlgebraic().substr(0, 1);
            san += m->getAlgebraic().substr(2, 2);
            Move test = translate(san, MOVE_TYPE_AMBIGUOUS, lastGame);
            if (test.isValid() && !test.isAmbiguous())
            {
                m->setHuman(san);
                return;
            }
        }

        // if still ambiguous, then try adding the row
        if (test.isAmbiguous())
        {
            san = "";
            san += pieceToChar(piece);
            san += m->getAlgebraic().substr(1, 1);
            san += m->getAlgebraic().substr(2, 2);
            Move test = translate(san, MOVE_TYPE_AMBIGUOUS, lastGame);
            if (test.isValid() && !test.isAmbiguous())
            {
                m->setHuman(san);
                return;
            }
        }
    }
    // piece moves that are captures
    else if (m->isCapture())
    {
        // first try simple move, without ambiguity
        san += pieceToChar(piece);
        san += "x";
        san += m->getAlgebraic().substr(2, 2);
        Move test = translate(san, MOVE_TYPE_CAPTURE_SIMPLE, lastGame);
        if (test.isValid() && !test.isAmbiguous())
        {
            m->setHuman(san);
            return;
        }

        // if ambiguous, then try adding the column
        if (test.isAmbiguous())
        {
            san = "";
            san += pieceToChar(piece);
            san += m->getAlgebraic().substr(0, 1);
            san += "x";
            san += m->getAlgebraic().substr(2, 2);
            Move test = translate(san, MOVE_TYPE_CAPTURE_LONG, lastGame);
            if (test.isValid() && !test.isAmbiguous())
            {
                m->setHuman(san);
                return;
            }
        }

        // if still ambiguous, then try adding the row
        if (test.isAmbiguous())
        {
            san = "";
            san += pieceToChar(piece);
            san += m->getAlgebraic().substr(1, 1);
            san += "x";
            san += m->getAlgebraic().substr(2, 2);
            Move test = translate(san, MOVE_TYPE_CAPTURE_LONG, lastGame);
            if (test.isValid() && !test.isAmbiguous())
            {
                m->setHuman(san);
                return;
            }
        }
    }
    // default move
    else
    {
        m->setHuman(m->getAlgebraic());
    }
}


/*!
 * Internal method to translate a pawn move (specified by column+row, e.g. d4).
 *
 * @param input Input string that the user enter as the move.
 * @param g     Pointer to the current game's object.
 *
 * @return a Move object with the translated move.
 */
Move MoveParser::translatePawn(string input, Game *g)
{
    string match = "";

    vector<Move> moves = g->getBoard()->getAllValidMoves(g->getPlayer());

    // move matching
    for (unsigned int i = 0; i < moves.size(); i++)
    {
        match = moves[i].getAlgebraic().substr(2, 2);
        if ((input == match) && (simplePiece(moves[i].getPiece()) == PIECE_TYPE_PAWN))
        {
            move.fill(moves[i]);
            move.setHuman(input);
        }
    }

    return move; 
}


/*!
 * Internal method to translate a simple move (specified by piece+column+row,
 * e.g. Nd4).
 *
 * @param input Input string that the user enter as the move.
 * @param g     Pointer to the current game's object.
 *
 * @return a Move object which is ready to be utilized.
 */
Move MoveParser::translateSimple(string input, Game *g)
{
    bool found = false;
    string orig;
    string dest = input.substr(1, 2);
    string match = "";
    SimplePieceType piece;
    SimplePieceType mypiece = charToSimplePiece(input[0]);
    Board *b = g->getBoard();

    vector<Move> moves = b->getAllValidMoves(g->getPlayer());

    // move matching
    for (unsigned int i = 0; i < moves.size(); i++)
    {
        // is a capture, a castle or a promotion
        if (moves[i].getType() != MOVE_TYPE_XY)
            continue;

        orig  = moves[i].getAlgebraic().substr(0, 2);
        match = moves[i].getAlgebraic().substr(2, 2);
        piece = charToSimplePiece(b->getPieceCharAt(bmap(orig)));

        if ((dest == match) && (piece == mypiece))
        {
            if (found)
            {
                move.setValid(true);
                move.setAmbiguous(true);
                return move;
            }
            else
            {
                move.fill(moves[i]);
                move.setHuman(input);
                found = true;
            }
        }
    }

    return move; 
}


/*!
 * Internal method to translate a short castling move (specified by 0-0).
 * Actually, there is no need to translate anything. Instead, the
 * GameManager::perform() method should check the 0-0 and perform the necessary
 * updates according to the current board situation.
 *
 * @param input Input string that the user enter as the move.
 * @param g     Pointer to the current game's object.
 *
 * @return a Move object which is ready to be utilized.
 */
Move MoveParser::translateCastleShort(string input, Game *g)
{
    vector<Move> moves = g->getBoard()->getAllValidMoves(g->getPlayer());

    // support O-O and o-o    
    if ((input == "O-O") || (input == "o-o"))
        input = "0-0";

    // move matching
    for (unsigned int i = 0; i < moves.size(); i++)
    {
        if ((moves[i].getType() == MOVE_TYPE_CASTLE_SHORT) &&
            (input == moves[i].getAlgebraic()))
        {
            move.fill(moves[i]);
            move.setHuman(input);
        }
    }

    return move; 
}


/*!
 * Internal method to translate a well-defined move (specified by
 * column+row-column+row, e.g. d2d4).
 *
 * @param input Input string that the user enter as the move.
 * @param g     Pointer to the current game's object.
 *
 * @return a Move object which is ready to be utilized.
 */
Move MoveParser::translateXY(string input, Game *g)
{
    vector<Move> moves = g->getBoard()->getAllValidMoves(g->getPlayer());

    // move matching
    for (unsigned int i = 0; i < moves.size(); i++)
    {
        if ((moves[i].getType() == MOVE_TYPE_XY) &&
            (input == moves[i].getAlgebraic()))
        {
            move.fill(moves[i]);
            move.setHuman(input);
        }
    }

    return move;
}


/*!
 * Internal method to translate a simple capturing move made by a pawn
 * (specified by column+'x'+column+row, e.g. exd4).
 *
 * @param input Input string that the user enter as the move.
 * @param g     Pointer to the current game's object.
 *
 * @return a Move object which is ready to be utilized.
 */
Move MoveParser::translateCapturePawn(string input, Game *g)
{
    vector<Move> moves = g->getBoard()->getAllValidMoves(g->getPlayer());

    // move matching
    for (unsigned int i = 0; i < moves.size(); i++)
    {
        if ((moves[i].getType() == MOVE_TYPE_CAPTURE_PAWN) &&
            (input == moves[i].getAlgebraic()))
        {
            move.fill(moves[i]);
            move.setHuman(input);
        }
    }

    return move;
}


/*!
 * Internal method to translate a simple capturing move made by a pawn
 * (specified by column+'x'+column, e.g. exd).
 *
 * @param input Input string that the user enter as the move.
 * @param g     Pointer to the current game's object.
 *
 * @return a Move object which is ready to be utilized.
 */
Move MoveParser::translateCapturePawnShort(string input, Game *g)
{
    bool found = false;
    string dest = input.substr(1, 2);
    string match = "";
    Board *b = g->getBoard();

    vector<Move> moves = b->getAllValidMoves(g->getPlayer());

    // move matching
    for (unsigned int i = 0; i < moves.size(); i++)
    {
        if (moves[i].getType() != MOVE_TYPE_CAPTURE_PAWN)
            continue;

        match = moves[i].getAlgebraic().substr(0, 3);

        if (input == match)
        {
            if (found)
            {
                move.setValid(true);
                move.setAmbiguous(true);
                return move;
            }
            else
            {
                move.fill(moves[i]);
                move.setHuman(input);
                found = true;
            }
        }
    }

    return move; 
}


/*!
 * Internal method to translate a simple capturing move (specified by
 * piece+'x'+column+row, e.g. Nxd4).
 *
 * @param input Input string that the user enter as the move.
 * @param g     Pointer to the current game's object.
 *
 * @return a Move object which is ready to be utilized.
 */
Move MoveParser::translateCaptureSimple(string input, Game *g)
{
    bool found = false;
    string orig;
    string dest = input.substr(2, 2);
    string match = "";
    SimplePieceType piece;
    SimplePieceType mypiece = charToSimplePiece(input[0]);
    Board *b = g->getBoard();

    vector<Move> moves = b->getAllValidMoves(g->getPlayer());

    // move matching
    for (unsigned int i = 0; i < moves.size(); i++)
    {
        // is a capture, a castle or a promotion
        if (moves[i].getType() != MOVE_TYPE_XY)
            continue;

        orig  = moves[i].getAlgebraic().substr(0, 2);
        match = moves[i].getAlgebraic().substr(2, 2);
        piece = charToSimplePiece(b->getPieceCharAt(bmap(orig)));

        if ((dest == match) && (piece == mypiece))
        {
            if (found)
            {
                move.setValid(true);
                move.setAmbiguous(true);
                return move;
            }
            else
            {
                move.fill(moves[i]);
                move.setHuman(input);
                found = true;
            }
        }
    }

    return move; 
}


/*!
 * Internal method to translate a simple capturing move (specified by
 * piece+'x'+column, e.g. Nxd).
 *
 * @param input Input string that the user enter as the move.
 * @param g     Pointer to the current game's object.
 *
 * @return a Move object which is ready to be utilized.
 */
Move MoveParser::translateCaptureShort(string input, Game *g)
{
    bool found = false;
    string orig;
    char dest = input[2];
    char match = '\0';
    SimplePieceType piece;
    SimplePieceType mypiece = charToSimplePiece(input[0]);
    Board *b = g->getBoard();
    Piece *test;

    vector<Move> moves = b->getAllValidMoves(g->getPlayer());

    // move matching
    for (unsigned int i = 0; i < moves.size(); i++)
    {
        // is a capture, a castle or a promotion
        if (moves[i].getType() != MOVE_TYPE_XY)
            continue;

        orig  = moves[i].getAlgebraic().substr(0, 2);
        match = (moves[i].getAlgebraic())[2];
        piece = charToSimplePiece(b->getPieceCharAt(bmap(orig)));
        test  = b->getPieceAt(moves[i].getDestination());

        if ((dest == match) && (piece == mypiece) && (test) &&
                               (test->getColor() != moves[i].getColor()))
        {
            if (found)
            {
                move.setValid(true);
                move.setAmbiguous(true);
                return move;
            }
            else
            {
                move.fill(moves[i]);
                move.setHuman(input);
                found = true;
            }
        }
    }

    return move; 
}


/*!
 * Internal method to translate an ambiguous move (specified by
 * piece+column|row+column+row, e.g. Nde4, N2d3).
 *
 * @param input Input string that the user enter as the move.
 * @param g     Pointer to the current game's object.
 *
 * @return a Move object which is ready to be utilized.
 */
Move MoveParser::translateAmbiguous(string input, Game *g)
{
    bool found = false;
    string orig;
    string dest = input.substr(2, 2);
    string match = "";
    char orig_col, orig_row;
    SimplePieceType piece;
    SimplePieceType mypiece = charToSimplePiece(input[0]);
    Board *b = g->getBoard();

    vector<Move> moves = b->getAllValidMoves(g->getPlayer());

    orig_col = orig_row = input[1];

    // move matching
    for (unsigned int i = 0; i < moves.size(); i++)
    {
        // is a capture, a castle or a promotion
        if (moves[i].getType() != MOVE_TYPE_XY)
            continue;

        orig  = moves[i].getAlgebraic().substr(0, 2);
        match = moves[i].getAlgebraic().substr(2, 2);
        piece = charToSimplePiece(b->getPieceCharAt(bmap(orig)));

        if (((orig_col == orig[0]) || (orig_row == orig[1])) &&
            (dest == match) && (piece == mypiece))
        {
            if (found)
            {
                move.setValid(true);
                move.setAmbiguous(true);
                return move;
            }
            else
            {
                move.fill(moves[i]);
                move.setHuman(input);
                found = true;
            }
        }
    }

    return move; 
}


/*!
 * Internal method to translate a long castling move (specified by 0-0-0).
 * Actually, there is no need to translate anything. Instead, the
 * GameManager::perform() method should check the 0-0-0 and perform the
 * necessary updates according to the current board situation.
 *
 * @param input Input string that the user enter as the move.
 * @param g     Pointer to the current game's object.
 *
 * @return a Move object which is ready to be utilized.
 */
Move MoveParser::translateCastleLong(string input, Game *g)
{
    vector<Move> moves = g->getBoard()->getAllValidMoves(g->getPlayer());

    // support O-O-O and o-o-o
    if ((input == "O-O-O") || (input == "o-o-o"))
        input = "0-0-0";

    // move matching
    for (unsigned int i = 0; i < moves.size(); i++)
    {
        if ((moves[i].getType() == MOVE_TYPE_CASTLE_LONG) &&
            (input == moves[i].getAlgebraic()))
        {
            move.fill(moves[i]);
            move.setHuman(input);
        }
    }

    return move; 
}


/*!
 * Internal method to translate a long-specified capturing move (specified by
 * piece+column|row+'x'+column+row, e.g. N2xd4, Ndxe5).
 *
 * @param input Input string that the user enter as the move.
 * @param g     Pointer to the current game's object.
 *
 * @return a Move object which is ready to be utilized.
 */
Move MoveParser::translateCaptureLong(string input, Game *g)
{
    bool found = false;
    string orig;
    string dest = input.substr(3, 2);
    string match = "";
    SimplePieceType piece;
    SimplePieceType mypiece = charToSimplePiece(input[0]);
    Board *b = g->getBoard();

    vector<Move> moves = b->getAllValidMoves(g->getPlayer());

    // move matching
    for (unsigned int i = 0; i < moves.size(); i++)
    {
        // is a capture, a castle or a promotion
        if (moves[i].getType() != MOVE_TYPE_XY)
            continue;

        orig  = moves[i].getAlgebraic().substr(0, 2);
        match = moves[i].getAlgebraic().substr(2, 2);
        piece = charToSimplePiece(b->getPieceCharAt(bmap(orig)));

        if ((dest == match) && (piece == mypiece) &&
            ((input[1] == orig[0]) || (input[1] == orig[1])))
        {
            if (found)
            {
                move.setValid(true);
                move.setAmbiguous(true);
                return move;
            }
            else
            {
                move.fill(moves[i]);
                move.setHuman(input);
                found = true;
            }
        }
    }

    return move; 
}


/*!
 * Internal method to translate a simple promotion move (specified by
 * column+'8'+'='+piece, e.g. d8=Q)
 *
 * @param input Input string that the user enter as the move.
 * @param g     Pointer to the current game's object.
 *
 * @return a Move object which is ready to be utilized.
 */
Move MoveParser::translatePromotionSimple(string input, Game *g)
{
    string match = "";

    vector<Move> moves = g->getBoard()->getAllValidMoves(g->getPlayer());

    // move matching
    for (unsigned int i = 0; i < moves.size(); i++)
    {
        match = moves[i].getAlgebraic().substr(0, 3);

        if ((moves[i].getType() == MOVE_TYPE_PROMOTION_SIMPLE) &&
            (input.substr(0, 3) == match))
        {
            move.fill(moves[i]);
            move.setHuman(input);
        }
    }

    // override the queen by the user's desired promotion piece
    move.setAlgebraic(input);
 
    return move;
}


/*!
 * Internal method to translate a capturing promotion move (specified by
 * column+'x'+column+'8'+'='+piece, e.g. exd8=Q)
 *
 * @param input Input string that the user enter as the move.
 * @param g     Pointer to the current game's object.
 *
 * @return a Move object which is ready to be utilized.
 */
Move MoveParser::translatePromotionCapture(string input, Game *g)
{
    string match = "";

    vector<Move> moves = g->getBoard()->getAllValidMoves(g->getPlayer());

    // move matching
    for (unsigned int i = 0; i < moves.size(); i++)
    {
        match = moves[i].getAlgebraic().substr(0, 5);

        if ((moves[i].getType() == MOVE_TYPE_PROMOTION_CAPTURE) &&
            (input.substr(0, 5) == match))
        {
            move.fill(moves[i]);
            move.setHuman(input);
        }
    }

    // override the queen by the user's desired promotion piece
    move.setAlgebraic(input);

    return move;
}


/*!
 * Internal method to translate a short capturing promotion move (specified by
 * column+'x'+column+'='+piece, e.g. exd=Q)
 *
 * @param input Input string that the user enter as the move.
 * @param g     Pointer to the current game's object.
 *
 * @return a Move object which is ready to be utilized.
 */
Move MoveParser::translatePromotionCaptureShort(string input, Game *g)
{
    bool found = false;
    string match = "";
    Board *b = g->getBoard();
    char desired = input[4];

    vector<Move> moves = b->getAllValidMoves(g->getPlayer());

    // move matching
    for (unsigned int i = 0; i < moves.size(); i++)
    {
        if (moves[i].getType() != MOVE_TYPE_PROMOTION_CAPTURE)
            continue;

        match = moves[i].getAlgebraic().substr(0, 3);

        if (input.substr(0, 3) == match)
        {
            if (found)
            {
                move.setValid(true);
                move.setAmbiguous(true);
                return move;
            }
            else
            {
                move.fill(moves[i]);
                move.setHuman(input);
                found = true;
            }
        }
    }

    // override the queen by the user's desired promotion piece
    string override = match;
    override += "8=";
    override += desired;
    move.setAlgebraic(override);

    return move;
}
