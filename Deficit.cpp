#include "Deficit.h"

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
}
