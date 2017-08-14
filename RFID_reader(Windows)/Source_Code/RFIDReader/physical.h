/*------------------------------------------------------------------------------------------------------------------
-- SOURCE FILE: physical.h
--
-- PROGRAM: RFID Reader
--
-- DATE: November 15, 2016
--
-- DESIGNER: Terry Kang, Tim Makimov
--
-- PROGRAMMER: Terry Kang, Tim Makimov
--
-- NOTES:
-- This header file contains the declaration of Physical class.
----------------------------------------------------------------------------------------------------------------------*/
#ifndef _PHYSICAL_H
#define _PHYSICAL_H

#include <windows.h>
#include "main.h"
#include <algorithm>

/*------------------------------------------------------------------------------------------------------------------
-- CLASS NAME: Physical
--
-- DATE: November 15, 2016
--
-- FUNCTIONS:
-- BOOL initilize(HWND, LPSKYETEK_READER);
-- BOOL startRead();
-- void stopRead();
-- static DWORD WINAPI selectTag(LPVOID);
--
-- VARIABLES:
-- HANDLE readThread;
-- DWORD threadId;
-- HWND hwnd;
-- LPSKYETEK_READER reader;
-- 
-- DESIGNER: Terry Kang, Tim Makimov
--
-- PROGRAMMER: Terry Kang, Tim Makimov
--
-- NOTES:
-- This class is for physical layer of OSI layers.
----------------------------------------------------------------------------------------------------------------------*/
class Physical {
private:
	HANDLE readThread; // handle for read thread.
	DWORD threadId; // unique id for read thread.
	LPSKYETEK_READER reader;

	static DWORD WINAPI selectTag(LPVOID); // static function for read thread.
public:
	std::vector<Tag> tagList;
	HWND hwnd; // handle for window
	BOOL initilize(HWND, LPSKYETEK_READER);
	BOOL startRead();
	void stopRead();
};

unsigned char tagFound(LPSKYETEK_TAG tag, void* user);


#endif // !_PHYSICAL_H
#pragma once
