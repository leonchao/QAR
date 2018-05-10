#include "form.h"
#include "ui_form.h"
#include <QDebug>

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mainForm)
{
    ui->setupUi(this);
    this->resize(900,760);
    //system("start /min calc");
    system("D:/debug/program/bin/start.bat");
    const char *appPath = "D:/debug/program/bin/XHSI2.exe";
    system(appPath);
    //QVBoxLayout *layout = new QVBoxLayout(widgetXPlane);
    //layout->addWidget(panel_full);
    //widgetXPlane->setLayout(layout);

    setWindowFlags(Qt::FramelessWindowHint | Qt::Tool);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setAttribute(Qt::WA_TransparentForMouseEvents);
    //this->setWindowOpacity(0);
    xplaneId = 0;

    while(xplaneId == 0)
    {
        //xplaneId = (WId)FindWindow(L"CalcFrame",NULL);
        xplaneId = (WId)FindWindow(L"X-System",L"X-System");
    }
    widget = new QWidget();
    widget->resize(this->size());
    xplaneLayout = new QVBoxLayout(widget);

    //widget->setAttribute(Qt::WA_TransparentForMouseEvents);
    windowXPlane = QWindow::fromWinId(xplaneId);
    widgetXPlane = QWidget::createWindowContainer(windowXPlane,this);
    widgetXPlane->installEventFilter(this);

    xplaneLayout->setContentsMargins(0,0,0,0);
    xplaneLayout->setMargin(0);
    xplaneLayout->addWidget(widgetXPlane);
    widgetSpace = new QWidget();
    xplaneLayout->addWidget(widgetSpace);
    xplaneLayout->setStretch(0,634);
    xplaneLayout->setStretch(1,446);
    widget->show();
    widget->installEventFilter(this);



    panel_full = new PanelFull();
    panel_full->installEventFilter(this);
    ui->verticalLayout->addWidget(panel_full);
    panel_full->setObjectName("view");
    //panel_full->setAttribute(Qt::WA_TransparentForMouseEvents);
    //panel_full->setStyleSheet("#view{background-color:transparent; border:none;}");
    panel_full->setGeometry(widget->geometry());
    //this->raise();
    QRect rect = widget->geometry();
    this->move(rect.left(),rect.top());
    timerId = startTimer(1000);
    receiver.start();
    connect(&receiver,SIGNAL(doGetQARInfo(QAROriginData)),this,SLOT(onGetQARInfo(QAROriginData)));
    connect(&receiver,SIGNAL(doGetAircraftInfo(QARAircraft)),this,SLOT(onGetAircraftInfo(QARAircraft)));

    xpl.startConnect();


}

Form::~Form()
{
    delete ui;
}



bool Form::eventFilter(QObject *watched, QEvent *e)
{
    if (watched == widget)
    {

        if ((e->type() == QEvent::Close) ||(e->type() == QEvent::Destroy))
        {
            receiver.terminate();
            system("taskkill /F /IM X-Plane.exe");
            system("taskkill /F /IM javaw.exe");
            if(panel_full)
                panel_full->close();
            if(this)
                this->close();
        }
        else if (e->type() == QEvent::MouseButtonPress)
        {
            qDebug() << "mouse click on background";

//            QRect rect = widget->geometry();
//            this->move(rect.left(),rect.top());
            //auto state = widget->windowState();
            //this->overrideWindowState(state);
        }
        else if(e->type() == QEvent::WindowActivate)
        {
            this->setGeometry(widget->geometry());
            this->raise();
        }
        else if(e->type() == QEvent::KeyPress)
        {
            QKeyEvent *key = (QKeyEvent*)e;
            static bool b = false;
            switch (key->key()) {
            case Qt::Key_1:
            {
                this->setVisible(b);
                if(!b)
                {
                    xplaneLayout->setStretch(0,1);
                    xplaneLayout->setStretch(1,0);
                }
                else
                {
                    xplaneLayout->setStretch(0,634);
                    xplaneLayout->setStretch(1,446);
                }
                b = !b;
                break;
            }
            case Qt::Key_2:
            {
                static bool farornear = false;
                if(!farornear)
                {
                    xpl.setXplaneCommand("sim/view/chase");
                }
                else
                {
                    xpl.setXplaneCommand("sim/view/forward_with_nothing");
                }
                farornear = !farornear;
                break;
            }
            case Qt::Key_F1:
            {
                static bool fullScreen = false;
                if(!fullScreen)
                {
                    widget->setWindowState(Qt::WindowFullScreen);
                }
                else
                {
                    widget->showNormal();
                }
                this->raise();
                fullScreen = !fullScreen;
                break;
            }
            case Qt::Key_Escape:
            {
                receiver.terminate();
                widget->close();
                panel_full->close();

                this->close();
            }

            default:
                break;
            }

        }
        else if(e->type() == QEvent::Hide)
        {
            this->hide();
            return QObject::eventFilter(watched,e);
        }
        else if(e->type() == QEvent::Show)
        {
            this->show();

        }
        else if(e->type() == QEvent::Resize || e->type() == QEvent::Move)
        {//panel_full->setGeometry(widget->geometry());
            this->setGeometry(widget->geometry());
            this->raise();
        }
        //widget->activateWindow();
        //this->raise();
    }
    else if(watched == this)
    {
        if(e->type() == QEvent::WindowActivate)
        {
            widget->activateWindow();
        }
        if(e->type() == QEvent::MouseButtonPress)
            qDebug() << "mouse clicked";
    }
    else if(watched == panel_full)
    {
        if(e->type() == QEvent::WindowActivate)
        {
            widget->activateWindow();
        }
    }
    return QObject::eventFilter(watched,e);
}

