/*------------------------------------------------------------------------------------------------------------------
-- SOURCE FILE: session.h
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
-- This header file contains the declaration of Session class.
----------------------------------------------------------------------------------------------------------------------*/
#ifndef _SESSION_H
#define _SESSION_H
#include <windows.h>
#include "main.h"
#include "physical.h"



/*------------------------------------------------------------------------------------------------------------------
-- CLASS NAME: Physical
--
-- DATE: October 01, 2016
--
-- FUNCTIONS:
-- 	BOOL initilize();
-- 	BOOL connectReader();
-- 	void disconnectReader();
-- 	BOOL isConnected();
-- 	void setWindow(HWND, HINSTANCE);
--
-- VARIABLES:
--  BOOL boolConnected;
--  Physical ph;
--  HWND hwnd;
--  HINSTANCE hInst;
--  LPSKYETEK_DEVICE *devices = NULL;
--  LPSKYETEK_READER *readers = NULL;
--  LPSKYETEK_TAG *lpTags = NULL;
--  LPSKYETEK_DATA lpData = NULL;
--  SKYETEK_STATUS st;
--  unsigned short count;
--  unsigned int numDevices;
--  unsigned int numReaders;
--
-- DESIGNER: Terry Kang, Tim Makimov
--
-- PROGRAMMER: Terry Kang, Tim Makimov
--
-- NOTES:
-- This class is for session layer of OSI layers.
----------------------------------------------------------------------------------------------------------------------*/
class Session {
private:
	BOOL boolConnected = false;
	Physical ph; // instance of Physical class
	HWND hwnd; // handle for window
	HINSTANCE hInst;
	LPSKYETEK_DEVICE *devices = NULL;
	LPSKYETEK_READER *readers = NULL;
	LPSKYETEK_TAG *lpTags = NULL;
	LPSKYETEK_DATA lpData = NULL;
	SKYETEK_STATUS st;
	unsigned short count;
	unsigned int numDevices;
	unsigned int numReaders;

public:
	BOOL initilize();
	BOOL connectReader();
	void disconnectReader();
	BOOL isConnected();
	void setWindow(HWND, HINSTANCE);
};

#endif // !_SESSION_H

#pragma once
