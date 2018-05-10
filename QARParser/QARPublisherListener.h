#ifndef QARPUBLISHER_H
#define QARPUBLISHER_H

#include <QObject>
#include "databus.h"
#include "header.h"
#include "structs.h"

class QARPublisherListener : public QObject, public DDS::DataReaderListener
{
	Q_OBJECT

public:
	QARPublisherListener(QObject *parent = 0);
	~QARPublisherListener();

	void WriteMsg(const char *data, int size);
	//接收数据
	virtual void on_data_available(DDS::Long domainId, const std::string& topicName, char* buf, int len) override;

private:
	DataBus *dataBus;

signals:
	void doGetAircraftInfo(QARAircraft aircraft);
	
};

#endif // QARPUBLISHER_H
