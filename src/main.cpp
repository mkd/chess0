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
 * @file main.cpp
 *
 * This file contains the main routine to get the application started and
 * accepting input from the user.
 */
#ifndef _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_DEPRECATE
#endif
// windows only:
#if defined(_wn32) || defined(_WIN64)
#include <Windows.h>
#include <io.h>

#else
#include <unistd.h>
#include <stdio.h>
#define CDECL

#endif

#include <signal.h>
#include <iostream>
#include <thread>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdint.h>
#include <time.h>
#include <signal.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <assert.h>
#include <math.h>
#include <sys/timeb.h>


#include "defines.h"
#include "functions.h"
#include "globals.h"



using namespace std;



/*!
 * Main function that is executed when Chess0x is launched.
 */
int CDECL main(int argc, char *argv[])
{
	int i;

	/* don't quit when xboard sends SIGINT */
    if(!isatty(STDIN_FILENO))
        signal(SIGINT, SIG_IGN);

    /* force line buffering on stdin and stdout */
    
    setbuf(stdout, NULL);
    setbuf(stdin, NULL);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stdin, NULL, _IONBF, 0);   


	dataInit();
	board.init();

    unsigned cores = thread::hardware_concurrency();
  
    cout << "Welcome to " << PROG_NAME << "!" << endl; 
    cout << endl;
    cout << cores << " CPUs (1 CPU in use)" << endl;

	// read the initialization file:
	strcpy(PATHNAME, argv[0]);
	strcpy(INIFILE, "chess0.ini");  // default name
	// check command-line to see if we need to use another ini-file:
	// usage: "chess0.exe i=somefile.ini"
	for (i = 1; i < argc; i++) 
	{
		if (!strncmp(argv[i], "i=", 2)) sscanf(argv[i]+2,"%s", INIFILE);
	}
	readIniFile();

    cout << endl;

	commands();

	return 0;
}
