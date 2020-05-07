#include "Enemy.h"
#include "Game.h"

//globalny obiekt
extern Game *game;

Enemy::Enemy(QString n, int e) : Course(n, e){
    //Ustawienie rozmiaru
    setRect(0,0,100,100);
    int modulo = 500;
    setX(rand()%modulo);

    //Tworzenie timera i laczenie go przez timeout z move
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(50);
}

//Ruch wroga
void Enemy::move(){
    setPos(x(),y()+5);
    //Znalezienie colidujacych obiektow
    QList<QGraphicsItem *> colliding_item = collidingItems();
    for(int i = 0, n = colliding_item.size(); i < n; ++i){
        if(typeid(*(colliding_item[i])) == typeid(Player)){
            scene()->removeItem(this);
            game->score->increase(getEcts());
            game->enemyList.removeAll(this);
            delete this;
            return;
        }
    }

    //Jesli bloczek nie zostal zlapany to naliczany jest deficyt
    if(pos().y() > scene()->height()){
        scene()->removeItem(this);
        game->deficit->decrease(getEcts());
        //game->enemyList.insert(game->enemyList.indexOf(this)+5, this);
        //changeStatus(true);
        game->enemyList.removeAll(this);
        delete this;
    }
}
/*
void Enemy::timeMoveStart(){
    if(!getStatus()){
        timer = new QTimer();
        connect(timer, SIGNAL(timeout()), this, SLOT(move()));
        timer->start(50);
    }
    else{
        int modulo = 500;
        setPos(rand()%modulo,0);
        changeStatus(false);
    }
}
*/
