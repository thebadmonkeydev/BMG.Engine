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
#include "cHardwarePlatform.h"

#ifdef BMDEBUG
#include <iostream>
using namespace std;
#define BMTrace(b) cout<<__FILE__<<" ("<<__LINE__<<"): "<<(b)<<endl
#endif

namespace bmcore
{
	/**
		\class	cHardwarePlatform_Win cHardwarePlatform_Win.h
		\brief	Windows specific implementation for the cHardwarPlatform class

		\see cHardwarePlatform
	*/
	class cHardwarePlatform_Win :
		public cHardwarePlatform
	{
	public:
		/**
			cHardwarePlatform_Win::Get

			\brief	Obtains the singleton instance of cHardwarePlatform_Win

			This method should not be called directly from any of your code.
			it is designed to be used internally when providing the cHardwarePlatform
			singleton instance.

			\return The pointer to the singleton instance of cHardwarePlatform_Win
		
			\see cHardwarePlatform::Get
		*/
		static				cHardwarePlatform_Win* Get(void);

		/**
			cHardwarePlatform_Win::getCPUSpeed

			\brief	Returns the maximum operating frequency of the platform CPU as reported by WMI

			This method should not be called directly from any of your code.
			it is designed to be used internally.

			\return The frequency of the CPU as a real number in GHz
		
			\see cHardwarePlatform::getCPUSpeed
		*/
		virtual tReal32		getCPUSpeed(void);

		/**
			cHardwarePlatform_Win::getDevURL

			\brief	Obtains the URL for this project

			This method should not be called directly from any of your code.
			it is designed to be used internally.

			\return A character array containing the web URL for this project
		
			\see cHardwarePlatform::getDevURL
		*/
		virtual tuChar8*	getDevURL(void);

		/**
			cHardwarePlatform_Win::getDiskAccessSpeed

			\brief	Obtains the average HDD access speed as reported by WMI

			This method should not be called directly from any of your code.
			it is designed to be used internally.

			\return A real number average disk access speed in MB/s
		
			\see cHardwarePlatform::getDiskAccessSpeed
		*/
		virtual tReal32		getDiskAccessSpeed(void);

		/**
			cHardwarePlatform_Win::getDiskReadSpeed

			\brief	Obtains the average HDD read speed as reported by WMI

			This method should not be called directly from any of your code.
			it is designed to be used internally.

			\return A real number average disk read speed in MB/s
		
			\see cHardwarePlatform::getDiskReadSpeed
		*/
		virtual tReal32		getDiskReadSpeed(void);

		/**
			cHardwarePlatform_Win::getDocsURL

			\brief	Obtains the relative local location of this projects documentation

			This method should not be called directly from any of your code.
			it is designed to be used internally.

			\return A character array containing the relative local location of documentation
		
			\see cHardwarePlatform::getDocsURL
		*/
		virtual tuChar8*	getDocsURL(void);

		/**
			cHardwarePlatform_Win::getMemorySize

			\brief	Obtains the total installed physical memory as reported by WMI

			This method should not be called directly from any of your code.
			it is designed to be used internally.

			\return A memsize value representing the total physical memory in MB
		
			\see cHardwarePlatform::getMemorySize
		*/
		virtual tMemSize	getMemorySize(void);

		/**
			cHardwarePlatform_Win::getNumCPUs

			\brief	Obtains the number of CPU cores as reported by WMI

			This method should not be called directly from any of your code.
			it is designed to be used internally.  The number of cores represents
			the logical cores, therefore, hyperthreading will change this value

			\return An integer value representing the number of CPU cores
		
			\see cHardwarePlatform::getNumCPUs
		*/
		virtual tuInt32		getNumCPUs(void);

		/**
			cHardwarePlatform_Win::getNumMemBanks

			\brief	Obtains the number of physical memory slots as reported by WMI

			This method should not be called directly from any of your code.
			it is designed to be used internally.

			\return The number of memory slots on the platform
		
			\see cHardwarePlatform::getNumMemBanks
		*/
		virtual tuInt32		getNumMemBanks(void);

		/**
			cHardwarePlatform_Win::getPlatform

			\brief	Obtains the platform name as reported by WMI

			This method should not be called directly from any of your code.
			it is designed to be used internally.

			\return A character array containing the name of the platform
		
			\see cHardwarePlatform::getPlatform
		*/
		virtual tuChar8*	getPlatform(void);

		virtual				~cHardwarePlatform_Win(void);

	private:
		//!	The singleton instance for this class
		static cHardwarePlatform_Win* sm_pinstance;

		//!	Hidden default constructor
		cHardwarePlatform_Win(void);

		//!	Hidden copy constructor
		cHardwarePlatform_Win(const cHardwarePlatform_Win& other);

		/**
			cHardwarePlatform_Win::initialize

			\brief	Initializes the necesary WMI components for accessing platform information

			\return A boolean value indicating success
		*/
		tBool initialize (void);

		//!	Instance of sPlatformInfo structure containing platform information
		sPlatformInfo m_sysInfo;
	};
}

#endif // _CHARDWAREPLATFORM_WIN_H_
