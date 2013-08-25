/**
	\file	bmdebug.h
	\brief	
*/

#ifndef _DEBUG_H_
#define _DEBUG_H_

#include "datatypes.h"
#include "bmutil_defines.h"

/**** Debugging defines */
// Make sure that all supported compiler pre-defined debug macros are included in this expression
#if defined(DEBUG) || defined(_DEBUG) || defined(NRELEASE) || defined(__DEBUG) || defined(DEBUG_BUILD)
	#define BMDEBUG
#endif // if defined(DEBUG)

// Assertion expansion code
#ifndef BMAssert

	#ifdef BMDEBUG
		#if WINDOWS
			#define BMAssert(b) do{if (!(b)) {OutputDebugStringA("Assert: " #b " failed\n");}}while(0)
		#elif UNIX
			#define BMAssert(b) do{if (!(b)) {cerr << "Assert: " #b " failed\n");}}while(0)
		#endif // WINDOWS
	#else
		#define BMAssert(b)
	#endif // BMDEBUG

#endif // BMAssert

//	Tracing Macros
#ifndef BMTrace
	#ifdef BMDEBUG
		#define BMTrace	BMOutputTrace
	#else
		#define	BMTrace sizeof
	#endif	//	BMDEBUG
#endif	//	BMTrace

#define BM_ERR_FATAL	5
#define BM_ERR_ERROR	4
#define BM_ERR_WARNING	3
#define BM_ERR_MESSAGE	2
#define BM_ERR_INFO		1

#define BM_ERR_REPORT_NONE	6
#define BM_ERR_REPORT_ALL	0

static tuInt16 gTraceLevel = BM_ERR_REPORT_ALL;
BM_INLINE void SetTraceLevel (tuInt16 iLvl)
{
	gTraceLevel = iLvl;
}

#define SID_FATAL(msg)		BM_ERR_FATAL,__FILE__,__LINE__,msg
#define SID_ERROR(msg)		BM_ERR_ERROR,__FILE__,__LINE__,msg
#define SID_WARNING(msg)	BM_ERR_WARNING,__FILE__,__LINE__,msg
#define SID_MESSAGE(msg)	BM_ERR_MESSAGE,__FILE__,__LINE__,msg
#define SID_INFO(msg)		BM_ERR_INFO,__FILE__,__LINE__,msg

/** End Debugging defines */

#if WINDOWS
	#include "bmdebug_win.h"
#elif UNIX
#else
#endif

#endif	//	_DEBUG_H_