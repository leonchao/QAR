#ifndef _CLOUD_BUS_PUB_BROKER_H_
#define _CLOUD_BUS_PUB_BROKER_H_

#include "../core/dcps_core.h"
#include <WinSock2.h>
#include <map>
#include <string>

#pragma comment(lib,"ws2_32.lib")

BEGIN_DDS_NAMESPACE

class SubscriberImpl;

class RecvBroker
{
public:
	RecvBroker(SubscriberImpl*);
	~RecvBroker();

	bool			start();

	bool			stop();

	bool			isStarted();

	bool			isStopped();
	void			setInetInterface(const char * ipmask);

	void			onRecv(char* data, size_t len);

	void			sub_topic(Long domainId, const char* topicName);

	void			cancel_sub(Long domainId, const char* topicName);

	bool			joinMulitGroup(ULONG& mcastAddr, ULONG& interfaceAddr);

	bool			leaveMultiGroup(ULONG& mcastAddr, ULONG& interfaceAddr);

	SOCKET			getSocket();


private:
	SOCKET									m_socket;
	SubscriberImpl*							m_pSub;
	ULONG									m_sIpAddr;
	bool									m_bStopped;
	bool									m_bStarted;
	HANDLE									m_threadHandle;
	typedef std::map<std::string, size_t>	SeqMap;
	SeqMap									m_seqMap;
	std::map<Long, std::map<std::string, SOCKADDR_IN> > m_ipmap;
};

END_DDS_NAMESPACE

#endif