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
		 *	cHardwarePlatform::getCPUSpeed
		 *
		 *	\brief	Returns the maximum operating frequency of the CPU
		 *
		 *	Uses platform specific methodologies to determine this property.
		 *	On *nix systems this is done using
		 */

		virtual ~cHardwarePlatform_Unix();

	protected:
		cHardwarePlatform_Unix();
	};

} /* namespace bmcore */
#endif /* CHARDWAREPLATFORM_UNIX_H_ */
