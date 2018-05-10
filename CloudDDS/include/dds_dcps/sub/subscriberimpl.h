#ifndef _CLOUD_BUS_SUBSCRIBER_IMPL_H_
#define _CLOUD_BUS_SUBSCRIBER_IMPL_H_


#include "../core/types.h"
#include "../core/thread_lock.h"
#include "recvbroker.h"
#include <map>
#include <string>

#if HERMES_OS == HERMES_OS_WINDOWS_NT
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")
#endif

namespace DDS
{
    class SubscriberImpl
    {
    public:
        SubscriberImpl(DomainParticipant_ptr  dp,
                       const SubscriberQos &  qos,
                       SubscriberListener_ptr a_listener,
                       StatusMask             mask);

        ~SubscriberImpl();

        ReturnCode_t                add_datareader(DataReader_ptr a_datareader, std::string& topic_name);

        ReturnCode_t                delete_datareader(DataReader_ptr a_datareader);

        DomainParticipant_ptr       get_domainparticipant();

        ReturnCode_t                delete_contained_entities();

        ReturnCode_t                lookup_datareader(DataReaderSeq& readers, const std::string& topic_name);

        ReturnCode_t                set_listener(SubscriberListener_ptr a_listener, StatusMask mask);

        SubscriberListener_ptr      get_listener();
		void setInetInterface(const char* ipmask);
		
		void						on_recv(Long domainId, const char* topicName, char* data, size_t len);
        
    private:

        SubscriberImpl(const SubscriberImpl&);
        SubscriberImpl& operator=(const SubscriberImpl&);

    private:
        DomainParticipant_ptr           m_pDp;
        SubscriberListener_ptr          m_pListener;
        typedef std::map<DataReader_ptr, std::string> DataReaderMap;
        DataReaderMap                   m_dataReaderMap;
        thread_lock                     m_lock;
		RecvBroker						m_broker;

    };
}
#endif