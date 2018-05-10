#include "pushbutton.h"

#include <QLabel>
#include <QPixmap>
#include <QResizeEvent>
#include <QPropertyAnimation>

PushButton::PushButton(QWidget *parent)
    : QPushButton(parent)
{
    init();
}

PushButton::PushButton(const QString &text, QWidget *parent)
    : QPushButton(text, parent)
{
    init();
}

PushButton::PushButton(const QIcon &icon, const QString &text, QWidget *parent)
    : QPushButton(icon, text, parent)
{
    init();
}

void PushButton::setTipImage(const QPixmap &pix)
{
    if (pix.isNull()) return;
    _pix = pix;
//    tipLabel->setPixmap(scaleImage(qMin(tipLabel->width(), tipLabel->height())));
    tipLabel->setPixmap(_pix);
}

void PushButton::init()
{
    setCheckable(true);
    tipLabel = new QLabel(this, Qt::Tool | Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);
    tipLabel->setFixedSize(256, 256);
    tipLabel->setAttribute(Qt::WA_TranslucentBackground);
    setTipImage(QPixmap(":/component/images/Push.png"));
    tipLabel->setAlignment(Qt::AlignCenter);
    animation = new QPropertyAnimation(tipLabel, "pos", this);
    animation->setDuration(500);
    animation->setLoopCount(3);
    connect(animation, &QPropertyAnimation::finished, [=](){
        tipLabel->hide();
    });
    connect(this, &PushButton::toggled, [=](bool) {
        if (tipLabel->pixmap()->isNull()) return;
        QSize size = this->size();
        int w = size.width();
        int h = size.height();
        QWidget *widget = qobject_cast<QWidget *>(parent());
        QPoint pt = widget->mapToGlobal(pos());
        int x = pt.x() + (w - 256) / 2;
        int y = pt.y() + (h - 256) / 2;
        tipLabel->show();
        tipLabel->move(x, y);
        if (animation != nullptr) {
            animation->setKeyValueAt(0, QPoint(x, y));
            animation->setKeyValueAt(0.5, QPoint(x, y - 10));
            animation->setKeyValueAt(1, QPoint(x, y));
        }
        animation->start();
    });
}

QPixmap PushButton::scaleImage(int w)
{
    QPixmap t;
    if (!_pix.isNull()) {
        t = _pix.scaled(w, w, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    }
    return t;
}
