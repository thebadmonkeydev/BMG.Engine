/**
	\file	bmutil.h
	\brief	General included header for all utility headers
*/

#ifndef _BMUTIL_H_
#define _BMUTIL_H_

#include "bmutil_defines.h"
#include "cDebugger.h"

namespace bmutil
{
	BM_INLINE void InitBMUtil(void)
	{
		cDebugger::Get();
	}
}

#endif	//	_BMUTIL_H_
