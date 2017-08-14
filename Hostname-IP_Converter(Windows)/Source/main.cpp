#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#define STRICT
#include "Command.h"

#pragma warning (disable: 4096)
#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

/*--------------------------------------------------------------------------
-- FUNCTION:  WinMain
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
-- INTERFACE: int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
--
-- RETURNS: If the function succeeds, terminating when it receives a WM_QUIT message,
--			it should return the exit value contained in that message's wParam parameter.
--			If the function terminates before entering the message loop, it should return zero.
--
-- NOTES: Retrieves messages from message loop translating incoming messages and dispatching them to the application's message
procedure
--------------------------------------------------------------------------*/
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hprevInstance, LPSTR lspszCmdParam, int nCmdShow)
{
	hInstance = hInst;
	hwnd1 = CreateDialog(hInst, MAKEINTRESOURCE(IDD_DIALOG_MAIN), NULL, WndProc);
	HMENU hMenu = LoadMenu(hInst, MAKEINTRESOURCE(MENU_MYMENU));
	SetMenu(hwnd1, hMenu);
	
	// Display & update window
	ShowWindow(hwnd1, nCmdShow);
	UpdateWindow(hwnd1);

	while (GetMessage(&Msg, NULL, 0, 0))
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	return Msg.wParam;
}
/*--------------------------------------------------------------------------
-- FUNCTION:  WndProc
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
-- INTERFACE: BOOL CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM)
--
-- RETURNS: BOOL
--
-- NOTES: Processes mesages received from WinMain
--------------------------------------------------------------------------*/
BOOL CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	switch (Message)
	{
	case WM_COMMAND:
		if ((HWND)lParam == GetDlgItem(hwnd, BTN_CONVERT))
		{
			SetWindowText(GetDlgItem(hwnd, EDIT_RX), hostToIp(generateString(text, hwnd, EDIT_TX)));
			
			//clear global buffers
			memset(text, 0, sizeof(text));
			memset(result, 0, sizeof(result));
			memset(error, 0, sizeof(error));
			break;
		}
		if ((HWND)lParam == GetDlgItem(hwnd, BTN_CLEAR))
		{
			clear();
			break;
		}
		switch (wParam)
		{
		case IDCANCEL:
			PostQuitMessage(0);
			break;
		case MENU_PROP: // popup a dialog for IP/host name conversion.
			DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG), hwnd, dialogProc);
			break;
		case MENU_HELP:
			MessageBox(NULL,
				"Enter host name or IP address to make conversion. Select Options -> Service name/Port lookup to extract service name, port and protocol properties.",
				"", MB_OK | MB_ICONINFORMATION);
			break;
		case MENU_EXIT:
			PostQuitMessage(0);
			break;
		}
		break;
	case WM_DESTROY:	// Terminate program
		PostQuitMessage(0);
		break;
	default:
		return FALSE;
	}
}

/*--------------------------------------------------------------------------
-- FUNCTION: generateString
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
-- INTERFACE: char* generateString(char*, HWND, int)
--
-- RETURNS: char*
--
-- NOTES:
-- This function captures user's input from the input box and returns
--	a string valid for further processing
--------------------------------------------------------------------------*/


char* generateString(char *input, HWND hDlg, int nIDDlgItem)
{
	const int bufferLength = GetWindowTextLength(GetDlgItem(hDlg, nIDDlgItem)) + 1;
	input[bufferLength];
	GetWindowText(GetDlgItem(hDlg, nIDDlgItem), input, bufferLength);
	input[bufferLength - 1] = 0;
	trimStr(input);
	return(input);
}

/*--------------------------------------------------------------------------
-- FUNCTION: trimStr
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
-- INTERFACE: void trimStr(char*)
--
-- RETURNS: void
--
-- NOTES:
-- This function uses C++ string class and it's regex_replace function
-- to eliminate following and trailing spaces and other characters
--------------------------------------------------------------------------*/

