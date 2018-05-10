#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../include/common.h"
#include "QWebEngineView"
#include <QSplitter>
#include <QListView>
#include <QStringListModel>
#include <QList>
#include <QTimer>
#include <QMap>
#include <QPair>
#include "aircraftinfoform.h"
#include <QListWidgetItem>
#include "xplaneConnect.h"
#include <QCloseEvent>
#include "qarreceiver.h"
#include <QLabel>
#include <QProgressBar>
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

private:
    Ui::MainWindow *ui;
    //QMap<QString,QPair<QListWidgetItem*,AircraftInfoForm*> > aircraftInfoMap;
    QTimer timer;
    //根据航班号获取航班信息
    //返回值 0 成功 非0失败
    int getAircraftInfo(QString aircraftNum,AircraftInfo &info);
    XPCSocket sock;
    QARReceiver receiver;
    //地图加载成功？
    bool isMapLoaded;

    QLabel *timeLabel;
    QLabel *flightNumLabel;
    QProgressBar *progressBar;
    bool changeColor;
    bool warnOpen;
    QString currentFlightNum;
    QImage image;
    QMap<QString,AircraftInfo> aircraftInfoMap;

    AircraftInfoForm *selectedAircraft;



protected:
    void closeEvent(QCloseEvent *event);
    void paintEvent(QPaintEvent *event);

signals:
    //设定某个航班在地图上的位置
    void setPosition(const QString &str);
    //添加一个航班到地图上
    void addAirplane(const QString &str);
    //设定地图上某个航班的朝向
    void setRotation(const QString &aircraftNum,const float &rotation);
    //设定航班的状态
    void setPlaneState(const QString &aircraftNum,const bool &isFault);
    //从地图上删除一个飞机信息
    void deleteAircraft(const QString &aircraftNum);
    //设定某个航班为焦点
    void setFocusAircraft(const QString &aircraftNum,const bool &getFocus);

    void jsonToObject(const QString &str);

private slots:
    //打开视景
    void onOpenView(bool);
    //关闭视景
    void onCloseView(bool);
    //暂停视景
    void onPauseView(bool);
    //解除暂停
    void onUnPauseView(bool);
    //设定天气
    void onSetWeather(bool);
    //关于
    void onAbout(bool);
    //帮助
    void onHelp(bool);

    void onListItemClicked(QModelIndex index);

    void onTimeout();
    //地图加载完成
    void onMapLoadFinished(bool finished);

    void onLoadProgress(int progress);

    void onDeleteAction(bool b);
    void onFocusAction(bool b);
    void onSimulateAction(bool b);

    void onGetAirplaneInfo(AircraftInfo info);

    void onAboutHovered();

    void onChangeColor(bool b,QString aircraftNum);

    void onOpenWarnSystem(const QByteArray& bytedata);


public slots:
    //添加一个航班
    void onAddOneFlight(const AircraftInfo &info);
    //添加一组航班
    void onAddFlightList(const QList<AircraftInfo> &infoList);
    //删除一个航班
    void onDeleteOneFlight(const AircraftInfo &info);
    //删除一组航班
    void onDeleteFlightList(const QList<AircraftInfo> &infoList);

    void onSetSelectedPlane(const QString &airplaneNum);

    //更新航班信息
    void updateAircraftInfo(const AircraftInfo &info);
};

#endif // MAINWINDOW_H
