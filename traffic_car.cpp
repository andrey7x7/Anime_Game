#include "traffic_car.h"

Traffic_Car::Traffic_Car(QObject *parent, int tipe, int k_speed) :  QObject(parent)
{
    spriteImage = new QPixmap(":/new/traffic_car.png"); // Загружаем изображение спрайта в QPixmap
    this->setData(1,tipe);
    this->nap=random()%4;
    this->setPos(800,310+(48*nap));
    this->koef_speed=k_speed;
    // Подключаем сигнал от таймера к слоту перелистывания кадров спрайта
    connect(&timer, SIGNAL(timeout()), this, SLOT(next_Frame()));
    timer.start(10);   // Запускаем таймер на генерацию сигнала
    this->setData(0,"TRAFFIC CAR");
}

QRectF Traffic_Car::boundingRect() const
{
    return QRectF(0,0,ww,hh);
}

void Traffic_Car::set_Nap(int nap)
{
    this->nap=nap;
}

void Traffic_Car::set_Tipe(int tipe)
{
    this->tipe=tipe;
}

void Traffic_Car::next_Frame()
{

    this->speed=this->data(2).toInt();
    if(speed>0)
    {
        this->setPos(this->pos().x()-1,this->pos().y());

        if(this->pos().x()<-91)this->deleteLater();
        this->update();

        if(tipe==66 && this->pos().x()<80)this->deleteLater();
        if(tipe==88)this->deleteLater();


        if(tipe==77)
                timer.start(10*1-(this->speed*1));
            else
                timer.start(10*koef_speed-(this->speed*koef_speed));
    }
    else
        timer.start(1000);
}

void Traffic_Car::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    tipe=this->data(1).toInt();
    if(tipe==0){ww=91;hh=53;painter->drawPixmap(0,0, *spriteImage, 18, 113, ww, hh);}
    if(tipe==1){ww=91;hh=53;painter->drawPixmap(0,0, *spriteImage, 244, 113, ww, hh);}
    if(tipe==2){ww=84;hh=55;painter->drawPixmap(0,0, *spriteImage, 593, 19, ww, hh);}
    if(tipe==3){ww=83;hh=59;painter->drawPixmap(0,0, *spriteImage, 491, 17, ww, hh);}

    if(tipe==66){ww=127;hh=100;painter->drawPixmap(0,0, *spriteImage, 18, 182, ww, hh);}
    if(tipe==77){ww=80;hh=56;painter->drawPixmap(0,0, *spriteImage, 201, 206, ww, hh);}

    Q_UNUSED(option);
    Q_UNUSED(widget);
}
