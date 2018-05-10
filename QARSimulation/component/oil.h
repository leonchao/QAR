#ifndef OIL_H
#define OIL_H

#include "planecomponent.h"
class Oil : public PlaneComponent
{
public:
    explicit Oil(QWidget *parent = Q_NULLPTR);
    Oil(QQmlEngine* engine, QWidget *parent);
    explicit Oil(const QUrl &source, QWidget *parent = Q_NULLPTR);
    enum Direction { LEFT, RIGHT };
    Q_ENUM(Direction)
    void setValue(int value, Direction = LEFT);
};

#endif // OIL_H
