#ifndef QARRECEIVER_H
#define QARRECEIVER_H

#include <QObject>
#include <QThread>
#include "databus.h"
#include <structs.h>
#include "xplaneconnect.h"
#include <QTimer>
#include "header.h"

class QARReceiver : public QThread,public DDS::DataReaderListener
{
    Q_OBJECT
public:
    QARReceiver();
    ~QARReceiver();
    void run();
    virtual void on_data_available(DDS::Long domainId, const std::string& topicName, char* buf, int len) override;

private:
    DataBus* dataBus;
    int timeCount;

signals:
    void doGetQARInfo(QAROriginData data);
    void doGetAircraftInfo(QARAircraft aircraft);
};

#endif // QARRECEIVER_H
