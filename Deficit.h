#ifndef DEFICIT_H
#define DEFICIT_H

#include <QGraphicsTextItem>
#include <QFont>

class Deficit: public QGraphicsTextItem{
    int deficyt;
public:
    //Konstruktor inicjaliozuje wartosc i generuje pierwszy napis
    Deficit(QGraphicsItem *parent = 0);

    //Metoda naliczajaca deficyt, argumentem jest ilosc naliczonych punktow
    void decrease(int value);

    void increase(int value);

    //Zwracanie wartosci deficuty
    int getDeficyt(){ return deficyt; }
    void resetDeficit(){ deficyt = 0;}
};

#endif // DEFICIT_H
