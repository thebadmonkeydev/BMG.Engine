/**
	\file	cHardwarePlatform_Win.h
	\brief	Provides declarations for windows-specific hardware platform
*/

#ifndef _CHARDWAREPLATFORM_WIN_H_
#define _CHARDWAREPLATFORM_WIN_H_

#define _WIN32_DCOM
#include <comdef.h>
#include <Wbemidl.h>

# pragma comment(lib, "wbemuuid.lib")

#include <Windows.h>
#include "datatypes.h"
#include "chardwareplatform.h"

#ifdef BMDEBUG
#include <iostream>
using namespace std;
#endif

class cHardwarePlatform_Win :
	public cHardwarePlatform
{
public:
	static				cHardwarePlatform_Win* Get(void);
	virtual tReal32		getCPUSpeed(void);
	virtual tuChar8*	getDevURL(void);
	virtual tReal32		getDiskAccessSpeed(void);
	virtual tReal32		getDiskReadSpeed(void);
	virtual tuChar8*	getDocsURL(void);
	virtual tMemSize	getMemorySize(void);
	virtual tuInt32		getNumCPUs(void);
	virtual tuInt32		getNumMemBanks(void);
	virtual tuChar8*	getPlatform(void);

	virtual				~cHardwarePlatform_Win(void);

private:
	static cHardwarePlatform_Win* sm_pinstance;
	cHardwarePlatform_Win(void);
	tBool initialize (void);
	sPlatformInfo m_sysInfo;
};

#endif // _CHARDWAREPLATFORM_WIN_H_
