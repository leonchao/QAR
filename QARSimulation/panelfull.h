#ifndef PANELFULL_H
#define PANELFULL_H

#include <QWidget>
#include <QImage>
#include <QEvent>
#include <QPainter>
#include <Windows.h>
#include <QWindow>
#include <QScreen>
#include <QRect>
#include <QLabel>
#include "structs.h"
#include "warningform.h"
#include <QPropertyAnimation>

namespace Ui {
class PanelFull;
}

class PanelFull : public QWidget
{
    Q_OBJECT

public:
    explicit PanelFull(QWidget *parent = 0);
    ~PanelFull();

    bool eventFilter(QObject *watched, QEvent *event);
    QWindow *windowPFD;
    QWidget *widgetPFD;
    void drawTime(QString time);
    void drawWarning(WarningInfo warning);
    void showInfo(QAROriginData data);

private:
    Ui::PanelFull *ui;
    QImage image;
    QScreen *sc;
    QSize fullSize;
    QSize pfdSize;
    QSize ndSize;
    QSize ecamSize;
    QSize mfdSize;

    QSize landSize,warnSize,cauSize,fdSize,lsSize;
    QSize cstrSize,wptSize,vorSize,ndbSize,arptSize,locSize,ap1Size,ap2Size,athrSize,apprSize,gearSize;

    QSize spdSize,baroSize,hdgSize,altSize,vsSize;

    QSize rudderSize,joystickSize,throttleSize;
    QSize gearleftSize,gearmainSize,gearrightSize;
    QSize rot1Size,rot2Size;
    QSize loSize,medSize,maxSize,terrSize;

    QPoint pfdPos;
    QPoint ndPos;
    QPoint ecamPos;
    QPoint mfdPos;
    QPoint landPos,warnPos,cauPos,fdPos,lsPos;
    QPoint cstrPos,wptPos,vorPos,ndbPos,arptPos,locPos,ap1Pos,ap2Pos,athrPos,apprPos,gearPos;

    QPoint baroPos,spdPos,hdgPos,altPos,vsPos;
    QPoint rudderPos,joystickPos,throttlePos;
    QPoint gearleftPos,gearmainPos,gearrightPos;
    QPoint rot1Pos,rot2Pos;
    QPoint loPos,medPos,maxPos,terrPos;

    QLabel *pfdLabel,*ndLabel,*ecamLabel,*mfdLabel;

    WarningForm *warnForm;

    QLabel *tipLabel;
    QPropertyAnimation *animation1,*animation2,*animation3;
};

#endif // PANELFULL_H
