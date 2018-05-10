#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QHBoxLayout>
#include <QMovie>
#include <QDebug>
#include <QWheelEvent>
#include <QKeyEvent>

#include <QDialog>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QFormLayout>
#include <QGraphicsProxyWidget>
#include <QGraphicsGridLayout>
#include <QScreen>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),image(":/background.png"),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    installEventFilter(this);

    //ui->widget->setAttribute(Qt::WA_TranslucentBackground);

    //ui->widget_2->setAttribute(Qt::WA_TranslucentBackground);

    //xplane
    //system("C:/Users/000009/Documents/first/debug/XHSI2.exe");
    xplaneId = (WId)FindWindow(L"X-System",L"X-System");
    windowXPlane = QWindow::fromWinId(xplaneId);
    widgetXPlane = QWidget::createWindowContainer(windowXPlane);

    ui->verticalLayout->addWidget(widgetXPlane);
    //ui->verticalLayout_2->addWidget(widgetXPlane);
    panel_full = new PanelFull(this);
    panel_full->installEventFilter(this);
    panel_full->resize(this->size());
    //panel_full->setAttribute(Qt::WA_TranslucentBackground);
    panel_full->raise();

    //ui->widgetXPlane->setLayout(layoutXPlane);
    //this->setWindowState(Qt::WindowFullScreen);


    //proxyWidget->resetTransform();
    //proxyWidget->setScale(ui->graphicsView->width()/proxyWidget->widget()->width());



//    QGraphicsGridLayout *layout = new QGraphicsGridLayout;
//    layout->addItem(top1,0,0);
//    layout->addItem(top2,0,1);
//    layout->addItem(top3,0,2);
//    QGraphicsWidget *form = new QGraphicsWidget;
//    form->setLayout(layout);
//    scene.addItem(form);


//    scene.addText("hello");

//    layoutFrame->setContentsMargins(0,0,0,0);
//    layoutFrame->setMargin(0);
//    layoutFrame->addWidget(widgetNull);
//    layoutFrame->addWidget(widgetpanel);
//    widgetFrame->setLayout(layoutFrame);

//    widgetFrame->resize(this->size());
//    widgetFrame->show();


}

MainWindow::~MainWindow()
{
    system("taskkill /F /IM javaw.exe");
    system("taskkill /F /IM X-Plane.exe");
    delete ui;
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    static bool b = true;

    if(watched == this)
    {
        switch (event->type()) {
        case QEvent::KeyPress:
        {
            QKeyEvent *key = (QKeyEvent*)event;
            switch (key->key()) {
            case Qt::Key_3:
            {
                if(b)
                {

                }
                else
                {
                }
                b = !b;
                break;
            }
            default:
                break;
            }
            break;
        }
        case QEvent::Paint:
        {
            //ui->widgetXPlane->stackUnder(panel_full);
            panel_full->raise();

        }
        case QEvent::Resize:
        {

        }
        default:
            break;
        }
    }
    return QObject::eventFilter(watched,event);
}
