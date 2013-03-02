/**
	\file	datatypes.h
	\brief	Provides the directed include of abstracted dataypes
*/
#ifndef _DATATYPES_H_
#define _DATATYPES_H_

#include <cstdlib>
#include <cstddef>

#include "bmplatform.h"

#define BM_ENUM_PADDING 0x7fffffff

#if WINDOWS
	#include "datatypes_Win.h"
#elif UNIX
	#include "datatypes_Unix.h"
#else
	typedef signed char		tChar8;
	typedef unsigned char   tuChar8;
	typedef signed short    tInt16;
	typedef unsigned short  tuInt16;
	typedef signed int      tInt32;
	typedef unsigned int    tuInt32;
	typedef signed long     tInt64;
	typedef unsigned long   tuInt64;

	typedef float           tReal32;
	typedef double          tReal64;

	typedef unsigned char   tByte;
	typedef tInt32          tBool;
	typedef size_t			tMemSize;

	#ifndef TRUE
	#define TRUE    1
	#endif

	#ifndef FALSE
	#define FALSE   0
	#endif

	#ifndef NULL
	#define NULL    0
	#endif
#endif

#endif
