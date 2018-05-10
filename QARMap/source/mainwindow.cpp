#include "../include/mainwindow.h"
#include "ui_mainwindow.h"
#include <QWebChannel>
#include <QGridLayout>

#define PI 3.1415926


char *dataRefs[] = {"sim/weather/visibility_reported_m",
                    "sim/weather/cloud_type[0]"
                   };

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QWebEnginePage *page = new QWebEnginePage(this);
    ui->webView->setPage(page);
    ui->webView->setContextMenuPolicy(Qt::NoContextMenu);   //无右键菜单
    //添加QWebChannel并利用其与HTML页面通信
    QWebChannel *channel = new QWebChannel(this);
    channel->registerObject(QString("content"),this);
    page->setWebChannel(channel);
    ui->webView->load(qApp->applicationDirPath() + "/Map.html");
    connect(ui->webView,SIGNAL(loadFinished(bool)),this,SLOT(onMapLoadFinished(bool)));
    connect(ui->webView,SIGNAL(loadProgress(int)),this,SLOT(onLoadProgress(int)));

    connect(ui->listWidget,SIGNAL(clicked(QModelIndex)),this,SLOT(onListItemClicked(QModelIndex)));
//    connect(ui->toolButton,SIGNAL(clicked()),this,SLOT(onToolButtonClicked()));
//    connect(ui->toolButton_move,SIGNAL(clicked()),this,SLOT(onMoveClicked()));

    //菜单操作


//    ui->listWidget->setStyleSheet("QListWidget{border:1px solid gray; color:black; }"
//                                  "QListWidget::Item{height:174px;padding-bottom:3px; }"
//                                  );

    ui->listWidget->setStyleSheet("QListWidget{border:1px solid gray; color:black; }"
                                  "QListWidget::Item{height:20px;padding-bottom:3px; }"
                                  "QListWidget::item:selected{background:lightgreen; color:black; }"
                                  );
//    ui->listWidget->setStyleSheet("QListWidget{border:1px solid gray; color:black; }"
//                                  "QListWidget::Item{height:105px;border:1px solid gray;padding-bottom:3px; }"
//                                  "QListWidget::item:selected{background:lightgreen; color:red; }"
//                                  );

    sock = openUDP("127.0.0.1");
    connect(&timer,SIGNAL(timeout()),this,SLOT(onTimeout()));
    timer.start(1000);

    //列表单选模式
    ui->listWidget->setSelectionMode(QAbstractItemView::SingleSelection);

    //listWidget菜单
    ui->listWidget->setContextMenuPolicy(Qt::ActionsContextMenu);
    //删除一个航班
    QAction *del = new QAction(QString::fromLocal8Bit("删除"),NULL);
    connect(del,SIGNAL(triggered(bool)),this,SLOT(onDeleteAction(bool)));
    //设置地图焦点
    QAction *focus = new QAction(QString::fromLocal8Bit("焦点查看"),NULL);
    focus->setCheckable(true);
    connect(focus,SIGNAL(triggered(bool)),this,SLOT(onFocusAction(bool)));
    //航班进行仿真
    QAction *simulate = new QAction(QString::fromLocal8Bit("进行仿真"),NULL);
    simulate->setCheckable(false);
    connect(simulate,SIGNAL(triggered(bool)),this,SLOT(onSimulateAction(bool)));
    QList<QAction*> actionList;
    actionList << del << focus << simulate;
    ui->listWidget->addActions(actionList);

    connect(&receiver,SIGNAL(doGetAirplaneInfo(AircraftInfo)),this,SLOT(onGetAirplaneInfo(AircraftInfo)));
    isMapLoaded = false;

    timeLabel = new QLabel(this);
    ui->statusBar->addWidget(timeLabel);
    flightNumLabel = new QLabel(QString::fromLocal8Bit("当前仿真飞机:"),this);
    ui->statusBar->addWidget(flightNumLabel);
    progressBar = new QProgressBar(this);
    ui->statusBar->addWidget(progressBar);
    progressBar->setMaximum(100);
    setWindowState(Qt::WindowMaximized);
    connect(ui->actionAbout,SIGNAL(hovered()),this,SLOT(onAboutHovered()));
    currentFlightNum = "";

    selectedAircraft = new AircraftInfoForm(AircraftInfo());
    ui->verticalLayout_2->addWidget(selectedAircraft);
    connect(selectedAircraft,SIGNAL(changeColor(bool,QString)),this,SLOT(onChangeColor(bool,QString)));

    //connect(&warnTimer,SIGNAL(timeout()),this,SLOT(onTimeout()));
    //image.load(":/background.png");
}

