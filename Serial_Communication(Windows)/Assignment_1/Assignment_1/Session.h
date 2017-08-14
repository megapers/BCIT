#pragma once
#include <windows.h>

void connect(HANDLE&, LPCSTR, bool&);
void disconnect(HANDLE&, bool&, LPCSTR);

/*----------------------------------------------------------------------------------
	SOURCE FILE:	Session.cpp		An application that enables the user 
									to establish connection (session) as well
									as to terminate the connection

	PROGRAM:		"Dumb Terminal"

	FUNCTIONS:		
					void connect(HANDLE&, LPCSTR, bool&);
					void disconnect(HANDLE&, bool&);

	DATE:			October 5, 2016

	REVISIONS:		(Date and Description)

	DESIGNR:		Tim Makimov

	PROGRAMMER:		Tim Makimov

	NOTES:
	The program is designed to be part of OSI model's layers that is responsible for
	establishing and terminating connection between 2 PCs. 
-----------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------
	FUNCTION:		connect

	DATE:			October 5, 2016	

	REVISIONS:		(Date and Description)

	DESIGNR:		Tim Makimov

	PROGRAMMER:		Tim Makimov

	INTERFACE:		void connect(HANDLE&, LPCSTR, bool&)

	RETURNS:		void

	NOTES:			This function creates a connection by openning a Serial Port.
					
-----------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------
	FUNCTION:		disconnect

	DATE:			October 5, 2016

	REVISIONS:		(Date and Description)

	DESIGNR:		Tim Makimov

	PROGRAMMER:		Tim Makimov

	INTERFACE:		void disconnect(HANDLE&, bool&)

	RETURNS:		void

	NOTES:			This function terminates connection by closing the comm port.

-----------------------------------------------------------------------------------*/