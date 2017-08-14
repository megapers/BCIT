/*--------------------------------------------------------------------------------------
  --	SOURCE FILE:            clientConnect.c
  --
  --    PROGRAM:                client.exe
  --
  --    FUNCTIONS:              
  --	
  --    DATE:                   March 10, 2017
  --
  --    REVISIONS:             	(Date and Description)
  --
  --
  --    DESIGNERS:              Tim Makimov, Yiaoping Shu
  --
  --    PROGRAMMERS:            Tim Makimov, Yiaoping Shu
  --
  --    NOTES:
  --    The funcion  will establish a TCP connection to a user specifed server.
  --	The 4th argument can be supplied as the filename for chat history.
  --	User has to specify username as 3rd argument and filename as 4th argument 
  --	to save the file.
  ---------------------------------------------------------------------------------------*/


#include "client.h"

void clientConnect(int argc, char **argv)
{

	switch(argc)
	{
		case 2:
			host =  argv[1];        // Host name
			port =  SERVER_TCP_PORT;
			username = host;
			break;
		case 3:
			host =  argv[1];
			port =  atoi(argv[2]);  // User specified port
			username = host;
			break;

		case 4: host = argv[1];
			port = atoi(argv[2]);
			username = argv[3];
			break;

		case 5: host = argv[1];
			port = atoi(argv[2]);
			username = argv[3];
			fileName = argv[4];
			fileCheck = 1;	
			break; 

		default:
			fprintf(stderr, "Usage: %s host [port]\n", argv[0]);
			exit(1);
	}

	if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("Cannot create socket");
		exit(1);
	}
	bzero((char *)&server, sizeof(struct sockaddr_in));
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	if ((hp = gethostbyname(host)) == NULL)
	{
		fprintf(stderr, "Unknown server address\n");
		exit(1);
	}
	bcopy(hp->h_addr, (char *)&server.sin_addr, hp->h_length);

	// Connecting to the server
	if (connect (sd, (struct sockaddr *)&server, sizeof(server)) == -1)
	{
		fprintf(stderr, "Can't connect to server\n");
		perror("connect");
		exit(1);
	}
	printf("Connected!\nServer Name: %s\n", hp->h_name);
	pptr = hp->h_addr_list;
	printf("IP Address: %s\n", inet_ntop(hp->h_addrtype, *pptr, str, sizeof(str)));


}