MainWindow::~MainWindow()
{
    delete timeLabel;
    timeLabel = NULL;
    disconnect();
    delete ui;
}



int MainWindow::getAircraftInfo(QString aircraftNum, AircraftInfo &info)
{
    if(!aircraftInfoMap.contains(aircraftNum))
        return -1;
    info = aircraftInfoMap[aircraftNum];
    return 0;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    receiver.exit();
    receiver.wait();
    QWidget::closeEvent(event);
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    //QPainter painter(ui->widget_2);
    //painter.drawImage(ui->widget_2->rect(),image,image.rect());
}


void MainWindow::onOpenView(bool)
{
    //打开视景程序

}

void MainWindow::onCloseView(bool)
{
    //关闭视景程序

}

void MainWindow::onPauseView(bool)
{
    //暂停视景程序

}

void MainWindow::onUnPauseView(bool)
{
    //解除视景暂停

}

void MainWindow::onSetWeather(bool)
{
    //视景天气设定
}

void MainWindow::onAbout(bool)
{
    //关于信息
    qDebug() << QString::fromLocal8Bit("关于");
}

void MainWindow::onHelp(bool)
{
    //帮助手册
    qDebug() << QString::fromLocal8Bit("帮助");
}

void MainWindow::onListItemClicked(QModelIndex index)
{
    qDebug() << index.row() << index.column();
    QListWidgetItem *item = ui->listWidget->item(index.row());
    AircraftInfo air = aircraftInfoMap[item->text()];
    selectedAircraft->updateAircraftInfo(air);
    //AircraftInfoForm *form = (AircraftInfoForm*)ui->listWidget->itemWidget(ui->listWidget->item(index.row()));

//    addAirplane(air.aircraftNum,air.latitude,air.longitude,air.rotation);
//    setPlaneState(air.aircraftNum,air.isFault);
//    if(air.aircraftNum == "SZ4324")
//        timer.start(10);
}


void MainWindow::onTimeout()
{
    timeLabel->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss"));
    static bool showFault = false;
    for(QMap<QString,AircraftInfo>::iterator it = aircraftInfoMap.begin(); it != aircraftInfoMap.end(); ++it)
    {
        if(!it.value().isFault)
        {
            setPlaneState(it.value().aircraftNum,it.value().isFault);
        }
        else
        {
            setPlaneState(it.value().aircraftNum,showFault);
        }
    }
    showFault = !showFault;
}

void MainWindow::onMapLoadFinished(bool finished)
{
    isMapLoaded = finished;
}

void MainWindow::onLoadProgress(int progress)
{
    progressBar->setValue(progress);
    if(progress >= 100)
    {
        progressBar->hide();
        ui->statusBar->removeWidget(progressBar);

    }
    qDebug() << progress;
}


void MainWindow::onDeleteAction(bool b)
{
    QList<QListWidgetItem*> items = ui->listWidget->selectedItems();
    if(items.isEmpty())
        return;

    AircraftInfo info = aircraftInfoMap[items.at(0)->text()];
    delete items.at(0);
    items[0] = NULL;

    onDeleteOneFlight(info);

}

void MainWindow::onFocusAction(bool b)
{
    QList<QListWidgetItem*> items = ui->listWidget->selectedItems();
    if(items.isEmpty())
    {
        ui->listWidget->actions()[1]->setChecked(false);
        return;
    }

    AircraftInfo info = aircraftInfoMap[items[0]->text()];
    setFocusAircraft(info.aircraftNum,b);


}

void MainWindow::onSimulateAction(bool b)
{
    QList<QListWidgetItem*> items = ui->listWidget->selectedItems();
    if(items.isEmpty())
    {
        ui->listWidget->actions()[2]->setChecked(false);
        return;
    }

    AircraftInfo info = aircraftInfoMap[items[0]->text()];
    selectedAircraft->updateAircraftInfo(info);
    QARAircraft qarInfo;
    qarInfo.flightNumber = info.aircraftNum;
    qarInfo.tailNumber = info.tailNumber;
    currentFlightNum = info.aircraftNum;
    flightNumLabel->setText(QString::fromLocal8Bit("当前仿真飞机:") + currentFlightNum);
    receiver.writeMsg(Serialize<QARAircraft>(qarInfo).data(),Serialize<QARAircraft>(qarInfo).size());
}

