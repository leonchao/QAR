#ifndef _CLOUD_BUS_DOMAIN_PARTICIPANT_IMPL_H_
#define _CLOUD_BUS_DOMAIN_PARTICIPANT_IMPL_H_

#include "../core/types.h"
#include "../core/entity.h"
#include "../core/thread_lock.h"
#include "domainparticipant.h"
#include <map>
#include <set>





namespace DDS
{


    class CLOUDBUS_API DomainParticipantImpl
    {
    public:
        DomainParticipantImpl(DomainId_t                     domainID,
                              const DomainParticipantQos &   qos,
                              DomainParticipantListener_ptr  a_listener,
                              StatusMask                     mask);

        virtual ~DomainParticipantImpl();

        virtual DomainParticipantListener_ptr   get_listener();

        virtual ReturnCode_t                    set_listener(DomainParticipantListener_ptr a_listener, StatusMask mask);

        virtual ReturnCode_t                    add_publisher(Publisher_ptr pPub);

		Publisher_ptr							get_a_publisher();
            
        virtual ReturnCode_t                    delete_publisher(Publisher_ptr p);
   
        virtual ReturnCode_t                    add_subscriber(Subscriber_ptr pSub);

		Subscriber_ptr							get_a_subscriber();

        virtual ReturnCode_t                    delete_subscriber(Subscriber_ptr pSub);

        virtual ReturnCode_t                    add_topic(Topic_ptr pTopic);

        virtual ReturnCode_t                    delete_topic(Topic_ptr a_topic);

        virtual Topic_ptr                       find_topic(const std::string& topic_name, const Duration_t & timeout);

        virtual TopicDescription_ptr            lookup_topicdescription(const std::string& name);

        virtual DomainId_t                      get_domain_id();

        virtual ReturnCode_t                    delete_contained_entities();

        virtual Boolean                         contains_entity(InstanceHandle_t a_handle);
            
        int                                     get_datareaders(const std::string& topic_name, DataReaderSeq& readers);

        GUID&                                   get_node_id();
        private:
            DomainParticipantImpl(const DomainParticipantImpl &);

            void operator= (const DomainParticipantImpl &);

        private:
            GUID                                m_nodeId;
            DomainParticipantListener_ptr       m_pListener;
            DomainId_t                          m_domainId;

            PublisherQos                        m_defaultPublisherQos;
            SubscriberQos                       m_defaultSubscriberQos;
            TopicQos                            m_defaultTopicQos;
            DomainParticipantQos                m_domainParticipantQos;
#if (HERMES_OS == HERMES_OS_WINDOWS_NT)
#pragma warning(push)
#pragma warning(disable:4251)
#endif
            typedef std::set<Publisher_ptr>     PublisherSet;
            typedef std::set<Subscriber_ptr>    SubscriberSet;
            typedef std::map<std::string, Topic_ptr> TopicMap;

            PublisherSet                        m_publisherSet;
            SubscriberSet                       m_subscriberSet;
            TopicMap                            m_topicMap;

            thread_lock                         m_pubLock;
            thread_lock                         m_subLock;
            thread_lock                         m_topicLock;
#if (HERMES_OS == HERMES_OS_WINDOWS_NT)
#pragma warning(pop)
#endif
    };
    
}


#endif
