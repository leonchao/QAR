#ifndef _CLOUD_BUS_PUBLISHER_IMPL_H_
#define _CLOUD_BUS_PUBLISHER_IMPL_H_

#include "../core/types.h"
#include "../core/entity.h"
#include "../core/thread_lock.h"
#include "pubbroker.h"
#include <map>
#include <string>


namespace DDS
{
    class PublisherImpl : virtual public Entity
    {
    public:
        PublisherImpl(DomainParticipant_ptr dp,
                      const PublisherQos &   qos,
                      PublisherListener_ptr  a_listener,
                      StatusMask             mask);

        ~PublisherImpl();
		void setInetInterface(const char *);

        virtual PublisherListener_ptr   get_listener();

        virtual ReturnCode_t            set_listener(PublisherListener_ptr a_listener, StatusMask mask);


        virtual ReturnCode_t            add_datawriter(DataWriter_ptr a_datawriter, std::string& topic_name);

        virtual ReturnCode_t            delete_datawriter(DataWriter_ptr a_datawriter);

        virtual ReturnCode_t            lookup_datawriter(DataWriterSeq& writers, const std::string& topic_name);

		virtual DataWriter_ptr			get_a_datawriter(const std::string& topic_name);

        virtual DomainParticipant_ptr   get_participant();

        virtual ReturnCode_t            delete_contained_entities();

		ReturnCode_t					pub_data(const char* topic, const char* data, size_t len);

    private:
        PublisherListener_ptr           m_pListener;
        typedef std::map<DataWriter_ptr, std::string> DataWriterMap;
        DataWriterMap                   m_dataWriterMap;
        DomainParticipant_ptr           m_pDp;
        thread_lock                     m_lock;
		PubBroker						m_pubBroker;
    };
}

#endif