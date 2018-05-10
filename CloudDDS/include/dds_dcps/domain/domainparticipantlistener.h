#ifndef _CLOUD_BUS_DOMAIN_PARTICIPANT_LISTENER_H_
#define _CLOUD_BUS_DOMAIN_PARTICIPANT_LISTENER_H_

#include "../core/types.h"
#include "../topic/topiclistener.h"
#include "../pub/publisherlistener.h"
#include "../sub/subscriberlistener.h"


namespace DDS
{

    class CLOUDBUS_API DomainParticipantListener : public virtual TopicListener,
        public virtual PublisherListener,
        public virtual SubscriberListener
    {

    };
    
}


#endif