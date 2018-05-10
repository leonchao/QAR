#ifndef AIRCRAFTINFOFORM_H
#define AIRCRAFTINFOFORM_H

#include <QWidget>
#include "../include/common.h"
#include <QTimer>

namespace Ui {
class AircraftInfoForm;
}

class AircraftInfoForm : public QWidget
{
    Q_OBJECT

public:
    explicit AircraftInfoForm(const AircraftInfo &info);
    ~AircraftInfoForm();
    void updateAircraftInfo(const AircraftInfo &info);
    AircraftInfo getAircraftInfo();
    void clearInfo();

private:
    Ui::AircraftInfoForm *ui;
    AircraftInfo info;
    QTimer timer;
    bool bShowFault;

private slots:
    void onTimeout();
signals:
    void changeColor(bool b,QString aircraftNum);
};

#endif // AIRCRAFTINFOFORM_H
