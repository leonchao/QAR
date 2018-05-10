#ifndef _CLOUDBUS_WAITSET_H_
#define _CLOUDBUS_WAITSET_H_

#include "types.h"
#include "condition.h"

namespace DDS
{

    class CLOUDBUS_API WaitSet
    {
    public:
        WaitSet();

        virtual ~WaitSet();

        ReturnCode_t wait(ConditionSeq& active_conditions, const Duration_t& timeout);

        ReturnCode_t attach_condition(Condition_ptr cond);

        ReturnCode_t detach_condition(Condition_ptr cond);

        ReturnCode_t get_conditions(ConditionSeq& attached_conditions);

        /// Convenience method for detaching multiple conditions,
        /// for example when shutting down.
        ReturnCode_t detach_conditions(const ConditionSeq& conditions);

    private:
        WaitSet(const WaitSet &);

        void operator= (const WaitSet &);

    private:

        void*       m_pImpl;
    };



}

#endif