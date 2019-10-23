#include "panel.h"

Panel::Panel(QObject *parent) :  QObject(parent)
{
    //spriteImage = new QPixmap(":/new/traffic_car.png"); // Загружаем изображение спрайта в QPixmap

    timer = new QTimer();   // Создаём таймер для анимации спрайта
    // Подключаем сигнал от таймера к слоту перелистывания кадров спрайта
    connect(timer, &QTimer::timeout, this, &Panel::next_Frame);
    timer->start(100);   // Запускаем спрайт на генерацию сигнала
}

QRectF Panel::boundingRect() const
{
    return QRectF(0,0,91,55);
}

void Panel::set_Panel(int speed,int health,int coins)
{
    this->speed=10+speed*10;
    this->health=health;
    this->coins=coins;
    this->update();
}

void Panel::next_Frame()
{
this->update();
}

void Panel::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //if(tipe==0)painter->drawPixmap(0,0, *spriteImage, 18, 113, 91, 53);
    painter->setPen(Qt::white);

    painter->drawText(10,20,"H");
    painter->drawRect(20,10,100,10);
    painter->drawText(10,40,"S");
    painter->drawRect(20,30,100,10);

    painter->setBrush(Qt::green);
    painter->drawText(120,40,QString("%1 %").arg(speed));
    painter->drawRect(20,30,speed,10);

    painter->drawText(120,20,QString("%1 %").arg(health));
    painter->drawRect(20,10,health,10);

    painter->setFont(QFont ("Courier", 16, QFont::Bold, true));
    painter->drawText(30,70,QString("COINS=%1").arg(coins));

    if(health==0)
    {
        painter->setFont(QFont ("Courier", 38, QFont::Bold, true));
        painter->drawText(240,100,"GAME OVER");
    }


    Q_UNUSED(option);
    Q_UNUSED(widget);
}
