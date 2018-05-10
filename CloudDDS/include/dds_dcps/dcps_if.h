/*
 *                         CloudBus DDS
 *
 */
#ifndef 	_CLOUDBUS_DCPS_IF_H_
#define 	_CLOUDBUS_DCPS_IF_H_

#include "../os/os_if.h"


#ifdef CLOUDBUS_BUILD_DLL
#define CLOUDBUS_API OS_API_EXPORT
#else
#define CLOUDBUS_API OS_API_IMPORT
#endif

#endif

 