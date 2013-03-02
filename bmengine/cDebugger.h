/**
	\file	cDebugger.h
	\brief	Main include header for debugger functionality
*/
#ifndef _CDEBUGGER_H_
#define _CDEBUGGER_H_

#include <iostream>
#include <stdio.h>
#include <cstdarg>
#include <cstring>

#include "bmplatform.h"
#include "datatypes.h"
#include "bmutil_defines.h"

// Make sure that all supported compiler pre-defined debug macros are included in this expression
#if defined(DEBUG) || defined(_DEBUG) || defined(NRELEASE) || defined(__DEBUG) || defined(DEBUG_BUILD)
	#define BMDEBUG
#endif // if defined(DEBUG)

//	Tracing defines
#define BM_ERR_FATAL	5
#define BM_ERR_ERROR	4
#define BM_ERR_WARNING	3
#define BM_ERR_MESSAGE	2
#define BM_ERR_INFO		1

#define BM_ERR_REPORT_NONE	6
#define BM_ERR_REPORT_ALL	0

#define SID_FATAL(msg)		BM_ERR_FATAL,__FILE__,__LINE__,msg
#define SID_ERROR(msg)		BM_ERR_ERROR,__FILE__,__LINE__,msg
#define SID_WARNING(msg)	BM_ERR_WARNING,__FILE__,__LINE__,msg
#define SID_MESSAGE(msg)	BM_ERR_MESSAGE,__FILE__,__LINE__,msg
#define SID_INFO(msg)		BM_ERR_INFO,__FILE__,__LINE__,msg

//	Tracing Macros
#ifndef BMTrace
	#ifdef BMDEBUG
		#define BMTrace	bmutil::cDebugger::Get()->outputTrace
	#else
		#define	BMTrace sizeof
	#endif	//	BMDEBUG
#endif	//	BMTrace

// Assertion expansion code
#ifndef BMAssert

	#ifdef BMDEBUG
		#define BMAssert(b) do{if (!(b)) {BMTrace(SID_ERROR("Assert: " (#b) " failed\n"));}}while(0)
	#else
		#define BMAssert(b)
	#endif // BMDEBUG

#endif // BMAssert



namespace bmutil
{
	/**
		\class	cDebugger
		\brief	Debug module driver
	*/
	class cDebugger
	{
	public:
		/**
			cDebugger::Get

			\brief	Obtains the singleton instance of cDebugger

			Calling this method dynamically determines the proper platform singleton
			to return.  If for some reason the platform specific pointer is not 
			available or the platform cannot be determined, the pointer to the null
			driver instance is returned.

			\return	The pointer to the singleton instance of cDebugger
		*/
		static cDebugger* Get();

		/**
			cDebugger::outputTrace

			\brief	Null driver for trace output

			Uses the ANSI C++ standard iostream functions to output trace
			messages to the standard stdout.

			\param iLevel	The trace level for this message
			\param iFile	The file that this message originates from
			\param iLine	The line number of this trace message
			\param iMsg		The actual message contents
			\param ...		Variable param list for values flagged in the iMsg string
		*/
		virtual void outputTrace (tuInt16 iLevel, const tChar8* iFile, tMemSize iLine, const tChar8* iMsg, ...);

		/**
			cDebugger::setTraceLevel

			\brief	Sets the filter level for the trace module

			Trace filtering is exclusive meaning that only messages of the current
			trace level and higher are output. (i.e. if the current trace level is
			BM_ERR_WARNING then a message with level BM_ERR_ERROR will be output
			but a message of level BM_ERR_INFO will not).

			\param iLevel	The new trace level
		*/
		void setTraceLevel (tuInt16 iLevel);
		virtual ~cDebugger(void);

	protected:
		cDebugger(void);

		//!	Trace level
		tuInt16 m_itraceLevel;

	private:
		//!	The singleton instance for this class
		static cDebugger* sm_pinstance;
	};
}

#if WINDOWS
	#include "cDebugger_Win.h"
#elif UNIX
#else
#endif

#endif	//_CDEBUGGER_H_
