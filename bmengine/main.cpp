
//#include <iostream>
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
#ifdef BMDEBUG
	//	Perform Sanity check
	CheckSanity();
#endif

	bmcore::InitBMCore();
	bmutil::InitBMUtil();
	cDebugger::Get()->setTraceLevel (BM_ERR_REPORT_ALL);
	cHardwarePlatform* platform = cHardwarePlatform::Get();
	
	BMTrace (SID_INFO("Platform information:"));
	BMTrace (SID_INFO("Platform Name:\t%s"), platform->getPlatform());
	BMTrace (SID_INFO("Num of CPUs:\t%d"), platform->getNumCPUs());
	BMTrace (SID_INFO("CPU Frequency\t%3.2f GHz"), platform->getCPUSpeed());
	BMTrace (SID_INFO("Available Mem:\t%d MB"), platform->getMemorySize());
	
	system("PAUSE");
	return 0;
}