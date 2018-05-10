#include "panelfull.h"
#include "ui_panelfull.h"
#include <QMouseEvent>
#include <QDebug>
#include <QApplication>

PanelFull::PanelFull(QWidget *parent) :
    QWidget(parent),image(":/background.png"),
    ui(new Ui::PanelFull)
{
    ui->setupUi(this);
    ui->widgetNull->setAttribute(Qt::WA_TransparentForMouseEvents);
    //ui->widgetPanel->setAttribute(Qt::WA_TransparentForMouseEvents);
    //installEventFilter(this);
    ui->widgetPanel->installEventFilter(this);
    //this->setAttribute(Qt::WA_TransparentForMouseEvents);
    this->setAttribute(Qt::WA_TranslucentBackground);
    ui->widgetNull->setWindowOpacity(1);
    ui->widgetPanel->setWindowOpacity(1);
    this->setWindowOpacity(1);
    sc = QApplication::primaryScreen();
    ui->widgetPanel->resize(2946,972);
    fullSize = ui->widgetPanel->size();
    pfdSize = ui->widgetPFD->size();
    ndSize = ui->widgetND->size();
    ecamSize = ui->widgetECAM->size();
    mfdSize = ui->widgetMFD->size();
    landSize = ui->pushButtonLand->size();
    cauSize = ui->pushButton_master_cau->size();
    warnSize = ui->pushButton_master_warn->size();
    fdSize = ui->pushButton_FD->size();
    lsSize = ui->pushButton_LS->size();

    pfdPos = ui->widgetPFD->pos();
    ndPos = ui->widgetND->pos();
    ecamPos = ui->widgetECAM->pos();
    mfdPos = ui->widgetMFD->pos();

    landPos = ui->pushButtonLand->pos();
    cauPos = ui->pushButton_master_cau->pos();
    warnPos = ui->pushButton_master_warn->pos();
    fdPos = ui->pushButton_FD->pos();
    lsPos = ui->pushButton_LS->pos();

    cstrSize = ui->pushButton_CSTR->size();
    cstrPos = ui->pushButton_CSTR->pos();
    wptSize = ui->pushButton_WPT->size();
    wptPos = ui->pushButton_WPT->pos();

    vorSize = ui->pushButton_VOR->size();
    ndbSize = ui->pushButton_NDB->size();
    arptSize = ui->pushButton_ARPT->size();
    locSize = ui->pushButton_LOC->size();
    ap1Size = ui->pushButton_AP1->size();
    ap2Size = ui->pushButton_AP2->size();
    athrSize = ui->pushButton_ATHR->size();
    apprSize = ui->pushButton_APPR->size();
    gearSize = ui->pushButton_GEAR->size();

    vorPos = ui->pushButton_VOR->pos();
    ndbPos = ui->pushButton_NDB->pos();
    arptPos = ui->pushButton_ARPT->pos();
    locPos = ui->pushButton_LOC->pos();
    ap1Pos = ui->pushButton_AP1->pos();
    ap2Pos = ui->pushButton_AP2->pos();
    athrPos = ui->pushButton_ATHR->pos();
    apprPos = ui->pushButton_APPR->pos();
    gearPos = ui->pushButton_GEAR->pos();

    spdSize = ui->label_SPD->size();
    spdPos = ui->label_SPD->pos();
    baroSize = ui->label_BARO->size();
    baroPos = ui->label_BARO->pos();
    altSize = ui->label_ALT->size();
    altPos = ui->label_ALT->pos();
    hdgSize = ui->label_HDG->size();
    hdgPos = ui->label_HDG->pos();
    vsSize = ui->label_VS->size();
    vsPos = ui->label_VS->pos();

    rudderSize = ui->quickWidget->size();
    rudderPos = ui->quickWidget->pos();
    joystickSize = ui->quickWidget_joystick->size();
    joystickPos = ui->quickWidget_joystick->pos();
    throttleSize = ui->quickWidget_throttle->size();
    throttlePos = ui->quickWidget_throttle->pos();

    gearleftSize = ui->toolButton_gearleft->size();
    gearmainSize = ui->toolButton_gearmain->size();
    gearrightSize = ui->toolButton_gearright->size();
    gearleftPos = ui->toolButton_gearleft->pos();
    gearmainPos = ui->toolButton_gearmain->pos();
    gearrightPos = ui->toolButton_gearright->pos();

    rot1Size = ui->quickWidget_1->size();
    rot2Size = ui->quickWidget_2->size();
    rot1Pos = ui->quickWidget_1->pos();
    rot2Pos = ui->quickWidget_2->pos();

    loSize = ui->toolButton_BRK_LO->size();
    loPos = ui->toolButton_BRK_LO->pos();
    medSize = ui->toolButton_BRK_MED->size();
    medPos = ui->toolButton_BRK_MED->pos();
    maxSize = ui->toolButton_BRK_MAX->size();
    maxPos = ui->toolButton_BRK_MAX->pos();
    terrSize = ui->toolButton_TERR_ON_ND->size();
    terrPos = ui->toolButton_TERR_ON_ND->pos();


    pfdLabel = new QLabel();
    pfdLabel->setScaledContents(true);
    ui->verticalLayout_PFD->addWidget(pfdLabel);

    ndLabel = new QLabel();
    ndLabel->setScaledContents(true);
    ui->verticalLayout_ND->addWidget(ndLabel);

    ecamLabel = new QLabel();
    ecamLabel->setScaledContents(true);
    ui->verticalLayout_ECAM->addWidget(ecamLabel);

    mfdLabel = new QLabel();
    mfdLabel->setScaledContents(true);
    ui->verticalLayout_MFD->addWidget(mfdLabel);
    //windowPFD = QWindow::fromWinId(Id);
    //widgetPFD = QWidget::createWindowContainer(windowPFD);
    //ui->verticalLayout_2->addWidget(widgetPFD);
    //ui->widget->installEventFilter(this);
    setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    //this->setAttribute(Qt::WA_TransparentForMouseEvents);
    //ui->widgetPFD->setBackgroundRole(QPalette::Window);
    warnForm = new WarningForm(this);
    warnForm->setVisible(false);

    animation1 = new QPropertyAnimation(ui->toolButton_gearleft);
    animation1->setDuration(5000);
    animation2 = new QPropertyAnimation(ui->toolButton_gearmain);
    animation2->setDuration(5000);
    animation3 = new QPropertyAnimation(ui->toolButton_gearright);
    animation3->setDuration(5000);
    connect(animation1, &QPropertyAnimation::finished, [=](){
        ui->toolButton_gearleft->setStyleSheet("QToolButton{border:none;border-image: url(:/LDG-3.png);}"
                                               "QToolButton:checked{border-image: url(:/LDG-4.png);}"
                                               );
    });
    connect(ui->toolButton_gearleft, &QPushButton::toggled, [=](bool) {
        ui->toolButton_gearleft->setStyleSheet("QToolButton{border:none;border-image: url(:/LDG-2.png);}");
        animation1->start();
    });
    connect(animation2, &QPropertyAnimation::finished, [=](){
        ui->toolButton_gearmain->setStyleSheet("QToolButton{border:none;border-image: url(:/LDG-3.png);}"
                                               "QToolButton:checked{border-image: url(:/LDG-4.png);}"
                                               );
    });
    connect(ui->toolButton_gearmain, &QPushButton::toggled, [=](bool) {
        ui->toolButton_gearmain->setStyleSheet("QToolButton{border:none;border-image: url(:/LDG-2.png);}");
        animation2->start();
    });
    connect(animation3, &QPropertyAnimation::finished, [=](){
        ui->toolButton_gearright->setStyleSheet("QToolButton{border:none;border-image: url(:/LDG-3.png);}"
                                               "QToolButton:checked{border-image: url(:/LDG-4.png);}"
                                               );
    });
    connect(ui->toolButton_gearright, &QPushButton::toggled, [=](bool) {
        ui->toolButton_gearright->setStyleSheet("QToolButton{border:none;border-image: url(:/LDG-2.png);}");
        animation3->start();
    });
}

