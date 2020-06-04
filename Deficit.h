#ifndef DEFICIT_H
#define DEFICIT_H

/*!
 *
 * \file
 * \brief Definicja klasy Deficit
 * Plik zawiera definicję klasy Deficit, ktora jest
 * klasa pochodna QGraphicsTextItem.
 * Klasa odpowida za liczenie niezdobytych punktów ects
 * oraz ustawienie napisu do wyswietlenia
 *
 */

#include <QGraphicsTextItem>
#include <QFont>

class Deficit: public QGraphicsTextItem{
    /*!
     * \brief Liczba niezdobytych punktów
     */
    int deficyt;

public:
    /*!
     * \brief Kontruktor inicjalizuje wartość deficyt jako 0
     * oraz tworzy napis do wyswietlenia
     * \param [in] parent - wskaźnik na rodzica
     */
    Deficit(QGraphicsItem *parent = 0);

    /*!
     * \brief Metoda zmniejsza ilość niezdobtych punktów
     * \param [in] value - odjęte punkty od atrybutu deficyt
     */
    void decrease(int value);

    /*!
     * \brief Metoda zwiększa ilość niezdobtych punktów
     * \param [in] value - dodane punkty do atrybuty deficyt
     */
    void increase(int value);

    /*!
     * \brief Zwraca wartość deficytu
     * \return deficyt - ilosc niezdobytych punktów
     */
    inline int getDeficyt() const { return deficyt; }

    /*!
     * \brief Metoda resetuje wartość niezdobytych punktów na 0
     */
    inline void resetDeficit(){ deficyt = 0;}
};

#endif // DEFICIT_H
