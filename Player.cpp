#include "Player.h"
#include "Game.h"

void Player::keyPressEvent(QKeyEvent *event){
    if(event->key() == Qt::Key_Left &&  pos().x() > 0)
        setPos(x()-10,y());
    else if(event->key() == Qt::Key_Right && pos().x() + rect().width() < scene()->width())
        setPos(x()+10,y());
}

Player::Player(){
    device = new serialPort();
    timer1 =  new QTimer();
    connect(timer1, SIGNAL(timeout()), this, SLOT(move()));
    timer1->start(50);
    //Polaczenie z portem
    timer2 =  new QTimer();
    connect(timer2, SIGNAL(timeout()), device, SLOT(UART())); //Proba nawiazania polaczenia co 2s
    timer2->start(500);
}

bool Player::checkConn(){
    if(device->created)
        if(device->checkConn())
            return device->isData;
        return false;
    return false;
}

void Player::move(){
    if(pos().x()+device->getX()/50 > 0 && pos().x() + rect().width() + device->getX()/50 < scene()->width()){
        setPos(x()+device->getX()/50,y());
    }
    /*
    if(pos().y()+device->getY()/120 > scene()->height()/2 && pos().y() + rect().width() + device->getY()/120 < scene()->height()){
        setPos(x(),y()+device->getY()/120);
    }*/
}



