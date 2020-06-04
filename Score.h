#ifndef SCORE_H
#define SCORE_H

/*!
 *
 * \file
 * \brief Definicja klasy Score
 * Plik zawiera definicję klasy Score, ktora jest
 * klasa pochodna QGraphicsTextItem.
 * Klasa odpowida za liczenie zdobytych punktów ects
 * oraz ustawienie napisu do wyswietlenia
 *
 */

#include <QGraphicsTextItem>
#include <QFont>

class Score: public QGraphicsTextItem{
    /*!
     * \brief Liczba zdobytych punktów
     */
    int score;

public:
    /*!
     * \brief Kontruktor inicjalizuje wartość score jako 0
     * oraz tworzy napis do wyswietlenia
     * \param [in] parent - wskaźnik na rodzica
     */
    Score(QGraphicsItem *parent = 0);

    /*!
     * \brief Metoda zwiększa ilość zdobtych punktów
     * \param [in] value - dodane punkty do atrybutu score
     */
    void increase(int value);

    /*!
     * \brief Metoda zwraca ilość zdobytych punktów
     * \return score - ilość punktów
     */
    inline int getScore(){ return score; }

    /*!
     * \brief Metoda resetuje wartość zdobytych punktów na 0
     */
    inline void resetScore(){ score = 0; }
};

#endif // SCORE_H
