#include "needle.h"

#include <QQuickItem>

Needle::Needle(QWidget *parent)
    : PlaneComponent(parent)
{
     setSource(QUrl("qrc:/component/qml/Needle.qml"));
}

Needle::Needle(QQmlEngine *engine, QWidget *parent)
    : PlaneComponent(engine, parent)
{
     setSource(QUrl("qrc:/component/qml/Needle.qml"));
}

Needle::Needle(const QUrl &source, QWidget *parent)
    : PlaneComponent(source, parent)
{
    setSource(QUrl("qrc:/component/qml/Needle.qml"));
}

void Needle::setState(State s)
{
    QQuickItem *root = rootObject();
    if (root) {
        rootObject()->setProperty("needleState", s);
    }
}