PanelFull::~PanelFull()
{
    delete ui;
}


bool PanelFull::eventFilter(QObject *watched, QEvent *event)
{
    //ui->widgetPFD->setGeometry(getNewRect(ui->widgetPanel->geometry()));
    if(event->type() == QEvent::Move || event->type() == QEvent::Resize)
    {


        QFont font;
        QSize newSize = ui->widgetPanel->size();
        ui->label_time->move(newSize.width() - 130,0);
        QVector2D scale;
        scale.setX((float)newSize.width() / (float)fullSize.width());
        scale.setY((float)newSize.height() / (float)fullSize.height());
        if(scale.x() * scale.y() >= 0.30f)
        {
            font.setPointSize(11);
        }
        else
        {
            font.setPointSize(5);
        }
        font.setBold(true);
        font.setFamily("Arial");
        ui->label_ALT->setFont(font);
        ui->label_BARO->setFont(font);
        ui->label_HDG->setFont(font);
        ui->label_SPD->setFont(font);
        ui->label_VS->setFont(font);

        ui->quickWidget_1->resize((float)rot1Size.width() * scale.x(),(float)rot1Size.height() * scale.y());
        ui->quickWidget_1->move((float)rot1Pos.x() * scale.x(),(float)rot1Pos.y() * scale.y());
        ui->quickWidget_2->resize((float)rot2Size.width() * scale.x(),(float)rot2Size.height() * scale.y());
        ui->quickWidget_2->move((float)rot2Pos.x() * scale.x(),(float)rot2Pos.y() * scale.y());

        ui->toolButton_gearleft->resize((float)gearleftSize.width() * scale.x(),(float)gearleftSize.height() * scale.y());
        ui->toolButton_gearleft->move((float)gearleftPos.x() * scale.x(),(float)gearleftPos.y() * scale.y());
        ui->toolButton_gearmain->resize((float)gearmainSize.width() * scale.x(),(float)gearmainSize.height() * scale.y());
        ui->toolButton_gearmain->move((float)gearmainPos.x() * scale.x(),(float)gearmainPos.y() * scale.y());
        ui->toolButton_gearright->resize((float)gearrightSize.width() * scale.x(),(float)gearrightSize.height() * scale.y());
        ui->toolButton_gearright->move((float)gearrightPos.x() * scale.x(),(float)gearrightPos.y() * scale.y());

        ui->quickWidget->resize((float)rudderSize.width() * scale.x(),(float)rudderSize.height() * scale.y());
        ui->quickWidget->move((float)rudderPos.x() * scale.x(),(float)rudderPos.y() * scale.y());
        ui->quickWidget_joystick->resize((float)joystickSize.width() * scale.x(),(float)joystickSize.height() * scale.y());
        ui->quickWidget_joystick->move((float)joystickPos.x() * scale.x(),(float)joystickPos.y() * scale.y());
        ui->quickWidget_throttle->resize((float)throttleSize.width() * scale.x(),(float)throttleSize.height() * scale.y());
        ui->quickWidget_throttle->move((float)throttlePos.x() * scale.x(),(float)throttlePos.y() * scale.y());

        ui->pushButton_CSTR->resize((float)cstrSize.width() * scale.x(),(float)cstrSize.height() * scale.y());
        ui->pushButton_CSTR->move((float)cstrPos.x() * scale.x(),(float)cstrPos.y() * scale.y());
        ui->pushButton_WPT->resize((float)wptSize.width() * scale.x(),(float)wptSize.height() * scale.y());
        ui->pushButton_WPT->move((float)wptPos.x() * scale.x(),(float)wptPos.y() * scale.y());

        ui->pushButton_VOR->resize((float)vorSize.width() * scale.x(),(float)vorSize.height() * scale.y());
        ui->pushButton_VOR->move((float)vorPos.x() * scale.x(),(float)vorPos.y() * scale.y());
        ui->pushButton_NDB->resize((float)ndbSize.width() * scale.x(),(float)ndbSize.height() * scale.y());
        ui->pushButton_NDB->move((float)ndbPos.x() * scale.x(),(float)ndbPos.y() * scale.y());
        ui->pushButton_ARPT->resize((float)arptSize.width() * scale.x(),(float)arptSize.height() * scale.y());
        ui->pushButton_ARPT->move((float)arptPos.x() * scale.x(),(float)arptPos.y() * scale.y());
        ui->pushButton_LOC->resize((float)locSize.width() * scale.x(),(float)locSize.height() * scale.y());
        ui->pushButton_LOC->move((float)locPos.x() * scale.x(),(float)locPos.y() * scale.y());
        ui->pushButton_AP1->resize((float)ap1Size.width() * scale.x(),(float)ap1Size.height() * scale.y());
        ui->pushButton_AP1->move((float)ap1Pos.x() * scale.x(),(float)ap1Pos.y() * scale.y());
        ui->pushButton_AP2->resize((float)ap2Size.width() * scale.x(),(float)ap2Size.height() * scale.y());
        ui->pushButton_AP2->move((float)ap2Pos.x() * scale.x(),(float)ap2Pos.y() * scale.y());
        ui->pushButton_ATHR->resize((float)athrSize.width() * scale.x(),(float)athrSize.height() * scale.y());
        ui->pushButton_ATHR->move((float)athrPos.x() * scale.x(),(float)athrPos.y() * scale.y());
        ui->pushButton_APPR->resize((float)apprSize.width() * scale.x(),(float)apprSize.height() * scale.y());
        ui->pushButton_APPR->move((float)apprPos.x() * scale.x(),(float)apprPos.y() * scale.y());
        ui->pushButton_GEAR->resize((float)gearSize.width() * scale.x(),(float)gearSize.height() * scale.y());
        ui->pushButton_GEAR->move((float)gearPos.x() * scale.x(),(float)gearPos.y() * scale.y());


        ui->widgetPFD->resize((float)pfdSize.width() * scale.x(),(float)pfdSize.height() * scale.y());
        ui->widgetPFD->move((float)pfdPos.x() * scale.x(),(float)pfdPos.y() * scale.y());
        ui->widgetND->resize((float)ndSize.width() * scale.x(),(float)ndSize.height() * scale.y());
        ui->widgetND->move((float)ndPos.x() * scale.x(),(float)ndPos.y() * scale.y());
        ui->widgetECAM->resize((float)ecamSize.width() * scale.x(),(float)ecamSize.height() * scale.y());
        ui->widgetECAM->move((float)ecamPos.x() * scale.x(),(float)ecamPos.y() * scale.y());
        ui->widgetMFD->resize((float)mfdSize.width() * scale.x(),(float)mfdSize.height() * scale.y());
        ui->widgetMFD->move((float)mfdPos.x() * scale.x(),(float)mfdPos.y() * scale.y());

        ui->pushButtonLand->resize((float)landSize.width() * scale.x(),(float)landSize.height() * scale.y());
        ui->pushButtonLand->move((float)landPos.x() * scale.x(),(float)landPos.y() * scale.y());
        ui->pushButton_master_cau->resize((float)cauSize.width() * scale.x(),(float)cauSize.height() * scale.y());
        ui->pushButton_master_cau->move((float)cauPos.x() * scale.x(),(float)cauPos.y() * scale.y());
        ui->pushButton_master_warn->resize((float)warnSize.width() * scale.x(),(float)warnSize.height() * scale.y());
        ui->pushButton_master_warn->move((float)warnPos.x() * scale.x(),(float)warnPos.y() * scale.y());
        ui->pushButton_FD->resize((float)fdSize.width() * scale.x(),(float)fdSize.height() * scale.y());
        ui->pushButton_FD->move((float)fdPos.x() * scale.x(),(float)fdPos.y() * scale.y());
        ui->pushButton_LS->resize((float)lsSize.width() * scale.x(),(float)lsSize.height() * scale.y());
        ui->pushButton_LS->move((float)lsPos.x() * scale.x(),(float)lsPos.y() * scale.y());

        ui->label_SPD->resize((float)spdSize.width() * scale.x(),(float)spdSize.height() * scale.y());
        ui->label_SPD->move((float)spdPos.x() * scale.x(),(float)spdPos.y() * scale.y());
        ui->label_BARO->resize((float)baroSize.width() * scale.x(),(float)baroSize.height() * scale.y());
        ui->label_BARO->move((float)baroPos.x() * scale.x(),(float)baroPos.y() * scale.y());
        ui->label_ALT->resize((float)altSize.width() * scale.x(),(float)altSize.height() * scale.y());
        ui->label_ALT->move((float)altPos.x() * scale.x(),(float)altPos.y() * scale.y());
        ui->label_HDG->resize((float)hdgSize.width() * scale.x(),(float)hdgSize.height() * scale.y());
        ui->label_HDG->move((float)hdgPos.x() * scale.x(),(float)hdgPos.y() * scale.y());
        ui->label_VS->resize((float)vsSize.width() * scale.x(),(float)vsSize.height() * scale.y());
        ui->label_VS->move((float)vsPos.x() * scale.x(),(float)vsPos.y() * scale.y());

        ui->toolButton_BRK_LO->resize((float)loSize.width() * scale.x(),(float)loSize.height() * scale.y());
        ui->toolButton_BRK_LO->move((float)loPos.x() * scale.x(),(float)loPos.y() * scale.y());
        ui->toolButton_BRK_MAX->resize((float)maxSize.width() * scale.x(),(float)maxSize.height() * scale.y());
        ui->toolButton_BRK_MAX->move((float)maxPos.x() * scale.x(),(float)maxPos.y() * scale.y());
        ui->toolButton_BRK_MED->resize((float)medSize.width() * scale.x(),(float)medSize.height() * scale.y());
        ui->toolButton_BRK_MED->move((float)medPos.x() * scale.x(),(float)medPos.y() * scale.y());
        ui->toolButton_TERR_ON_ND->resize((float)terrSize.width() * scale.x(),(float)terrSize.height() * scale.y());
        ui->toolButton_TERR_ON_ND->move((float)terrPos.x() * scale.x(),(float)terrPos.y() * scale.y());



        warnForm->move(this->geometry().left(),this->geometry().top());
    }
    if(watched == ui->widgetPanel && event->type() == QEvent::Wheel)
    {
        QWheelEvent* e = (QWheelEvent*)event;

        //static int value = 0;
        //if(e->delta() > 0)
        //{
        //    ui->quickWidget_1->setAngle(ui->quickWidget_1->angle + 45);
        //    ui->quickWidget_2->setAngle(ui->quickWidget_2->angle + 45);
        //    value++;
        //}
        //if(e->delta() < 0)
        //{
        //    ui->quickWidget_1->setAngle(ui->quickWidget_1->angle - 45);
        //    ui->quickWidget_2->setAngle(ui->quickWidget_2->angle - 45);
        //    value--;
        //}
        //ui->quickWidget_throttle->setValue(value,Oil::Direction::LEFT);
    }
    if(watched == ui->widgetPanel && event->type() == QEvent::Paint)
    {
        QSize newSize = ui->widgetPanel->size();
        QVector2D scale;
        scale.setX((float)newSize.width() / (float)fullSize.width());
        scale.setY((float)newSize.height() / (float)fullSize.height());
        QPainter painter(ui->widgetPanel);
        painter.setRenderHint(QPainter::SmoothPixmapTransform,true);
        painter.setRenderHint(QPainter::HighQualityAntialiasing,true);
        //image.scaled(ui->widget->size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
        painter.drawImage(ui->widgetPanel->rect(),image,image.rect());
        QPen pen;
        pen.setColor(Qt::yellow);
        pen.setStyle(Qt::SolidLine);
        pen.setWidth(5);
        painter.setPen(pen);

        WId Id = (WId)FindWindow(L"SunAwtFrame",L"PFD");
        if(Id != 0)
        {
            QPixmap pix = sc->grabWindow(Id);
            pfdLabel->setPixmap(pix);
        }
        Id = (WId)FindWindow(L"SunAwtFrame",L"ND");
        if(Id != 0)
        {
            QPixmap pix = sc->grabWindow(Id);
            ndLabel->setPixmap(pix);
        }
        Id = (WId)FindWindow(L"SunAwtFrame",L"EICAS");
        if(Id != 0)
        {
            QPixmap pix = sc->grabWindow(Id);
            ecamLabel->setPixmap(pix);
        }
        Id = (WId)FindWindow(L"SunAwtFrame",L"MFD");
        if(Id != 0)
        {
            QPixmap pix = sc->grabWindow(Id);
            mfdLabel->setPixmap(pix);
        }
        //painter.drawText(QRectF(QPointF((float)spdPos.x() * scale.x(),(float)spdPos.y() * scale.y()),QSizeF((float)spdSize.width() * scale.x(),(float)spdSize.height() * scale.y())),
        //                 Qt::AlignJustify | Qt::AlignCenter,"12345");

    }
    if(watched == ui->widgetPFD && event->type() == QEvent::Paint)
    {
        //QPainter painter(ui->widget);
        //painter.setRenderHint(QPainter::SmoothPixmapTransform,true);
        //painter.setRenderHint(QPainter::HighQualityAntialiasing,true);
        //WId Id = (WId)FindWindow(L"SunAwtFrame",L"PFD");
        //if(Id != 0)
        //{
        //    QPixmap pix = sc->grabWindow(Id);
        //    painter.drawPixmap(ui->widget->rect(),pix,pix.rect());
        //}

    }
    if(event->type() == QEvent::MouseButtonPress)
    {
        //static bool b = false;
        //ui->pushButton_master_cau->setChecked(b);
        //ui->pushButtonLand->setChecked(b);
        //ui->pushButton_AP1->setChecked(b);
        //ui->pushButton_AP2->setChecked(b);
        //ui->pushButton_GEAR->setChecked(b);
        //b = !b;
        //QMouseEvent* e = (QMouseEvent*)event;
        //static int i = 0;
        //ui->quickWidget->tread((Pedal::Direction)i);
        //i++;
        //if(i > 2)
        //    i = 0;
        //qDebug() << "mouse click" << e->button();
    }
    //QPainter painter(ui->widgetPFD);
    //painter.setRenderHint(QPainter::SmoothPixmapTransform,true);
    //painter.setRenderHint(QPainter::HighQualityAntialiasing,true);


    return QObject::eventFilter(watched,event);
}

