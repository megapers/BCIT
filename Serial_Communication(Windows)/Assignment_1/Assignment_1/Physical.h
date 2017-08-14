#pragma once
#include <windows.h>

void commSettings(HANDLE, LPCSTR, HWND);
void setTimeouts(HANDLE);
bool writeProc(HANDLE, char);

/*----------------------------------------------------------------------------------
	SOURCE FILE:	Physical.cpp		An application that transmits bytes using 
										comm ports

	PROGRAM:		"Dumb Terminal"

	FUNCTIONS:
					void commSettings(HANDLE, LPCSTR, HWND);
					void setTimeouts(HANDLE);
					bool writeProc(HANDLE, char*, DWORD);

	DATE:			October 5, 2016

	REVISIONS:		(Date and Description)

	DESIGNR:		Tim Makimov

	PROGRAMMER:		Tim Makimov

	NOTES:
	The program is designed to be part of OSI model's layers that is responsible for
	transmitting bytes in form of chars between 2 PCs.
-----------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------
	FUNCTION:		commSettings

	DATE:			October 5, 2016

	REVISIONS:		(Date and Description)

	DESIGNR:		Tim Makimov

	PROGRAMMER:		Tim Makimov

	INTERFACE:		void commSettings(HANDLE, LPCSTR, HWND)

	RETURNS:		void

	NOTES:			This function allows the user to set comm port settings such as
					port number, bitrate, number of data bits, 
					number of stop and start bits, and parity

-----------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------
	FUNCTION:		setTimeouts

	DATE:			October 5, 2016

	REVISIONS:		(Date and Description)

	DESIGNR:		Tim Makimov

	PROGRAMMER:		Tim Makimov

	INTERFACE:		void setTimeouts(HANDLE)

	RETURNS:		void

	NOTES:			This function sets timeouts and provides a mechanism for ensuring 
					that a program does not "hang" when an unexpected event occurs or
					an expected event does not occur when sending and receiving data.

-----------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------
	FUNCTION:		writeProc

	DATE:			October 5, 2016

	REVISIONS:		(Date and Description)

	DESIGNR:		Tim Makimov

	PROGRAMMER:		Tim Makimov

	INTERFACE:		bool writeProc(HANDLE, char*, DWORD)

	RETURNS:		bool

	NOTES:			Writes bytes to the serial port

-----------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------
FUNCTION:		readProc

DATE:			October 5, 2016

REVISIONS:		(Date and Description)

DESIGNR:		Tim Makimov

PROGRAMMER:		Tim Makimov

INTERFACE:		bool writeProc(HANDLE, char*, DWORD)

RETURNS:		bool

NOTES:			Reads bytes from the serial port. Unfortunately I wasn't able to move
				this function to physical layer as it was originally designed so 
				I had to leave it in main.

-----------------------------------------------------------------------------------*/