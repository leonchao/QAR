#ifndef _CLOUD_BUS_MESSAGE_BROKER_H_
#define _CLOUD_BUS_MESSAGE_BROKER_H_

#include "../core/types.h"

#if (HERMES_OS == HERMES_OS_WINDOWS_NT)
#include <WinSock2.h>
#endif

#define LOCAL_SERVER_PORT       5701

namespace dds
{
    class DomainParticipantImpl;
    class MessageBroker
    {
    public:
        MessageBroker();

        ~MessageBroker();

        int                         run();

        int                         sendMsg(void* pbuf, long length);

    public:
        int                         startLocalServer();

        int                         stopLocalServer();

        bool                        isLocalServerStarted();

        int                         connectToLocalServer();

        void                        sendProcessId();

        int                         startRecvThread();

        int                         stopRecvThread();

        bool                        isStoppedRecvThread();

        bool                        isRecvThreadStopped();

#if (HERMES_OS == HERMES_OS_WINDOWS_NT)
        void                        getLocalServerPath(char* path);
#endif

        SOCKET                      getSocket();

        void                        onRecv(char* buf, int len);

		void						setParticipant(DomainParticipantImpl*);
    private:
        DomainParticipantImpl*      m_dp;
#if (HERMES_OS == HERMES_OS_WINDOWS_NT)
        SOCKET                      m_socket;
#elif defined(__VXWORKS__) || defined(__QNXNTO__) || (HERMES_OS == HERMES_OS_LINUX)
        int							m_socket;
#endif
        Boolean                     m_bStop;

    };

}



#endif
