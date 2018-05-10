#ifndef PLANECOMPONENT_H
#define PLANECOMPONENT_H

#include <QQuickWidget>

class PlaneComponent : public QQuickWidget
{
public:
    explicit PlaneComponent(QWidget *parent = Q_NULLPTR);
    PlaneComponent(QQmlEngine* engine, QWidget *parent);
    explicit PlaneComponent(const QUrl &source, QWidget *parent = Q_NULLPTR);

private:
    virtual void init();
};

#endif // PLANECOMPONENT_H
