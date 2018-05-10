/*
 *                         CloudBus DDS
 *
 */
#ifndef OS_WIN32_IF_H
#define OS_WIN32_IF_H

#if _MSC_VER==1200
#pragma warning(disable:4251)
#pragma warning(disable:4786)
#endif

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

#endif /* OS_WIN32_IF_H */
