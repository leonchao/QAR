/*
 *                         CloudBus DDS
 *
 */
#ifndef _CLOUDBUS_OS_QNXNTO_DEFS_H
#define _CLOUDBUS_OS_QNXNTO_DEFS_H


#if defined (__cplusplus)
extern "C" {
#endif

#include <sys/types.h> /* needed for _off_t */

#include <stdint.h>


#define OS_SOCKET_USE_FCNTL 0
#define OS_SOCKET_USE_IOCTL 1
#define OS_HAS_UCONTEXT_T

#include "../os_types.h"


#if defined (__cplusplus)
}
#endif

#endif /* OS_QNXNTO_DEFS_H */
