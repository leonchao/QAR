#ifndef _CLOUD_BUS_DOMAIN_PARTICIPANT_FACTORY_IMPL_H_
#define _CLOUD_BUS_DOMAIN_PARTICIPANT_FACTORY_IMPL_H_

#include "../core/types.h"
#include "../core/entity.h"
#include "../core/thread_lock.h"
#include "domainparticipantfactory.h"
#include <map>

namespace DDS
{

	class DomainParticipantFactoryImpl : virtual public DomainParticipantFactory
	{
	public:

			

		virtual DomainParticipant_ptr           create_participant(DomainId_t                     domainId,
																	const DomainParticipantQos &   qos,
																	DomainParticipantListener_ptr  a_listener,
																	StatusMask                     mask);

		virtual ReturnCode_t                    delete_participant(DomainParticipant_ptr a_participant);
            
		static DomainParticipantFactory*        get_instance();

		virtual DomainParticipant_ptr           lookup_participant(DomainId_t domainId);

		virtual ReturnCode_t                    set_default_participant_qos(const DomainParticipantQos & qos);

		virtual ReturnCode_t                    get_default_participant_qos(DomainParticipantQos & qos);

		virtual ReturnCode_t                    get_qos(DomainParticipantFactoryQos & qos);

		virtual ReturnCode_t                    set_qos(const DomainParticipantFactoryQos & qos);

    private:
        DomainParticipantFactoryImpl();

        virtual ~DomainParticipantFactoryImpl();


	private:
            
        static thread_lock                      m_lock;
        static DomainParticipantFactoryImpl*    m_pInstance;

        DomainParticipantFactoryQos             m_factoryQos;
        DomainParticipantQos                    m_defaultParticipantQos;

        typedef std::map<DomainParticipant*, DomainId_t>     ParticipantMap;
        ParticipantMap                          m_participantMap;
        thread_lock                             m_mapLock;
	};
	
}



#endif