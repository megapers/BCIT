/*---------------------------------------------------------------------------------------
  --	SOURCE FILE:		client.c
  --
  --	PROGRAM:		client.exe
  --
  --	FUNCTIONS:		signalHandler() - sends SIGINT on CTRL+C to terminate the program
  --				clientConnect(argc, argv) - conects client to server
  --				clientSelect() - monitors activities on file descriptors	

  --	DATE:			March 10, 2017
  --
  --	REVISIONS:		(Date and Description)
  --
  --
  --	DESIGNERS:		Tim Makimov, Yiaoping Shu
  --
  --	PROGRAMMERS:		Tim Makimov, Yiaoping Shu
  --
  --	NOTES:
  --	The program will establish a TCP connection to a user specifed server.
  -- 	The server can be specified using a fully qualified domain name  and
  --	IP address. The user can also specify filename as 4th argument to save chat history.
  -- 	Server echoes messages sent by this client to other clients, however,
  --	not to this client. Similarly, this client receives messages from other clents 
  --	(echoed back by server).
  ---------------------------------------------------------------------------------------*/
#include "client.h"

void signalHandler(int);


int main (int argc, char **argv)
{
	signal(SIGINT, signalHandler);
	clientConnect(argc, argv);
	clientSelect();
	return (0);
}

/*---------------------------------------------------------------------------------------
  --	SOURCE FILE:		client.c
  --
  --	PROGRAM:		client.exe
  --
  --	FUNCTIONS:		signalHandler()
  -- 
  --	DATE:			March 10, 2017
  --
  --	REVISIONS:		(Date and Description)
  --
  --
  --	DESIGNERS:		Tim Makimov, Yiaoping Shu
  --
  --	PROGRAMMERS:		Tim Makimov, Yiaoping Shu
  --
  --	NOTES:			Handles SIGINT (CTRL+C) signal from the user to terminate
  --				progrma gracefuly.
  ---------------------------------------------------------------------------------------*/

void signalHandler(int param)
{
	printf("\nUser pressed Ctrl+C\n");
	close (sd); 
	fflush(stdout);
	exit(1);
}


