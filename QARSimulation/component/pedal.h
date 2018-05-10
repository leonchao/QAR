#ifndef PEDAL_H
#define PEDAL_H

#include "planecomponent.h"

class Pedal : public PlaneComponent
{
public:
    explicit Pedal(QWidget *parent = Q_NULLPTR);
    Pedal(QQmlEngine* engine, QWidget *parent);
    explicit Pedal(const QUrl &source, QWidget *parent = Q_NULLPTR);

    enum Direction { LEFT, RIGHT, NORMAL };
    Q_ENUM(Direction)
    void tread(int , Direction = Pedal::LEFT);
};

#endif // PEDAL_H
