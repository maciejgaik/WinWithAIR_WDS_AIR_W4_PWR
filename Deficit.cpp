#include "Deficit.h"
#include "Game.h"

extern Game *game;

Deficit::Deficit(QGraphicsItem *parent): QGraphicsTextItem(parent){
    deficyt = 0;

    setPlainText(QString("Deficyt ") + QString::number(deficyt));
    setDefaultTextColor(Qt::red);
    setFont(QFont("times",16));
}

void Deficit::decrease(int value){
    deficyt += value;
    setPlainText(QString("Deficyt ") + QString::number(deficyt));
    setDefaultTextColor(Qt::red);
    setFont(QFont("times",16));

    if(deficyt > 11){
        game->gameOver(false);
    }
}

void Deficit::increase(int value){
    deficyt -= value;
    setPlainText(QString("Deficyt ") + QString::number(deficyt));
    setDefaultTextColor(Qt::red);
    setFont(QFont("times",16));
}
