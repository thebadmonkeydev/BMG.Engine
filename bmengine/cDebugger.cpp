#include "cDebugger.h"

namespace bmutil
{
	cDebugger* cDebugger::sm_pinstance = NULL;

	//	Forward class definition for sub classes
	//class cDebugger_Win;
	class cDebugger_Unix;

	cDebugger* cDebugger::Get(void)
	{
	#if WINDOWS
		return cDebugger_Win::Get();
	#elif UNIX
		if (NULL == sm_pinstance){sm_pinstance = new cDebugger();}
				return sm_pinstance;
	#else
		if (NULL == sm_pinstance){sm_pinstance = new cDebugger();}
		return sm_pinstance;
	#endif
	}

	void cDebugger::setTraceLevel(tuInt16 iLevel)
	{
		this->m_itraceLevel = iLevel;
	}

	void cDebugger::outputTrace(tuInt16 iLevel, const char* iFile, tMemSize iLine, const char* iMsg, ...)
	{
		if (iLevel < m_itraceLevel)
		{
			return;
		}
		
		char buffer[1024];

		va_list va;

		sprintf(buffer, "%s(%d): ", iFile, iLine);

		va_start(va, iMsg);
		vsprintf(strchr(buffer, '\0'), iMsg, va);
		va_end(va);

		std::cout << buffer << std::endl;
	}

	cDebugger::cDebugger(void)
	{
	}


	cDebugger::~cDebugger(void)
	{
	}
}
