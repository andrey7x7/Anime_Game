#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <QObject>
#include <QGraphicsItem>
#include <QTimer>
#include <QPixmap>
#include <QPainter>
#include <QDebug>

class BackGround : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit BackGround(QObject *parent = nullptr, QString image="", int k_w=0, int k_h=0, int ww=0, int hh=0, int k_speed=0);

private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
    QTimer timer;          // Таймер для пролистывания изображения в QPixmap
    QPixmap *spriteImage;   // В данный объект QPixamp будет помещён спрайт
    int nap=0;
    int speed=0;
    int koef_speed=0;
    int i=0;

    int hh;
    int ww;
    int k_w;
    int k_h;

private slots:
    void next_Frame();
};

#endif // BACKGROUND_H
