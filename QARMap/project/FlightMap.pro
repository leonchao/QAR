#-------------------------------------------------
#
# Project created by QtCreator 2017-07-26T15:26:38
#
#-------------------------------------------------

QT       += core gui webenginewidgets webchannel network xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG +=

TARGET = FlightMap
TEMPLATE = app

RESOURCES += \
    src.qrc

FORMS += \
    ../source/resource/mainwindow.ui \
    aircraftinfoform.ui

HEADERS += \
    ../include/common.h \
    ../include/mainwindow.h \
    ../include/qarreceiver.h \
    aircraftinfoform.h \
    xplaneConnect.h

SOURCES += \
    ../source/main.cpp \
    ../source/mainwindow.cpp \
    ../source/qarreceiver.cpp \
    aircraftinfoform.cpp \
    xplaneConnect.c




INCLUDEPATH += $$PWD/../include
INCLUDEPATH += $$PWD/../../include


DISTFILES +=


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../CloudDDS/lib/X86/ -lCloudDDS
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../CloudDDS/lib/X86/ -lCloudDDSd
else:unix: LIBS += -L$$PWD/../../CloudDDS/lib/X86/ -lCloudDDS

INCLUDEPATH += $$PWD/../../CloudDDS/include
DEPENDPATH += $$PWD/../../CloudDDS/include
