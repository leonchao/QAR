#ifndef _CLOUD_BUS_TOPIC_LISTENER_H_
#define _CLOUD_BUS_TOPIC_LISTENER_H_

#include "../core/types.h"
#include "../core/listener.h"


namespace DDS
{

    class CLOUDBUS_API TopicListener : virtual public Listener
    {
    public:
        virtual void on_inconsistent_topic(Topic_ptr the_topic, const InconsistentTopicStatus& status) = 0;
    };
    
}

#endif