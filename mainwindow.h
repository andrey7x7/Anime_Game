#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QKeyEvent>
#include <QTimer>
#include <QTime>
#include <QMessageBox>
#include <background.h>
#include <car.h>
#include <traffic_car.h>
#include <panel.h>
#include <coin.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    int speed=1;
    int health=100;
    int coins=0;

private:
    Ui::MainWindow *ui;
    QTimer timer_t;
    QTimer timer_c;
    QGraphicsScene  *scene;
    BackGround *back_0;
    BackGround *back_1;
    BackGround *back_2;
    Car *car_1;
    Panel *panel_1;


protected:
   void keyPressEvent(QKeyEvent *event);
   void keyReleaseEvent(QKeyEvent *event);

private slots:
   void traffic_Generator();
   void search_Collides();
   void carCollision(QGraphicsItem *item);
   void carRepair(QGraphicsItem *item);
   void start_game();
   void on_actionStart_triggered();
   void carCoin(QGraphicsItem *item);
};

#endif // MAINWINDOW_H
