#include "client.h"


/*--------------------------------------------------------------------------------------
  --	SOURCE FILE:            clientSelect.c
  --
  --    PROGRAM:                client.exe
  --
  --    FUNCTIONS:              void makeUserName(char*, const char*, const char*);

  --    DATE:                   March 10, 2017
  --
  --    REVISIONS:              (Date and Description)
  --
  --
  --    DESIGNERS:              Tim Makimov, Yiaoping Shu
  --
  --    PROGRAMMERS:            Tim Makimov, Yiaoping Shu
  --
  --    NOTES:
  --    This function generates username that is attached to each received message
  --	wiht current date and time concatenated.
  ---------------------------------------------------------------------------------------*/

void makeUserName(char *text, const char *username, const char *sbuf)
{

	time_t t = time(NULL);
	struct tm* tm = localtime(&t);
	char timeDate[26];
	strftime(timeDate, 26, "%Y-%m-%d %H:%M:%S", tm);
	strcpy(text, "[");
	strcat(text, username);
	strcat(text, " ");
	strcat(text, timeDate);
	strcat(text, "]: ");
	strcat(text, sbuf);   
}


/*--------------------------------------------------------------------------------------
  --	SOURCE FILE:            clientSelect.c
  --
  --    PROGRAM:                client.exe
  --
  --    FUNCTIONS:              void clientSelect();

  --    DATE:                   March 10, 2017
  --
  --    REVISIONS:              (Date and Description)
  --
  --
  --    DESIGNERS:              Tim Makimov, Yiaoping Shu
  --
  --    PROGRAMMERS:            Tim Makimov, Yiaoping Shu
  --
  --    NOTES:
  --    This function reads data from stdin and sends it to server. It monitors file descriptors
  --	using select() function. It also creates and writes chat history to a file if specified
  --	by user as an additional argument.
  ---------------------------------------------------------------------------------------*/

void clientSelect()
{

	FD_ZERO(&rset);
	FD_SET(0, &allset);
	FD_SET(1, &allset);
	FD_SET(sd, &allset);


	if(fileCheck == 1)	
	{	
		file = open(fileName,O_CREAT |O_RDWR | O_APPEND,  0666);
	}

	while(1)
	{
		rset = allset;

		sret = select(4, &rset, NULL, NULL, NULL);
		if(sret == 0)
		{
			printf("sret = %d", sret);
		}
		if(FD_ISSET(0, &rset))
		{
			bzero(sbuf, sizeof(sbuf));

			if((input = read(0, sbuf, BUFLEN)) == -1)
			{
				perror("read");
				exit(1);
			}

			char text[BUFLEN];
			makeUserName(text, username, sbuf);


			// Transmit data through the socket
			send(sd, text, BUFLEN, 0);

			if(file != 0)	
			{	
				if((write(file, text, strlen(text))) == -1)//write sent text to file
				{
					perror("write");
					exit(-1);
				}
			}
		}


		else if(FD_ISSET(sd, &rset))

		{               
			bp = rbuf;
			bytes_to_read = BUFLEN;

			// client makes repeated calls to recv until no more data is expected to arrive.
			n = 0;
			while ((n = recv(sd, bp, bytes_to_read, 0)) < BUFLEN)
			{

				bp += n;
				bytes_to_read -= n;
				if(n == 0)
					break;
			}

			if((output = write(1, rbuf, strlen(rbuf))) == -1)
			{
				perror("write");
				exit(1);
			}

			if(file != 0)	
			{	
				if((write(file, rbuf, strlen(rbuf))) == -1)//write received text to file
				{
					perror("write");
					exit(-1);
				}

			} 

			bp = 0;

			if(n == 0) //connection closed by server
			{
				printf("Server closed connection\n");
				break;
			}

		}

	}
}