void Form::timerEvent(QTimerEvent *e)
{
    if(e->timerId() == timerId)
    {
        timeoutCount++;
        if(timeoutCount >= 5)
        {
            xpl.setXplaneDataref(0,"sim/time/sim_speed");
        }
    }
    QWidget::timerEvent(e);
}

void Form::onGetQARInfo(QAROriginData data)
{
    if(simulationAirctaft.flightNumber != data.aircraft.flightNumber)
        return;
    timeoutCount = 0;
    xpl.setXplaneDataref(1,"sim/time/sim_speed");
    panel_full->showInfo(data);
    veh1_struct pos;
    pos.p = 0;
    //int size = sizeof(veh1_struct);
    pos.lat_lon_ele[0] = data.LATP_LSH + data.LATP_MSH;
    pos.lat_lon_ele[1] = data.LONP_LSH + data.LONP_MSH;
    pos.lat_lon_ele[2] = /*((data.ALT_STD_LSH + data.ALT_STD_MSH)  * 0.3048 <= groundAlt) ? groundAlt : */((data.ALT_STD_LSH + data.ALT_STD_MSH)  * 0.3048);
    pos.psi_the_phi[0] = data.TRUE_HEADING;
    pos.psi_the_phi[1] = data.PITCH_ATT_1;
    pos.psi_the_phi[2] = data.ROLL_ATT;
    pos.gear_flap_vect[0] = data.LG_M_DNLK_L1;
    pos.gear_flap_vect[1] = 0;
    pos.gear_flap_vect[2] = (data.THROTT_ANG1 + data.THROTT_ANG2) / 50.0 / 2;
    xpl.setPosition(pos);
    if (data.LG_M_DNLK_L1)
    {
        xpl.setXplaneDataref(1, "sim/aircraft/parts/acf_gear_deploy[0]");
        xpl.setXplaneDataref(1, "sim/aircraft/parts/acf_gear_deploy[1]");
        xpl.setXplaneDataref(1, "sim/aircraft/parts/acf_gear_deploy[2]");
        xpl.setXplaneDataref(1, "sim/cockpit/switches/gear_handle_status");
    }
    else
    {
        xpl.setXplaneDataref(0, "sim/aircraft/parts/acf_gear_deploy[0]");
        xpl.setXplaneDataref(0, "sim/aircraft/parts/acf_gear_deploy[1]");
        xpl.setXplaneDataref(0, "sim/aircraft/parts/acf_gear_deploy[2]");
        xpl.setXplaneDataref(0, "sim/cockpit/switches/gear_handle_status");
    }
    xpl.setXplaneDataref(data.CAS_L,"sim/flightmodel/position/indicated_airspeed");
    xpl.setXplaneDataref(data.PITCH_CAPT_1, "sim/joystick/yoke_pitch_ratio");
    xpl.setXplaneDataref(data.ROLL_CAPT_1, "sim/joystick/yoke_roll_ratio");
    xpl.setXplaneDataref(data.RUDDER_1, "sim/joystick/yoke_heading_ratio");
    xpl.setXplaneDataref(data.THROTT_ANG1 / 50.0,"sim/cockpit2/engine/actuators/throttle_ratio[0]");
    xpl.setXplaneDataref(data.THROTT_ANG2 / 50.0,"sim/cockpit2/engine/actuators/throttle_ratio[1]");
}

void Form::onGetAircraftInfo(QARAircraft aircraft)
{
    simulationAirctaft = aircraft;
}
