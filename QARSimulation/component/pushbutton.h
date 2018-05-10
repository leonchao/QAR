#ifndef PUSHBUTTON_H
#define PUSHBUTTON_H

#include <QPushButton>
class QLabel;
class QPropertyAnimation;
class PushButton : public QPushButton
{
public:
    explicit PushButton(QWidget *parent = Q_NULLPTR);
    explicit PushButton(const QString &text, QWidget *parent = Q_NULLPTR);
    PushButton(const QIcon& icon, const QString &text, QWidget *parent = Q_NULLPTR);

    void setTipImage(const QPixmap &);

private:
    void init();
    QPixmap scaleImage(int w);
private:
    QLabel *tipLabel;
    QPropertyAnimation *animation;
    QPixmap _pix;
};

#endif // PUSHBUTTON_H
