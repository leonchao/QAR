#ifndef DATABUS_H
#define DATABUS_H

#pragma warning (disable : 4786)
#pragma warning (disable : 4275)
#pragma warning (disable : 4099)
#pragma warning (disable : 4251)

#include "dds_dcps/dcps.h"
#include <vector>
#include <map>
#include <set>
#include <string>

enum QosType {
	QosTypeDefault,
	QosTypeHistorySave
};

using MyReaderListener = DDS::DataReaderListener;
// template class CLOUDBUS_API std::allocator<MyReaderListener*>;
// template class CLOUDBUS_API std::allocator<DDS::DataReader_ptr>;
// template class CLOUDBUS_API std::allocator<DDS::DataWriter_ptr>;
// template class CLOUDBUS_API std::allocator<DDS::Topic_ptr>;
// template class CLOUDBUS_API std::less<MyReaderListener *>;
// template class CLOUDBUS_API std::set<MyReaderListener*>;
// template class CLOUDBUS_API std::set<std::string>;
// template class CLOUDBUS_API std::map<std::string, std::set<MyReaderListener*>>;
// template class CLOUDBUS_API std::map<std::string, DDS::DataReader_ptr>;
// template class CLOUDBUS_API std::map<std::string, DDS::DataWriter_ptr>;
// template class CLOUDBUS_API std::map<std::string, DDS::Topic_ptr>;

class  CLOUDBUS_API DataBus
{
public:
	static DataBus* getInstanse(int argc, char* argrv[], int domainId = 1);
	static DataBus* getInstanse(int domainId);
	static void releaseInstance(int domainId);
	//DataBus(int domainId = 1, DDS::DomainParticipantQos domainQos = PARTICIPANT_QOS_DEFAULT);
	~DataBus();
	//转换函数
	inline static void translateTopicToTag(const std::string& topicName, int& tag_1, int& tag_2)
	{
		int temp = topicName.find(':', 0);
		if (temp < 0)
		{
			return;
		}
		tag_1 = atoi(topicName.substr(0, temp).c_str());
		tag_2 = atoi(topicName.substr(temp + 1).c_str());
	}

	inline int getDomainID() { return mDomainID; };
	inline static std::string& translateTagToTopic(int tag_1, int tag_2)
	{
		static std::map<int, std::map<int, std::string>> tagTopic;
		if (tagTopic[tag_1][tag_2].empty())
		{
			char arr[ 25 ];
			sprintf_s(arr, "%02d:%02d", tag_1, tag_2);
			tagTopic[ tag_1 ][ tag_2 ].append(arr);
		}
		return tagTopic[ tag_1 ][ tag_2 ];
	}
	inline static bool initFactory(const char* ipaddr)
	{
		strcpy_s(m_ipmask, sizeof(m_ipmask), ipaddr);
		return true;
	}

	// 停止监听者
	void stopListener(const std::string &item);
	// 发送数据,第一个参数主题名称，第二个参数发送大小，第三个参数发送内容，第四个参数是写入者属性
	DDS::ReturnCode_t writer(const std::string& topicName, int size, const  char* data, QosType qosType = QosTypeDefault);
	DDS::ReturnCode_t writer(const char* topicName, int size, const  char* data, QosType qosType = QosTypeDefault);
	// 注册监听
	bool registerListener(const std::string& topicName, MyReaderListener* listener, QosType qosType = QosTypeDefault);
	bool registerPublisher(const std::string& topicName, QosType qosType = QosTypeDefault);

private:
	DataBus() = default;
	static char m_ipmask[24];
	int mDomainID;
	DDS::DomainParticipant_ptr d_ptr;

	DDS::Publisher_ptr m_ppub;
	DDS::Subscriber_ptr m_psub;

	using TopicListenMap = std::map<std::string, std::set<MyReaderListener*>>;
	using TopicSet = std::set<std::string>;
	TopicSet mRegisterPub;
	TopicListenMap mRegisterSub;
	std::map<std::string, DDS::DataReader_ptr> m_reader;
	std::map<std::string, DDS::DataWriter_ptr> m_writer;
	std::map<std::string, DDS::Topic_ptr> m_topic;
};

#ifndef DataBusIns
#define DataBusIns(a) DataBus::getInstanse(a)
#endif

#endif //DATABUS_H
