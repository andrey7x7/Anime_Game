#ifndef CAR_H
#define CAR_H
#include <QObject>
#include <QGraphicsItem>
#include <QTimer>
#include <QPixmap>
#include <QPainter>
#include <QDebug>

class Car : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Car(QObject *parent = nullptr,int nap=0);

private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
    QTimer timer;          // Таймер для пролистывания изображения в QPixmap
    QPixmap *spriteImage;   // В данный объект QPixamp будет помещён спрайт
    int nap=0,ww=128,hh=91;
    int speed=0;
    int i=0;
    bool fire;


public slots:
    void set_Nap(int nap);
    int type(){return 77;};
    void set_Fire(bool fire);

private slots:
    void next_Frame();
};

#endif // CAR_H
