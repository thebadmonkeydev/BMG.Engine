#ifndef _SANITY_H_
#define _SANITY_H_

#include "bmcore.h"

void CheckSanity(void)
{
	tuInt32 platT = 12;
	unsigned int ansiT = (int) platT;
	
	BMAssert(platT == ansiT);
	//BMAssert(platT != ansiT);
}

#endif
