#ifndef _CLOUD_BUS_DATA_READER_LISTENER_H_
#define _CLOUD_BUS_DATA_READER_LISTENER_H_

#include "../core/types.h"

namespace DDS
{

    class CLOUDBUS_API DataReaderListener
    {
    public:
        virtual void on_data_available(Long domainId, const std::string& topicName, char* buf, int len) = 0;
    };
}

#endif