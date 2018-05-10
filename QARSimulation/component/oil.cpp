#include "oil.h"

#include <QQuickItem>
#include <QDebug>

Oil::Oil(QWidget *parent)
    : PlaneComponent(parent)
{
     setSource(QUrl("qrc:/component/qml/Oil.qml"));
}

Oil::Oil(QQmlEngine *engine, QWidget *parent)
    : PlaneComponent(engine, parent)
{
     setSource(QUrl("qrc:/component/qml/Oil.qml"));
}

Oil::Oil(const QUrl &source, QWidget *parent)
    : PlaneComponent(source, parent)
{
    setSource(QUrl("qrc:/component/qml/Oil.qml"));
}

void Oil::setValue(int value, Oil::Direction d)
{
    if (value < -20 || value > 45) {
        qDebug() << "out of range!";
        return;
    }
    QQuickItem *root = rootObject();
    if (root) {
        rootObject()->setProperty(d == Oil::LEFT ? "leftValue" : "rightValue", value);
    }
}
