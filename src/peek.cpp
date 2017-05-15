#ifndef _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_DEPRECATE
#endif



#include <stdio.h>
#include <string.h>

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#include <conio.h>
#else
#include <unistd.h>
#include <sys/select.h>


#define DWORD int32_t

static int Bioskey(void) {
  fd_set readfds;
  struct timeval timeout;
   
  FD_ZERO(&readfds);
  FD_SET(fileno(stdin), &readfds);
   /* Set to timeout immediately */
  timeout.tv_sec = 0;
  timeout.tv_usec = 0;
  select(16, &readfds, 0, 0, &timeout);
   
  return (FD_ISSET(fileno(stdin), &readfds));
}


static int _kbhit(void)
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
#include <stdio.h>
#include <string.h>


#include "extglobals.h" 
#include "functions.h" 
#include "timer.h" 

void Board::readClockAndInput()
{
	// check if we need to stop, because time is up, or because the user has hit the keyboard.
	// UPDATEINTERVAL defines how often this check is done in terms of nodes searched.
	// For example, if the search speed is 1000 knods per second, then a value of UPDATEINTERVAL = 100000 
	// will result in 10 checks per second (or 0.1s time intervals)

	DWORD nchar;
	char command[80];

	// reset countdown
	countdown = UPDATEINTERVAL;

	if ((!XB_NO_TIME_LIMIT && ((timer.getms() - msStart) > maxTime)) || (!XB_MODE && _kbhit()))
	{
		timedout = true;
		return;
	}

noPonder:

  
    #if defined(_WIN32) || defined(_WIN64)
	if ((XB_MODE) && (PeekNamedPipe(GetStdHandle(STD_INPUT_HANDLE), NULL, 0, NULL, &nchar, NULL)))
	#else
	if ((XB_MODE) && Bioskey())
	#endif
	{

		for (CMD_BUFF_COUNT = 0; CMD_BUFF_COUNT < (int)nchar; CMD_BUFF_COUNT++)
	    {
			CMD_BUFF[CMD_BUFF_COUNT] = getc(stdin);
			// sometimes we do not receive a newline character 
			if (((CMD_BUFF_COUNT+1)==(int)nchar) || CMD_BUFF[CMD_BUFF_COUNT] == '\n')
//			if (CMD_BUFF[CMD_BUFF_COUNT] == '\n')

			{
				if (CMD_BUFF[CMD_BUFF_COUNT] == '\n') CMD_BUFF[CMD_BUFF_COUNT] = '\0';
				else CMD_BUFF[CMD_BUFF_COUNT+1] = '\0';
//				CMD_BUFF[CMD_BUFF_COUNT] = '\0';

				if (CMD_BUFF=="" || !CMD_BUFF_COUNT) return;

				sscanf(CMD_BUFF, "%s", command);

				// do not stop thinking/pondering/analyzing for any of the following commands:
				if (!strcmp(command, ".")) return;
				if (!strcmp(command, "?")) return;
				if (!strcmp(command, "bk")) return;
				if (!strcmp(command, "easy")) 
				{
					XB_PONDER = false;
					return;
				}
				if (!strcmp(command, "hint")) return; 
				if (!strcmp(command, "nopost"))
				{
					XB_POST = false;
					return;
				}	
				if (!strcmp(command, "otim")) 
				{
					sscanf(CMD_BUFF, "otim %d", &XB_OTIM);
					XB_OTIM *= 10;  // convert centiseconds to miliseconds;
					goto noPonder;
				}	
				if (!strcmp(command, "post")) 
				{
					XB_POST = true;
					return;
				}	
				if (!strcmp(command, "time")) 
				{
					sscanf(CMD_BUFF,"time %d",&XB_CTIM);
					XB_CTIM *= 10; // convert centiseconds to milliseconds
					goto noPonder;
				}
				timedout = true;
				CMD_BUFF_COUNT = (int)strlen(CMD_BUFF);
				XB_DO_PENDING = true;
				return;
			}
		}
	}
	return;
}








