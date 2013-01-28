/**
	\file	cHardwarePlatform.h
	\brief	Provides declarations for the abstracted/null driver hardware platform class
*/

#ifndef _CHARDWAREPLATFORM_H_
#define _CHARDWAREPLATFORM_H_

#include "datatypes.h"
#include "bmplatform.h"
#include "bmdebug.h"

namespace bmcore
{
	/**
		\struct		sPlatformInfo
		\brief		Contains members representing the plaform critical information
	*/
	struct sPlatformInfo
	{
		
		tReal32		CPUSpeed;	//!	The CPU speed
		tReal32		diskAccess;	//!	avg disk access speed
		tReal32		diskRead;	//!	avg disk read speed
		tuInt32		numCPUs;	//!	Number of processor cores
		tuInt32		numMemBanks;//!	Number of memory slots
		tMemSize	memSize;	//!	Total physical memory
		tuChar8*	name;		//!	Platform name string

	};

	class cHardwarePlatform
	{
	public:
		/**
			cHardwarePlatform::Get

			\brief	Obtains the singleton instance of cHardwarePlatform

			Calling this method dynamically determines the proper platform singleton
			to return.  If for some reason the platform specific pointer is not 
			available or the platform cannot be determined, the pointer to the null
			driver instance is returned.

			\return The pointer to the singleton instance of cHardwarePlatform
		*/
		static				cHardwarePlatform* Get(void);

		/**
			cHardwarePlatform::getCPUSpeed

			\brief	Returns the maximum operating frequency of the platform CPU

			Uses platform specific methods to determine and return the maximum CPU
			operating frequency.

			\return The frequency of the CPU as a real number in GHz
		*/
		virtual tReal32		getCPUSpeed(void);

		/**
			cHardwarePlatform::getDevURL

			\brief	Obtains the URL for this project

			\return A character array containing the web URL for this project
		*/
		virtual tuChar8*	getDevURL(void);

		/**
			cHardwarePlatform::getDiskAccessSpeed

			\brief	Obtains the average HDD access speed

			This average is determined for the first registered HDD on boot.
			This is usually the OS drive and thus the most likely installation
			location.

			\return A real number average disk access speed in MB/s
		*/
		virtual tReal32		getDiskAccessSpeed(void);

		/**
			cHardwarePlatform::getDiskReadSpeed

			\brief	Obtains the average HDD read speed

			This average is determined for the first registered HDD on boot
			which is usually the OS installation drive and thus the
			most likely installation location

			\return A real number average disk read speed in MB/s
		*/
		virtual tReal32		getDiskReadSpeed(void);

		/**
			cHardwarePlatform::getDocsURL

			\brief	Obtains the relative local location of this projects documentation

			The return value is a relative URI based from the installation root directory
			or conversely the location of the executable.

			\return A character array containing the relative local location of documentation
		*/
		virtual tuChar8*	getDocsURL(void);

		/**
			cHardwarePlatform::getMemorySize

			\brief	Obtains the total installed physical memory

			This value is the total installed memory and does not take into account
			BIOS reserved memory or video reserved memory that is obtained from
			the general purpose system meory.

			\return A memsize value representing the total physical memory in MB
		*/
		virtual tMemSize	getMemorySize(void);

		/**
			cHardwarePlatform::getNumCPUs

			\brief	Obtains the number of CPU cores

			The number of cores represents the logical cores, therefore, hyperthreading
			will change this value.

			\return An integer value representing the number of CPU cores
		*/
		virtual tuInt32		getNumCPUs(void);

		/**
			cHardwarePlatform::getNumMemBanks

			\brief	Obtains the number of physical memory slots

			\return The number of memory slots on the platform
		*/
		virtual tuInt32		getNumMemBanks(void);

		/**
			cHardwarePlatform::getPlatform

			\brief	Obtains the platform name

			\return A character array containing the name of the platform
		*/
		virtual tuChar8*	getPlatform(void);

		virtual				~cHardwarePlatform(void);

	protected:
		cHardwarePlatform(void);

	private:
		//!	The singleton instance for this class
		static cHardwarePlatform* sm_pinstance;
	};
}
#if WINDOWS
	#include "cHardwarePlatform_Win.h"
#elif UNIX
	#include "cHardwarePlatform_Unix.h"
#endif

#endif // _CHARDWAREPLATFORM_H_
