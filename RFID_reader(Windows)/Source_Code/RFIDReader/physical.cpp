/*------------------------------------------------------------------------------------------------------------------
-- SOURCE FILE: physical.cpp
--
-- PROGRAM: RFID Reader
--
-- FUNCTIONS:
-- BOOL initilize(HWND, LPSKYETEK_READER);
-- BOOL startRead();
-- void stopRead();
-- static DWORD WINAPI selectTag(LPVOID);
-- unsigned char tagFound(LPSKYETEK_TAG tag, void* user)
-- 
--
-- DATE: November 15, 2016
--
-- DESIGNER: Terry Kang, Tim Makimov
--
-- PROGRAMMER: Terry Kang, Tim Makimov
--
-- NOTES:
-- This file contains the definition of functions of Physical class.
--
----------------------------------------------------------------------------------------------------------------------*/

#include "physical.h"


/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: initilize
--
-- DATE: November 15, 2016
--
-- DESIGNER: Terry Kang, Tim Makimov
--
-- PROGRAMMER: Terry Kang, Tim Makimov
--
-- INTERFACE: BOOL Physical::initilize(HWND, LPSKYETEK_READER)
--
-- RETURNS: BOOL
--
-- NOTES:
-- This function receives the handles for window and RFID reader and stores as local members for future use.
----------------------------------------------------------------------------------------------------------------------*/
BOOL Physical::initilize(HWND paramhwnd, LPSKYETEK_READER r) {
	reader = r;
	hwnd = paramhwnd;
	return true;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: startRead
--
-- DATE: November 15, 2016
--
-- DESIGNER: Terry Kang, Tim Makimov
--
-- PROGRAMMER: Terry Kang, Tim Makimov
--
-- INTERFACE: BOOL Physical::startRead()
--
-- RETURNS: sucess of failiure of starting read thread.
--
-- NOTES:
-- This function creates new thread for reading tags from the reader.
----------------------------------------------------------------------------------------------------------------------*/
BOOL Physical::startRead() {
	readThread = CreateThread(NULL, 0, selectTag, this, 0, &threadId);

	if (readThread == NULL)// fails to create thread.
		return false;
	return true;
};

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: stopRead
--
-- DATE: November 15, 2016
--
-- DESIGNER: Terry Kang, Tim Makimov
--
-- PROGRAMMER: Terry Kang, Tim Makimov
--
-- INTERFACE: BOOL Physical::stopRead()
--
-- RETURNS: void
--
-- NOTES:
-- This function closes the read thread
----------------------------------------------------------------------------------------------------------------------*/
void Physical::stopRead() {
	CloseHandle(readThread);
};


/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: selectTag
--
-- DATE: November 15, 2016
--
-- DESIGNER: Terry Kang, Tim Makimov
--
-- PROGRAMMER: Terry Kang, Tim Makimov
--
-- INTERFACE: DWORD WINAPI Physical::selectTag(LPVOID)
--
-- RETURNS: return 0;
--
-- NOTES:
-- This function is the procedure for detecting tags from the reader and called when the new thread of reading is created.
----------------------------------------------------------------------------------------------------------------------*/
DWORD WINAPI Physical::selectTag(LPVOID param) {

	Physical* thisObj = (Physical*)(param);
	SkyeTek_SelectTags(thisObj->reader, AUTO_DETECT, tagFound, 0, 1, thisObj);

	return 0;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: tagFound
--
-- DATE: November 15, 2016
--
-- DESIGNER: Terry Kang, Tim Makimov
--
-- PROGRAMMER: Terry Kang, Tim Makimov
--
-- INTERFACE: DWORD WINAPI Physical::tagFound(LPSKYETEK_TAG, void*)
--
-- RETURNS: return 0;
--
-- NOTES:
-- This function is the callback funtion that is called when a tag is detected by the RFID reader.
-- This reads the tag information and stores it into a list and display it.
----------------------------------------------------------------------------------------------------------------------*/
unsigned char tagFound(LPSKYETEK_TAG tag, void* user) {
	if (tag == NULL) {
		return true;
	}
	Physical* thisObj = (Physical*)(user);

	WCHAR *name(tag->friendly);
	WCHAR *type(SkyeTek_GetTagTypeNameFromType(tag->type));

	if (thisObj->tagList.empty()) {
		thisObj->tagList.push_back(Tag(SkyeTek_GetTagTypeNameFromType(tag->type), tag->friendly));
		displayTag(thisObj->hwnd, thisObj->tagList, 0);
		return true;
	}
	auto it = find_if(thisObj->tagList.begin(), thisObj->tagList.end(), [name](Tag &t) {return wcscmp(t.name_, name) == 0; });
	if (it == thisObj->tagList.end()) {
		thisObj->tagList.push_back(Tag(SkyeTek_GetTagTypeNameFromType(tag->type), tag->friendly));
		displayTag(thisObj->hwnd, thisObj->tagList, thisObj->tagList.size() - 1);
	}
	else {
		auto index = std::distance(thisObj->tagList.begin(), it);
		displayTag(thisObj->hwnd, thisObj->tagList, index);
	}

	return true;
}