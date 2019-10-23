#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Подключаем сигнал от таймера к слоту перелистывания кадров спрайта
    connect(&timer_t,SIGNAL(timeout()), this, SLOT(traffic_Generator()));


    // Подключаем сигнал от таймера к слоту поиска коллизий
    connect(&timer_c,SIGNAL(timeout()), this, SLOT(search_Collides()));


    scene = new QGraphicsScene(ui->graphicsView);
    scene->setSceneRect(0,0,ui->graphicsView->width(),ui->graphicsView->height());//фиксим сцену

    back_0 = new BackGround(this,":/new/citie_sky.png", 78, 692, 920, 245,0);//sky
    scene->addItem(back_0);

    back_1 = new BackGround(this,":/new/citie_sky.png", 78, 0, 838, 207,10);//sity
    scene->addItem(back_1);
    back_1->setPos(0,50);

    back_2 = new BackGround(this,":/new/citie_sky.png",78, 229, 848, 304,1);//road
    scene->addItem(back_2);
    back_2->setPos(0,230);

    panel_1 = new Panel(this);
    scene->addItem(panel_1);
    panel_1->setPos(0,0); 

    panel_1->set_Panel(speed,health,coins);
    scene->update(ui->graphicsView->rect());

    ui->graphicsView->setScene(scene);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_actionStart_triggered()
{
    start_game();
}

void MainWindow::start_game()
{
    health=100;
    speed=1;
    coins=0;

    car_1 = new Car(this,0);//hero car
    scene->addItem(car_1);
    car_1->setPos(50,305);

    timer_t.start(3000);   // Запускаем таймер трафика
    timer_c.start(100);    // Запускаем таймер поиска коллизий
}

int repair=1;
void MainWindow::traffic_Generator()
{
    if(repair<10)
    {
        repair++;

        if(repair%5==0)scene->addItem(new Coin(this));

        QTime time = QTime::currentTime();
        qsrand((uint)time.msec());
        scene->addItem(new Traffic_Car(this,random()%4,2));
    }
    else
    {
        repair=0;
        scene->addItem(new Traffic_Car(this,77,2));
    }
    timer_t.start(3000-(speed*300));
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key()==Qt::Key_Up)
    {
        car_1->set_Nap(-1);
    }

    if (event->key()==Qt::Key_Down)
    {
        car_1->set_Nap(1);
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    car_1->set_Nap(0);

    if (event->key()==Qt::Key_Right)
    {
        if(speed<9)
        speed+=1;
    }

    if (event->key()==Qt::Key_Left)
    {
        if(speed>1)
        speed-=1;
    }

}

void MainWindow::search_Collides()
{
    panel_1->set_Panel(speed,health,coins);

    scene->update(ui->graphicsView->rect());

    if(health==0)
    {
        timer_c.stop();
        timer_t.stop();
        car_1->deleteLater();
        ui->statusBar->showMessage("GAME OVER");
    }

    QList <QGraphicsItem * > list = scene->items();
    for(QGraphicsItem *item : scene->items())
    {
        item->setData(2,speed);

        //Захват монет
        if(car_1->collidesWithItem(item) && item->data(0).toString()=="COIN")
        {

            if(item->pos().y()>car_1->pos().y())
            {
                car_1->stackBefore(item);
                if(item->pos().y()-40<car_1->pos().y())carCoin(item);
            }
            else
            {
                item->stackBefore(car_1);
                if(car_1->pos().y()+40<item->pos().y())carCoin(item);
            }
        }

        //Столкновение с машинкой
        if(car_1->collidesWithItem(item) && item->data(0).toString()=="TRAFFIC CAR" && item->data(1).toInt()!=66 && item->data(1).toInt()!=77)
        {
            if(item->pos().y()>car_1->pos().y())
            {
                car_1->stackBefore(item);
                if(item->pos().y()-40<car_1->pos().y())carCollision(item);
            }
            else
            {
                item->stackBefore(car_1);
                if(car_1->pos().y()+40<item->pos().y())carCollision(item);
            }

            if(item->data(1)==66)car_1->stackBefore(item);
        }
        else // или аптечкой
        {
            if(car_1->collidesWithItem(item) && item->data(1).toInt()==77)
            {
                if(item->pos().y()>car_1->pos().y())
                {
                    car_1->stackBefore(item);
                    if(item->pos().y()-40<car_1->pos().y())carRepair(item);
                }
                else
                {
                    item->stackBefore(car_1);
                    if(car_1->pos().y()+40<item->pos().y())carRepair(item);
                }
            }
        }
    }
}

//Ущерб при столкновении
void MainWindow::carCollision(QGraphicsItem *item)
{
    item->setData(1,66);
    item->setPos(item->pos().x(),item->pos().y()-20);

    if(health>0)
    {
        health-=10;
    }
    else
    {
        timer_c.stop();
        timer_t.stop();
        car_1->deleteLater();
        ui->statusBar->showMessage("GAME OVER");
    }
}

//Восстановление
void MainWindow::carRepair(QGraphicsItem *item)
{
    if(health<100)
        health+=10;

    item->setData(1,88);
}

//Монетки
void MainWindow::carCoin(QGraphicsItem *item)
{
    coins++;
    item->setData(1,false);
}
