/********************************************************************************
** Form generated from reading UI file 'aircraftinfoform.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AIRCRAFTINFOFORM_H
#define UI_AIRCRAFTINFOFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AircraftInfoForm
{
public:
    QGridLayout *gridLayout;
    QFrame *frame;
    QGridLayout *gridLayout_2;
    QLabel *label_icon;
    QLabel *label_aircraft_number;
    QLabel *label_2;
    QLabel *label_tailNumber;
    QLabel *label;
    QLabel *label_latitude;
    QLabel *label_3;
    QLabel *label_longitude;
    QLabel *label_5;
    QLabel *label_altitude;
    QLabel *label_4;
    QLabel *label_Speed;
    QLabel *label_7;
    QLabel *label_status;

    void setupUi(QWidget *AircraftInfoForm)
    {
        if (AircraftInfoForm->objectName().isEmpty())
            AircraftInfoForm->setObjectName(QStringLiteral("AircraftInfoForm"));
        AircraftInfoForm->resize(245, 188);
        AircraftInfoForm->setStyleSheet(QStringLiteral(""));
        gridLayout = new QGridLayout(AircraftInfoForm);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        frame = new QFrame(AircraftInfoForm);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setMinimumSize(QSize(260, 0));
        frame->setMaximumSize(QSize(260, 16777215));
        QFont font;
        font.setPointSize(8);
        frame->setFont(font);
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout_2 = new QGridLayout(frame);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        label_icon = new QLabel(frame);
        label_icon->setObjectName(QStringLiteral("label_icon"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Adobe \351\273\221\344\275\223 Std R"));
        font1.setPointSize(12);
        font1.setBold(true);
        font1.setWeight(75);
        label_icon->setFont(font1);

        gridLayout_2->addWidget(label_icon, 0, 0, 1, 1);

        label_aircraft_number = new QLabel(frame);
        label_aircraft_number->setObjectName(QStringLiteral("label_aircraft_number"));
        label_aircraft_number->setFont(font1);

        gridLayout_2->addWidget(label_aircraft_number, 0, 1, 1, 1);

        label_2 = new QLabel(frame);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setFont(font1);

        gridLayout_2->addWidget(label_2, 1, 0, 1, 1);

        label_tailNumber = new QLabel(frame);
        label_tailNumber->setObjectName(QStringLiteral("label_tailNumber"));
        label_tailNumber->setFont(font1);

        gridLayout_2->addWidget(label_tailNumber, 1, 1, 1, 1);

        label = new QLabel(frame);
        label->setObjectName(QStringLiteral("label"));
        label->setFont(font1);

        gridLayout_2->addWidget(label, 2, 0, 1, 1);

        label_latitude = new QLabel(frame);
        label_latitude->setObjectName(QStringLiteral("label_latitude"));
        label_latitude->setFont(font1);

        gridLayout_2->addWidget(label_latitude, 2, 1, 1, 1);

        label_3 = new QLabel(frame);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setFont(font1);

        gridLayout_2->addWidget(label_3, 3, 0, 1, 1);

        label_longitude = new QLabel(frame);
        label_longitude->setObjectName(QStringLiteral("label_longitude"));
        label_longitude->setFont(font1);

        gridLayout_2->addWidget(label_longitude, 3, 1, 1, 1);

        label_5 = new QLabel(frame);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setFont(font1);

        gridLayout_2->addWidget(label_5, 4, 0, 1, 1);

        label_altitude = new QLabel(frame);
        label_altitude->setObjectName(QStringLiteral("label_altitude"));
        label_altitude->setFont(font1);

        gridLayout_2->addWidget(label_altitude, 4, 1, 1, 1);

        label_4 = new QLabel(frame);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setFont(font1);

        gridLayout_2->addWidget(label_4, 5, 0, 1, 1);

        label_Speed = new QLabel(frame);
        label_Speed->setObjectName(QStringLiteral("label_Speed"));
        label_Speed->setFont(font1);

        gridLayout_2->addWidget(label_Speed, 5, 1, 1, 1);

        label_7 = new QLabel(frame);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setFont(font1);

        gridLayout_2->addWidget(label_7, 6, 0, 1, 1);

        label_status = new QLabel(frame);
        label_status->setObjectName(QStringLiteral("label_status"));
        label_status->setFont(font1);

        gridLayout_2->addWidget(label_status, 6, 1, 1, 1);


        gridLayout->addWidget(frame, 0, 0, 1, 1);


        retranslateUi(AircraftInfoForm);

        QMetaObject::connectSlotsByName(AircraftInfoForm);
    } // setupUi

    void retranslateUi(QWidget *AircraftInfoForm)
    {
        AircraftInfoForm->setWindowTitle(QApplication::translate("AircraftInfoForm", "Form", 0));
        label_icon->setText(QApplication::translate("AircraftInfoForm", "\350\210\252\347\217\255\350\257\206\345\210\253\345\217\267\357\274\232", 0));
        label_aircraft_number->setText(QString());
        label_2->setText(QApplication::translate("AircraftInfoForm", "\346\263\250\345\206\214\345\217\267\357\274\232", 0));
        label_tailNumber->setText(QString());
        label->setText(QApplication::translate("AircraftInfoForm", "\347\273\217\345\272\246\357\274\232", 0));
        label_latitude->setText(QString());
        label_3->setText(QApplication::translate("AircraftInfoForm", "\347\272\254\345\272\246\357\274\232", 0));
        label_longitude->setText(QString());
        label_5->setText(QApplication::translate("AircraftInfoForm", "\351\253\230\345\272\246\357\274\232", 0));
        label_altitude->setText(QString());
        label_4->setText(QApplication::translate("AircraftInfoForm", "\351\200\237\345\272\246\357\274\232", 0));
        label_Speed->setText(QString());
        label_7->setText(QApplication::translate("AircraftInfoForm", "\347\212\266\346\200\201\357\274\232", 0));
        label_status->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class AircraftInfoForm: public Ui_AircraftInfoForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AIRCRAFTINFOFORM_H
