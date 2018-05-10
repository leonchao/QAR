#ifndef _CLOUD_BUS_DATA_WRITER_H_
#define _CLOUD_BUS_DATA_WRITER_H_

#include "../core/types.h"
#include "../core/entity.h"

namespace DDS
{
    class DataWriterImpl;

    class CLOUDBUS_API DataWriter : virtual public Entity
    {
    public:
        virtual ~DataWriter();

        virtual ReturnCode_t            write(void* data, Long size);

        virtual ReturnCode_t            set_listener(DataWriterListener_ptr a_listener, StatusMask mask);

        virtual DataWriterListener_ptr  get_listener();

        virtual Publisher_ptr           get_publisher();


    protected:
        friend class Publisher;
        DataWriter(Publisher_ptr pPub, Topic_ptr pTopic,const DataWriterQos& qos, DataWriterListener_ptr a_listener, StatusMask mask);

    private:

        DataWriterImpl*                 m_pImpl;
    };
}


#endif // !_CLOUD_BUS_DATA_WRITER_H_
