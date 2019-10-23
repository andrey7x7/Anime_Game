#include "car.h"

Car::Car(QObject *parent, int nap) :  QObject(parent)
{
    spriteImage = new QPixmap(":/new/jeep.png"); // Загружаем изображение спрайта в QPixmap
    this->nap=nap;
    // Подключаем сигнал от таймера к слоту перелистывания кадров спрайта
    connect(&timer, SIGNAL(timeout()), this, SLOT(next_Frame()));
    timer.start(10);   // Запускаем таймер на генерацию сигнала
    this->setData(0,"CAR");
    connect(parent,SIGNAL(fire(bool)),this,SLOT(set_Fire(bool)));
}

QRectF Car::boundingRect() const
{
    return QRectF(0,0,ww,hh);
}

void Car::set_Nap(int nap)
{
    this->nap=nap;
}

void Car::set_Fire(bool fire)
{
    this->fire=fire;
}


void Car::next_Frame()
{


    if(this->pos().y()>445)
        this->setPos(this->pos().x(),440);
    else
    {
        if(this->pos().y()<290)
        {
            this->setPos(this->pos().x(),295);
            this->update();
        }
        else
        {
        if(this->pos().y()<445 && this->pos().y()>290)
            this->setPos(this->pos().x(),this->pos().y()+nap);
        else
            this->setPos(this->pos().x(),this->pos().y()-nap);
        }
    }
}

void Car::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(nap==0){ww=127;hh=76;painter->drawPixmap(0,0, *spriteImage, 2, 11, 127, 76);}
    if(nap==1){ww=128;hh=91;painter->drawPixmap(0,0, *spriteImage, 130, 6, 128, 91);}
    if(nap==-1){ww=128;hh=91;painter->drawPixmap(0,0, *spriteImage, 264, 2, 128, 91);}

    //painter->setBrush(Qt::red);
    //if(fire)painter->drawEllipse(91,24,17,9);

    Q_UNUSED(option);
    Q_UNUSED(widget);
}
