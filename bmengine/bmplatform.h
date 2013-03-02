/**

	\file	bmplatform.h
	\brief	Provides platform/compiler specific defines and includes
*/

#ifndef _PLATFORM_H_
#define _PLATFORM_H_

#define UNIX	1
#define WINDOWS	0

/**** Platform includes for use in MACROS in this file */

#if WINDOWS
	#include <Windows.h>
#elif UNIX

#else
	#include <iostream>
#endif // WINDOWS

/** End platform includes */





#endif // _PLATFORM_H_
