/*------------------------------------------------------------------------------
-- SOURCE FILE: main.cpp - The COMMAND state of the protocol. 
-- 							Main entrance point
--
-- PROGRAM: Assign1.exe
--
-- DATE: January 20, 2017
--
-- REVISIONS:
-- Version 1.0
--
-- DESIGNER: Tim Makimov 
--
-- PROGRAMMER: Tim Makimov
--
-- NOTES:
-- This is the main starting point of the program - controls UI and Dialog's behavior
------------------------------------------------------------------------------*/

#pragma once

#include <stdio.h>
#include "winmenu2.h"
#include <winsock2.h>
#include <Windows.h>
#include <windowsx.h>
#include <malloc.h>
#include <string>
#include <regex>


/****************************
DATA MEMEBER DECLARATIONS*
******************************/
static bool radio = false;
static HDC hdc;
static HINSTANCE hInstance;
static HWND hwnd1; // Window handler for the main window
static MSG Msg;//Holds message(s) from message queue
static char text[50];//user input string
static char text1[50];//user input string
static char error[50];//error that is returned as output
static char result[2000];//result returned from the socket


/****************************
MEMEBER FUNCTION DECLARATIONS*
******************************/
BOOL CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK dialogProc(HWND, UINT, WPARAM, LPARAM);
void configCommPort(HANDLE, LPCSTR, HWND);
void availableCOM(HWND);
char *generateString(char *, HWND, int);
char *hostToIp(char *);
char *serviceToPort(char*, char*, bool);
void trimStr(char*);
void clear(void);