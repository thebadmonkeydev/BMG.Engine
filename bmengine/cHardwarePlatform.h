/**
	\file	cHardwarePlatform.h
	\brief	Provides declarations for the abstracted/null driver hardware platform class
*/

#ifndef _CHARDWAREPLATFORM_H_
#define _CHARDWAREPLATFORM_H_

#include "datatypes.h"
#include "platform.h"

struct sPlatformInfo
{
	tReal32		CPUSpeed;
	tReal32		diskAccess;
	tReal32		diskRead;
	tuInt32		numCPUs;
	tuInt32		numMemBanks;
	tMemSize	memSize;
	tuChar8*	name;
};

class cHardwarePlatform
{
public:
	static				cHardwarePlatform* Get(void);
	virtual tReal32		getCPUSpeed(void);
	virtual tuChar8*	getDevURL(void);
	virtual tReal32		getDiskAccessSpeed(void);
	virtual tReal32		getDiskReadSpeed(void);
	virtual tuChar8*	getDocsURL(void);
	virtual tMemSize	getMemorySize(void);
	virtual tuInt32		getNumCPUs(void);
	virtual tuInt32		getNumMemBanks(void);
	virtual tuChar8*	getPlatform(void);

	virtual				~cHardwarePlatform(void);

protected:
	cHardwarePlatform(void);

private:
	static cHardwarePlatform* sm_pinstance;
};

#if WINDOWS
	#include "cHardwarePlatform_Win.h"
#elif UNIX
	#include "cHardwarePlatform_Unix.h"
#endif

#endif // _CHARDWAREPLATFORM_H_
