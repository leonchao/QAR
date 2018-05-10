#ifndef _CLOUD_BUS_DOMAIN_PARTICIPANT_H_
#define _CLOUD_BUS_DOMAIN_PARTICIPANT_H_

#include "../core/types.h"
#include "../core/entity.h"

namespace DDS
{
    class DomainParticipantImpl;
    class CLOUDBUS_API DomainParticipant : public Entity
    {
    public:
        virtual ~DomainParticipant(void);

        virtual DomainParticipantListener_ptr   get_listener();

        virtual ReturnCode_t                    set_listener(DomainParticipantListener_ptr a_listener,
                                                             StatusMask                    mask);

        virtual Publisher_ptr                   create_publisher(const PublisherQos &   qos,
                                                                 PublisherListener_ptr  a_listener,
                                                                 StatusMask             mask);
		Publisher_ptr							get_a_publisher();

        virtual ReturnCode_t                    delete_publisher(Publisher_ptr p);


        virtual Subscriber_ptr                  create_subscriber(const SubscriberQos &  qos,
                                                                  SubscriberListener_ptr a_listener,
                                                                  StatusMask             mask);
		void setNetInterface(const char* ipaddr);
		Subscriber_ptr							get_a_subscriber();

        virtual ReturnCode_t                    delete_subscriber(Subscriber_ptr s);


        virtual Topic_ptr                       create_topic(const char *        topic_name,
                                                             const char *        type_name,
                                                             const TopicQos &    qos,
                                                             TopicListener_ptr   a_listener,
                                                             StatusMask          mask);

        virtual ReturnCode_t                    delete_topic(Topic_ptr a_topic);


        virtual Topic_ptr                       find_topic(const char *topic_name, const Duration_t & timeout);

        virtual TopicDescription_ptr            lookup_topicdescription(const char * name);

        virtual DomainId_t                      get_domain_id();

        virtual ReturnCode_t                    delete_contained_entities();

        virtual Boolean                         contains_entity(InstanceHandle_t a_handle);
		void setInetInterfaceIpaddr(const char* ipmask);

    protected:
        virtual DomainParticipantImpl*          get_domainparticipant_impl();


    protected:
        
        DomainParticipant(DomainId_t                     domainID,
                          const DomainParticipantQos &   qos,
                          DomainParticipantListener_ptr  a_listener,
                          StatusMask                     mask);


    private:

        DomainParticipant(const DomainParticipant &);
        void operator= (const DomainParticipant &);

    private:
        friend class Subscriber;
        friend class Publisher;
        friend class DataWriter;
        friend class DataReader;
        friend class DataWriterImpl;
        friend class DataReaderImpl;
        friend class DomainParticipantFactoryImpl;
		char m_ipMask[24];
        DomainParticipantImpl*                 m_pImpl;

    };
    
}


#endif