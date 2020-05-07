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

    //Zwracanie wartosci deficuty
    int getDeficyt(){ return deficyt; }
};

#endif // DEFICIT_H
