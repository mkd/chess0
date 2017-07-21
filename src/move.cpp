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



// @file move.cpp
//
// This file contains operations to work set and get information from Move
// objects.
#include <sstream>
#include "move.h"


using namespace std;


 
void Move::clear()
{
       moveInt = 0;
}
 
void Move::setFrom(unsigned int from)  
{   // bits  0.. 5
       moveInt &= 0xffffffc0; moveInt |= (from & 0x0000003f);
}
 
void Move::setTosq(unsigned int tosq)  
{   // bits  6..11      
       moveInt &= 0xfffff03f; moveInt |= (tosq & 0x0000003f) << 6;
}
 
void Move::setPiec(unsigned int piec)  
{   // bits 12..15
       moveInt &= 0xffff0fff; moveInt |= (piec & 0x0000000f) << 12;
} 
 
void Move::setCapt(unsigned int capt)  
{   // bits 16..19
       moveInt &= 0xfff0ffff; moveInt |= (capt & 0x0000000f) << 16;
} 
 
void Move::setProm(unsigned int prom)  
{   // bits 20..23
       moveInt &= 0xff0fffff; moveInt |= (prom & 0x0000000f) << 20;
} 
      
// read move information:
// first shift right, then mask to get the info
 
unsigned int Move::getFrom()  
{   // 6 bits (value 0..63), position  0.. 5
       return (moveInt        & 0x0000003f);
}  
 
unsigned int Move::getTosq()  
{   // 6 bits (value 0..63), position  6..11
       return (moveInt >>  6) & 0x0000003f; 
}   
 
unsigned int Move::getPiec()  
{   // 4 bits (value 0..15), position 12..15
       return (moveInt >> 12) & 0x0000000f; 
}   
 
unsigned int Move::getCapt()  
{   // 4 bits (value 0..15), position 16..19
       return (moveInt >> 16) & 0x0000000f; 
}   
 
unsigned int Move::getProm()  
{   // 4 bits (value 0..15), position 20..23
       return (moveInt >> 20) & 0x0000000f; 
}   
 
// boolean checks for some types of moves.
// first mask, then compare
// Note that we are using the bit-wise properties of piece identifiers, so we cannot just change them anymore !
 
bool Move::isWhitemove()  
{   // piec is white: bit 15 must be 0
       return (~moveInt & 0x00008000) == 0x00008000;
} 
 
bool Move::isBlackmove()  
{   // piec is black: bit 15 must be 1
       return ( moveInt & 0x00008000) == 0x00008000;
} 
 
bool Move::isCapture()    
{   // capt is nonzero, bits 16 to 19 must be nonzero
       return ( moveInt & 0x000f0000) != 0x00000000;
} 
 
bool Move::isKingcaptured()
{   // bits 17 to 19 must be 010
       return ( moveInt & 0x00070000) == 0x00020000;
} 
 
bool Move::isRookmove()
{   // bits 13 to 15 must be 110
       return ( moveInt & 0x00007000) == 0x00006000;
} 
 
bool Move::isRookcaptured()
{   // bits 17 to 19 must be 110
       return ( moveInt & 0x00070000) == 0x00060000;
} 
 
bool Move::isKingmove()
{   // bits 13 to 15 must be 010
       return ( moveInt & 0x00007000) == 0x00002000;
} 
 
bool Move::isPawnmove()
{   // bits 13 to 15 must be 001
       return ( moveInt & 0x00007000) == 0x00001000;
} 
 
bool Move::isPawnDoublemove()
{   // bits 13 to 15 must be 001 &
       //     bits 4 to 6 must be 001 (from rank 2) & bits 10 to 12 must be 011 (to rank 4)
    // OR: bits 4 to 6 must be 110 (from rank 7) & bits 10 to 12 must be 100 (to rank 5)
 
       return ((( moveInt & 0x00007000) == 0x00001000) && (((( moveInt & 0x00000038) == 0x00000008) && ((( moveInt & 0x00000e00) == 0x00000600))) || 
                                                          ((( moveInt & 0x00000038) == 0x00000030) && ((( moveInt & 0x00000e00) == 0x00000800)))));
} 
 
bool Move::isEnpassant()  
{   // prom is a pawn, bits 21 to 23 must be 001
       return ( moveInt & 0x00700000) == 0x00100000;
} 
 
bool Move::isPromotion()  
{   // prom (with color bit removed), .xxx > 2 (not king or pawn)
       return ( moveInt & 0x00700000) >  0x00200000;
} 
 
bool Move::isCastle()     
{   // prom is a king, bits 21 to 23 must be 010
       return ( moveInt & 0x00700000) == 0x00200000;
} 
 
bool Move::isCastleOO()   
{   // prom is a king and tosq is on the g-file
       return ( moveInt & 0x007001c0) == 0x00200180;
} 
 
bool Move::isCastleOOO()  
{   // prom is a king and tosq is on the c-file
       return ( moveInt & 0x007001c0) == 0x00200080;
}


 
/*!
 * Generate an algebraic row+column square from a given internal integer value.
 *
 * @param pos Integer representing the square in the internal format.
 *
 * @return a string (column+row).
 */
string bunmap(int pos)
{
    ostringstream square(ostringstream::out);

    square << static_cast<char>((pos % 8) + 'a');
    square << static_cast<char>((pos / 8) + '1');
    
    return square.str();
}
