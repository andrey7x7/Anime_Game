#ifndef PANEL_H
#define PANEL_H

#include <QObject>
#include <QGraphicsItem>
#include <QTimer>
#include <QPixmap>
#include <QPainter>
#include <QDebug>

class Panel : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Panel(QObject *parent = nullptr);
    int speed=0;
    int health=0;
    int coins=0;

private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
    QTimer *timer;          // Таймер для пролистывания изображения в QPixmap
    QPixmap *spriteImage;   // В данный объект QPixamp будет помещён спрайт

public slots:
    void set_Panel(int speed, int health, int coins);

private slots:
    void next_Frame();
};

#endif // PANEL_H
