#pragma once

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include "Command.h"

/*---------------------------------------------------------------------------------------
--	SOURCE FILE:	HostToIP.cpp -   A function to extract IP address and Host Name information
--									by entering either an IP address or a Host Name.
--
--	PROGRAM:		Assign1.exe
--
--	FUNCTIONS:		Winsock 2 API
--
--	DATE:			January 20, 2017
--
--	REVISIONS:		
--	Version 1.0
--
--	DESIGNERS:		Tim Makimov
--
--	PROGRAMMER:		Tim Makimov
--
--	NOTES:
--     This function takes a user specified input string and returns both IP address 
--		information as well as Host Name (and aliases if there are any). 
---------------------------------------------------------------------------------------*/


char *hostToIp(char *argv)
{
	int		a, err;
	struct	hostent *hp;
	struct	in_addr *addr_p;
	char	**p;
	char	ip_address[256];      // String for IP address

	WORD wVersionRequested;
	WSADATA wsaData;
	wVersionRequested = MAKEWORD(2, 2);
	// Open up a Winsock v2.2 session
	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0) {
		strcpy(error, "WSAStartup failed with error:  ");
		sprintf(error, "%d", err);
		return error;
	}

	addr_p = (struct in_addr*)malloc(sizeof(struct in_addr));

	if (isdigit(*argv))	// Dotted IP?
	{
		if ((a = inet_addr(argv)) == 0)
		{
			WSACleanup();
			free(addr_p);
			return("IP Address must be of the form x.x.x.x");
		}

		// Copy IP address  into ip_address
		strcpy(ip_address, argv);
		addr_p->s_addr = inet_addr(ip_address);

		hp = gethostbyaddr((char *)addr_p, PF_INET, sizeof(addr_p));

		if (hp == NULL)
		{
			WSACleanup();
			free(addr_p);
			strcpy(error, "Host information for ");
			strcat(error, ip_address);
			strcat(error, " not found.");
			return(error);
		}
	}
	else
	{
		if ((hp = (hostent*)gethostbyname(argv)) == NULL) 	// Host name?
		{
			switch (h_errno)
			{
			case HOST_NOT_FOUND:
				WSACleanup();
				free(addr_p);
				strcpy(error, "No such host ");
				strcat(error, argv);
				return(error);
			case TRY_AGAIN:
				WSACleanup();
				free(addr_p);
				strcpy(error, "Host ");
				strcat(error, argv);
				strcat(error, " try again later");
				return(error);
			case NO_RECOVERY:
				WSACleanup();
				free(addr_p);
				strcpy(error, "Host ");
				strcat(error, argv);
				strcat(error, " DNS Error");
				return(error);
			case NO_ADDRESS:
				WSACleanup();
				free(addr_p);
				strcpy(error, "No IP Address for ");
				strcat(error, argv);
				return(error);
			default:
				WSACleanup();
				free(addr_p);
				strcpy(error, "Unknown Error: ");
				sprintf(error, "%d", h_errno);
				return(error);
			}
		}
	}
	strcpy(result, "");
	int aliasCount = 0;

	for (p = hp->h_addr_list; *p != 0; p++)
	{
		struct in_addr in;
		memcpy(&in.s_addr, *p, sizeof(in.s_addr));
		//Populate result string with results returned from socket
		strcat(result, "IP address: ");
		strcat(result, inet_ntoa(in));
		strcat(result, "\t");
		strcat(result, "Host name: ");
		strcat(result, hp->h_name);
		strcat(result, "\r\n\r\n");

		//Add aliases to result if there are any
		if (hp->h_aliases[0] != 0)
		{
			strcat(result, "Aliases: ");
			strcat(result, hp->h_aliases[aliasCount]);
			aliasCount++;
		}
	}
	WSACleanup();
	free(addr_p);
	return result;
}