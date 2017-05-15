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
 * @file timer.h
 *
 * TODO: replace this by C++11 timers (using clock_t).
 */
#ifndef TIMER_H
#define TIMER_H
 
#include <sys/timeb.h>
#include "definitions.h"
 
struct Timer
{
	U64   startTime;   
	U64   stopTime;    
	U64   currentTime;
	U64   stopTimeDelta;
	timeb startBuffer;   
	timeb stopBuffer;   
	timeb currentBuffer;
	BOOLTYPE running;  
 
	void init();               // start the timer
	void stop();               // stop the timer
	void reset();              // reset the timer
	void display();                   // display time in seconds with 2 decimals
	void displayhms();         // display time in hh:mm:ss.dd
	U64 getms();               // return time in milliseconds
	U64 getsysms();         // return system time
	Timer();
};
 
 
#endif
