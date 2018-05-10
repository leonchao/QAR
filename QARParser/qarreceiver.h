#ifndef QARRECEIVER_H
#define QARRECEIVER_H

#include <QThread>
#include <QUdpSocket>
#include <structs.h>
#include <QSharedPointer>
#include "header.h"

class QARReceiver : public QThread
{
	Q_OBJECT

public:
	QARReceiver(QObject *parent = 0);
	~QARReceiver();

	void run();

	void startListening();
	void stopListenning();

private:
	QUdpSocket *socket;

	private slots:
	void onReadData();

signals:
	void doGetQARData(QAROriginData data);
	
};

#endif // QARRECEIVER_H