void PanelFull::drawTime(QString time)
{


    ui->label_time->setText(time);
}

void PanelFull::drawWarning(WarningInfo warning)
{

}

void PanelFull::showInfo(QAROriginData data)
{
    ui->label_time->setText(data.aircraft.flightNumber + "\n" + data.time);
    ui->pushButton_AP1->setChecked(data.AP_1);
    ui->pushButton_master_warn->setChecked(!data.MAS_WAR_CA_CLR);
    ui->pushButton_master_cau->setChecked(!data.MAS_CAU_CA_CLR);
    ui->pushButton_GEAR->setChecked(!data.LG_M_DNLK_L1);
    ui->toolButton_gearleft->setChecked(!data.LG_M_DNLK_L1);
    ui->toolButton_gearmain->setChecked(!data.LG_M_DNLK_L1);
    ui->toolButton_gearright->setChecked(!data.LG_M_DNLK_L1);

    if(data.RUDDER_1 >= 0)
        ui->quickWidget->tread(data.RUDDER_PEDAL_1 / 20.0 * 100.0,Pedal::Direction::LEFT);
    else
        ui->quickWidget->tread(abs(data.RUDDER_1 / 20.0 * 100.0),Pedal::Direction::RIGHT);

    ui->label_ALT->setText(QString::number(data.ALT_SEL));
    ui->label_SPD->setText(QString::number(data.SPD_MACH_A_M));
    ui->label_HDG->setText(QString::number((int)(data.HEADING_SEL < 0 ? data.HEADING_SEL + 360 : data.HEADING_SEL)));
    warnForm->showWarning(data.warning);

    ui->quickWidget_throttle->setValue(data.THROTT_ANG1,Oil::Direction::LEFT);
    ui->quickWidget_throttle->setValue(data.THROTT_ANG2,Oil::Direction::RIGHT);
    if(data.PITCH_CAPT_1 == 0)
    {
        if(data.ROLL_CAPT_1 == 0)
            ui->quickWidget_joystick->setDirection(Rocker::Direction::NORMAL);
        else if(data.ROLL_CAPT_1 > 0.0)
            ui->quickWidget_joystick->setDirection(Rocker::Direction::RIGHT);
        else
            ui->quickWidget_joystick->setDirection(Rocker::Direction::LEFT);
    }
    else if(data.PITCH_CAPT_1 < 0.0)
    {
        if(data.ROLL_CAPT_1 == 0)
            ui->quickWidget_joystick->setDirection(Rocker::Direction::DOWN);
        else if(data.ROLL_CAPT_1 > 0.0)
            ui->quickWidget_joystick->setDirection(Rocker::Direction::RIGHTDOWNM);
        else
            ui->quickWidget_joystick->setDirection(Rocker::Direction::LEFTDOWN);
    }
    else
    {
        if(data.ROLL_CAPT_1 == 0)
            ui->quickWidget_joystick->setDirection(Rocker::Direction::UP);
        else if(data.ROLL_CAPT_1 > 0.0)
            ui->quickWidget_joystick->setDirection(Rocker::Direction::RIGHTUP);
        else
            ui->quickWidget_joystick->setDirection(Rocker::Direction::LEFTUP);
    }

//    font.setWeight();
//    ui->label_ALT->setFont(fonr);
//    ui->label_BARO->adjustSize();
//    ui->label_HDG->adjustSize();
//    ui->label_SPD->adjustSize();
//    ui->label_VS->adjustSize();
//    ui->label_ALT->adjustSize();
}

