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
 * @file src/application/test.cpp
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <cmath>
#include <iomanip>
#include "utils"
#include "application/manager"
#include "application/prompt"
#include "ai/adaptive"



/*!
 * Test how many nodes can be evaluated per second.
 *
 * This function is a profiling function that is useful just do demonstrate how
 * good is the evaluation algorithm.
 */
void ApplicationManager::testNodesPerSecond()
{
    // store current AI settings to restore them after the test
    int cur_depth = ai->getDepth();
    unsigned prevTPM = ai->getTPM();
    bool wasBookInUse = usingBook();

    // test settings
    ai->setDepth(NODES_TEST_DEPTH);
    ai->setTPM(NODES_TEST_TIME);
    useBook(false);

    // perform the test
    clock_t start;
    clock_t end;
    start = clock();
    ai->getMove();
    end = clock();

    // estimate nodes per second
    double ms = (end - start) / (CLOCKS_PER_SEC / 1000);
    cout << "Nodes: " << ai->getNodes() << " nodes evaluated in " << fixed << setprecision(2) <<  (ms / 1000) << "s ";
    cout << "(" << fixed << setprecision(2) << (ai->getNodes() / ms);
    cout << " Knps)." << endl;

    cout << "Recursion: " << ai->getAB() << " in " << fixed << setprecision(2) << (ms / 1000) << "s ";
    cout << "(" << fixed << setprecision(2) << (ai->getAB() / ms) * 1000 << " iterations/s)." << endl;

    // restore AI settings after the test
    useBook(wasBookInUse);
    ai->setTPM(prevTPM);
    ai->setDepth(cur_depth);
}


/*!
 * Test how many moves can be performed per second.
 *
 * This function is a profiling function that is useful just do demonstrate how
 * fast is the logic of the game (Board).
 */
void ApplicationManager::testMovesPerSecond()
{
    clock_t start;
    clock_t end;
    Move m;
    vector<Move> moves = board->getAllValidMoves(COLOR_TYPE_WHITE);

    // if the game is finished, then restart the board
    if (moves.size() <= 0)
    {
        gman->restart();
        moves = board->getAllValidMoves(COLOR_TYPE_WHITE);
    }

    // perform the test
    m = moves.back();
    start = clock();
    for (int i = 0; i < MOVES_TEST_TIMES; i++)
    {
        board->doMove(m);
        board->undoMove(m);
    }
    end = clock();

    // estimate nodes per second
    double ms = (end - start) / (CLOCKS_PER_SEC / 1000);
    cout << "Moves: " << MOVES_TEST_TIMES << " moves performed in ";
    cout << fixed << setprecision(2) << (ms / 1000) << "s ";
    cout << "(" << fixed << setprecision(2);
    cout << (MOVES_TEST_TIMES / ms) / 1000 << " Mmps)." << endl;
}

/*!
 * testPerft() performs a test where all the possible moves are found at
 * different depths. This function also prints statistics of how many moves
 * where performed at each depth and what was the time/speed during the test.
 */
void ApplicationManager::testPerft()
{
    cout << "Perft(): " << endl;
    cout << "Ply\t  Moves\t     Time\t Moves/s" << endl;
    cout << flush;

    clock_t start, end;
    uint64_t moves;

    for (int i = 0; i < PERFT_DEPTH_LIMIT + 1; i++)
    {
        start = clock();
        moves = Perft(i, COLOR_TYPE_WHITE);
        end = clock();
        float sec = (end - start) / (CLOCKS_PER_SEC / 1000);
        float speed = moves / sec;

        // PRINT: Depth, Moves, Time, Moves/s
        cout.fill(' ');
        cout << setw(3) << i << "\t" << setw(7) << moves << "\t   " << setw(5) << fixed << setprecision(2) << sec / 1000 << "s\t";
        if (isinf(speed))
            cout << "  -" << endl;
        else
            cout << fixed << setw(4) << setprecision(0) << moves/sec << "K" << endl;
        cout << flush;
    }
}



/*!
 * Source: https://chessprogramming.wikispaces.com/Perft
 *
 * Perft() is a debugging function to walk the move generation tree of
 * strictly legal moves to count all the leaf nodes of a certain depth, which
 * can be compared to predetermined values and used to isolate bugs.
 * 
 * In perft, nodes are only counted at the end after the last doMove(). Thus
 * "higher" terminal nodes (e.g., mate or stalemate) are not counted, instead
 * the number of move paths of a certain depth. Perft ignores draws by
 * repetition, by the fifty-move rule and by insufficient material.
 */
uint64_t ApplicationManager::Perft(unsigned depth, ColorType color)
{
    uint64_t nodesCount = 0;
    ColorType opcolor = oppose(color);
 
    if (depth == 0)
        return 1;
 
    vector<Move> moves = board->getAllValidMoves(color);
    for (unsigned int i = 0; i < moves.size(); i++)
    {
        board->doMove(moves[i]);
        nodesCount += Perft(depth - 1, opcolor);
        board->undoMove(moves[i]);
    }

    return nodesCount;
}
