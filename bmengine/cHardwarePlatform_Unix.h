/*
 *	\file	cHardwarePlatform_Unix.h
 *	\brief	Contains definitions for the Unix specific hardware driver
 */

#ifndef CHARDWAREPLATFORM_UNIX_H_
#define CHARDWAREPLATFORM_UNIX_H_

#include "cHardwarePlatform.h"

namespace bmcore {

	class cHardwarePlatform_Unix: public virtual bmcore::cHardwarePlatform {
	public:
		/**
		 *	cHardwarePlatform_Unix::Get
		 *
		 *	\brief	Obtains the singleton instance of cHardwarePlatform_Unix
		 *
		 *	This method should not be called directly.  Use cHardwarePlatform::Get.
		 *
		 *	\return	The point to the singleton instance of cHardwarePlatform_Unix
		 *
		 *	\see	cHardwarePlatform::Get
		 */
		static cHardwarePlatform_Unix* Get(void);

		/**
		 *	cHardwarePlatform_Unix::getCPUSpeed
		 *
		 *	\brief	Returns the maximum operating frequency of the CPU
		 *
		 *	Uses platform specific methodologies to determine this property.
		 *	On *nix systems this is done using
		 */
		virtual tReal32 getCPUSpeed(void);

		/**
		 *	cHardwarePlatform_Unix::getDevURL
		 *
		 *	\brief	Obtains the URL for this project
		 *
		 *	\return	A character array containing the web URL for the project
		 */
		virtual tuChar8* getDevURL(void);

		/**
		 *	cHardwarePlatform_Unix::getDiskAccessSpeed
		 *
		 *	\brief	Obtains the average HDD access speed
		 *
		 *	This average is determined for the first registered HDD on boot.
		 *	This is usually the OS drive and thus the most likely installation
		 *	location.
		 *
		 *	\return A real number average disk access speed in MB/s
		 */
		virtual tReal32 getDiskAccessSpeed(void);

		~cHardwarePlatform_Unix();

	protected:
		cHardwarePlatform_Unix();

		static cHardwarePlatform_Unix* sm_pinstance;
	};

} /* namespace bmcore */
#endif /* CHARDWAREPLATFORM_UNIX_H_ */
