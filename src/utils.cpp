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
 * @file src/utils.cpp
 */
#include "utils"
#include <fstream>
#include <iostream>
#include <algorithm>



/*!
 * Check every bit set in a BitBoard and return a list of integers which
 * represent the integer position of the internal representation of the square
 * in a 8x8 board.
 *
 * @param bb BitBoard containing the bitmap with the given positions.
 *
 * @return a list of integers, ordered from LSB to MSB, of which bits are set in
 *         the given BitBoard.
 */
vector<int> positionsFromBitboard(BitBoard bb)
{
    vector<int> positions;

    if (bb == 0)
        return positions;

    BitBoard test = 1;

    for (int i = 0; i < 64; i++)
    {
        if (test & bb)
            positions.push_back(i);

        test <<= 1;
    }

    return positions;
}


/*!
 * Check every position in a given list and set, selectively, each bit in an
 * empty BitBoard, thus generating a BitBoard with bits set to those given
 * positions.
 *
 * @param positions list containing all the positions which must be set.
 *
 * @return a BitBoard containing the bits set to those positions.
 */
BitBoard BitboardFromPositions(vector<int> positions)
{
    BitBoard bb = 0;
    int size = positions.size();

    for (int i = 0; i < size; i++)
        bb |= (BitBoard) 1 << positions[i];

    return bb;
}


/*!
 * Display, using 0s and 1s, the state of a BitBoard.
 *
 * @param bb BitBoard to be displayed.
 */
void displayBitboard(BitBoard bb)
{
    int i = 0;
    int j = 0;
    vector<int> positions = positionsFromBitboard(bb);
    bool found = false;

    cout << "\n       +----+----+----+----+----+----+----+----+\n";

    for (i = 7; i >= 0; i--)
    {
        cout << "  " << i + 1 << "    ";
        for (j = 0; j < 8; j++)
        {
            found = false;

            // check if there is a piece or not
            for (unsigned int k = 0; k < positions.size(); k++)
            {
                if (positions[k] == ((i * 8) + j))
                {
                    found = true;
                    break;
                }
            }
            if (found)
                cout << "|  " << 1 << " ";
            else
                cout << "|  " << 0 << " ";
        }
        cout << "|";
        cout << "\n       +----+----+----+----+----+----+----+----+\n";
    }

    cout << "\n         a    b    c    d    e    f    g    h\n\n";
}


/*!
 * Calculate Time Per Move (TPM) based on total game time available, elapsed
 * time and the number of current moves made.
 *
 * This formula is used to calculate how much time the computer can use to think
 * per move. Based on the initial game time and how much time has been already
 * consumed, the computer can use this formula to recompute how much time is
 * left to make all the moves until the end of the game. This formula asumes
 * that a game is on an average maximum of 100 moves, thus the 100 in the
 * formula. The less time left, the smaller the TPM and therefore the faster the
 * computer will make a move (it will think less).
 *
 * @param totalTime Total time (in seconds) for the whole game (e.g., a 30min
 *        game is 1800 seconds)
 * @param elapsedTime Amount of time consumed (in seconds) by the computer.
 * @param numberOfMoves Amount of moves made in the board, in an absolute
 *        figure. One move is made of two actual moves: White and Black.
 *
 * @return an unsigned short containing the amount of seconds that can be used
 * per move, for the TPM value.
 */
unsigned short calculateTPM(unsigned short totalTime, unsigned short elapsedTime, unsigned short numberOfMoves)
{
    unsigned short newTPM = (totalTime - elapsedTime) / (100 - numberOfMoves);
    if (newTPM < 1)
        return 1;

     return newTPM;
}


/*!
 * Perform some string tests on a given board file (.c0b) to check if the
 * position saved there is not corrupted.
 *
 * @param fileName Name of the file to read.
 *
 * @return true if all the tests were passed, otherwise return false.
 */
bool testBoardFile(string fileName)
{
    // load the given file into a string, for easier manipulation
    std::ifstream ifs(fileName);
    std::string content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
    
    // check if file was empty
    if (content == "")
        return false;

    // check if the file contains exactly two kings
    if (count(content.begin(), content.end(), 'K') != 2)
        return false;

    // check if the file contains at least one '#', but no more than 2 '#'
    if ((count(content.begin(), content.end(), '#') > 2) ||
        (count(content.begin(), content.end(), '#') < 1))
        return false;

    // detect the first '#' which separates white from black pieces
    size_t pos = content.find('#');
    if (pos == string::npos)
        return false;

    // detect white king within list of white pieces
    if (count(content.begin(), content.begin() + pos, 'K') != 1)
        return false;

    // detect black king within list of black pieces
    if (count(content.begin() + pos + 1, content.end(), 'K') != 1)
        return false;

    return true;
}
