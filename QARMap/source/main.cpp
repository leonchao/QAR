#include "../include/mainwindow.h"
#include <QApplication>
#include "xplaneConnect.h"
#include <QThread>
#include <iostream>
using namespace std;
#include <QUdpSocket>




int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qRegisterMetaType<AircraftInfo>("AircraftInfo");
    DataBus::initFactory("192.168.1.255");
    MainWindow w;
    w.show();


    return a.exec();
}

