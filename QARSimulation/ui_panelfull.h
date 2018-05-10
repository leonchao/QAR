/********************************************************************************
** Form generated from reading UI file 'panelfull.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PANELFULL_H
#define UI_PANELFULL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "QtQuickWidgets/QQuickWidget"
#include "oil.h"
#include "pedal.h"
#include "pushbutton.h"
#include "rocker.h"
#include "rotarybutton.h"

QT_BEGIN_NAMESPACE

class Ui_PanelFull
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *widgetNull;
    QLabel *label_time;
    QWidget *widgetPanel;
    QWidget *widgetPFD;
    QVBoxLayout *verticalLayout_PFD;
    QWidget *widgetND;
    QVBoxLayout *verticalLayout_ND;
    QWidget *widgetMFD;
    QVBoxLayout *verticalLayout_MFD;
    QWidget *widgetECAM;
    QVBoxLayout *verticalLayout_ECAM;
    PushButton *pushButtonLand;
    PushButton *pushButton_master_cau;
    PushButton *pushButton_master_warn;
    PushButton *pushButton_FD;
    PushButton *pushButton_LS;
    PushButton *pushButton_CSTR;
    PushButton *pushButton_WPT;
    PushButton *pushButton_VOR;
    PushButton *pushButton_NDB;
    PushButton *pushButton_ARPT;
    PushButton *pushButton_LOC;
    PushButton *pushButton_AP1;
    PushButton *pushButton_AP2;
    PushButton *pushButton_ATHR;
    PushButton *pushButton_APPR;
    PushButton *pushButton_GEAR;
    QLabel *label_BARO;
    QLabel *label_SPD;
    QLabel *label_HDG;
    QLabel *label_ALT;
    QLabel *label_VS;
    Pedal *quickWidget;
    Rocker *quickWidget_joystick;
    Oil *quickWidget_throttle;
    QToolButton *toolButton_gearleft;
    QToolButton *toolButton_gearmain;
    QToolButton *toolButton_gearright;
    RotaryButton *quickWidget_1;
    RotaryButton *quickWidget_2;
    QToolButton *toolButton_BRK_MED;
    QToolButton *toolButton_BRK_LO;
    QToolButton *toolButton_BRK_MAX;
    QToolButton *toolButton_TERR_ON_ND;

    void setupUi(QWidget *PanelFull)
    {
        if (PanelFull->objectName().isEmpty())
            PanelFull->setObjectName(QStringLiteral("PanelFull"));
        PanelFull->resize(2946, 1656);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(PanelFull->sizePolicy().hasHeightForWidth());
        PanelFull->setSizePolicy(sizePolicy);
        QFont font;
        font.setStyleStrategy(QFont::PreferDefault);
        PanelFull->setFont(font);
        verticalLayout = new QVBoxLayout(PanelFull);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        widgetNull = new QWidget(PanelFull);
        widgetNull->setObjectName(QStringLiteral("widgetNull"));
        label_time = new QLabel(widgetNull);
        label_time->setObjectName(QStringLiteral("label_time"));
        label_time->setGeometry(QRect(2810, 10, 130, 40));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_time->sizePolicy().hasHeightForWidth());
        label_time->setSizePolicy(sizePolicy1);
        label_time->setStyleSheet(QStringLiteral("color: rgb(0, 170, 0);"));
        label_time->raise();

        verticalLayout->addWidget(widgetNull);

        widgetPanel = new QWidget(PanelFull);
        widgetPanel->setObjectName(QStringLiteral("widgetPanel"));
        widgetPanel->setStyleSheet(QLatin1String("#widgetPanel{\n"
"	border-image: url(:/background.png);\n"
"}"));
        widgetPFD = new QWidget(widgetPanel);
        widgetPFD->setObjectName(QStringLiteral("widgetPFD"));
        widgetPFD->setGeometry(QRect(310, 379, 495, 492));
        verticalLayout_PFD = new QVBoxLayout(widgetPFD);
        verticalLayout_PFD->setSpacing(0);
        verticalLayout_PFD->setObjectName(QStringLiteral("verticalLayout_PFD"));
        verticalLayout_PFD->setContentsMargins(0, 0, 0, 0);
        widgetND = new QWidget(widgetPanel);
        widgetND->setObjectName(QStringLiteral("widgetND"));
        widgetND->setGeometry(QRect(840, 379, 495, 492));
        verticalLayout_ND = new QVBoxLayout(widgetND);
        verticalLayout_ND->setSpacing(0);
        verticalLayout_ND->setObjectName(QStringLiteral("verticalLayout_ND"));
        verticalLayout_ND->setContentsMargins(0, 0, 0, 0);
        widgetMFD = new QWidget(widgetPanel);
        widgetMFD->setObjectName(QStringLiteral("widgetMFD"));
        widgetMFD->setGeometry(QRect(1898, 379, 495, 492));
        verticalLayout_MFD = new QVBoxLayout(widgetMFD);
        verticalLayout_MFD->setSpacing(0);
        verticalLayout_MFD->setObjectName(QStringLiteral("verticalLayout_MFD"));
        verticalLayout_MFD->setContentsMargins(0, 0, 0, 0);
        widgetECAM = new QWidget(widgetPanel);
        widgetECAM->setObjectName(QStringLiteral("widgetECAM"));
        widgetECAM->setGeometry(QRect(1369, 379, 495, 492));
        verticalLayout_ECAM = new QVBoxLayout(widgetECAM);
        verticalLayout_ECAM->setSpacing(0);
        verticalLayout_ECAM->setObjectName(QStringLiteral("verticalLayout_ECAM"));
        verticalLayout_ECAM->setContentsMargins(0, 0, 0, 0);
        pushButtonLand = new PushButton(widgetPanel);
        pushButtonLand->setObjectName(QStringLiteral("pushButtonLand"));
        pushButtonLand->setGeometry(QRect(152, 210, 62, 63));
        pushButtonLand->setStyleSheet(QLatin1String("QPushButton\n"
"{    \n"
"    border:none;\n"
"	border-image: url(:/AUTO-LAND-off.png);\n"
"}\n"
"\n"
"QPushButton:checked\n"
"{\n"
"    border-image: url(:/AUTO-LAND-on.png);\n"
"}"));
        pushButtonLand->setCheckable(true);
        pushButtonLand->setChecked(false);
        pushButton_master_cau = new PushButton(widgetPanel);
        pushButton_master_cau->setObjectName(QStringLiteral("pushButton_master_cau"));
        pushButton_master_cau->setGeometry(QRect(596, 216, 62, 64));
        pushButton_master_cau->setStyleSheet(QLatin1String("QPushButton\n"
"{    \n"
"    border:none;\n"
"	border-image: url(:/MASTER-CAUT-off.png);\n"
"}\n"
"\n"
"QPushButton:checked\n"
"{\n"
"    border-image: url(:/MASTER-CAUT-on.png);\n"
"}"));
        pushButton_master_cau->setCheckable(true);
        pushButton_master_cau->setChecked(false);
        pushButton_master_warn = new PushButton(widgetPanel);
        pushButton_master_warn->setObjectName(QStringLiteral("pushButton_master_warn"));
        pushButton_master_warn->setGeometry(QRect(596, 125, 61, 65));
        pushButton_master_warn->setStyleSheet(QLatin1String("QPushButton\n"
"{    \n"
"    border:none;\n"
"	border-image: url(:/MASTER-WARN-off.png);\n"
"}\n"
"\n"
"QPushButton:checked\n"
"{\n"
"    border-image: url(:/MASTER-WARN-on.png);\n"
"}"));
        pushButton_master_warn->setCheckable(true);
        pushButton_master_warn->setChecked(false);
        pushButton_FD = new PushButton(widgetPanel);
        pushButton_FD->setObjectName(QStringLiteral("pushButton_FD"));
        pushButton_FD->setGeometry(QRect(1010, 254, 47, 33));
        pushButton_FD->setStyleSheet(QLatin1String("QPushButton\n"
"{    \n"
"    border:none;\n"
"	border-image: url(:/FD-off.png);\n"
"}\n"
"\n"
"QPushButton:checked\n"
"{\n"
"    border-image: url(:/FD-on.png);\n"
"}"));
        pushButton_FD->setCheckable(true);
        pushButton_FD->setChecked(false);
        pushButton_LS = new PushButton(widgetPanel);
        pushButton_LS->setObjectName(QStringLiteral("pushButton_LS"));
        pushButton_LS->setGeometry(QRect(1067, 253, 47, 33));
        pushButton_LS->setStyleSheet(QLatin1String("QPushButton\n"
"{    \n"
"    border:none;\n"
"	border-image: url(:/LS-off.png);\n"
"}\n"
"\n"
"QPushButton:checked\n"
"{\n"
"    border-image: url(:/LS-on.png);\n"
"}"));
        pushButton_LS->setCheckable(true);
        pushButton_LS->setChecked(false);
        pushButton_CSTR = new PushButton(widgetPanel);
        pushButton_CSTR->setObjectName(QStringLiteral("pushButton_CSTR"));
        pushButton_CSTR->setGeometry(QRect(1144, 64, 47, 34));
        pushButton_CSTR->setStyleSheet(QLatin1String("QPushButton\n"
"{    \n"
"    border:none;\n"
"	border-image: url(:/CSTR-off.png);\n"
"}\n"
"\n"
"QPushButton:checked\n"
"{\n"
"    border-image: url(:/CSTR-on.png);\n"
"}"));
        pushButton_CSTR->setCheckable(true);
        pushButton_WPT = new PushButton(widgetPanel);
        pushButton_WPT->setObjectName(QStringLiteral("pushButton_WPT"));
        pushButton_WPT->setGeometry(QRect(1195, 64, 47, 34));
        pushButton_WPT->setStyleSheet(QLatin1String("QPushButton\n"
"{    \n"
"    border:none;\n"
"	border-image: url(:/WPT-off.png);\n"
"}\n"
"\n"
"QPushButton:checked\n"
"{\n"
"    border-image: url(:/WPT-on.png);\n"
"}"));
        pushButton_WPT->setCheckable(true);
        pushButton_VOR = new PushButton(widgetPanel);
        pushButton_VOR->setObjectName(QStringLiteral("pushButton_VOR"));
        pushButton_VOR->setGeometry(QRect(1244, 64, 47, 34));
        pushButton_VOR->setStyleSheet(QLatin1String("QPushButton\n"
"{    \n"
"    border:none;\n"
"	border-image: url(:/VOR.D-off.png);\n"
"}\n"
"\n"
"QPushButton:checked\n"
"{\n"
"    border-image: url(:/VOR.D-on.png);\n"
"}"));
        pushButton_VOR->setCheckable(true);
        pushButton_NDB = new PushButton(widgetPanel);
        pushButton_NDB->setObjectName(QStringLiteral("pushButton_NDB"));
        pushButton_NDB->setGeometry(QRect(1294, 64, 47, 34));
        pushButton_NDB->setStyleSheet(QLatin1String("QPushButton\n"
"{    \n"
"    border:none;\n"
"	border-image: url(:/NDB-off.png);\n"
"}\n"
"\n"
"QPushButton:checked\n"
"{\n"
"    border-image: url(:/NDB-on.png);\n"
"}"));
        pushButton_NDB->setCheckable(true);
        pushButton_ARPT = new PushButton(widgetPanel);
        pushButton_ARPT->setObjectName(QStringLiteral("pushButton_ARPT"));
        pushButton_ARPT->setGeometry(QRect(1345, 64, 47, 34));
        pushButton_ARPT->setStyleSheet(QLatin1String("QPushButton\n"
"{    \n"
"    border:none;\n"
"	border-image: url(:/ARPT-off.png);\n"
"}\n"
"\n"
"QPushButton:checked\n"
"{\n"
"    border-image: url(:/ARPT-on.png);\n"
"}"));
        pushButton_ARPT->setCheckable(true);
        pushButton_LOC = new PushButton(widgetPanel);
        pushButton_LOC->setObjectName(QStringLiteral("pushButton_LOC"));
        pushButton_LOC->setGeometry(QRect(1619, 237, 65, 46));
        pushButton_LOC->setStyleSheet(QLatin1String("QPushButton\n"
"{    \n"
"    border:none;\n"
"	border-image: url(:/LOC-off.png);\n"
"}\n"
"\n"
"QPushButton:checked\n"
"{\n"
"    border-image: url(:/LOC-on.png);\n"
"}"));
        pushButton_LOC->setCheckable(true);
        pushButton_AP1 = new PushButton(widgetPanel);
        pushButton_AP1->setObjectName(QStringLiteral("pushButton_AP1"));
        pushButton_AP1->setGeometry(QRect(1726, 163, 53, 55));
        pushButton_AP1->setStyleSheet(QLatin1String("QPushButton\n"
"{    \n"
"    border:none;\n"
"	border-image: url(:/AP-1-off.png);\n"
"}\n"
"\n"
"QPushButton:checked\n"
"{\n"
"    border-image: url(:/AP-1-on.png);\n"
"}"));
        pushButton_AP1->setCheckable(true);
        pushButton_AP2 = new PushButton(widgetPanel);
        pushButton_AP2->setObjectName(QStringLiteral("pushButton_AP2"));
        pushButton_AP2->setGeometry(QRect(1789, 163, 53, 55));
        pushButton_AP2->setStyleSheet(QLatin1String("QPushButton\n"
"{    \n"
"    border:none;\n"
"	border-image: url(:/AP-2-off.png);\n"
"}\n"
"\n"
"QPushButton:checked\n"
"{\n"
"    border-image: url(:/AP-2-on.png);\n"
"}"));
        pushButton_AP2->setCheckable(true);
        pushButton_ATHR = new PushButton(widgetPanel);
        pushButton_ATHR->setObjectName(QStringLiteral("pushButton_ATHR"));
        pushButton_ATHR->setGeometry(QRect(1756, 224, 53, 56));
        pushButton_ATHR->setStyleSheet(QLatin1String("QPushButton\n"
"{    \n"
"    border:none;\n"
"	border-image: url(:/A-THR-off.png);\n"
"}\n"
"\n"
"QPushButton:checked\n"
"{\n"
"    border-image: url(:/A-THR-on.png);\n"
"}"));
        pushButton_ATHR->setCheckable(true);
        pushButton_APPR = new PushButton(widgetPanel);
        pushButton_APPR->setObjectName(QStringLiteral("pushButton_APPR"));
        pushButton_APPR->setGeometry(QRect(2050, 235, 69, 47));
        pushButton_APPR->setStyleSheet(QLatin1String("QPushButton\n"
"{    \n"
"    border:none;\n"
"	border-image: url(:/APPR-off.png);\n"
"}\n"
"\n"
"QPushButton:checked\n"
"{\n"
"    border-image: url(:/APPR-on.png);\n"
"}"));
        pushButton_APPR->setCheckable(true);
        pushButton_GEAR = new PushButton(widgetPanel);
        pushButton_GEAR->setObjectName(QStringLiteral("pushButton_GEAR"));
        pushButton_GEAR->setGeometry(QRect(2624, 64, 132, 231));
        pushButton_GEAR->setStyleSheet(QLatin1String("QPushButton\n"
"{    \n"
"    border:none;\n"
"	border-image: url(:/gearDown.png);\n"
"}\n"
"\n"
"QPushButton:checked\n"
"{\n"
"    border-image: url(:/gearUp.png);\n"
"}"));
        pushButton_GEAR->setCheckable(true);
        pushButton_GEAR->setChecked(false);
        label_BARO = new QLabel(widgetPanel);
        label_BARO->setObjectName(QStringLiteral("label_BARO"));
        label_BARO->setGeometry(QRect(1030, 114, 68, 21));
        QFont font1;
        font1.setPointSize(5);
        font1.setBold(true);
        font1.setWeight(75);
        label_BARO->setFont(font1);
        label_BARO->setStyleSheet(QStringLiteral("color: rgb(255, 255, 127);"));
        label_BARO->setAlignment(Qt::AlignCenter);
        label_SPD = new QLabel(widgetPanel);
        label_SPD->setObjectName(QStringLiteral("label_SPD"));
        label_SPD->setGeometry(QRect(1480, 70, 58, 24));
        label_SPD->setFont(font1);
        label_SPD->setStyleSheet(QStringLiteral("color: rgb(255, 175, 37);"));
        label_SPD->setAlignment(Qt::AlignCenter);
        label_HDG = new QLabel(widgetPanel);
        label_HDG->setObjectName(QStringLiteral("label_HDG"));
        label_HDG->setGeometry(QRect(1587, 69, 90, 25));
        label_HDG->setFont(font1);
        label_HDG->setStyleSheet(QStringLiteral("color: rgb(255, 175, 37);"));
        label_HDG->setAlignment(Qt::AlignCenter);
        label_ALT = new QLabel(widgetPanel);
        label_ALT->setObjectName(QStringLiteral("label_ALT"));
        label_ALT->setGeometry(QRect(1874, 71, 91, 26));
        QFont font2;
        font2.setFamily(QStringLiteral("Arial"));
        font2.setPointSize(5);
        font2.setBold(true);
        font2.setWeight(75);
        label_ALT->setFont(font2);
        label_ALT->setStyleSheet(QStringLiteral("color: rgb(255, 175, 37);"));
        label_ALT->setAlignment(Qt::AlignCenter);
        label_VS = new QLabel(widgetPanel);
        label_VS->setObjectName(QStringLiteral("label_VS"));
        label_VS->setGeometry(QRect(2047, 69, 85, 28));
        label_VS->setFont(font1);
        label_VS->setStyleSheet(QStringLiteral("color: rgb(255, 175, 37);"));
        label_VS->setAlignment(Qt::AlignCenter);
        quickWidget = new Pedal(widgetPanel);
        quickWidget->setObjectName(QStringLiteral("quickWidget"));
        quickWidget->setGeometry(QRect(16, 598, 269, 331));
        quickWidget->setStyleSheet(QStringLiteral(""));
        quickWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);
        quickWidget_joystick = new Rocker(widgetPanel);
        quickWidget_joystick->setObjectName(QStringLiteral("quickWidget_joystick"));
        quickWidget_joystick->setGeometry(QRect(50, 397, 204, 197));
        quickWidget_joystick->setResizeMode(QQuickWidget::SizeRootObjectToView);
        quickWidget_throttle = new Oil(widgetPanel);
        quickWidget_throttle->setObjectName(QStringLiteral("quickWidget_throttle"));
        quickWidget_throttle->setGeometry(QRect(2407, 373, 516, 580));
        quickWidget_throttle->setResizeMode(QQuickWidget::SizeRootObjectToView);
        toolButton_gearleft = new QToolButton(widgetPanel);
        toolButton_gearleft->setObjectName(QStringLiteral("toolButton_gearleft"));
        toolButton_gearleft->setGeometry(QRect(2226, 74, 59, 58));
        toolButton_gearleft->setStyleSheet(QLatin1String("QToolButton\n"
"{    \n"
"    border:none;\n"
"	border-image: url(:/LDG-3.png);\n"
"}\n"
"\n"
"QToolButton:checked\n"
"{\n"
"    border-image: url(:/LDG-4.png);\n"
"}"));
        toolButton_gearleft->setCheckable(true);
        toolButton_gearleft->setChecked(false);
        toolButton_gearmain = new QToolButton(widgetPanel);
        toolButton_gearmain->setObjectName(QStringLiteral("toolButton_gearmain"));
        toolButton_gearmain->setGeometry(QRect(2285, 74, 57, 57));
        toolButton_gearmain->setStyleSheet(QLatin1String("QToolButton\n"
"{    \n"
"    border:none;\n"
"	border-image: url(:/LDG-3.png);\n"
"}\n"
"\n"
"QToolButton:checked\n"
"{\n"
"    border-image: url(:/LDG-4.png);\n"
"}"));
        toolButton_gearmain->setCheckable(true);
        toolButton_gearmain->setChecked(false);
        toolButton_gearright = new QToolButton(widgetPanel);
        toolButton_gearright->setObjectName(QStringLiteral("toolButton_gearright"));
        toolButton_gearright->setGeometry(QRect(2343, 74, 58, 57));
        toolButton_gearright->setStyleSheet(QLatin1String("QToolButton\n"
"{    \n"
"    border:none;\n"
"	border-image: url(:/LDG-3.png);\n"
"}\n"
"\n"
"QToolButton:checked\n"
"{\n"
"    border-image: url(:/LDG-4.png);\n"
"}"));
        toolButton_gearright->setCheckable(true);
        toolButton_gearright->setChecked(false);
        quickWidget_1 = new RotaryButton(widgetPanel);
        quickWidget_1->setObjectName(QStringLiteral("quickWidget_1"));
        quickWidget_1->setGeometry(QRect(1169, 147, 68, 68));
        quickWidget_1->setResizeMode(QQuickWidget::SizeRootObjectToView);
        quickWidget_2 = new RotaryButton(widgetPanel);
        quickWidget_2->setObjectName(QStringLiteral("quickWidget_2"));
        quickWidget_2->setGeometry(QRect(1311, 147, 68, 68));
        quickWidget_2->setResizeMode(QQuickWidget::SizeRootObjectToView);
        toolButton_BRK_MED = new QToolButton(widgetPanel);
        toolButton_BRK_MED->setObjectName(QStringLiteral("toolButton_BRK_MED"));
        toolButton_BRK_MED->setGeometry(QRect(2278, 196, 58, 55));
        toolButton_BRK_MED->setStyleSheet(QLatin1String("QToolButton\n"
"{    \n"
"    border:none;\n"
"	border-image: url(:/AUTO-BRK-2.png);\n"
"}\n"
"\n"
"QToolButton:checked\n"
"{\n"
"    border-image: url(:/AUTO-BRK-1.png);\n"
"}"));
        toolButton_BRK_MED->setCheckable(true);
        toolButton_BRK_MED->setChecked(false);
        toolButton_BRK_LO = new QToolButton(widgetPanel);
        toolButton_BRK_LO->setObjectName(QStringLiteral("toolButton_BRK_LO"));
        toolButton_BRK_LO->setGeometry(QRect(2218, 196, 57, 55));
        toolButton_BRK_LO->setStyleSheet(QLatin1String("QToolButton\n"
"{    \n"
"    border:none;\n"
"	border-image: url(:/AUTO-BRK-2.png);\n"
"}\n"
"\n"
"QToolButton:checked\n"
"{\n"
"    border-image: url(:/AUTO-BRK-1.png);\n"
"}"));
        toolButton_BRK_LO->setCheckable(true);
        toolButton_BRK_LO->setChecked(false);
        toolButton_BRK_MAX = new QToolButton(widgetPanel);
        toolButton_BRK_MAX->setObjectName(QStringLiteral("toolButton_BRK_MAX"));
        toolButton_BRK_MAX->setGeometry(QRect(2353, 196, 57, 56));
        toolButton_BRK_MAX->setStyleSheet(QLatin1String("QToolButton\n"
"{    \n"
"    border:none;\n"
"	border-image: url(:/AUTO-BRK-2.png);\n"
"}\n"
"\n"
"QToolButton:checked\n"
"{\n"
"    border-image: url(:/AUTO-BRK-1.png);\n"
"}"));
        toolButton_BRK_MAX->setCheckable(true);
        toolButton_BRK_MAX->setChecked(false);
        toolButton_TERR_ON_ND = new QToolButton(widgetPanel);
        toolButton_TERR_ON_ND->setObjectName(QStringLiteral("toolButton_TERR_ON_ND"));
        toolButton_TERR_ON_ND->setGeometry(QRect(2540, 138, 56, 54));
        toolButton_TERR_ON_ND->setStyleSheet(QLatin1String("QToolButton\n"
"{    \n"
"    border:none;\n"
"	border-image: url(:/TREE-ON-ND-2.png);\n"
"}\n"
"\n"
"QToolButton:checked\n"
"{\n"
"    border-image: url(:/TREE-ON-ND-1.png);\n"
"}"));
        toolButton_TERR_ON_ND->setCheckable(true);
        toolButton_TERR_ON_ND->setChecked(false);

        verticalLayout->addWidget(widgetPanel);

        verticalLayout->setStretch(0, 446);
        verticalLayout->setStretch(1, 634);

        retranslateUi(PanelFull);

        QMetaObject::connectSlotsByName(PanelFull);
    } // setupUi

    void retranslateUi(QWidget *PanelFull)
    {
        PanelFull->setWindowTitle(QApplication::translate("PanelFull", "Form", 0));
        label_time->setText(QString());
        pushButtonLand->setText(QString());
        pushButton_master_cau->setText(QString());
        pushButton_master_warn->setText(QString());
        pushButton_FD->setText(QString());
        pushButton_LS->setText(QString());
        pushButton_CSTR->setText(QString());
        pushButton_WPT->setText(QString());
        pushButton_VOR->setText(QString());
        pushButton_NDB->setText(QString());
        pushButton_ARPT->setText(QString());
        pushButton_LOC->setText(QString());
        pushButton_AP1->setText(QString());
        pushButton_AP2->setText(QString());
        pushButton_ATHR->setText(QString());
        pushButton_APPR->setText(QString());
        pushButton_GEAR->setText(QString());
        label_BARO->setText(QApplication::translate("PanelFull", "1013", 0));
        label_SPD->setText(QString());
        label_HDG->setText(QString());
        label_ALT->setText(QString());
        label_VS->setText(QString());
        toolButton_gearleft->setText(QString());
        toolButton_gearmain->setText(QString());
        toolButton_gearright->setText(QString());
        toolButton_BRK_MED->setText(QString());
        toolButton_BRK_LO->setText(QString());
        toolButton_BRK_MAX->setText(QString());
        toolButton_TERR_ON_ND->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class PanelFull: public Ui_PanelFull {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PANELFULL_H
