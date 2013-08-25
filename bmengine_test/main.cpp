
#include <iostream>
#include <stdlib.h>

//#define _DEBUG

#include "bmcore.h"
#include "bmutil.h"

#ifdef BMDEBUG
#include "sanity.h"
#endif

using namespace bmcore;
using namespace bmutil;
using namespace std;

int main (void)
{
	cDebugger::Get()->setTraceLevel (BM_ERR_REPORT_ALL);

#ifdef BMDEBUG
	BMTrace(SID_INFO("Checking sanity..."));
	//	Perform Sanity check
	CheckSanity();
	BMTrace(SID_INFO("...Done."));
#endif
	BMTrace (SID_INFO("Initializing BMCore..."));
	bmcore::InitBMCore();
	BMTrace (SID_INFO("BMCore Initialized."));
	BMTrace (SID_INFO("Initializing BMUtil..."));
	bmutil::InitBMUtil();
	BMTrace (SID_INFO("BMUtil Initialized."));

	cHardwarePlatform* platform = cHardwarePlatform::Get();
	
	BMTrace (SID_INFO("Platform information:"));
	BMTrace (SID_INFO("Platform Name:\t%s"), platform->getPlatform());
	BMTrace (SID_INFO("Num of CPUs:\t\t%d"), platform->getNumCPUs());
	BMTrace (SID_INFO("CPU Frequency\t\t%3.2f GHz"), platform->getCPUSpeed());
	BMTrace (SID_INFO("Available Mem:\t%d MB"), platform->getMemorySize());
	BMTrace (SID_INFO("Memory Banks:\t%d"), platform->getNumMemBanks());
	
#if WINDOWS
	std::system("PAUSE");
#elif UNIX

#endif
	return 0;
}
