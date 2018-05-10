#include "planecomponent.h"
#include <QQmlError>
#include <QDebug>

PlaneComponent::PlaneComponent(QWidget *parent)
    : QQuickWidget(parent)
{
    init();
}

PlaneComponent::PlaneComponent(QQmlEngine *engine, QWidget *parent)
    : QQuickWidget(engine, parent)
{
    init();
}

PlaneComponent::PlaneComponent(const QUrl &source, QWidget *parent)
    : QQuickWidget(source, parent)
{
    init();
}

void PlaneComponent::init()
{
    setClearColor(Qt::transparent);
    setAttribute(Qt::WA_AlwaysStackOnTop);
    setResizeMode(QQuickWidget::SizeRootObjectToView);
    connect(this, &PlaneComponent::statusChanged, [this](QQuickWidget::Status status){
        if (status == QQuickWidget::Error) {
            qDebug() << "load qml file failed:";
            for (auto &error: errors()) {
                qDebug() << error.toString();
            }
        }
    });
}
