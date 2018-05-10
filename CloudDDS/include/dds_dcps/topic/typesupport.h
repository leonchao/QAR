#ifndef _CLOUD_BUS_TYPE_SUPPORT_H_
#define _CLOUD_BUS_TYPE_SUPPORT_H_

#include "../core/types.h"

namespace DDS
{
    namespace topic
    {
        class TypeSupport
        {
            virtual ReturnCode_t    register_type(DomainParticipant_ptr domain, const char * type_name) = 0;

            virtual char *          get_type_name() = 0;
        };
    }
}

#endif