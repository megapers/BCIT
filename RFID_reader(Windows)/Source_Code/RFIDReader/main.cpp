/*------------------------------------------------------------------------------------------------------------------
-- SOURCE FILE: main.cpp
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
-- This source file is the main entry for the program.
-- The functions in this file are basically for controling Window.
--
----------------------------------------------------------------------------------------------------------------------*/
#include "main.h"
#include "session.h"

// help message that shows from help menu.
LPCWSTR lpszHelp = L"Select connect to discover the RFID reader and scan tags on the reader after establishing the connection";


DWORD char_x = 0; // x position for character to be displayed.
DWORD char_y = 0; // y position for character to be displayed.

Session session; // instance of Session class.

char comPort[10]; // name of com port selected from the list.
HWND myHwnd; // handle for window



/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: WinMain
--
-- DATE: November 15, 2016
--
-- DESIGNER: Terry Kang, Tim Makimov
--
-- PROGRAMMER: Terry Kang, Tim Makimov
--
-- INTERFACE: int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
--
-- RETURNS: If the function succeeds, terminating when it receives a WM_QUIT message,
--			it should return the exit value contained in that message's wParam parameter.
--			If the function terminates before entering the message loop, it should return zero.
--
-- NOTES:
-- This function is the main function for this proram and calls initilizeWindow function to create window.
----------------------------------------------------------------------------------------------------------------------*/
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hprevInstance,
	LPSTR lspszCmdParam, int nCmdShow)
{
	MSG Msg;
	// attempt to initialize the application and create the main window and class
	if (!initializeWindow(hInst, nCmdShow)) {
		MessageBox(NULL, L"RFID Reader couldn't start!", NULL, MB_OK | MB_ICONSTOP);
		return 0;
	}

	while (GetMessage(&Msg, NULL, 0, 0))
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}

	return Msg.wParam;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: initializeWindow
--
-- DATE: November 15, 2016
--
-- DESIGNER: Terry Kang, Tim Makimov
--
-- PROGRAMMER: Terry Kang, Tim Makimov
--
-- INTERFACE: BOOL initializeWindow(HINSTANCE, int);
--
-- RETURNS: returns true if window is succefully created, otherwise returns false.
--
-- NOTES:
-- This function create window for this program and also initilizes session.
----------------------------------------------------------------------------------------------------------------------*/
BOOL initializeWindow(HINSTANCE hInst, int nCmdShow) {
	HWND hwnd; // handle for window
	WNDCLASSEX Wcl; // window class

	Wcl.cbSize = sizeof(WNDCLASSEX);
	Wcl.style = CS_HREDRAW | CS_VREDRAW;
	Wcl.hIcon = LoadIcon(NULL, IDI_APPLICATION); // large icon 
	Wcl.hIconSm = NULL; // use small version of large icon
	Wcl.hCursor = LoadCursor(NULL, IDC_ARROW);  // cursor style

	Wcl.lpfnWndProc = WndProc;
	Wcl.hInstance = hInst;
	Wcl.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //white background
	Wcl.lpszClassName = Name;

	Wcl.lpszMenuName = L"MYMENU"; // The menu Class
	Wcl.cbClsExtra = 0;      // no extra memory needed
	Wcl.cbWndExtra = 0;

	if (!RegisterClassEx(&Wcl)) {
		PrintError(GetLastError());
		return false;
	}

	hwnd = CreateWindow(Name, Name, WS_OVERLAPPED | WS_SYSMENU, WIN_X, WIN_Y,
		WIN_WIDTH, WIN_HEIGHT, NULL, NULL, hInst, NULL); // create the window.
	myHwnd = hwnd;

	if (!hwnd) {  // if fails to create window.
		PrintError(GetLastError());
		return false;
	}

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);


	session.setWindow(hwnd, hInst); // pass the handle for window and instance to session instance.
	return true;
}
HANDLE				readThrd;

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: menuProc
--
-- DATE: November 15, 2016
--
-- DESIGNER: Terry Kang, Tim Makimov
--
-- PROGRAMMER: Terry Kang, Tim Makimov
--
-- INTERFACE: void menuProc(HWND, WPARAM)
--
-- RETURNS: void
--
-- NOTES:
-- This function handles the menu slection. Called from WndProc function when user slects a menu(WM_COMMAND).
----------------------------------------------------------------------------------------------------------------------*/
void menuProc(HWND hwnd, WPARAM wParam) {
	switch (LOWORD(wParam))
	{
	case IDM_CONNECT: // Connect
		if (session.isConnected()) // if there is already session created, 
			session.disconnectReader(); // close the session
		session.connectReader(); // connect to RFID reader
		break;
	case IDM_DISCONNECT: // Disconnect
		if (session.isConnected()) // if there is already session created, 
			session.disconnectReader(); // close the session before quitting the program.
		break;
	case IDM_HELP: // Help
		MessageBox(NULL, lpszHelp, L"", MB_OK); // shows the help message.
		break;
	case IDM_EXIT:
		if (session.isConnected()) // if there is already session created, 
			session.disconnectReader(); // close the session before quitting the program.
		PostQuitMessage(0); // quit
		break;
	}
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: menu
--
-- DATE: November 15, 2016
--
-- DESIGNER: Terry Kang, Tim Makimov
--
-- PROGRAMMER: Terry Kang, Tim Makimov
--
-- INTERFACE: LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
--
-- RETURNS: The return value is the result of the message processing and depends on the message sent.
--
-- NOTES:
-- This function is the main process of this program.
-- Monitors uesr's action including selecting a menu, pressing keyboard and quitting program.
----------------------------------------------------------------------------------------------------------------------*/
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message,
	WPARAM wParam, LPARAM lParam)
{
	HMENU hMenu;
	static unsigned k = 0;

	switch (Message)
	{
	case WM_CREATE:
		hMenu = GetMenu(hwnd);
		EnableMenuItem(hMenu,
			IDM_DISCONNECT, MF_GRAYED | MF_DISABLED); // disable the disconnect menu
		break;
	case WM_COMMAND: // Select menu
		menuProc(hwnd, wParam); // pass the selection to process
		break;
	case WM_CHAR:	// Process keystroke
		if (wParam == ASCII_ESC)
			if (session.isConnected()) // if there is already session created, 
				session.disconnectReader(); // close the session
		break;

	case WM_DESTROY:	// Terminate program
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, Message, wParam, lParam); // default procedure for window.
	}
	return 0;
}


