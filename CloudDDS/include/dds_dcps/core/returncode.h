#ifndef _CLOUDBUS_RETURN_CODE_T_H_
#define _CLOUDBUS_RETURN_CODE_T_H_

#include "basictypes.h"
// ----------------------------------------------------------------------
// Return codes
// ----------------------------------------------------------------------
namespace DDS
{
    typedef Long ReturnCode_t;
    const ReturnCode_t RETCODE_OK = 0;
    const ReturnCode_t RETCODE_ERROR = 1;
    const ReturnCode_t RETCODE_UNSUPPORTED = 2;
    const ReturnCode_t RETCODE_BAD_PARAMETER = 3;
    const ReturnCode_t RETCODE_PRECONDITION_NOT_MET = 4;
    const ReturnCode_t RETCODE_OUT_OF_RESOURCES = 5;
    const ReturnCode_t RETCODE_NOT_ENABLED = 6;
    const ReturnCode_t RETCODE_IMMUTABLE_POLICY = 7;
    const ReturnCode_t RETCODE_INCONSISTENT_POLICY = 8;
    const ReturnCode_t RETCODE_ALREADY_DELETED = 9;
    const ReturnCode_t RETCODE_TIMEOUT = 10;
    const ReturnCode_t RETCODE_NO_DATA = 11;
    const ReturnCode_t RETCODE_ILLEGAL_OPERATION = 12;
}



#endif
