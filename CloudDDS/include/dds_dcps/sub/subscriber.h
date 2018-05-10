#ifndef _CLOUD_BUS_SUBSCRIBER_H
#define _CLOUD_BUS_SUBSCRIBER_H

#include "../core/types.h"
#include "../core/entity.h"


namespace DDS
{
    class SubscriberImpl;
    class CLOUDBUS_API Subscriber : virtual public Entity
    {
    public:
        virtual ~Subscriber();

        virtual DataReader_ptr          create_datareader(Topic_ptr                 a_topic, 
                                                          const DataReaderQos&      qos, 
                                                          DataReaderListener_ptr    a_listener, 
                                                          StatusMask                mask);

        virtual ReturnCode_t            delete_datareader(DataReader_ptr a_datareader);

        DomainParticipant_ptr           get_domainparticipant();

        virtual ReturnCode_t            delete_contained_entities();

        virtual ReturnCode_t            lookup_datareader(DataReaderSeq& readers, const std::string& topic_name);

        virtual ReturnCode_t            set_listener(SubscriberListener_ptr a_listener, StatusMask mask);

        virtual SubscriberListener_ptr  get_listener();
		void setInetInterface(const char* ipaddr);

    protected:
        friend class DomainParticipant;
        Subscriber(DomainParticipant_ptr  dp,  
                   const SubscriberQos &  qos,
                   SubscriberListener_ptr a_listener,
                   StatusMask             mask);
    private:
        Subscriber(const Subscriber&);
        Subscriber& operator=(const Subscriber&);

    private:
        SubscriberImpl*                 m_pImpl;
    };
}
#endif