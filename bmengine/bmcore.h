/**
	\file	core.h
	\brief	Contains includes for the core namespace of the BMEngine
*/

#ifndef _CORE_H_
#define _CORE_H_

#include "bmplatform.h"	//	Platform subsystem include
#include "bmmemory.h"	//	Memory subsystem include

#include "cHardwarePlatform.h"

namespace bmcore
{
	BM_INLINE void InitBMCore(void)
	{
		cHardwarePlatform::Get();
	}
}

#endif // _CORE_H_