#include "mainwindow.h"
#include <QApplication>
#include <QThread>

#include "form.h"
#include "databus.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qRegisterMetaType<QAROriginData>("QAROriginData");
        qRegisterMetaType<QARAircraft>("QARAircraft");
    DataBus::initFactory("192.168.1.255");
    Form form;
    form.show();
    //PanelFull panel;
    //panel.show();
    return a.exec();
}


