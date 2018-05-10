#include "aircraftinfoform.h"
#include "ui_aircraftinfoform.h"

AircraftInfoForm::AircraftInfoForm(const AircraftInfo &info) :
    ui(new Ui::AircraftInfoForm)
{
    ui->setupUi(this);
    //ui->label_aircraft_number->setText(info.aircraftNum);
    //ui->label_latitude->setText(QString::number(info.longitude, 'g', 6));
    //ui->label_longitude->setText(QString::number(info.latitude, 'g', 6));
    //ui->label_altitude->setText(QString("%1(%2)/%3(m)").arg(QString::number(info.altitude, 'g', 6),"feet",QString::number(info.altitude * 0.3048, 'g', 6)));
    //ui->label_tailNumber->setText(info.tailNumber);
    //ui->label_Speed->setText(QString("%1(%2)").arg(QString::number(info.speed,'g',6),"kts"));
    connect(&timer,SIGNAL(timeout()),this,SLOT(onTimeout()));
    //bShowFault = info.isFault;
    //if(info.isFault)
    //{
    //    ui->label_status->setText(QString("异常"));
    //    switch (info.warningLevel)
    //    {
    //    case 1:
    //        ui->frame->setStyleSheet("QFrame#frame{border:6px solid yellow}");
    //        break;
    //    case 2:
    //        ui->frame->setStyleSheet("QFrame#frame{border:6px solid red}");
    //        break;
    //    default:
    //        break;
    //    }
    //}
    //else
    //{
    //    ui->label_status->setText(QString("正常"));
    //    ui->frame->setStyleSheet("QFrame#frame{border:6px solid green}");
    //
    //}
    this->info = info;

//    setWindowFlags(Qt::FramelessWindowHint);
}

AircraftInfoForm::~AircraftInfoForm()
{
    delete ui;
}

void AircraftInfoForm::updateAircraftInfo(const AircraftInfo &info)
{
    ui->label_tailNumber->setText(info.tailNumber);
    ui->label_Speed->setText(QString("%1(%2)").arg(QString::number(info.speed,'g',6),"kts"));
    ui->label_aircraft_number->setText(info.aircraftNum);
    ui->label_latitude->setText(QString::number(info.longitude, 'g', 6));
    ui->label_longitude->setText(QString::number(info.latitude, 'g', 6));
    ui->label_altitude->setText(QString("%1(%2)/%3(m)").arg(QString::number(info.altitude, 'g', 6),"feet",QString::number(info.altitude * 0.3048, 'g', 6)));
    bShowFault = info.isFault;
    if(info.isFault)
    {
        ui->label_status->setText(QString("异常"));

//        switch (info.warningLevel)
//        {
//        case 1:
//            ui->frame->setStyleSheet("QFrame#frame{border:6px solid yellow}");
//            break;
//        case 2:
//            ui->frame->setStyleSheet("QFrame#frame{border:6px solid red}");
//            break;
//        default:
//            break;
//        }
        if(!timer.isActive())
            timer.start();
    }
    else
    {
        ui->label_status->setText(QString("正常"));
        ui->frame->setStyleSheet("QFrame#frame{border:6px solid green}");
        if(timer.isActive())
            timer.stop();
    }
    this->info = info;
}

AircraftInfo AircraftInfoForm::getAircraftInfo()
{
    return info;
}

void AircraftInfoForm::clearInfo()
{
    this->info.aircraftNum = "";
    this->info.tailNumber = "";
    ui->label_aircraft_number->setText("");
    ui->label_latitude->setText("");
    ui->label_longitude->setText("");
    ui->label_altitude->setText("");
    ui->label_tailNumber->setText("");
    ui->label_Speed->setText("");
    ui->label_status->setText("");
}

void AircraftInfoForm::onTimeout()
{

    if(bShowFault)
    {
        switch (info.warningLevel)
        {
        case 1:
            ui->frame->setStyleSheet("QFrame#frame{border:6px solid yellow}");
            break;
        case 2:
            ui->frame->setStyleSheet("QFrame#frame{border:6px solid red}");
            break;
        default:
            break;
        }

    }
    else
    {
        ui->frame->setStyleSheet("QFrame#frame{border:6px solid green}");
    }
    bShowFault = !bShowFault;
    emit changeColor(bShowFault,info.aircraftNum);
}
