/*
 * 接收QAR实时数据，解析成相应的数据格式，供其他模块使用
 */
#ifndef QARRECEIVER_H
#define QARRECEIVER_H

#include <QObject>
#include "../include/common.h"
#include "structs.h"
#include <QThread>
#include <QTimer>
#include <QTimerEvent>
#include "databus.h"
#include "header.h"

class QARReceiver : public QThread, public DDS::DataReaderListener
{
    Q_OBJECT
public:
    QARReceiver();
    ~QARReceiver();

    //解析QAR数据 输入参数待定 输出航班信息结构体
    AircraftInfo parseQAR(const QAROriginData &data);
    void run();
    virtual void on_data_available(DDS::Long domainId, const std::string& topicName, char* buf, int len) override;
    void writeMsg(char *data,int len);

private:
//    QTimer *timer;
    DataBus *dataBus;

signals:
    void doGetAirplaneInfo(AircraftInfo info);

private slots:

};

#endif // QARRECEIVER_H
