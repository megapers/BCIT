#pragma once

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include "Command.h"

/*---------------------------------------------------------------------------------------
--	SOURCE FILE:	Service_Port.cpp -   A function to resolve a service name and protocol to
--											its port number. And a protocol and port number to service name.
--
--	PROGRAM:		Assign1.exe
--
--	FUNCTIONS:		Winsock 2 API
--
--	DATE:			January 20, 2017
--
--	REVISIONS:		
--  Version 1.0
--
--	DESIGNERS:		Tim Makimov
--
--	PROGRAMMER:		Tim Makimov
--
--	NOTES:
--     This function takes 2 input strings and based on BOOL flag eiher returns 
		Port Number or Service Name
---------------------------------------------------------------------------------------*/

char* serviceToPort(char *input1, char *input2, bool choice)
{
	struct servent *sv;
	int s_port;
	WORD wVersionRequested = MAKEWORD(2, 2);
	WSADATA wsaData;
	strcpy(result, "");

	// Open up a Winsock v2.2 session
	WSAStartup(wVersionRequested, &wsaData);

	if (choice == true)//Get port number selected
	{
		sv = getservbyname(input1, input2);
		if (sv == NULL)
		{
			WSACleanup();
			return "Error in getservbyname";
		}
		sprintf(result, "%d", ntohs(sv->s_port));
	}
	else //Get service name selected
	{
		s_port = atoi(input1);
		sv = getservbyport(htons(s_port), input2);
	
		if (sv == NULL)
		{
			WSACleanup();
			return "Error in getservbyport";
		}
		strcat(result, sv->s_name);
	}

	WSACleanup();
	
	return result;
}