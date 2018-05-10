#ifndef _CLOUD_BUS_TOPIC_DESCRIPTION_H_
#define _CLOUD_BUS_TOPIC_DESCRIPTION_H_

#include "../core/types.h"

namespace DDS
{

    class CLOUDBUS_API TopicDescription
    {
    public:
        virtual std::string             get_type_name();

        virtual std::string             get_name();

        virtual DomainParticipant_ptr   get_participant();

    protected:
        TopicDescription(const DomainParticipant_ptr dp, const std::string& name, const std::string& type_name);

        virtual ~TopicDescription(void);

    private:
        TopicDescription(const TopicDescription &);

        void operator= (const TopicDescription &);
#pragma warning(push)
#pragma warning(disable:4251)
        std::string                     m_name;
        std::string                     m_typeName;
        const DomainParticipant_ptr     m_dp;
#pragma warning(pop)
    };

}


#endif