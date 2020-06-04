#include "Player.h"
#include "Game.h"

void Player::keyPressEvent(QKeyEvent *event){
    if(event->key() == Qt::Key_Left &&  pos().x() > 0)
        setPos(x()-10,y());
    else if(event->key() == Qt::Key_Right && pos().x() + boundingRect().width() < scene()->width())
        setPos(x()+10,y());
}

Player::Player(){
    device = new serialPort();
    setPixmap(QPixmap(":/images/s1.png"));
    setScale(scale);
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
        return device->checkConn();
    return false;
}

void Player::cleanPort(){
    delete device;
}

void Player::move(){
    if(pos().x()+device->getX()/50 > 0 && pos().x() + boundingRect().width()*scale + device->getX()/50 < scene()->width()){
        setPos(x()+device->getX()/50,y());
    }

    /*
    if(pos().y()+device->getY()/120 > scene()->height()/2 && pos().y() + rect().width() + device->getY()/120 < scene()->height()){
        setPos(x(),y()+device->getY()/120);
    }*/
}

void Player::changeSkin(int n){
    switch(n){
        case 1: setPixmap(QPixmap(":/images/s1.png")); break;
        case 2: setPixmap(QPixmap(":/images/s2.png")); break;
        case 3: setPixmap(QPixmap(":/images/s3.png")); break;
        case 4: setPixmap(QPixmap(":/images/s4.png")); break;
        case 5: setPixmap(QPixmap(":/images/s5.png")); break;
        case 6: setPixmap(QPixmap(":/images/s6.png")); break;
        default: break;
    }
}



