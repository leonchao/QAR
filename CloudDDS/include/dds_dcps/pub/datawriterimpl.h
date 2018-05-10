#ifndef _DATA_WRITER_IMPL_H_
#define _DATA_WRITER_IMPL_H_

#include "../core/types.h"
#include "../core/entity.h"

#if (HERMES_OS == HERMES_OS_WINDOWS_NT)
#include <objbase.h>
#endif
namespace DDS
{
    class DataWriterImpl
    {
    public:
        DataWriterImpl(Publisher_ptr pPub, Topic_ptr pTopic, const DataWriterQos& qos, DataWriterListener_ptr a_listener, StatusMask mask);

        ~DataWriterImpl();

        ReturnCode_t                    write(void* data, Long size);

        ReturnCode_t                    set_listener(DataWriterListener_ptr a_listener, StatusMask mask);

        DataWriterListener_ptr          get_listener();

        Publisher_ptr                   get_publisher();

    private:
        DataWriterListener_ptr          m_pListener;
        Publisher_ptr                   m_pPub;
        Topic_ptr                       m_pTopic;
        DomainParticipant_ptr           m_pDp;
        GUID                            m_nodeId;
    };
}
#endif