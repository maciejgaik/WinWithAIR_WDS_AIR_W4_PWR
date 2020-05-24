#ifndef ENEMY_H
#define ENEMY_H

#include <QGraphicsEllipseItem>
#include <QTimer>
#include <QObject>
#include <QGraphicsScene>
#include <cstdlib>
#include <QDebug>
#include <QList>
#include <QString>
#include <QGraphicsTextItem>
#include <QColor>

#include "Player.h"
#include "Course.h"

class Enemy: public QObject, public QGraphicsEllipseItem, public Course{
    Q_OBJECT

    //Timer sluzacy do ruchu obiektu
    QTimer *timer;
public:
    //Konstruktor ustawiajacy rozmiar i losowa pozycje oraz wykonanie connect timera i move
    Enemy(int interval, QString n, int e, bool s = false);

    //Zatrzymywanie ruchu
    void stopMove(){timer->stop();}

    //Wznawianie ruchu
    void startMove(){timer->start();}
    QGraphicsTextItem *text;
    QGraphicsTextItem *t_ects;
    void faster();
    void slower();
public slots:
    //Metoda odpowiadajaca za ruch
    void move();
    //void timeMoveStart();
};

#endif // ENEMY_H