void trimStr(char* s)
{
	std::string str = s;
	str = std::regex_replace(str, std::regex("^ +| +$|( ) +"), "$1");
	strcpy(s, str.c_str());
}


/*--------------------------------------------------------------------------
-- FUNCTION: clear
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
-- INTERFACE: void clear()
--
-- RETURNS: void
--
-- NOTES:
-- This function uses clears all global buffers to make sure that they're ready
-- for a new input. It also clears both input and output fields.
--------------------------------------------------------------------------*/

void clear()
{
	memset(text, 0, sizeof(text));
	memset(result, 0, sizeof(result));
	memset(error, 0, sizeof(error));
	SetWindowText(GetDlgItem(hwnd1, EDIT_TX), "");
	SetWindowText(GetDlgItem(hwnd1, EDIT_RX), "");
}


/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: dialogProc
--
-- DATE: October 01, 2016
--
-- REVISIONS: 
-- Version 1.0
--
-- DESIGNER: Tim Makimov
--
-- PROGRAMMER: Tim Makimov
--
-- INTERFACE: INT_PTR CALLBACK comDialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
--
-- RETURNS: return TRUE if it processed the message, and FALSE if it did not.
-- If the dialog box procedure returns FALSE, the dialog manager performs the default dialog operation in response to the message.
--
-- NOTES:
-- Application-defined callback function used with the CreateDialog and DialogBox families of functions.
-- Provides GUI for get Port Number and get Service Name functionality
----------------------------------------------------------------------------------------------------------------------*/

INT_PTR CALLBACK dialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
	
	int output = EDIT3;
	int input1 = EDIT1;
	int input2 = EDIT2;
	
	switch (message) {
	case WM_INITDIALOG:
		radio = true;
		CheckRadioButton(hDlg, RB_NAME, RB_PORT, RB_NAME);//default state
		Edit_Enable(GetDlgItem(hDlg, EDIT1), TRUE);
		Edit_Enable(GetDlgItem(hDlg, EDIT2), TRUE);	
		break;
	case WM_COMMAND:

		if ((HWND)lParam == GetDlgItem(hDlg, BTN_LOOKUP))
		{
			//clear global variables
			memset(text, 0, sizeof(text));
			memset(text1, 0, sizeof(text1));
			memset(result, 0, sizeof(result));
			memset(error, 0, sizeof(error));

			if(radio == false)
			{
				output = EDIT1;
				input1 = EDIT3;
				input2 = EDIT2;
			}
			SetWindowText(GetDlgItem(hDlg, output), serviceToPort((generateString(text, hDlg, input1)), (generateString(text1, hDlg, input2)), radio));
			break;
		}

		switch (wParam) {
		case BTN_CANCEL:
			EndDialog(hDlg, 0); // close dialog
			return TRUE;
		case WM_DESTROY:
			EndDialog(hDlg, 0); // close dialog
			return TRUE;
		case WM_CHAR:	// Process keystroke
			if (wParam == 27)
			{
				EndDialog(hDlg, 0); // close dialog
				return TRUE;
			}
		case RB_NAME:
			radio = true;
			CheckRadioButton(hDlg, RB_NAME, RB_PORT, RB_NAME);
			Edit_Enable(GetDlgItem(hDlg, EDIT1), TRUE);
			Edit_Enable(GetDlgItem(hDlg, EDIT2), TRUE);
			Edit_Enable(GetDlgItem(hDlg, EDIT3), FALSE);
			return TRUE;
		
		case RB_PORT:
			radio = false;
			CheckRadioButton(hDlg, RB_NAME, RB_PORT, RB_PORT);
			Edit_Enable(GetDlgItem(hDlg, EDIT1), FALSE);
			Edit_Enable(GetDlgItem(hDlg, EDIT2), TRUE);
			Edit_Enable(GetDlgItem(hDlg, EDIT3), TRUE);
			return TRUE;
		}
		break;

	case WM_SETFOCUS:
		return TRUE;
	}
	return FALSE;
}