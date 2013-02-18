#include "cDebugger_Win.h"

namespace bmutil
{
	cDebugger_Win* cDebugger_Win::sm_pinstance = NULL;

	cDebugger_Win* cDebugger_Win::Get(void)
	{
		if (NULL == sm_pinstance){sm_pinstance = new cDebugger_Win();}
		return sm_pinstance;
	}

	void cDebugger_Win::outputTrace(tuInt16 iLevel, const tChar8* iFile, tMemSize iLine, const tChar8* iMsg, ...)
	{
		//	Filter by trace level
		if(iLevel < m_itraceLevel){return;}

		tChar8 buffer[1024];

		va_list va;

		sprintf(buffer, "%s(%d): ", iFile, iLine);

		va_start(va, iMsg);
		vsprintf(strchr(buffer, '\0'), iMsg, va);
		va_end(va);

		OutputDebugString(buffer);
		OutputDebugString("\n");
	}

	cDebugger_Win::cDebugger_Win(void)
	{
	}


	cDebugger_Win::~cDebugger_Win(void)
	{
	}
}