/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: PrintError
--
-- DATE: October 01, 2016
--
-- DESIGNER: Terry Kang
--
-- PROGRAMMER: Terry Kang
--
-- INTERFACE: void PrintError(DWORD)
--
-- RETURNS: void
--
-- NOTES:
-- This function receives the error number as parameter (GetLastError()) and translates it to message.
----------------------------------------------------------------------------------------------------------------------*/
void PrintError(DWORD dwErrorNo)
{
	LPVOID lpMsgBuf;
	if (!FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		dwErrorNo,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),// Default language
		(LPTSTR)&lpMsgBuf,
		0,
		NULL))
	{
		return;
	} // Tanslate the error code to a message.

	  // Display the string.
	MessageBox(NULL, (LPCTSTR)lpMsgBuf, L"Error", MB_OK | MB_ICONINFORMATION);

	// Free the buffer.
	LocalFree(lpMsgBuf);
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: displayString
--
-- DATE: November 15, 2016
--
-- DESIGNER: Terry Kang, Tim Makimov
--
-- PROGRAMMER: Terry Kang, Tim Makimov
--
-- INTERFACE: void displayString(HWND, LPCWSTR)
--
-- RETURNS: void
--
-- NOTES:
-- This function receives the window handle and string as parameters and displays on the window.
----------------------------------------------------------------------------------------------------------------------*/
void displayString(HWND hwnd, LPCWSTR str) {

	HDC hdc; // handle for device contect
	SIZE sz; // size of charcter
	hdc = GetDC(hwnd);			 // get device context
	char_x = 0;
	TextOut(hdc, char_x, char_y, str, wcslen(str)); // display character on window
	GetTextExtentPoint32(hdc, str, 1, &sz); // get the size of current character.

	char_y += sz.cy; // increse y position.
	ReleaseDC(hwnd, hdc); // Release device context
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: displayTag
--
-- DATE: November 15, 2016
--
-- DESIGNER: Terry Kang, Tim Makimov
--
-- PROGRAMMER: Terry Kang, Tim Makimov
--
-- INTERFACE: void displayTag(HWND, std::vector<Tag>, size_t)
--
-- RETURNS: void
--
-- NOTES:
-- This function receives the window handle and vector<Tag> as parameters and 
-- displays the list of tags stored on the window.
-- also highlights the tag in the given index.
----------------------------------------------------------------------------------------------------------------------*/
void displayTag(HWND hwnd, std::vector<Tag> tagList, size_t index) {

	HDC hdc; // handle for device contect
	SIZE sz; // size of charcter
	hdc = GetDC(hwnd);			 // get device context
	size_t y = char_y + 20;

	for (size_t i = 0; i<tagList.size(); i++) {
		Tag x = tagList[i];
		if (i == index)
			SetBkColor(hdc, RGB(15, 255, 15));
		else
			SetBkColor(hdc, RGB(255, 255, 255));
		TextOut(hdc, 0, y, x.type_, wcslen(x.type_)); // display character on window
		GetTextExtentPoint32(hdc, x.type_, 1, &sz); // get the size of current character.
		y += sz.cy;
		TextOut(hdc, 0, y, x.name_, wcslen(x.name_)); // display character on window
		GetTextExtentPoint32(hdc, x.name_, 1, &sz); // get the size of current character.
		y += sz.cy;
		y += sz.cy;
	}
	ReleaseDC(hwnd, hdc); // Release device context
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: cls
--
-- DATE: November 15, 2016
--
-- DESIGNER: Terry Kang, Tim Makimov
--
-- PROGRAMMER: Terry Kang, Tim Makimov
--
-- INTERFACE: void cls(HWND hwnd)
--
-- RETURNS: void
--
-- NOTES:
-- This funtion clears the window screen.
----------------------------------------------------------------------------------------------------------------------*/
void cls(HWND hwnd)
{
	HDC hdc; // handle for device contect
	SIZE sz; // size of charcter
	hdc = GetDC(hwnd);			 // get device context
	size_t x = 0, y = 0;
	LPCWCHAR space = L" ";
	while (y < WIN_HEIGHT) {
		while (x < WIN_WIDTH) {
			TextOut(hdc, x, y, space, wcslen(space)); // display character on window
			GetTextExtentPoint32(hdc, space, 1, &sz); // get the size of current character.
			x += sz.cx;
		}
		GetTextExtentPoint32(hdc, space, 1, &sz); // get the size of current character.
		y += sz.cy;
		x = 0;
	}
	ReleaseDC(hwnd, hdc); // Release device context
	char_x = char_y = 0;
}
