#include "background.h"

BackGround::BackGround(QObject *parent, QString image, int k_w, int k_h, int ww, int hh , int k_speed) : QObject(parent)
{
    this->hh=hh;
    this->ww=ww;
    this->k_w=k_w;
    this->k_h=k_h;
    this->koef_speed=k_speed;
    spriteImage = new QPixmap(image); // Загружаем изображение спрайта в QPixmap

    // Подключаем сигнал от таймера к слоту перелистывания кадров спрайта
    connect(&timer, SIGNAL(timeout()), this, SLOT(next_Frame()));
    timer.start(100);   // Запускаем спрайт на генерацию сигнала
}

QRectF BackGround::boundingRect() const
{
    return QRectF(0,0,ww,hh);
}

void BackGround::next_Frame()
{
    this->speed=this->data(2).toInt();
    if(koef_speed>0)
    {
        i++;
        this->update();

        timer.start(10*koef_speed-(this->speed*koef_speed));
    }
    else
        timer.stop();
    if(speed>9)
        timer.start(1000);
}

void BackGround::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0,0, *spriteImage, k_w+i, k_h, ww, hh);
    painter->drawPixmap(0,0, *spriteImage, k_w-ww+i, k_h, ww, hh);
    if(i>ww)i=0;

    Q_UNUSED(option);
    Q_UNUSED(widget);
}