void MainWindow::onGetAirplaneInfo(AircraftInfo info)
{
    if(!isMapLoaded)
        return;
//    info.aircraftNum = "SZ4326";
    //info.tailNumber = "B777";
    //info.speed = 300.8;
    if(!aircraftInfoMap.contains(info.aircraftNum))
        onAddOneFlight(info);
    else
    {
        updateAircraftInfo(info);
    }
}

void MainWindow::onAboutHovered()
{
}


void MainWindow::onChangeColor(bool b, QString aircraftNum)
{
    //aircraftInfoMap[aircraftNum].first->setSelected(b);
//    if(b)
//    {
//        aircraftInfoMap[aircraftNum].first->setSelected(b);
//    }
//    else
//    {
//        aircraftInfoMap[aircraftNum].second->setStyleSheet("QWidget#AircraftInfoForm{border:2px solid red;}");
//    }
}

void MainWindow::onOpenWarnSystem(const QByteArray &bytedata)
{

}


void MainWindow::onAddOneFlight(const AircraftInfo &info)
{
    //如果航班列表中已经存在该航班号，则不添加
    if(aircraftInfoMap.contains(info.aircraftNum))
    {
        qDebug() << info.aircraftNum << " already exist!";
        return;
    }
    QListWidgetItem *item = new QListWidgetItem();
    //AircraftInfoForm *form = new AircraftInfoForm(info);
    item->setText(info.aircraftNum);
    //connect(form,SIGNAL(changeColor(bool,QString)),this,SLOT(onChangeColor(bool,QString)));
    aircraftInfoMap[info.aircraftNum] = info;
    ui->listWidget->addItem(item);
    //ui->listWidget->setItemWidget(item,form);
    QString str = structToJson(info);
    addAirplane(str);
    setPlaneState(info.aircraftNum,info.isFault);
    //if(info.isFault)
    //{
    //    item->setSelected(true);
    //}
    //else
    //{
    //    item->setSelected(false);
    //}
}

void MainWindow::onAddFlightList(const QList<AircraftInfo> &infoList)
{
    for(int i = 0; i < infoList.size(); i++)
    {
        onAddOneFlight(infoList[i]);
    }
}

void MainWindow::onDeleteOneFlight(const AircraftInfo &info)
{
    if(!aircraftInfoMap.contains(info.aircraftNum))
    {
        qDebug() << info.aircraftNum << " not exist!";
        return;
    }
//    QListWidgetItem *item = aircraftInfoMap[info.aircraftNum].first;
//    AircraftInfoForm *form = aircraftInfoMap[info.aircraftNum].second;
//    delete item;
//    delete form;
//    item = NULL;
//    form = NULL;
    selectedAircraft->clearInfo();
    deleteAircraft(info.aircraftNum);
    aircraftInfoMap.remove(info.aircraftNum);

}

void MainWindow::onDeleteFlightList(const QList<AircraftInfo> &infoList)
{
    for(int i = 0; i < infoList.size(); i++)
    {
        onDeleteOneFlight(infoList[i]);
    }
}

void MainWindow::onSetSelectedPlane(const QString &airplaneNum)
{
    qDebug() << "map select " << airplaneNum;
    QList<QListWidgetItem*> items = ui->listWidget->findItems(airplaneNum,Qt::MatchExactly);
    items[0]->setSelected(true);
    if(aircraftInfoMap.contains(airplaneNum))
    {
        selectedAircraft->updateAircraftInfo(aircraftInfoMap[airplaneNum]);
        //aircraftInfoMap[airplaneNum].first->setSelected(true);
    }
}

void MainWindow::updateAircraftInfo(const AircraftInfo &info)
{
    if(!aircraftInfoMap.contains(info.aircraftNum))
        return;
    //列表更新
    //aircraftInfoMap[info.aircraftNum].second->updateAircraftInfo(info);

    //jsonToObject(str);
    if(info.aircraftNum == selectedAircraft->getAircraftInfo().aircraftNum)
        selectedAircraft->updateAircraftInfo(info);
    QString str = structToJson(info);
    setPosition(str);
   //if(info.isFault)
   //{
   //    aircraftInfoMap[info.aircraftNum].first->setSelected(true);
   //}
   //else
   //{
   //    aircraftInfoMap[info.aircraftNum].first->setSelected(false);
   //}
}
