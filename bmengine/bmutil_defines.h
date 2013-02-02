/**
	\file	bmutil_defines.h
	\brief	Declares all util namespace related defines and Macros
*/

#ifndef _BMUTIL_DEFINES_H_
#define _BMUTIL_DEFINES_H_

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

#endif	//	_BMUTIL_DEFINES_H_
