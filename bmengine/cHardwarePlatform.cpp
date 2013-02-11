#include "cHardwarePlatform.h"

namespace bmcore
{
	cHardwarePlatform* cHardwarePlatform::sm_pinstance = NULL;

	// Forward declaration of sub classes
	class cHardwarePlatform_Win;
	class cHardwarePlatform_Unix;

	cHardwarePlatform* cHardwarePlatform::Get(void)
	{
	#if WINDOWS
		return cHardwarePlatform_Win::Get();
	#elif UNIX
		return cHardwarePlatform_Unix::Get();
	#else
		if (NULL == sm_pinstance){sm_pinstance = new cHardwarePlatform();}
		return sm_pinstance;
	#endif
	}

	cHardwarePlatform::cHardwarePlatform(void)
	{
	}

	cHardwarePlatform::~cHardwarePlatform(void)
	{
		//	Release singleton pointer
		if (NULL != sm_pinstance)
			delete sm_pinstance;
		sm_pinstance = NULL;
	}

	/// <summary>
	/// Gets the CPU speed.
	/// </summary>
	/// <returns></returns>
	tReal32 cHardwarePlatform::getCPUSpeed()
	{
		return 0.0;
	}

	tuChar8* cHardwarePlatform::getDevURL()
	{
		return (tuChar8*)"https://sourceforge.net/users/michaelkelly322";
	}

	tReal32 cHardwarePlatform::getDiskAccessSpeed()
	{
		return 0.0;
	}

	tReal32 cHardwarePlatform::getDiskReadSpeed()
	{
		return 0.0;
	}

	tuChar8* cHardwarePlatform::getDocsURL()
	{
		return (tuChar8*)"./docs/";
	}

	tMemSize cHardwarePlatform::getMemorySize()
	{
		return 0;
	}

	tuInt32 cHardwarePlatform::getNumCPUs()
	{
		return 0;
	}

	tuInt32 cHardwarePlatform::getNumMemBanks()
	{
		return 0;
	}

	tuChar8* cHardwarePlatform::getPlatform()
	{
		return (tuChar8*)"Unknown";
	}
}