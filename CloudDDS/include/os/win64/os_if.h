/*
 *                         CloudBus DDS
 *
 */
#ifndef OS_WIN64_IF_H
#define OS_WIN64_IF_H

#if defined (__cplusplus)
extern "C" {
#endif

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#ifndef OS_API_EXPORT
#define OS_API_EXPORT __declspec(dllexport)
#endif

#ifndef OS_API_IMPORT
#define OS_API_IMPORT __declspec(dllimport)
#endif

#if defined (__cplusplus)
}
#endif

#endif /* OS_WIN64_IF_H */
