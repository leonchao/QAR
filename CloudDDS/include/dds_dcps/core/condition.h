#ifndef _CLOUDBUS_CONDITION_H_
#define _CLOUDBUS_CONDITION_H_

#include "types.h"

namespace DDS
{
 
    class CLOUDBUS_API Condition
    {
    public:
        virtual Boolean get_trigger_value() = 0;

    protected:
        Condition(void){}

        virtual ~Condition(void){}

    private:
        Condition(const Condition &);

        void operator= (const Condition &);
    };


    /*************************************************
        *       class GuardCondition
        ************************************************/

    class CLOUDBUS_API GuardCondition : public virtual Condition
    {
    public:
        GuardCondition();

        virtual ~GuardCondition();

        Boolean         get_trigger_value();

        ReturnCode_t    set_trigger_value(Boolean value);

    private:
        void*           m_pImpl;

    };

    /**********************************************
    *       class StatusCondition
    **********************************************/

    class CLOUDBUS_API StatusCondition : public virtual Condition
    {
    public:
        explicit StatusCondition(Entity* parent);

        virtual ~StatusCondition();

        virtual Boolean         get_trigger_value();
            
        virtual StatusMask      get_enabled_statuses();

        virtual ReturnCode_t    set_enabled_statuses(StatusMask mask);

        virtual Entity_ptr      get_entity();



    private:
        void*                   m_pImpl;
        Entity*                 m_parent;
    };


    
}

#endif