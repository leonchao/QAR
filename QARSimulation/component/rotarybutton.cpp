#include "rotarybutton.h"
#include <QQuickItem>

RotaryButton::RotaryButton(QWidget *parent)
    : PlaneComponent(parent)
{
     setSource(QUrl("qrc:/component/qml/RotaryButton.qml"));
}

RotaryButton::RotaryButton(QQmlEngine *engine, QWidget *parent)
    : PlaneComponent(engine, parent)
{
     setSource(QUrl("qrc:/component/qml/RotaryButton.qml"));
}

RotaryButton::RotaryButton(const QUrl &source, QWidget *parent)
    : PlaneComponent(source, parent)
{
    setSource(QUrl("qrc:/component/qml/RotaryButton.qml"));
}

void RotaryButton::setAngle(int angle)
{
    this->angle = angle;
    QQuickItem *root = rootObject();
    if (root) {
        rootObject()->setProperty("angle", angle);
    }
}

