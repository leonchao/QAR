#-------------------------------------------------
#
# Project created by QtCreator 2017-10-10T14:00:10
#
#-------------------------------------------------

QT       += core opengl gui quickwidgets xml
QT += network
LIBS += -luser32

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = simulation
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    panelfull.cpp \
    form.cpp \
    component/needle.cpp \
    component/pedal.cpp \
    component/planecomponent.cpp \
    component/pushbutton.cpp \
    component/rocker.cpp \
    component/rotarybutton.cpp \
    qarreceiver.cpp \
    warningform.cpp \
    component/oil.cpp

HEADERS  += mainwindow.h \
    panelfull.h \
    form.h \
    component/needle.h \
    component/pedal.h \
    component/planecomponent.h \
    component/pushbutton.h \
    component/rocker.h \
    component/rotarybutton.h \
    qarreceiver.h \
    warningform.h \
    component/oil.h

FORMS    += mainwindow.ui \
    panelfull.ui \
    form.ui \
    warningform.ui


INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.

INCLUDEPATH += $$PWD/component/.

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.

RESOURCES += \
    src.qrc

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../CloudDDS/lib/X86/ -lCloudDDS
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../CloudDDS/lib/X86/ -lCloudDDSd
else:unix: LIBS += -L$$PWD/../CloudDDS/lib/X86/ -lCloudDDS

INCLUDEPATH += $$PWD/../CloudDDS/include


CONFIG(debug, debug|release){
LIBS += -L$$PWD/../ConnectXPlane/libs/debug/ -lConnectXplane
} else {
LIBS += -L$$PWD/../../ConnectXPlane/release/ -lConnectXplane
}

INCLUDEPATH += $$PWD/../ConnectXPlane/include
INCLUDEPATH += $$PWD/../include
