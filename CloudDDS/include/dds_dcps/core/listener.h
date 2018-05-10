#ifndef _CLOUD_BUS_LISTENER_H_
#define _CLOUD_BUS_LISTENER_H_


namespace DDS
{
    class CLOUDBUS_API Listener
    {
    protected:
        Listener(void){}

        virtual ~Listener(void){}

    private:
        Listener(const Listener &);

        void operator= (const Listener &);
    };
    
}
#endif