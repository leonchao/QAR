#include "../include/qarreceiver.h"
#include <QDebug>

QARReceiver::QARReceiver()
{
    dataBus = NULL;
    this->start();
}

QARReceiver::~QARReceiver()
{
}

AircraftInfo QARReceiver::parseQAR(const QAROriginData &data)
{
    AircraftInfo info;
    info.aircraftNum = data.aircraft.flightNumber;
    info.tailNumber = data.aircraft.tailNumber;
    info.speed = data.CAS_L;
    info.isFault = (bool)data.warning.warningKind;
    info.warningKind = data.warning.warningKind;
    info.warningLevel = data.warning.warningLevel;
    info.latitude = data.LATP_LSH + data.LATP_MSH;
    info.longitude = data.LONP_LSH + data.LONP_MSH;
    info.altitude = data.ALT_STD_LSH + data.ALT_STD_MSH;
    info.rotation = data.TRUE_HEADING / 360.0f * 6.3;
    return info;
}

void QARReceiver::run()
{
    dataBus = DataBus::getInstanse(QARDomainId);
    dataBus->registerPublisher(QARAircraftTopic);
    dataBus->registerListener(QARDataTopic, this);
    exec();
    dataBus->releaseInstance(1);

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
            AircraftInfo info = parseQAR(qarData);
            emit doGetAirplaneInfo(info);
            qDebug() << "DDS receive qar" << qarData.time;
    }
}

void QARReceiver::writeMsg(char *data, int len)
{
    if(dataBus == NULL)
        return;
    dataBus->writer(QARAircraftTopic, len, data);
}



