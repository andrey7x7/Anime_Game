#ifndef COIN_H
#define COIN_H
#include <QObject>
#include <QGraphicsItem>
#include <QTimer>
#include <QPixmap>
#include <QPainter>
#include <QDebug>

class Coin : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Coin (QObject *parent = nullptr);

private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
    QTimer timer_s;          // Таймер для пролистывания изображения в QPixmap
    QTimer timer_f;
    QPixmap *spriteImage;   // В данный объект QPixamp будет помещён спрайт
    int i=0;
    int speed=1;

private slots:
    void next_Frame();
    void step_Frame();
};

#endif // COIN_H
