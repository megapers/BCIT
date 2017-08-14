#include "Session.h"
#include <windows.h>

void connect(HANDLE &commPort, LPCSTR CommName, bool &connection)
{
	if (connection == false)
	{
		if ((commPort = CreateFile(CommName, GENERIC_READ | GENERIC_WRITE, 0,
			NULL, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, NULL))
			== INVALID_HANDLE_VALUE)
		{
			MessageBox(NULL, "Error opening COM port", CommName, MB_OK);
		}
		else
		{
			MessageBox(NULL, "Conected to port", CommName, MB_OK);
			connection = true;
		}
	}
	else
	{
		return;
	}
}

void disconnect(HANDLE& commPort, bool& connection, LPCSTR CommName)
{
	if (connection == true)
	{
		CloseHandle(commPort);
		//ExitThread(threadId);//terminate thread
		MessageBox(NULL, "Disconnected from port", CommName, MB_OK);
		connection = false;
	}
	else
	{
		return;
	}
}

