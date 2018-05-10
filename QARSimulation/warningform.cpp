#include "warningform.h"
#include "ui_warningform.h"

WarningForm::WarningForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WarningForm)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_TransparentForMouseEvents);
}

WarningForm::~WarningForm()
{
    delete ui;
}

void WarningForm::showWarning(WarningInfo warning)
{
    switch (warning.warningKind) {
    case 0:
        this->setVisible(false);
        break;
    case 1:
    {
        this->setVisible(true);
        if(warning.warningLevel = 1)
        {
            ui->label->setText(QString("横滚角大"));
            ui->label->setStyleSheet("color:yellow");
        }
        else
        {
            ui->label->setText(QString("横滚角大"));
            ui->label->setStyleSheet("color:red");
        }
        break;
    }
    default:
        break;
    }
}
