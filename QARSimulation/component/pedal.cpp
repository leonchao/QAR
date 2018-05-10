#include "pedal.h"

#include <QQuickItem>

Pedal::Pedal(QWidget *parent)
    : PlaneComponent(parent)
{
     setSource(QUrl("qrc:/component/qml/Pedal.qml"));
}

Pedal::Pedal(QQmlEngine *engine, QWidget *parent)
    : PlaneComponent(engine, parent)
{
     setSource(QUrl("qrc:/component/qml/Pedal.qml"));
}

Pedal::Pedal(const QUrl &source, QWidget *parent)
    : PlaneComponent(source, parent)
{
    setSource(QUrl("qrc:/component/qml/Pedal.qml"));
}

void Pedal::tread(int value, Pedal::Direction d)
{
    QQuickItem *root = rootObject();
    if (root) {
        rootObject()->setProperty("direction", d);
        rootObject()->setProperty("sliderValue", value);
    }
}
