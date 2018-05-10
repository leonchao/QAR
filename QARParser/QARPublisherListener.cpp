#include "QARPublisherListener.h"

QARPublisherListener::QARPublisherListener(QObject *parent)
	: QObject(parent)
{
	dataBus = DataBus::getInstanse(QARDomainId);
	dataBus->registerPublisher(QARDataTopic);
	dataBus->registerListener(QARDataTopic, this);
	dataBus->registerListener(QARAircraftTopic, this);

}

QARPublisherListener::~QARPublisherListener()
{
	dataBus->releaseInstance(QARDomainId);
}

void QARPublisherListener::WriteMsg(const char *data, int size)
{
	dataBus->writer(QARDataTopic, size, data);
}

void QARPublisherListener::on_data_available(DDS::Long domainId, const std::string& topicName, char* buf, int len)
{
	if (domainId != QARDomainId)
		return;
	/*if (topicName == QARDataTopic)
	{
		QByteArray data;
		data.setRawData(buf, len);
		QARData qarData = deSerialize<QARData>(data);
		qDebug() << "DDS receive qar" << qarData.time;
	}*/
	if (topicName == QARAircraftTopic)
	{
		QByteArray data;
		data.setRawData(buf, len);
		QARAircraft aircraft = deSerialize<QARAircraft>(data);
		emit doGetAircraftInfo(aircraft);
	}
}
