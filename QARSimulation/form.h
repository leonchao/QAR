#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include "panelfull.h"
#include <QVBoxLayout>
#include <Windows.h>
#include <QWindow>
#include <QResizeEvent>
#include "qarreceiver.h"
#include "warningform.h"

namespace Ui {
class mainForm;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = 0);
    ~Form();

    bool eventFilter(QObject *watched, QEvent *event);

    void timerEvent(QTimerEvent *e);

private:
    Ui::mainForm *ui;
    WId xplaneId;
    PanelFull *panel_full;
    QWidget *widgetXPlane;
    QWindow *windowXPlane;
    QVBoxLayout *xplaneLayout;
    QWidget* widget;
    QWidget* widgetSpace;
    int timerId;
    QARReceiver receiver;
    QARAircraft simulationAirctaft;
    XplaneConnect xpl;
    int timeoutCount;
    WarningForm *warnForm;

private slots:
    void onGetQARInfo(QAROriginData data);
    void onGetAircraftInfo(QARAircraft aircraft);

};

#endif // FORM_H
