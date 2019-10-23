#ifndef TRAFFIC_CAR_H
#define TRAFFIC_CAR_H

#include <QObject>
#include <QGraphicsItem>
#include <QTimer>
#include <QPixmap>
#include <QPainter>
#include <QDebug>

class Traffic_Car : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Traffic_Car(QObject *parent = nullptr,int tipe=0, int k_speed=0);

private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
    QTimer timer;          // Таймер для пролистывания изображения в QPixmap
    QPixmap *spriteImage;   // В данный объект QPixamp будет помещён спрайт
    int nap=0,tipe=0,ww=91,hh=55;
    int speed=0;
    int koef_speed=0;
    int i=0;

public slots:
    void set_Nap(int nap);
    void set_Tipe(int tipe);

private slots:
    void next_Frame();
};

#endif // TRAFFIC_CAR_H
