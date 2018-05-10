#ifndef NEEDLE_H
#define NEEDLE_H

#include "planecomponent.h"

class Needle : public PlaneComponent
{
public:
    explicit Needle(QWidget *parent = Q_NULLPTR);
    Needle(QQmlEngine* engine, QWidget *parent);
    explicit Needle(const QUrl &source, QWidget *parent = Q_NULLPTR);

    enum State { LEFT, MID, RIGHT};
    Q_ENUM(State)
    void setState(State);
};

#endif // NEEDLE_H
