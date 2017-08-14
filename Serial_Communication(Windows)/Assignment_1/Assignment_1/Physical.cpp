#include "Physical.h"
#include <windows.h>
#include <stdio.h>

bool writeProc(HANDLE comm, char input)
{
	OVERLAPPED osWrite = { 0 };
	DWORD dwWritten;
	DWORD dwRes;
	BOOL fRes;
	char lpBuf[80] = "";

	sprintf_s(lpBuf, "%c", input); // Convert char to string

	// Create this write operation's OVERLAPPED structure's hEvent.
	osWrite.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	if (osWrite.hEvent == NULL)
	{
		MessageBox(NULL, "Error creating writing OVERLAPPED event", "", MB_OK);
	}
	// Issue write.
	if (!WriteFile(comm, lpBuf, 1, &dwWritten, &osWrite)) {
		if (GetLastError() != ERROR_IO_PENDING) {
			// WriteFile failed, but it isn't delayed. Report error and abort.
			fRes = FALSE;
		}
		else {
			// Write is pending.
			if (!GetOverlappedResult(comm, &osWrite, &dwWritten, TRUE))
				fRes = FALSE;
			else
				// Write operation completed successfully.
				fRes = TRUE;
		}
	}
	else
		// WriteFile completed immediately.
		fRes = TRUE;

	CloseHandle(osWrite.hEvent);

	return fRes;
}


void commSettings(HANDLE hComm, LPCSTR lpszCommName, HWND hwnd)
{
	COMMCONFIG	cc;
	cc.dwSize = sizeof(COMMCONFIG);
	cc.wVersion = 0x100;
	GetCommConfig(hComm, &cc, &cc.dwSize);
	if (!CommConfigDialog(lpszCommName, hwnd, &cc))
		MessageBox(NULL, lpszCommName, "Error setting DCB", MB_OK);
		return;
	if ((SetCommState(hComm, &cc.dcb)) == FALSE)
	{
		
		//return;
	}
}

void setTimeouts(HANDLE hComm)
{
	COMMTIMEOUTS timeouts;
	if (GetCommTimeouts(hComm, &timeouts))
	{
		timeouts.ReadIntervalTimeout = 20;
		timeouts.ReadTotalTimeoutMultiplier = 10;
		timeouts.ReadTotalTimeoutConstant = 100;
		timeouts.WriteTotalTimeoutMultiplier = 10;
		timeouts.WriteTotalTimeoutConstant = 100;
	}
	else
	{
		MessageBox(NULL, "Error geting timeouts:", "", MB_OK);
	}

	if (!SetCommTimeouts(hComm, &timeouts))
	{
		MessageBox(NULL, "Error seting timeouts:", "", MB_OK);
	}

}
