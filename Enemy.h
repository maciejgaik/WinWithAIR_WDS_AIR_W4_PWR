#ifndef ENEMY_H
#define ENEMY_H

#include <QGraphicsRectItem>
#include <QTimer>
#include <QObject>
#include <QGraphicsScene>
#include <cstdlib>
#include <QDebug>
#include <QList>
#include <QString>

#include "Player.h"
#include "Course.h"

class Enemy: public QObject, public QGraphicsRectItem, public Course{
    Q_OBJECT

    //Timer sluzacy do ruchu obiektu
    QTimer *timer;
public:
    //Konstruktor ustawiajacy rozmiar i losowa pozycje oraz wykonanie connect timera i move
    Enemy(QString n, int e);

    //Zatrzymywanie ruchu
    void stopMove(){timer->stop();}

    //Wznawianie ruchu
    void startMove(){timer->start(50);}

public slots:
    //Metoda odpowiadajaca za ruch
    void move();
    //void timeMoveStart();
};

#endif // ENEMY_H
