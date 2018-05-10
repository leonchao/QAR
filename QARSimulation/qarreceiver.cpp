#include "qarreceiver.h"

QARReceiver::QARReceiver()
{
}

QARReceiver::~QARReceiver()
{

}

void QARReceiver::run()
{
    dataBus = DataBus::getInstanse(QARDomainId);
    dataBus->registerListener(QARAircraftTopic,this);
    dataBus->registerListener(QARDataTopic, this);
    exec();
    DataBus::releaseInstance(QARDomainId);
}


void QARReceiver::on_data_available(DDS::Long domainId, const std::string &topicName, char *buf, int len)
{
    if(domainId != QARDomainId)
        return;
    if (topicName == QARDataTopic)
    {
            QByteArray data;
            data.setRawData(buf, len);
            QAROriginData qarData = deSerialize<QAROriginData>(data);
            emit doGetQARInfo(qarData);
            qDebug() << "DDS receive qar" << qarData.time;
    }
    if (topicName == QARAircraftTopic)
    {
        QByteArray data;
        data.setRawData(buf, len);
        QARAircraft aircraft = deSerialize<QARAircraft>(data);
        emit doGetAircraftInfo(aircraft);
    }
}
