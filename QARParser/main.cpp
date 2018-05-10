#include "qarparser.h"
#include <QtWidgets/QApplication>
#include <databus.h>

#if _DEBUG
#pragma comment(lib, "CloudDDSd.lib")
#else
#pragma comment(lib, "CloudDDS.lib")
#endif

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	qRegisterMetaType<QAROriginData>("QAROriginData");
	qRegisterMetaType<QARAircraft>("QARAircraft");
	DataBus::initFactory("192.168.1.255");
	QARParser w;
	w.show();
	int ret = a.exec();
	return ret;
}
