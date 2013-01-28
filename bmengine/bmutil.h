/**
	\file	bmutil.h
	\brief	General included header for all utility headers
*/

#ifndef _BMUTIL_H_
#define _BMUTIL_H_

/**** Inlining defines */
#if WINDOWS
	#pragma inline_depth (255)
	#pragma inline_recursion (on)
	#pragma auto_inline (on)
	#define BM_INLINE inline
#elif UNIX
	#define BM_INLINE __attribute__((always_inline))
#else
	#define BM_INLINE inline
#endif
/** End Inlining defines */

#include "bmdebug.h"

#endif	//	_BMUTIL_H_
