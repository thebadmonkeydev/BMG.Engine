/*
 * cHardwarePlatform_Unix.cpp
 *
 *  Created on: Feb 25, 2013
 *      Author: michael
 */

#include "cHardwarePlatform_Unix.h"

namespace bmcore {

cHardwarePlatform_Unix* cHardwarePlatform_Unix::sm_pinstance = NULL;

cHardwarePlatform_Unix::~cHardwarePlatform_Unix() {

}
cHardwarePlatform_Unix::cHardwarePlatform_Unix() {
	// TODO Auto-generated constructor stub
}

tReal32 cHardwarePlatform_Unix::getCPUSpeed()
{

}

tuChar8* cHardwarePlatform_Unix::getDevURL()
{

}

tReal32 cHardwarePlatform_Unix::getDiskAccessSpeed()
{

}

cHardwarePlatform_Unix* cHardwarePlatform_Unix::Get()
{
	if (NULL == sm_pinstance){sm_pinstance = new cHardwarePlatform_Unix;}
	return sm_pinstance;
}

} /* namespace bmcore */
