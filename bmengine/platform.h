/**

	\file	platform.h
	\brief	Provides platform/compiler specific defines and includes
*/

#ifndef _PLATFORM_H_
#define _PLATFORM_H_

#define UNIX	0
#define WINDOWS	1

/**** Platform includes for use in MACROS in this file */

#if WINDOWS
	#include <Windows.h>
#elif UNIX

#else
	#include <iostream>
#endif // WINDOWS

/** End platform includes */

/**** Inlining defines */
#if WINDOWS
	#pragma inline_depth (255)
	#pragma inline_recursion (on)
	#pragma auto_inline (on)
	#define __forceinline
#elif UNIX
	#define __forceinline __attribute__((always_inline))
#else
	#define __forceinline inline
#endif
/** End Inlining defines */

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
	#define BMAssert(b) do{if (!(b)) {cout << "Assert: " #b " failed\n");}}while(0)
#endif // WINDOWS

#else
	#define BMAssert(b)
#endif // BMDEBUG

#endif // BMAssert

/** End Debugging defines */

#endif // _PLATFORM_H_