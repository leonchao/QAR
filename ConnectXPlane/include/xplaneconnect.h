#ifndef XPLANE_CONNECT_H
#define XPLANE_CONNECT_H

#include <QUdpSocket>
#include <QThread>
#include <QSharedPointer>
#include "struct.h"
#include <QMap>
#include <map>
using namespace std;
#include <QList>
#include <QtCore/qglobal.h>
#include <datadisplay.h>

#ifdef CONNECTXPLANE_LIB
# define CONNECTXPLANE_EXPORT Q_DECL_EXPORT
#else
# define CONNECTXPLANE_EXPORT Q_DECL_IMPORT
#endif

class CONNECTXPLANE_EXPORT XplaneConnect : public QThread
{
	Q_OBJECT

public:
	XplaneConnect(QObject *parent = 0);
	~XplaneConnect();
	//请求位置信息
	void requestPosition(int freq);
	//设定xplane位置信息
	void setPosition(veh1_struct pos);
	//请求数据
	void requestDataref(int freq, int index, QString dataref);
	//设定数据
	void setXplaneDataref(float svalue, QString dataref);
	//xplane内部命令
	void setXplaneCommand(QString cmdStr);
	//设定机场位置
	void setPlaneAirport(papt_struct airport);
	//开始连接
	void startConnect();
	//停止连接
	void stopConnect();
	//是否连接上
	bool isConnected;
	//是否显示数据窗口
	void showDisplayWindow(bool b);
	void setXplaneAddress(QString addr);
	QString getXplaneAddress();

	DataDisplay *getDisplayWidget();

private:
	QSharedPointer<QUdpSocket> socket;

	QSharedPointer<QUdpSocket> xplaneFinder;

	//要获取的数据,以及获取对应数据的频率
	QMap<int, QPair<int,QString> > drefMap;
	//可以向xplane发送的命令
	QMap<COMMANDS, QString> cmdMap;
	//获取消息中的命令
	COMMANDS getCommand(char *buff, int &pos);
	//获取消息内容
	void getMessageData(char *buff, int &len);
	void getMessageData(char *buff, int &len, QHostAddress host);
	DataDisplay *display;
	QTimer *timer;
	bool isListen;
	QString xplaneAddress;
signals:
	//获取到了位置信息
	void doGetPosition(position_struct pos);
	//获取到了数据信息
	void doGetDatarefs(QList<dref_struct_out> list);
	//获取到了xplane的组播信息
	void doGetBecn(becn_struct becn,QHostAddress host);

	private slots :
		void onStartRequestPosition(int freq);
		void onStartRequestDataref(int freq, int index, QString dataref);
		void onSetXplaneDataref(float svalue, QString dataref);
		void onSetPosition(veh1_struct pos);
		void onSetXplaneCommand(QString cmdStr);
		void onSetPlaneAirport(papt_struct airport);
		//读取消息并解析
		void readXplaneData();

		void readBecnData();

		//线程开始
		void onThreadStart();
		//
		void onGetPosition(position_struct pos);
		void onGetDatarefs(QList<dref_struct_out> list);
		//线程结束
		void onFinished();

		void onTimeout();

		void onConnected();

};

#endif // XPLANE_CONNECT_H
