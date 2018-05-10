#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QEvent>
#include <QMovie>
#include <QWindow>
#include <QWidget>
#include <Windows.h>
#include <QHBoxLayout>
#include <QGraphicsScene>
#include <QGraphicsProxyWidget>
#include "panelfull.h"
#include <QGraphicsView>
#include <QImage>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    bool eventFilter(QObject *watched, QEvent *event);

private:
    Ui::MainWindow *ui;
    float currentPercent;
    QMovie* movie;
    QImage image;

    QHBoxLayout *layoutXPlane;
    QWindow *windowXPlane;
    QWidget *widgetXPlane;
    WId xplaneId;

    QHBoxLayout *layoutPFD;
    QWindow *windowPFD;
    QWidget *widgetPFD;
    WId pfdId;

    QHBoxLayout *layoutND;
    QWindow *windowND;
    QWidget *widgetND;
    WId ndId;

    QHBoxLayout *layoutECAM;
    QWindow *windowECAM;
    QWidget *widgetECAM;
    WId ecamId;

    QHBoxLayout *layoutLECAM;
    QWindow *windowLowerECAM;
    QWidget *widgetLowerECAM;
    WId lowerEcamId;

    QGraphicsScene *scene = new QGraphicsScene();
    QGraphicsView *view = new QGraphicsView();
    QGraphicsProxyWidget *proxyWidget = new QGraphicsProxyWidget();
    PanelFull *panel_full;

    QGridLayout *layout;

    QWidget *widgetpanel = new QWidget();
    QWidget *widgetNull = new QWidget();
    QWidget *widgetFrame = new QWidget();
    QVBoxLayout *layoutFrame = new QVBoxLayout();

};

#endif // MAINWINDOW_H
