#include "mapdownload.h"
#include <QString>
#include <QDir>
#include <QMessageBox>
#include <math.h>
#include <QChar>

MapDownload::MapDownload(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	manager = new QNetworkAccessManager(this);
	connect(manager, SIGNAL(finished(QNetworkReply *)), this, SLOT(replyFinished(QNetworkReply*)));
	file = new QFile();
	for (int i = 5; i <= 8; i++)
	{
		for (int j = 0; j < pow(2, i); j++)
		{
			for (int k = 0; k < pow(2, i); k++)
			{
				QString str;
				str.sprintf("%d,%d,%d", j, k, i);
				strList.append(str);
			}
		}
	}
	pos = 0;
	getXYZ();
	connect(this, SIGNAL(emitDownloadProcess(int, int)), this, SLOT(updateDataReadProgress(int, int)));
}

MapDownload::~MapDownload()
{
	delete file;
	file = NULL;
}

void MapDownload::startRequest(QUrl url)
{
	reply = manager->get(QNetworkRequest(url));
	connect(reply, SIGNAL(readyRead()), this, SLOT(httpReadyRead()));
	
	connect(reply, SIGNAL(finished()), this, SLOT(httpFinished()));
}

QString MapDownload::parseUrl(int x, int y, int z)
{
	QString strUrl = QString("http://mt1.google.cn/vt/lyrs=y&hl=zh-CN&gl=cn&x=") + QString::number(x) + QString("&y=") + QString::number(y) + QString("&z=") + QString::number(zoom);
	return strUrl;
}

void MapDownload::replyFinished(QNetworkReply *reply)
{
	file->close();
}

void MapDownload::httpReadyRead()
{
	if (file)
		file->write(reply->readAll());
}

void MapDownload::httpFinished()
{
	file->close();
	if (pos >= strList.size())
	{
		
		return;
	}
	emit updateDataReadProgress(pos+1, strList.size());
	pos++;
	getXYZ();
	on_pushButton_clicked();
	
}

void MapDownload::updateDataReadProgress(int bytesRead, int bytesTotal)
{
	ui.progressBar->setMaximum(bytesTotal);
	ui.progressBar->setValue(bytesRead);
}



void MapDownload::on_pushButton_clicked()
{
	if (pos >= strList.size())
		return;
	ui.label_x->setText(QString::number(x));
	ui.label_y->setText(QString::number(y));
	ui.label_z->setText(QString::number(zoom));
	ui.label_percent->setText(QString("%1/%2").arg(pos + 1).arg(strList.size()));
	QDir *dir = new QDir;
	QString dirName = "./Maps/" + QString::number(zoom) + "/" + QString::number(x);
	if (!dir->exists(dirName))
	{
		bool ok = dir->mkpath(dirName);
		if (!ok)
			return;
	}

	
	QString fileName = dirName + "/" + QString::number(y) + ".png";
	QUrl url = QUrl(parseUrl(x, y, zoom));
	file->setFileName(fileName);
	if (!file->open(QIODevice::WriteOnly))
	{
		qDebug() << "file open error";
		QMessageBox::information(this, "中断", "创建文件中断");
		delete file;
		file = 0;
		return;
	}
	delete dir;
	dir = NULL;
	startRequest(url);
	
}

void MapDownload::getXYZ()
{
	if (pos >= strList.size())
		return;
	QStringList xyz = strList[pos].split(",");
	x = xyz[0].toInt();
	y = xyz[1].toInt();
	zoom = xyz[2].toInt();
}
