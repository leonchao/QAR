#ifndef _CLOUDBUS_OS_IF_H_
#define _CLOUDBUS_OS_IF_H_
#include "platform.h"

#if (HERMES_OS == HERMES_OS_WINDOWS_NT)

#if (HERMES_ARCH == HERMES_ARCH_IA32)
#include "win32/os_if.h"
#include "win32/os_defs.h"
#elif (HERMES_ARCH == HERMES_ARCH_AMD64)
#include "win64/os_if.h"
#include "win64/os_defs.h"
#endif

#elif (HERMES_OS == HERMES_OS_VXWORKS)
#include "vx6_8/os_if.h"
#include "vx6_8/os_defs.h"

#elif (HERMES_OS == HERMES_OS_QNX)
#include "qnx/os_if.h"
#include "qnx/os_defs.h"

#elif (HERMES_OS == HERMES_OS_LINUX)
#include "linux/os_if.h"
#include "linux/os_defs.h"

#endif


#endif
