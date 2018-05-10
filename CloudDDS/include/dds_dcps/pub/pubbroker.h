#ifndef _CLOUD_BUS_PUB_BROKER_H_
#define _CLOUD_BUS_PUB_BROKER_H_

#include "../core/dcps_core.h"
#include <map>
#include <string>

#if HERMES_OS == HERMES_OS_WINDOWS_NT
#include <WinSock2.h>
#pragma comment(lib,"ws2_32.lib")
#endif

BEGIN_DDS_NAMESPACE

extern void generator_addr(SOCKADDR_IN &toAddr, const char* topic, Long domainID);
class PubBroker
{
public:
	PubBroker();

	~PubBroker();

	void setInetInterface(const char *);
	ReturnCode_t pub_data(Long domainId, const char* topicName, const char* data, int len);

	ReturnCode_t pub_topic(Long domainId, const char* topicName);
private:
	SOCKET									m_socket;
	typedef std::map<std::string, size_t>	SeqMap;
	SeqMap									m_seqMap;
	std::map<Long, std::map<std::string, SOCKADDR_IN> > m_ipmap;
	ULONG m_sIpAddr;
};

END_DDS_NAMESPACE

#endif