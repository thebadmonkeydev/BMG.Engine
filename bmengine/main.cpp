
#include <iostream>
#include "core.h"

#ifdef BMDEBUG
#include "sanity.h"
#endif

using namespace bmcore;

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
	std::cout << "Platform Name:\t" << platform->getPlatform() << std::endl;
	std::cout << "Num of CPUs:\t" << platform->getNumCPUs() << std::endl;
	std::cout << "CPU Frequency:\t" << platform->getCPUSpeed() << " GHz" << std::endl;
	std::cout << "Memory Banks:\t" << platform->getNumMemBanks() << std::endl;
	std::cout << "Available Mem:\t" << platform->getMemorySize() << " MB" << std::endl;
	std::cout << "Disk Access:\t" << platform->getDiskAccessSpeed() << " MB/s" << std::endl;
	std::cout << "Disk Read:\t" << platform->getDiskReadSpeed() << " MB/s" << std::endl;
	std::cout << "Doc Location:\t" << platform->getDocsURL() << std::endl;
	std::cout << "Proj Website:\t" << platform->getDevURL() << std::endl;

	system("PAUSE");
	return 0;
}