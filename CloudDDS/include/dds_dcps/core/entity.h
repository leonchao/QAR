#ifndef _CLOUDBUS_ENTITY_H_
#define _CLOUDBUS_ENTITY_H_

#include "types.h"

namespace DDS
{
    
    class CLOUDBUS_API Entity
    {
    public:
            
        //virtual ReturnCode_t        enable() = 0;

        //virtual StatusCondition_ptr get_statuscondition() = 0;

        //virtual StatusMask          get_status_changes() = 0;

        //virtual InstanceHandle_t    get_instance_handle() = 0;

    protected:
        Entity(){}

        virtual ~Entity(){}

    private:
        Entity(const Entity &);

        void operator= (const Entity &);

        friend class StatusCondition;
    };
    
}

#endif