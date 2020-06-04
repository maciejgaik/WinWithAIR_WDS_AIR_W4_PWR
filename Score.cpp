#include "Score.h"
#include "Game.h"

extern Game *game;

Score::Score(QGraphicsItem *parent): QGraphicsTextItem(parent){
    score = 0;

    setPlainText(QString("Zebrane ECTS ") + QString::number(score));
    setDefaultTextColor(Qt::green);
    setFont(QFont("times",16));
}

void Score::increase(int value){
    score += value;
    setPlainText(QString("Zebrane ECTS ") + QString::number(score));

    if(score == 210){
        game->gameOver(true);
    }
}
