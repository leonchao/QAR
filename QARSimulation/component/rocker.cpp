#include "rocker.h"
#include <QQuickItem>

Rocker::Rocker(QWidget *parent)
    : PlaneComponent(parent)
{
     setSource(QUrl("qrc:/component/qml/Rocker.qml"));
}

Rocker::Rocker(QQmlEngine *engine, QWidget *parent)
    : PlaneComponent(engine, parent)
{
     setSource(QUrl("qrc:/component/qml/Rocker.qml"));
}


Rocker::Rocker(const QUrl &source, QWidget *parent)
    : PlaneComponent(source, parent)
{
    setSource(QUrl("qrc:/component/qml/Rocker.qml"));
}

void Rocker::setDirection(Rocker::Direction d)
{
    QQuickItem *root = rootObject();
    if (root) {
        rootObject()->setProperty("index", d);
    }
}
