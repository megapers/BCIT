/*------------------------------------------------------------------------------------------------------------------
-- SOURCE FILE: main.h
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
-- This header file contains the declreations of the functions for main.cpp
-- Also, defines some macro for window's configuration.
-- The functions are basically global functions that are shared with otehr cpp files.
----------------------------------------------------------------------------------------------------------------------*/
#ifndef _MAIN_H
#define _MAIN_H

#include <windows.h>
#include<iostream>
#include<string>
#include <vector>
#include "menu.h"
#include "SkyeTekAPI/SkyeTekAPI.h"
#include "SkyeTekAPI/SkyeTekProtocol.h"

#define WIN_WIDTH 600 // WINDOW WIDTH
#define WIN_HEIGHT 600 // WINDOW HEIGHT
#define WIN_X 100 // X POSITION OF WINDOW
#define WIN_Y 100 // Y POSITION OF WINDOW

static wchar_t Name[] = L"RFID Reader"; // The name of this program.
struct Tag {
	WCHAR *type_;
	WCHAR *name_;
	Tag(WCHAR *type, WCHAR *name) :type_(type), name_(name) {}
};

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL initializeWindow(HINSTANCE, int);

void displayString(HWND, LPCWSTR);
void displayTag(HWND, std::vector<Tag>, size_t);

void PrintError(DWORD);
void menuProc(HWND, WPARAM);
void cls(HWND);


#endif // !_MAIN_H
#pragma once
