#ifndef _CLOUD_BUS_TOPIC_H_
#define _CLOUD_BUS_TOPIC_H_

#include "../core/types.h"
#include "../core/entity.h"
#include "topicdescription.h"


namespace DDS
{
    class TopicImpl;

    class CLOUDBUS_API Topic : virtual public Entity, virtual public TopicDescription
    {
    public:
        virtual ~Topic(void);

        virtual ReturnCode_t        set_listener(TopicListener_ptr a_listener, StatusMask mask);

        virtual TopicListener_ptr   get_listener();


    protected:
        Topic(DomainParticipant_ptr dp,
              std::string           topic_name,
              std::string           type_name,
              const TopicQos &      qos,
              TopicListener_ptr     a_listener,
              StatusMask            mask);


    private:
        Topic(const Topic &);

        void operator= (const Topic &);

    private:
        friend class DomainParticipant;
        friend class Publisher;
        TopicImpl*                  m_pImpl;
    };

}

#endif