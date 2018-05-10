#ifndef _CLOUD_BUS_DOMAIN_PARTICIPANT_FACTORY_H_
#define _CLOUD_BUS_DOMAIN_PARTICIPANT_FACTORY_H_

#include "../core/types.h"
#include "../core/entity.h"

namespace DDS
{

    class CLOUDBUS_API DomainParticipantFactory
    {
    public:
        virtual ~DomainParticipantFactory();

        virtual DomainParticipant_ptr           create_participant( DomainId_t                     domainId,
                                                                    const DomainParticipantQos &   qos,
                                                                    DomainParticipantListener_ptr  a_listener,
                                                                    StatusMask                     mask);

        virtual ReturnCode_t                    delete_participant(DomainParticipant_ptr a_participant);

        static  DomainParticipantFactory_ptr    get_instance();

        virtual DomainParticipant_ptr           lookup_participant(DomainId_t domainId);

    protected:
        DomainParticipantFactory();
    };
    
}



#endif