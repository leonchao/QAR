#ifndef FILEREADER_H
#define FILEREADER_H

#include <QThread>
#include <QFile>
#include <QTimer>
#include "header.h"
#include "structs.h"

class FileReader : public QThread
{
	Q_OBJECT

public:
	FileReader(QObject *parent = 0);
	~FileReader();

	void run();

	void OpenFile(QString fileName);
	void StopReader();
	//设定回放速度，每秒几次
	void SetSpeed(int speed);
	bool readFileData();

private:
	QTimer *timer;
	QString fileName;
	bool started;
	int speed;

	QList<QAROriginData> dataList;

	private slots:
	void onTimeout();

signals:
	void doGetQARData(QAROriginData qarData);
	void fileDone(QString fileName);
	
	
};

#endif // FILEREADER_H
