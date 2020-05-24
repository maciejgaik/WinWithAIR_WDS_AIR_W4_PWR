#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsRectItem>
#include <QKeyEvent>
#include <QGraphicsScene>
#include <QObject>
#include <QGraphicsTextItem>
#include <QTimer>
#include <QString>
#include <QByteArray>

#include "Enemy.h"
#include "Serialport.h"

class Player: public QObject, public QGraphicsRectItem{
    Q_OBJECT
    int flag = 0;
    QTimer *timer1;
    QTimer *timer2;
    serialPort *device;

    //Obslga klawiatury
    void keyPressEvent(QKeyEvent * event);
public:
        //Konstrukor tworzacy nowy QSerialport
        Player();
        bool checkConn();
        //Zatrzymywanie ruchu
        void stopMove(){timer1->stop();}

        //Wznawianie ruchu
        void startMove(){timer1->start();}

private slots:
        void move();
};

#endif // PLAYER_H
