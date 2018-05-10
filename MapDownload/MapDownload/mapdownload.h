#ifndef MAPDOWNLOAD_H
#define MAPDOWNLOAD_H

#include <QtWidgets/QMainWindow>
#include "ui_mapdownload.h"
#include <QtNetwork>
#include <QUrl>

class QNetworkReply;
class QNetworkAccessManager;
class QFile;
#include <QList>

class MapDownload : public QMainWindow
{
	Q_OBJECT

public:
	MapDownload(QWidget *parent = 0);
	~MapDownload();
	void startRequest(QUrl url);
	QString parseUrl(int x, int y, int z);

private:
	Ui::MapDownloadClass ui;
	QNetworkAccessManager *manager;
	QNetworkReply *reply;
	QFile *file;
	QStringList strList;
	int pos;
	int zoom;
	int x;
	int y;

private slots:
	void replyFinished(QNetworkReply *reply);
	void httpReadyRead();
	void httpFinished();
	void updateDataReadProgress(int bytesRead, int bytesTotal);


	void on_pushButton_clicked();
	void getXYZ();

signals:
	void emitDownloadProcess(int current, int total);
};

#endif // MAPDOWNLOAD_H
