#ifndef _CLOUD_BUS_PUBLISHER_H_
#define _CLOUD_BUS_PUBLISHER_H_

#include "../core/types.h"
#include "../core/entity.h"

namespace DDS
{
    class PublisherImpl;
    class CLOUDBUS_API Publisher : virtual public Entity
    {
    public:
        virtual ~Publisher();

		void setInetInterface(const char * ipaddr);

        virtual PublisherListener_ptr   get_listener();

        virtual ReturnCode_t            set_listener(PublisherListener_ptr a_listener, StatusMask mask);


        virtual DataWriter_ptr          create_datawriter(Topic_ptr              a_topic,
                                                          const DataWriterQos &  qos,
                                                          DataWriterListener_ptr a_listener,
                                                          StatusMask             mask);

        virtual ReturnCode_t            delete_datawriter(DataWriter_ptr a_datawriter);

        virtual ReturnCode_t            lookup_datawriter(DataWriterSeq& writers, const std::string& topic_name);

		virtual	DataWriter_ptr			get_a_datawriter(const std::string& topic_name);

        virtual DomainParticipant_ptr   get_domainparticipant();

        virtual ReturnCode_t            delete_contained_entities();

		ReturnCode_t					pub_data(const char* topic, const char* data, size_t len);
    protected:
        friend class DomainParticipant;
        Publisher(DomainParticipant_ptr dp,
                  const PublisherQos &   qos,
                  PublisherListener_ptr  a_listener,
                  StatusMask             mask);

    private:
        Publisher(const Publisher&);
        Publisher& operator = (const Publisher&);

    private:
        PublisherImpl*                  m_pImpl;

    };
    
}
#endif