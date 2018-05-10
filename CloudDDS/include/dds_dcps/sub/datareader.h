#ifndef _CLOUD_BUS_DATA_READER_H_
#define _CLOUD_BUS_DATA_READER_H_

#include "../core/types.h"
#include "../core/entity.h"

namespace DDS
{
    class DataReaderImpl;
    class CLOUDBUS_API DataReader : virtual public Entity
    {
    public:
        virtual ~DataReader();

        virtual ReturnCode_t            set_listener(DataReaderListener_ptr a_listener, StatusMask mask);

        virtual DataReaderListener_ptr  get_listener();

        virtual Subscriber_ptr          get_subscriber();

    protected:
        friend class Subscriber;
        DataReader(Subscriber_ptr pSub, Topic_ptr pTopic, const DataReaderQos& qos, DataReaderListener_ptr a_listener, StatusMask mask);


    private:
        DataReaderImpl*                 m_pImpl;
    };
}

#endif