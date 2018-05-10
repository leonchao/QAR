#ifndef WARNINGFORM_H
#define WARNINGFORM_H

#include <QWidget>
#include "structs.h"

namespace Ui {
class WarningForm;
}

class WarningForm : public QWidget
{
    Q_OBJECT

public:
    explicit WarningForm(QWidget *parent = 0);
    ~WarningForm();
    void showWarning(WarningInfo warning);
private:
    Ui::WarningForm *ui;
};

#endif // WARNINGFORM_H
