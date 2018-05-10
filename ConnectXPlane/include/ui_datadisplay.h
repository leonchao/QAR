/********************************************************************************
** Form generated from reading UI file 'datadisplay.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DATADISPLAY_H
#define UI_DATADISPLAY_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DataDisplay
{
public:
    QGridLayout *gridLayout;
    QTableView *tableView;

    void setupUi(QWidget *DataDisplay)
    {
        if (DataDisplay->objectName().isEmpty())
            DataDisplay->setObjectName(QStringLiteral("DataDisplay"));
        DataDisplay->resize(726, 524);
        gridLayout = new QGridLayout(DataDisplay);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        tableView = new QTableView(DataDisplay);
        tableView->setObjectName(QStringLiteral("tableView"));

        gridLayout->addWidget(tableView, 0, 0, 1, 1);


        retranslateUi(DataDisplay);

        QMetaObject::connectSlotsByName(DataDisplay);
    } // setupUi

    void retranslateUi(QWidget *DataDisplay)
    {
        DataDisplay->setWindowTitle(QApplication::translate("DataDisplay", "DataDisplay", 0));
    } // retranslateUi

};

namespace Ui {
    class DataDisplay: public Ui_DataDisplay {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DATADISPLAY_H
