
#include <iostream>
#include "core.h"

#ifdef BMDEBUG
#include "sanity.h"
#endif

using namespace bmcore;
using namespace std;

int main (void)
{
#ifdef BMDEBUG
	//	Perform Sanity check
	CheckSanity();
#endif

	std::cout << "========================================" << endl;
	std::cout << "|\tcHardwarePlatform Test" << endl;
	std::cout << "========================================" << endl;
	cHardwarePlatform* platform = cHardwarePlatform::Get();
	SetTraceLevel (BM_ERR_REPORT_NONE);
	BMTrace (SID_INFO("Platform Name:\t%s"), platform->getPlatform());
	BMTrace (SID_INFO("Num of CPUs:\t%d"), platform->getNumCPUs());
	BMTrace (SID_INFO("CPU Frequency\t%d GHz"), platform->getCPUSpeed());

	std::cout << "Memory Banks:\t" << platform->getNumMemBanks() << std::endl;
	std::cout << "Available Mem:\t" << platform->getMemorySize() << " MB" << std::endl;
	std::cout << "Disk Access:\t" << platform->getDiskAccessSpeed() << " MB/s" << std::endl;
	std::cout << "Disk Read:\t" << platform->getDiskReadSpeed() << " MB/s" << std::endl;
	std::cout << "Doc Location:\t" << platform->getDocsURL() << std::endl;
	std::cout << "Proj Website:\t" << platform->getDevURL() << std::endl;
	
	system("PAUSE");
	return 0;
}