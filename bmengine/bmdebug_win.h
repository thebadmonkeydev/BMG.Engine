/**
	\file	bmdebug_win.h
	\brief	Windows specific defines and includes for debugging
*/

#ifndef _BMDEBUG_WIN_H_
#define _BMDEBUG_WIN_H_

#include <Windows.h>
#include <iostream>
#include "datatypes.h"
#include "bmutil_defines.h"

BM_INLINE void BMOutputTraceMsg (const tChar8* iMsg)
{
	OutputDebugString(iMsg);
	OutputDebugString("\n");
}

BM_INLINE void BMOutputTrace (tuInt16 idx, const tChar8* iFile, tMemSize iLine, const tChar8* iMsg, ...)
{
	static tChar8 buffer[1024];

	va_list va;

	bool res = idx < gTraceLevel;

	if (res)
	{
		return;
	}

	sprintf(buffer, "%s(%d): ", iFile, iLine);

	va_start(va, iMsg);
	vsprintf(strchr(buffer, '\0'), iMsg, va);
	va_end(va);

	BMOutputTraceMsg(buffer);
}

#endif	//	_BMDEBUG_WIN_H_
