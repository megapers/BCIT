/*------------------------------------------------------------------------------------------------------------------
-- SOURCE FILE: session.cpp
--
-- PROGRAM: RFID Reader
--
-- FUNCTIONS:
-- 	BOOL initilize();
-- 	BOOL connectReader();
-- 	void disconnectReader();
-- 	BOOL isConnected();
-- 	void setWindow(HWND, HINSTANCE);
--
--
-- DATE: November 15, 2016
--
-- DESIGNER: Terry Kang, Tim Makimov
--
-- PROGRAMMER: Terry Kang, Tim Makimov
--
-- NOTES:
-- This file contains the definition of functions of Session class.
--
----------------------------------------------------------------------------------------------------------------------*/

#include "session.h"

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: initilize
--
-- DATE: November 15, 2016
--
-- DESIGNER: Terry Kang, Tim Makimov
--
-- PROGRAMMER: Terry Kang, Tim Makimov
--
-- INTERFACE: BOOL Session::initilize(LPCSTR paramCommName)
--
-- RETURNS: sucess of failiure of initilizing com port
--
-- NOTES:
-- a function to initilize the session
----------------------------------------------------------------------------------------------------------------------*/
BOOL Session::initilize() {
	wchar_t str[100];
	swprintf_s(str, L"%s - COMMAND MODE", Name);
	SetWindowText(hwnd, str); // set window name with the name of com port. 

	HMENU hMenu = GetMenu(hwnd);

	EnableMenuItem(hMenu,
		IDM_CONNECT, MF_ENABLED); // enable the connect menu
	EnableMenuItem(hMenu,
		IDM_DISCONNECT, MF_GRAYED | MF_DISABLED); // disable the disconnect menu

	return true;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: connetReader
--
-- DATE: November 15, 2016
--
-- DESIGNER: Terry Kang, Tim Makimov
--
-- PROGRAMMER: Terry Kang, Tim Makimov
--
-- INTERFACE: BOOL Session::connectReader()
--
-- RETURNS: sucess of failiure of creating session to RFID reader
--
-- NOTES:
-- This function searches the connected RFID readers and connects to it if found.
----------------------------------------------------------------------------------------------------------------------*/
BOOL Session::connectReader() {
	HDC		hdc = GetDC(hwnd);
	cls(hwnd);
	displayString(hwnd, TEXT("Discovering Devices..."));
	if (!boolConnected) {
		if ((numDevices = SkyeTek_DiscoverDevices(&devices)) > 0)
		{
			if ((numReaders = SkyeTek_DiscoverReaders(devices, numDevices, &readers)) > 0)
			{
				displayString(hwnd, TEXT("Discovered Reader: "));

				boolConnected = true; // CONNECTED

				HMENU hMenu = GetMenu(hwnd);

				EnableMenuItem(hMenu,
					IDM_CONNECT, MF_GRAYED | MF_DISABLED); // disable the connect menu
				EnableMenuItem(hMenu,
					IDM_DISCONNECT, MF_ENABLED); // enable the setting menu

				wchar_t str[100];
				swprintf_s(str, L"%s - CONNECT MODE", Name);
				SetWindowText(hwnd, str); // set window name with the name of com port. 
				swprintf_s(str, _T("Name : %s"), readers[0]->friendly);
				displayString(hwnd, str);
				swprintf_s(str, _T("ID : %s"), readers[0]->rid);
				displayString(hwnd, str);
				swprintf_s(str, _T("Model : %s"), readers[0]->model);
				displayString(hwnd, str);

				ph.initilize(hwnd, readers[0]); // initilize physical layer for com port.
				ph.startRead();

			}
			else {
				displayString(hwnd, TEXT("Failed to Discover Reader"));
				return false;
			}
		}
		else {
			displayString(hwnd, TEXT("Failed to Discover Device"));
			return false;
		}
	}
	return true;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: disconnectReader
--
-- DATE: November 15, 2016
--
-- DESIGNER: Terry Kang, Tim Makimov
--
-- PROGRAMMER: Terry Kang, Tim Makimov
--
-- INTERFACE: BOOL Session::disconnectReader()
--
-- RETURNS: void
--
-- NOTES:
-- This function closes the current session.
----------------------------------------------------------------------------------------------------------------------*/
void Session::disconnectReader() {
	HMENU hMenu = GetMenu(hwnd);
	EnableMenuItem(hMenu,
		IDM_DISCONNECT, MF_GRAYED | MF_DISABLED); // disable the disconnect menu
	EnableMenuItem(hMenu,
		IDM_CONNECT, MF_ENABLED); // enable the connect menu

	boolConnected = false; //DISCONNECTED
	ph.stopRead(); // stop reading from the port

	wchar_t str[100];
	swprintf_s(str, L"%s - COMMAND MODE", Name);
	SetWindowText(hwnd, str); // set window name with the name of com port. 
	SkyeTek_FreeReaders(readers, numReaders);
	SkyeTek_FreeDevices(devices, numDevices);
	cls(hwnd);
	displayString(hwnd, TEXT("Devices diconnected..."));

}


/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: isConnected
--
-- DATE: November 15, 2016
--
-- DESIGNER: Terry Kang, Tim Makimov
--
-- PROGRAMMER: Terry Kang, Tim Makimov
--
-- INTERFACE: BOOL Session::isConnected()
--
-- RETURNS: true if there is a session to the RFID reader, false if not.
--
-- NOTES:
-- This function return the connection status of the session to the reader.
----------------------------------------------------------------------------------------------------------------------*/
BOOL Session::isConnected() {
	return boolConnected;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: setWindow
--
-- DATE: November 15, 2016
--
-- DESIGNER: Terry Kang, Tim Makimov
--
-- PROGRAMMER: Terry Kang, Tim Makimov
--
-- INTERFACE: void Session::setWindow(HWND paramhwnd, HINSTANCE paramhInst)
--
-- RETURNS: void
--
-- NOTES:
-- This function stores the handle for window and instance for this program as class member for future uses.
----------------------------------------------------------------------------------------------------------------------*/
void Session::setWindow(HWND paramhwnd, HINSTANCE paramhInst) {
	hwnd = paramhwnd;
	hInst = paramhInst;
}