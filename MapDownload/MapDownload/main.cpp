#include "mapdownload.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MapDownload w;
	w.show();
	return a.exec();
}
