#include "coin.h"

Coin::Coin(QObject *parent) :  QObject(parent)
{
    spriteImage = new QPixmap(":/new/coin.png"); // Загружаем изображение спрайта в QPixmap
    // Подключаем сигнал от таймера к слоту перелистывания кадров спрайта
    connect(&timer_f,SIGNAL(timeout()), this, SLOT(next_Frame()));
    timer_f.start(150);   // Запускаем спрайт на генерацию сигнала

    connect(&timer_s,SIGNAL(timeout()), this, SLOT(step_Frame()));
    timer_s.start(200);   // Запускаем спрайт на генерацию сигнала

    int nap=random()%4;
    this->setPos(800,320+(48*nap));

    this->setData(0,"COIN");
    this->setData(1,true);
}

QRectF Coin::boundingRect() const
{
    return QRectF(0,0,48,48);
}

void Coin::next_Frame()
{
    if(i<5)
    i++;
    else
    i=0;
}

void Coin::step_Frame()
{
    this->speed=this->data(2).toInt();

    this->setPos(this->pos().x()-1,this->pos().y());

    if(this->pos().x()<-91 || this->data(1).toBool()==false)this->deleteLater();

    timer_s.start(10*1-(this->speed*1));
}

void Coin::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{   
    if(i==0)painter->drawPixmap(0,0, *spriteImage, 1, 2, 48, 48);
    if(i==1)painter->drawPixmap(0,0, *spriteImage, 56, 2, 48, 48);
    if(i==2)painter->drawPixmap(0,0, *spriteImage, 102, 3, 45, 48);
    if(i==3)painter->drawPixmap(0,0, *spriteImage, 5, 57, 45, 48);
    if(i==4)painter->drawPixmap(0,0, *spriteImage, 46, 57, 45, 48);
    if(i==5)painter->drawPixmap(0,0, *spriteImage, 99, 58, 45, 48);

    Q_UNUSED(option);
    Q_UNUSED(widget);
}
