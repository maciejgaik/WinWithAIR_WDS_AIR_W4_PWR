#ifndef SCORE_H
#define SCORE_H

#include <QGraphicsTextItem>
#include <QFont>

class Score: public QGraphicsTextItem{
    int score;
public:
    //Konstruktor inicjaliozuje wartosc i generuje pierwszy napis
    Score(QGraphicsItem *parent = 0);

    //Metoda dodawania punktow, argumentem jest ilosc dodawanych punktow
    void increase(int value);

    //Zwracanie wartosci ilosci punktow
    int getScore(){ return score; }
};

#endif // SCORE_H
