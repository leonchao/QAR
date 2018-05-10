#ifndef _CLOUD_BUS_DATA_READER_IMPL_H_
#define _CLOUD_BUS_DATA_READER_IMPL_H_

#include "../core/types.h"

#if (HERMES_OS == HERMES_OS_WINDOWS_NT)
#include <objbase.h>
#endif

namespace DDS
{
    class DataReaderImpl
    {
    public:
        DataReaderImpl(Subscriber_ptr pSub, Topic_ptr pTopic, const DataReaderQos& qos, DataReaderListener_ptr a_listener, StatusMask mask);

        virtual ~DataReaderImpl();

        virtual ReturnCode_t            set_listener(DataReaderListener_ptr a_listener, StatusMask mask);

        virtual DataReaderListener_ptr  get_listener();

        virtual Subscriber_ptr          get_subscriber();


    private:

        DataReaderListener_ptr          m_pListener;
        Subscriber_ptr                  m_pSubscriber;
        Topic_ptr                       m_pTopic;
        DomainParticipant_ptr           m_pDp;
        GUID                            m_nodeId;
    };
}
#endif