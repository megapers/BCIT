// Program WinMenu.cpp
// COMP 3980, Assignment 1
// Tim Makimov, A009031109

#define STRICT

#include <windows.h>
#include <stdio.h>
#include "winmenu2.h"
#include "Session.h"
#include "Physical.h"

char Name[] = "Comm Shell";
char str[80] = "";
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void print(HWND, char);
void createWindow(HINSTANCE, int);
DWORD WINAPI readProc(LPVOID n);

#pragma warning (disable: 4096)

LPCSTR	lpszCommName = "COM5";
HANDLE hComm, hThrd;
DWORD threadId;
bool connected = false;


int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hprevInstance,
	LPSTR lspszCmdParam, int nCmdShow)
{
	MSG Msg;
	createWindow(hInst, nCmdShow);
	while (GetMessage(&Msg, NULL, 0, 0))
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	return Msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT Message,
	WPARAM wParam, LPARAM lParam)
{
	HDC hdc = NULL;
	PAINTSTRUCT paintstruct;

	switch (Message)
	{
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDM_COM1:
			lpszCommName = "COM5";
			commSettings(hComm, lpszCommName, hwnd);
			break;
		case IDM_COM2:
			lpszCommName = "COM6";
			commSettings(hComm, lpszCommName, hwnd);
			break;
		case IDM_Connect:
			connect(hComm, lpszCommName, connected);//creates comm port connection
			commSettings(hComm, lpszCommName, hwnd);//opens up the port settings menu after user is coneted
			setTimeouts(hComm);//set timeouts
			hThrd = CreateThread(NULL, 0, readProc, hwnd, 0, &threadId);//creates a thread to read from serial port
			break;
		case IDM_Disconnect:
			disconnect(hComm, connected, lpszCommName);
			break;
		case IDM_HELP:
			MessageBox(NULL, "To establish a connection, chose Connect from Connection menu. To disconnect, press ESC or select Disconnect from Connection menu. In order to change comm port settings select a relevant port from Settings.", "", MB_OK);
			break;
		case IDM_Exit:
			PostQuitMessage(0);
			break;
		}
		break;

	case WM_CHAR:	// Process keystroke
		if (wParam == 27)
		{
			disconnect(hComm, connected, lpszCommName);
		}
		writeProc(hComm, wParam);
		break;

	case WM_PAINT:		// Process a repaint message
		hdc = BeginPaint(hwnd, &paintstruct); // Acquire DC
		TextOut(hdc, 0, 0, str, strlen(str)); // output character
		EndPaint(hwnd, &paintstruct); // Release DC
		break;

	case WM_DESTROY:	// Terminate program
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, Message, wParam, lParam);
	}

	return 0;
}

void createWindow(HINSTANCE hInst, int nCmdShow)
{
	HWND hwnd;
	WNDCLASSEX Wcl;

	Wcl.cbSize = sizeof(WNDCLASSEX);
	Wcl.style = CS_HREDRAW | CS_VREDRAW;
	Wcl.hIcon = LoadIcon(NULL, IDI_APPLICATION); // large icon 
	Wcl.hIconSm = NULL; // use small version of large icon
	Wcl.hCursor = LoadCursor(NULL, IDC_ARROW);  // cursor style

	Wcl.lpfnWndProc = WndProc;
	Wcl.hInstance = hInst;
	Wcl.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //white background
	Wcl.lpszClassName = Name;

	Wcl.lpszMenuName = "MYMENU"; // The menu Class
	Wcl.cbClsExtra = 0;      // no extra memory needed
	Wcl.cbWndExtra = 0;

	if (!RegisterClassEx(&Wcl))
		return;

	hwnd = CreateWindow(Name, Name, WS_OVERLAPPEDWINDOW, 10, 10,
		600, 400, NULL, NULL, hInst, NULL);
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
}

void print(HWND hwnd, char a)
{
	HDC hdc = NULL;
	static unsigned k = 0;
	hdc = GetDC(hwnd);			 // get device context
	sprintf_s(str, "%c", a); // Convert char to string
	TextOut(hdc, 10 * k, 0, str, strlen(str)); // output character			
	k++; // increment the screen x-coordinate
	ReleaseDC(hwnd, hdc); // Release device context
}


DWORD WINAPI readProc(LPVOID n)
{
	OVERLAPPED osRead = { 0 };
	DWORD dwCommEvent;
	DWORD dwRead;
	BOOL fRes;
	char  chRead;

	// Create this read operation's OVERLAPPED structure's hEvent.
	osRead.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	if (osRead.hEvent == NULL)
	{
		MessageBox(NULL, "Error creating writing OVERLAPPED event", "", MB_OK);
	}

	if (!SetCommMask(hComm, EV_RXCHAR))
	{
		MessageBox(NULL, "Error setting communications event mask:", "", MB_OK);

	}
	for (; ; ) {
		if (WaitCommEvent(hComm, &dwCommEvent, NULL)) {
			do {
				if (!ReadFile(hComm, &chRead, 1, &dwRead, &osRead))
				{
					print((HWND)n, chRead);
				}
				else
				{
					//ReadFile completed immediately.
					fRes = TRUE;
				}

			} while (dwRead);
		}
	}
	CloseHandle(osRead.hEvent);
	return 0;
}

