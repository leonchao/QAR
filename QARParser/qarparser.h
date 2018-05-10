#ifndef QARPARSER_H
#define QARPARSER_H

#include <QtWidgets/QMainWindow>
#include "ui_qarparser.h"
#include "qarreceiver.h"
#include "filereader.h"
#include <QStringListModel>
#include <QDir>
#include <QFileInfoList>
#include "QARPublisherListener.h"
#include "ids.h"

#include "globals.h"

class QARParser : public QMainWindow
{
	Q_OBJECT

public:
	QARParser(QWidget *parent = 0);
	~QARParser();

	void closeEvent(QCloseEvent *event);

private:
	Ui::QARParserClass ui;

	QARReceiver receiver;
	QMap<QString,FileReader*> readerMap;
	QStringListModel *model;
	QStringList fileList;
	QMenu *listViewMenu;
	bool isWarningOpen;
	QARPublisherListener publisher;
	QTimer timer;
	QUdpSocket udpSocket;
	QARAircraft simulatingAircraft;

	void LoadFileInfo();
	void sendADCDPakcet(const QAROriginData &data);
	void sendAvionicsPacket(const QAROriginData &data);
	void sendCustomAvionicsPacket(const QAROriginData &data);
	void sendEnginesPacket(const QAROriginData &data);
	void sendStaticPacket(const QAROriginData &data);
	

	private slots:
	void onStartListenning(bool b);
	void onOpenWarning(bool b);
	//获取到QAR原始数据,将其分发到各个子系统
	void onGetQARData(QAROriginData data);
	void onListViewMenuRequest(const QPoint&pos);
	void openQARFile(bool b);
	void stopFileReader(bool b);
	void onSetReaderSpeed(int value);
	void onGetAircraftInfo(QARAircraft aircraft);
	void keepXHSIGaugeAlive();
	void onFileDone(QString fileName);
};

#endif // QARPARSER_H
