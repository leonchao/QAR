#ifndef ROCKER_H
#define ROCKER_H

#include "planecomponent.h"

class Rocker : public PlaneComponent
{
    Q_OBJECT
public:

    explicit Rocker(QWidget *parent = Q_NULLPTR);
    Rocker(QQmlEngine* engine, QWidget *parent);
    explicit Rocker(const QUrl &source, QWidget *parent = Q_NULLPTR);

    enum Direction { LEFT, LEFTUP, UP, RIGHTUP, RIGHT, RIGHTDOWNM, DOWN, LEFTDOWN, NORMAL };
    Q_ENUM(Direction)
    void setDirection(Direction);
};

#endif // ROCKER_H
