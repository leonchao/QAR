#ifndef _CLOUD_BUS_TOPIC_IMPL_H_
#define _CLOUD_BUS_TOPIC_IMPL_H_

#include "../core/types.h"
#include "../core/entity.h"
#include "topic.h"


namespace DDS
{

        class  TopicImpl
        {
        public:
            TopicImpl(const TopicQos& qos, TopicListener_ptr a_listener, StatusMask mask);

            virtual ~TopicImpl(void);

            virtual ReturnCode_t        set_listener(TopicListener_ptr a_listener, StatusMask mask);

            virtual TopicListener_ptr   get_listener();


        private:
            TopicImpl(const TopicImpl &);

            void operator= (const TopicImpl &);

        private:
            TopicListener_ptr           m_pListener;
        };

}

#endif