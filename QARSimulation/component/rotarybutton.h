#ifndef ROTARYBUTTON_H
#define ROTARYBUTTON_H

#include "planecomponent.h"

class RotaryButton : public PlaneComponent
{
public:
    explicit RotaryButton(QWidget *parent = Q_NULLPTR);
    RotaryButton(QQmlEngine* engine, QWidget *parent);
    explicit RotaryButton(const QUrl &source, QWidget *parent = Q_NULLPTR);
    int angle = 0;
    void setAngle(int angle);
};

#endif // ROTARYBUTTON_H
