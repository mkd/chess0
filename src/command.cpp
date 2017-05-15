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



/*!
 * @file command.cpp
 *
 * This file contains the functions to handle user input and execute the
 * appropriate command inside the application.
 */
#if defined(_WIN32) || defined(_WIN64)
#include <conio.h>
#else
#include <unistd.h>

#include <sys/select.h>


int _kbhit(void)
{
struct timeval tv;
fd_set read_fd;

tv.tv_sec=0;
tv.tv_usec=0;
FD_ZERO(&read_fd);
FD_SET(0,&read_fd);

if(select(1, &read_fd, NULL, NULL, &tv) == -1)
return 0;

if(FD_ISSET(0,&read_fd))
return 1;

return 0;
}


#endif

#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "defines.h"
#include "functions.h"
#include "extglobals.h"
#include "board.h"
#include "timer.h"



using namespace std;



// Global variables
unsigned char movingSide = WHITE_MOVE;



/*
 * Read console input and execute the commands (also provide XBoard protocol).
 */
void commands()
{
	int i, j, number;
	int fenhalfmoveclock;
	int fenfullmovenumber;
	char fen[100];
	char fencolor[1];      
	char fencastling[4];
	char fenenpassant[2];
	char sanMove[12];
	char command[80];
	char userinput[80];
	U64 msStart,msStop, perftcount;
	Timer timer;
	Move move, dummy;


    // Application's main loop:
    // - Show the prompt and ask for an input (move or command)
    // - Read the input and check if it is a move or a command
    // - If invalid command or move, show error and return to previous prompt
    // - If valid command, execute and return to previous prompt
    // - If valid move, perform the move.
    //
    // This loop is exited by entering Ctrl+D or the commands "quit" or "exit",
    // which call terminateApp().
	while (1) 
	{ 
		cout << flush;


		// think & move
		if (XB_MODE)
		{
			if (XB_COMPUTER_SIDE == board.nextMove) 
			{
                // TODO: if useBook, get the move from the book
                    
                
                // store who's moving right now for netScore in search
                // statistics
                if (board.nextMove)
                    movingSide = BLACK_MOVE;
                else
                    movingSide = WHITE_MOVE;


                // search the move
				move = board.think();


				if (move.moveInt) 
				{
					printf("move "); printf("%s",SQUARENAME[move.getFrom()]); printf("%s",SQUARENAME[move.getTosq()]); 
					if (move.isPromotion()) printf("%s",PIECECHARS[move.getProm()]);
					printf("\n");
					makeMove(move);
					board.endOfGame++;
					board.endOfSearch = board.endOfGame;
				}
			}

			cout << flush;


			// ponder
			if (XB_COMPUTER_SIDE != XB_NONE && XB_COMPUTER_SIDE != XB_ANALYZE && XB_PONDER && board.endOfGame)
			{
                // TODO: if useBook, get the move from the book
                    
                
                // store who's moving right now for netScore in search
                // statistics
                if (board.nextMove)
                    movingSide = BLACK_MOVE;
                else
                    movingSide = WHITE_MOVE;


                // search the move
				XB_NO_TIME_LIMIT = true;
				move = board.think();
				XB_NO_TIME_LIMIT = false;
			} 


			// analyze
			if (XB_COMPUTER_SIDE == XB_ANALYZE)
			{
                // TODO: if useBook, get the move from the book
                    
                
                // store who's moving right now for netScore in search
                // statistics
                if (board.nextMove)
                    movingSide = BLACK_MOVE;
                else
                    movingSide = WHITE_MOVE;


                // search the move
				XB_NO_TIME_LIMIT = true;
				move = board.think();
				XB_NO_TIME_LIMIT = false;
			} 
		}

noPonder:

		// =================================================================
		// display the command prompt
		// =================================================================

		if (!XB_MODE)
		{
            int curMoveNumber = (board.endOfGame / 2) + 1;
			if (board.nextMove == WHITE_MOVE) cout << "White (" << curMoveNumber << "): ";
			else cout << "Black (" << curMoveNumber << "): ";
			cout << flush;
		}

		// =================================================================
		// read input, but only after attending a pending command received during 
		// search/ponder/analyze:
		// =================================================================

		if (!XB_DO_PENDING)
		{
			for (CMD_BUFF_COUNT = 0; (CMD_BUFF[CMD_BUFF_COUNT] = getchar()) != '\n'; CMD_BUFF_COUNT++);
			CMD_BUFF[CMD_BUFF_COUNT+1] = '\0';
		}
		XB_DO_PENDING = false;
	
		// =================================================================
		// ignore empty lines
		// =================================================================

		if (!CMD_BUFF_COUNT) continue; 

		// =================================================================
		// extract the first word
		// =================================================================

		sscanf(CMD_BUFF, "%s", command);

		// =================================================================
		// help, h or ?: show this help - list of CONSOLE-ONLY COMMANDS
		// =================================================================
		if ((!XB_MODE) && ((!strcmp(command, "help")) || (!strcmp(command, "h")) || (!strcmp(command, "?"))))
		{ 
			cout << endl << "help:" << endl;
			cout << "black               : BLACK to move" << endl;
			cout << "cc                  : play computer-to-computer " << endl;
			cout << "d                   : display board " << endl;
			cout << "eval                : show static evaluation of this position" << endl;
			cout << "exit                : exit program " << endl;
			cout << "game                : show game moves " << endl;
			cout << "go                  : computer next move " << endl;
			cout << "help, h, or ?       : show this help " << endl;
			cout << "info                : display variables (for testing purposes)" << endl;
			cout << "ini                 : read the initialization file" << endl;
			cout << "memory n            : max memory to use (in MB)" << endl;
			cout << "move e2e4, or h7h8q : enter a move (use this format)" << endl;
			cout << "moves               : show all legal moves" << endl;
			cout << "new                 : start new game" << endl;
			cout << "perft n             : calculate raw number of nodes from here, depth n " << endl;
			#ifdef VERBOSE_SEE
				cout << "qsearch             : shows sorted capture movelist" << endl;
			#endif
			cout << "quit                : exit program " << endl;
			cout << "r                   : rotate board " << endl;
			cout << "readfen filename n  : reads #-th FEN position from filename" << endl;
			cout << "sd n                : set the search depth to n" << endl;
			cout << "setup               : setup board... " << endl;
			cout << "test filename       : starts search on all FEN position in 'filename'" << endl;
			cout << "                      using current time & search depth parameters" << endl;
			cout << "                      output is written in test.log" << endl;
			cout << "time s              : time per move in seconds" << endl;
			cout << "undo                : take back last move" << endl;
			cout << "white               : WHITE to move" << endl;
			cout << endl;
			continue; 
		}

		// accepted: in reply to the "feature" command
		if (XB_MODE && !strcmp(command, "accepted")) continue; 

		// analyze: enter analyze mode
		if (XB_MODE && !strcmp(command, "analyze")) 
		{ 
			XB_COMPUTER_SIDE = XB_ANALYZE;			
			continue; 
		}

		// black: BLACK to move
		if (!XB_MODE && !strcmp(command, "black") && board.nextMove == WHITE_MOVE)
		{ 
			board.hashkey ^= KEY.side;
			board.endOfSearch = 0; 
			board.endOfGame = 0;
			board.nextMove = BLACK_MOVE;
			continue; 
		}

		// bk: show book moves from this position, if any
		if (XB_MODE && !strcmp(command, "bk")) continue; 

		// cc: play computer-to-computer
		if (!XB_MODE && !strcmp(command, "cc"))    
		{ 
			while (!_kbhit() && !board.isEndOfgame(i, dummy))
			{
                // TODO: if useBook, get the move from the book
                    
                
                // store who's moving right now for netScore in search
                // statistics
                if (board.nextMove)
                    movingSide = BLACK_MOVE;
                else
                    movingSide = WHITE_MOVE;


                // search the move
				move = board.think();


				if (move.moveInt) 
				{
					makeMove(move);
					board.endOfGame++;
					board.endOfSearch = board.endOfGame;
					board.display();
				}
			}
			continue; 
		}

		// computer: the opponent is also a computer chess engine
		if (XB_MODE && !strcmp(command, "computer")) continue; 

		// cores n: informs the engine on how many CPU cores it is allowed to use maximally
		if (XB_MODE && !strcmp(command, "cores")) continue; 

		// d: display board
		if (!XB_MODE && !strcmp(command, "d"))
		{
			board.display();
			continue; 
		}

		// easy: turn off pondering
		if (XB_MODE && !strcmp(command, "easy"))    
		{ 
			XB_PONDER = false;
			continue; 
		}

		// =================================================================
		// egtpath type path: informs the engine in which directory it can find end-game tables
		// =================================================================

		if (XB_MODE && !strcmp(command, "egtpath")) continue; 

		// =================================================================
		// eval: show static evaluation of this position
		// =================================================================

		if (!XB_MODE && !strcmp(command, "eval"))    
		{ 
			if (board.nextMove)
                number = -board.eval();
            else
                number = board.eval();

			cout << "eval score = " << number << endl;
			continue; 
		}

		// =================================================================
		// exit: leave analyze mode / exit program (if not in WB)
		// =================================================================

		if (!strcmp(command, "exit"))    
		{ 
			if (XB_MODE)
			{
				XB_COMPUTER_SIDE = XB_NONE;			
				continue; 
			}
			else break;
		}

		// =================================================================
		// force: Set the engine to play neither color
		// =================================================================

		if (XB_MODE && !strcmp(command, "force"))   
		{ 
			XB_COMPUTER_SIDE = XB_NONE;
			continue; 
		}


		// game: show game moves
		if (!XB_MODE && !strcmp(command, "game"))   
		{ 
			if (board.endOfGame)
			{
				// make a temporary copy of board.gameLine[];
				number = board.endOfGame;
				GameLineRecord *tmp = new GameLineRecord[number];
				memcpy(tmp, board.gameLine, number * sizeof(GameLineRecord));

				// unmake all moves:
				for (i = number-1 ; i >= 0 ; i--) 
				{ 
					unmakeMove(tmp[i].move);
					board.endOfSearch = --board.endOfGame;
				}

				// redo all moves:
				j = board.nextMove;
				for (i = 0 ; i < number; i++)
				{
					// move numbering:
					if (!((i+j+2)%2)) cout << (i+2*j+2)/2 << ". ";
					else if (!i) cout << "1. ... ";

					// construct the move string
					toSan(tmp[i].move, sanMove);
					cout << sanMove; 

					// output CRLF, or space:
					if (!((i+j+1)%2)) cout << endl;
					else cout << " ";

					// make the move:
					makeMove(tmp[i].move);
					board.endOfSearch = ++board.endOfGame;
				}
				cout << endl;

				// delete the temporary copy:
				delete[] tmp;
			} 
			else
			{
				cout << "there are no game moves" << endl;        
			}
			continue; 
		}


		// go: leave force mode and set the engine to play the color that is on move
		if (!strcmp(command, "go"))      
		{
			if (XB_MODE)
			{
				XB_COMPUTER_SIDE = board.nextMove;  
				continue; 
			}
			else
			{
				if (!board.isEndOfgame(i, dummy))
				{
                    // TODO: if useBook, get the move from the book
                    
                    
                    // store who's moving right now for netScore in search
                    // statistics
                    if (board.nextMove)
                        movingSide = BLACK_MOVE;
                    else
                        movingSide = WHITE_MOVE;


                    // search the move
					move = board.think();


					if (move.moveInt) 
					{
                        // tell which move the computer chose
                        cout << endl;
					    toSan(move, sanMove);
                        int curMoveNumber = (board.endOfGame / 2) + 1;
                        if (board.nextMove)
                            cout << "\aMy move: " << curMoveNumber << "... " << sanMove << endl;
                        else
                            cout << "\aMy move: " << curMoveNumber << ". " << sanMove << endl;

                        // make the move and show the board
						makeMove(move);
						board.endOfGame++;
						board.endOfSearch = board.endOfGame;
					}
					board.display();
					board.isEndOfgame(i, dummy);
					CMD_BUFF_COUNT = '\0';
				}
				else
				{
					board.display();
					CMD_BUFF_COUNT = '\0';
				}
			}
			continue;
		}

		// =================================================================
		// hard: turn on pondering
		// =================================================================

		if (XB_MODE && !strcmp(command, "hard"))    
		{ 
			XB_PONDER = true;  
			continue; 
		}

		// =================================================================
		// hint: respond with "Hint: xxx", where xxx is a suggested move
		// =================================================================

		if (XB_MODE && !strcmp(command, "hint")) 
		{
				continue; 
		}

		// =================================================================
		// ics hostname: the engine is playing on an Internet Chess Server (ICS) with the given hostname
		// =================================================================

		if (XB_MODE && !strcmp(command, "ics"))     { continue; }

		// =================================================================
		// info: display variables (for testing purposes)
		// =================================================================

		if (!XB_MODE && !strcmp(command, "info"))    
		{ 
			info();
			continue; 
		}

		// =================================================================
		// ini: read the initialization file
		// =================================================================

		if (!XB_MODE && !strcmp(command, "ini"))    
		{ 
			readIniFile();
			continue; 
		}

		// =================================================================
		// level mps base inc: set time controls
		// =================================================================

		if (XB_MODE && !strcmp(command, "level"))   
		{
			sscanf(CMD_BUFF, "level %d %d %d", &XB_MPS, &XB_MIN, &XB_INC) == 3 ||  
			sscanf(CMD_BUFF, "level %d %d:%d %d", &XB_MPS, &XB_MIN, &XB_SEC, &XB_INC);
			XB_INC *= 1000;
			continue;
		}

		// =================================================================
		// memory n: informs the engine on how much memory it is allowed to use maximally, in MB
		// =================================================================

		if (XB_MODE && !strcmp(command, "memory")) continue; 

		// =================================================================
		// moves: show all legal moves
		// =================================================================

		if (!XB_MODE && !strcmp(command, "moves"))    
		{ 
			board.moveBufLen[0] = 0;
			board.moveBufLen[1] = movegen(board.moveBufLen[0]);
			cout << endl << "moves from this position:" << endl;
			number = 0;
			for (i = board.moveBufLen[0]; i < board.moveBufLen[1]; i++)
			{
				makeMove(board.moveBuffer[i]);
				if (isOtherKingAttacked())
				{
					unmakeMove(board.moveBuffer[i]);
				}
				else
				{
					unmakeMove(board.moveBuffer[i]);
					toSan(board.moveBuffer[i], sanMove);
					cout << ++number << ". " << sanMove << endl;
				}
			}
			continue; 
		}

		// =================================================================
		// move: enter a move (use this format: move e2e4, or h7h8q)
		// =================================================================

		if (!XB_MODE && !strcmp(command, "move"))    
		{
			sscanf(CMD_BUFF,"move %s",userinput);
			// generate the pseudo-legal move list
			board.moveBufLen[0] = 0;
			board.moveBufLen[1] = movegen(board.moveBufLen[0]);
 
			if (isValidTextMove(userinput, move))        // check to see if the user move is also found in the pseudo-legal move list
			{
				makeMove(move);
 
				if (isOtherKingAttacked())              // post-move check to see if we are leaving our king in check
				{
					unmakeMove(move);
					cout << "    invalid move, leaving king in check: " << userinput << endl;
				}
				else
				{
					board.endOfGame++;
					board.endOfSearch = board.endOfGame;
					board.display();
				}
			}
			else
			{
				cout << "    move is invalid or not recognized: " << userinput << endl;
			}
			continue; 
		}

		// =================================================================
		// name <something>: informs the engine of its opponent's name
		// =================================================================

		if (XB_MODE && !strcmp(command, "name")) continue; 

		// =================================================================
		// new: reset the board to the standard chess starting position
		// =================================================================

		if (!strcmp(command, "new"))     
		{
			board.init(); 
			if (XB_MODE) 
			{
				XB_COMPUTER_SIDE = BLACK_MOVE;
				board.searchDepth = MAX_PLY;
			}
			continue; 
		}

		// =================================================================
		// nopost: turn off thinking/pondering output
		// =================================================================

		if (XB_MODE && !strcmp(command, "nopost"))  
		{ 
			XB_POST = false;
			continue; 
		}

		// =================================================================
		// otim n: set a clock that belongs to the opponent, in centiseconds
		// =================================================================
		if (XB_MODE && !strcmp(command, "otim"))    
		{ 
			// do not start pondering after receiving time commands, as a move will follow immediately
			sscanf(CMD_BUFF, "otim %d", &XB_OTIM);
			XB_OTIM *= 10;  // convert to miliseconds;
			goto noPonder; 
		} 

		// =================================================================
		// option name[=value]: setting of an engine-define option
		// =================================================================
		if (XB_MODE && !strcmp(command, "option"))  continue;

		// =================================================================
		// perft: calculate raw number of nodes from here, depth n 
		// =================================================================
		if (!XB_MODE && !strcmp(command, "perft"))  
		{ 
			sscanf(CMD_BUFF,"perft %d", &number);
			cout << "    starting perft " << number << "..." << endl;
			timer.init();
			board.moveBufLen[0] = 0;
 
			msStart = timer.getms();
			perftcount = perft(0, number);
			msStop = timer.getms();
 
			cout << "nodes        = " << perftcount << ", " << msStop - msStart << " ms, ";
			if ((msStop - msStart) > 0)
			cout << (perftcount/(msStop - msStart)) << " knods/s";
			cout << endl;
			CMD_BUFF_COUNT = '\0';
 
			continue; 
		}

		// =================================================================
		// ping n: reply by sending the string pong n
		// =================================================================

		if (XB_MODE && !strcmp(command, "ping"))    
		{ 
			sscanf(CMD_BUFF,"ping %d", &number);
			cout << "pong " << number << endl; 
			continue; 
		}

		// =================================================================
		// post: turn on thinking/pondering output
		// =================================================================

		if (XB_MODE && !strcmp(command, "post"))    
		{ 
			XB_POST = true; 
			continue; 
		}

		// =================================================================
		// protover n: protocol version
		// =================================================================

		if (XB_MODE && !strcmp(command, "protover")) 
		{
			cout << "feature ping=1" << endl;
			cout << "feature setboard=1" << endl;
			cout << "feature colors=0" << endl;
			cout << "feature usermove=1" << endl;
			cout << "feature memory=1" << endl;
			cout << "feature debug=1" << endl;
			cout << "feature done=1" << endl;

			continue;
		}

		#ifdef VERBOSE_SEE
		// =================================================================
		// qsearch: shows sorted capture movelist
		// =================================================================
				if (!XB_MODE && !strcmp(command, "qsearch"))  
				{ 
					board.moveBufLen[0] = 0;
					board.moveBufLen[1] = captgen(board.moveBufLen[0]);
					cout << endl << "sorted capturing moves from this position:" << endl;
					cout << endl << "        score:" << endl;
					number = 0;
					for (i = board.moveBufLen[0]; i < board.moveBufLen[1]; i++)
					{
						makeMove(board.moveBuffer[i]);
						if (isOtherKingAttacked())
						{
							unmakeMove(board.moveBuffer[i]);
						}
						else
						{
							unmakeMove(board.moveBuffer[i]);
							cout << ++number << ". "; 
							displayMove(board.moveBuffer[i]);
							cout << "   " << board.moveBuffer[i + OFFSET].moveInt << endl;
						}
					}
					continue; 
				}
		#endif

		// =================================================================
		// quit: exit program
		// =================================================================

		if ((!strcmp(command, "quit")) || (!strcmp(command, "q")))
        {
            cout << endl << "Goodbye!" << endl;
            break;
        }

		// =================================================================
		// r: rotate board
		// =================================================================
		if (!XB_MODE && !strcmp(command, "r"))  
		{ 
			board.flipBoard = !board.flipBoard;
            board.display();
			continue; 
		}


		// =================================================================
		// flip: flip board
		// =================================================================
		if (!XB_MODE && !strcmp(command, "flip"))  
		{ 
			board.flipBoard = !board.flipBoard;
            board.display();
			continue; 
		}

		// =================================================================
		// random: ignored
		// =================================================================

		if (XB_MODE && !strcmp(command, "random")) continue;

		// =================================================================
		// rating: ICS opponent's rating
		// =================================================================

		if (XB_MODE && !strcmp(command, "rating")) continue;

		// =================================================================
		// readfen filename n: reads #-th FEN position from filename
		// =================================================================

		if (!XB_MODE && !strcmp(command, "readfen"))  
		{ 
			sscanf(CMD_BUFF,"readfen %s %d", userinput, &number);
			board.init();
			readFen(userinput, number);
			board.display();
			continue; 
		}

		// =================================================================
		// rejected: feature is rejected
		// =================================================================

		if (XB_MODE && !strcmp(command, "rejected")) continue;


		// remove: undo the last two moves (one for each player) and continue playing the same color.
		if (XB_MODE && !strcmp(command, "remove"))  
		{ 
			if (board.endOfGame)
			{
				unmakeMove(board.gameLine[--board.endOfGame].move);
				board.endOfSearch = board.endOfGame;
			}
			if (board.endOfGame)
			{
				unmakeMove(board.gameLine[--board.endOfGame].move);
				board.endOfSearch = board.endOfGame;
			}
			continue; 
		}

		// result string {comment}: end the each game, e.g.: result 1-0 {White mates}
		if (XB_MODE && !strcmp(command, "result"))  
		{ 
			XB_COMPUTER_SIDE = XB_NONE;
			continue; 
		}

		// sd n: set the search depth to n
		if (!strcmp(command, "sd"))      
		{ 
			sscanf(CMD_BUFF,"sd %d", &board.searchDepth);
			if (board.searchDepth < 1) board.searchDepth = 1;
			if (board.searchDepth > MAX_PLY) board.searchDepth = MAX_PLY;
			cout << "Search depth: " << board.searchDepth << endl;
			continue; 
		}

		// setboard fen: set up the board/position 
		if (XB_MODE && !strcmp(command, "setboard"))
		{ 
			XB_COMPUTER_SIDE = XB_NONE;
			sscanf(CMD_BUFF, "setboard %s %s %s %s %d %d", fen, fencolor, fencastling, fenenpassant, &fenhalfmoveclock, &fenfullmovenumber);
			setupFen(fen, fencolor, fencastling, fenenpassant, fenhalfmoveclock, fenfullmovenumber);
			continue; 
		}

		// setup: setup board... 
		if (!XB_MODE && !strcmp(command, "setup"))
		{ 
			setup();
			continue; 
		}

		// stopfrac (0-100%): undocumented command to interactively change this 
		// parameter (e.g. for running testsuites), default value is 60
		// Don't start a new iteration if STOPFRAC fraction of the max search time 
		// has passed
		if (!XB_MODE && !strcmp(command, "stopfrac"))      
		{ 
			number = (int)(STOPFRAC * 100);
			sscanf(CMD_BUFF, "stopfrac %d", &number);
			if (number < 1) number = 1;
			if (number > 100) number = 100;
			STOPFRAC = (float)(number/100.0);
			cout << "stopfrac " << 100*STOPFRAC << endl;
			continue; 
		}

		// st time: set time controls
		if (XB_MODE && !strcmp(command, "st"))      
		{ 
			sscanf(CMD_BUFF, "st %d", &board.maxTime);
			board.maxTime *= board.maxTime;  // convert to ms
			continue; 
		}

		// test filename: starts search on all FEN position in 'filename
		if (!XB_MODE && !strcmp(command, "test"))      
		{ 
			sscanf(CMD_BUFF,"test %s", userinput);
			board.init();
			continue; 
		}

		// time: set a clock that belongs to the engine
		if (!strcmp(command, "time"))    
		{ 
			number = (int)board.maxTime / 1000;
			sscanf(CMD_BUFF,"time %d", &number);
			if (number < 1) number = 1;
			if (!XB_MODE) cout << "Max. time per move: " << number << " seconds" << endl;
			if (XB_MODE)
			{
				XB_CTIM = number * 10;
				board.maxTime = number * 10; // conversion to ms
			}
			else
			{
				board.maxTime = number * 1000; // conversion to ms
			}
			goto noPonder; 
		}

		// undo: take back last move
		if ((!strcmp(command, "undo")) || (!strcmp(command, "back")))
		{ 
			if (board.endOfGame)
			{
				unmakeMove(board.gameLine[--board.endOfGame].move);
				board.endOfSearch = board.endOfGame;
				if (!XB_MODE) board.display();
			}
			else if (!XB_MODE) cout << "already at start of game" << endl;
			continue; 
		}

		// =================================================================
		// usermove move: do a move
		// =================================================================

		if (XB_MODE && !strcmp(command, "usermove"))
		{
			sscanf(CMD_BUFF,"usermove %s",userinput);

			// generate the pseudo-legal move list
			board.moveBufLen[0] = 0;
			board.moveBufLen[1] = movegen(board.moveBufLen[0]);
 
			if (isValidTextMove(userinput, move))        // check to see if the user move is also found in the pseudo-legal move list
			{
				makeMove(move);
				if (isOtherKingAttacked())              // post-move check to see if we are leaving our king in check
				{
					unmakeMove(move);
				}
				else
				{
					board.endOfGame++;
					board.endOfSearch = board.endOfGame;
				}
			}
			else
			{
			} 
			continue;
		}

		// =================================================================
		// variant: the game is not standard chess
		// =================================================================

		if(XB_MODE && !strcmp(command, "variant")) continue; 

		// =================================================================
		// white: WHITE to move
		// =================================================================

		if (!XB_MODE && !strcmp(command, "white") && board.nextMove == BLACK_MOVE)    
		{ 
			board.hashkey ^= KEY.side;
			board.endOfSearch = 0; 
			board.endOfGame = 0;
			board.nextMove = WHITE_MOVE;
			continue; 
		}

		// =================================================================
		// xboard: put the engine into "xboard mode", stop all unsolicited output
		// =================================================================

		if (!XB_MODE && !strcmp(command, "xboard"))  
		{ 
			cout << endl;
			XB_COMPUTER_SIDE = XB_NONE;
			XB_MODE = true;
			XB_POST = false;
			board.init();
			continue; 
		}

		// =================================================================
		// unknown command: 
		// =================================================================

		printf("Error: unknown command: %s\n", command);
	}
}
