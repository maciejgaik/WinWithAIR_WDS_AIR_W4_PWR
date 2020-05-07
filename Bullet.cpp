#include "Bullet.h"

//Konstruktor pocisku
Bullet::Bullet(){
    //Ustawienie pozycji
    setRect(0,0,10,50);

    //Tworzenie timera i laczenie go przez timeout z move
    QTimer *timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));

    //Startowania timera przy tworzeniu nowego pocisku
    timer->start(50);
}

//Ruch pocisku
void Bullet::move(){
    setPos(x(),y()-10);

    if(pos().y() + rect().height() < 0 ){
        scene()->removeItem(this);
        delete this;
        //qDebug() << "Usunieto pocisk.";
    }
}
