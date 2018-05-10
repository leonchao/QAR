/********************************************************************************
** Form generated from reading UI file 'warningform.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WARNINGFORM_H
#define UI_WARNINGFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WarningForm
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;

    void setupUi(QWidget *WarningForm)
    {
        if (WarningForm->objectName().isEmpty())
            WarningForm->setObjectName(QStringLiteral("WarningForm"));
        WarningForm->resize(325, 115);
        verticalLayout = new QVBoxLayout(WarningForm);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(WarningForm);
        label->setObjectName(QStringLiteral("label"));
        QFont font;
        font.setPointSize(38);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        label->setStyleSheet(QStringLiteral("color: rgb(170, 0, 0);"));
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);


        retranslateUi(WarningForm);

        QMetaObject::connectSlotsByName(WarningForm);
    } // setupUi

    void retranslateUi(QWidget *WarningForm)
    {
        WarningForm->setWindowTitle(QApplication::translate("WarningForm", "Form", 0));
        label->setText(QApplication::translate("WarningForm", "\350\255\246\345\221\212\344\277\241\346\201\257", 0));
    } // retranslateUi

};

namespace Ui {
    class WarningForm: public Ui_WarningForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WARNINGFORM_H
