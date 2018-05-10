#ifndef _CLOUD_BUS_INTERNAL_TYPES_H_
#define _CLOUD_BUS_INTERNAL_TYPES_H_

#include "basictypes.h"

#if (HERMES_OS == HERMES_OS_WINDOWS_NT)
#include <WinSock2.h>
#include <windows.h>
#include <objbase.h>
#endif

#pragma pack(push)
#pragma pack(1)
namespace DDS
{
    enum INTERNALDATATYPE
    {
        TYPE_NONE = 0,
        TYPE_CLIENT_PUB_TOPIC   = 0xEB900101,
        TYPE_CLIENT_PUB_DATA    = 0xEB900102,
        TYPE_SERVER_PUB_DATA    = 0xEB900103,
        TYPE_CLIENT_SUB_TOPIC   = 0xEB900104,
        TYPE_CLIENT_CANCEL_PUB  = 0xEB900105,
        TYPE_CLIENT_CANCEL_SUB  = 0xEB900106,

        TYPE_CLIENT_PID         = 0xEB900110
    };

    enum SubResult
    {
        TOPIC_SUB_SUCCEEDED,
        TOPIC_NOT_EXIST,
        TOPIC_IN_OTHER_NODE
    };

    enum NODETYPE
    {
        UNKOWN,
        CLIENT,
        SERVER
    };

    enum SUBTYPE
    {
        REALTIME,
        RELIABILITY
    };


    typedef struct Header
    {
        INTERNALDATATYPE            type;
        ULong                       length;
        Long                        domainId;

        Header()
        {
            type = TYPE_NONE;
            length = sizeof(Header);
            domainId = 0;
        }

    }Header;

    typedef struct  TopicHeader
    {
        Header              header;
        char                topicName[40];

        TopicHeader()
        {
            header.length = sizeof(TopicHeader);
            memset(topicName, 0, sizeof(topicName));
        }
    }TopicHeader;

    typedef struct PublishHeader
    {
        TopicHeader         topic;
        GUID                publisherId;
        ULong               clientPid;

        PublishHeader()
        {
            topic.header.length = sizeof(PublishHeader);
            memset(&publisherId, 0, sizeof(publisherId));
            clientPid = 0;
        }
    }PublishHeader;

    typedef struct TransmitHeader
    {
        TopicHeader         topic;
        GUID                publisherId;
        ULong               seq;

        TransmitHeader()
        {
            topic.header.length = sizeof(TransmitHeader);
            memset(&publisherId, 0, sizeof(publisherId));
            seq = 0;
        }
    } TransmitHeader;


    typedef struct SubscribeHeader 
    {
        TopicHeader         topic;
        GUID                subscriberId;
        ULong               clientPid;
        SUBTYPE             subType;

        SubscribeHeader()
        {
            topic.header.length = sizeof(SubscribeHeader);
            memset(&subscriberId, 0, sizeof(subscriberId));
            clientPid = 0;
            subType = REALTIME;
        }
    }SubscribeHeader;

    typedef struct ClientPidHeader
    {
        Header              header;
        Long                clientPid;

        ClientPidHeader()
        {
            header.type = TYPE_CLIENT_PID;
            header.length = sizeof(ClientPidHeader);
            clientPid = 0;
        }
    }ClientPidHeader;

}
#pragma pack(pop)


#endif