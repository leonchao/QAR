/*
 *                         CloudBus DDS
 *
 */
#ifndef _CLOUDBUS_OS_WIN32_DEFS_H
#define _CLOUDBUS_OS_WIN32_DEFS_H

// Suppress spurious 'child' : inherits 'parent::member' via dominance warnings
#if defined (_MSC_VER)
    #pragma warning(disable:4250)
#endif /* _MSC_VER */

#if defined (__cplusplus)
extern "C" {
#endif

/* Included as part of VC7 include dir */
/* #include <sys/types.h> /* needed for _off_t */
#include <BaseTsd.h>

#if defined (_MSC_VER) && (_MSC_VER < 1600)
// VS 2005 & 2008 confirmed to have no stdint.h; Predecessors presumed likewise
#else
    #include <stdint.h>
#endif

#define OS_SOCKET_USE_FCNTL 0
#define OS_SOCKET_USE_IOCTL 1
#define OS_HAS_UCONTEXT_T

#include "../os_types.h"


#if defined (__cplusplus)
}
#endif

#endif /* OS_WIN32_DEFS_H */
