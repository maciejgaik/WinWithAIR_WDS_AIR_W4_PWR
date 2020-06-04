#ifndef ENEMY_H
#define ENEMY_H

/*!
 *
 * \file
 * \brief Definicja klasy Enemy
 * Plik zawiera definicję klasy Enemy, ktora jest
 * klasa pochodna QGraphicsEllipseItem oraz Course.
 * Klasa odpowida za obiekty spadających bloczków,
 * ich ruch oraz usuwanie
 *
 */

#include <QGraphicsEllipseItem>
#include <QTimer>
#include <QObject>
#include <QGraphicsScene>
#include <cstdlib>
#include <QDebug>
#include <QList>
#include <QString>
#include <QGraphicsTextItem>
#include <QColor>
#include <QBrush>

#include "Player.h"
#include "Course.h"

class Enemy: public QObject, public QGraphicsEllipseItem, public Course{
    Q_OBJECT

    /*!
     * \brief Interwał ruchu bloczków
     */
    QTimer *timer;

public:
    /*!
     * \brief Konstruktor ustawiajacy rozmiar i losowa pozycje oraz
     * połączenie timera ze slotem move
     * \param [in] interval - interwał ruchu bloczków
     * \param [in] _name - nazwa bloczku
     * \param [in] _ects - wartosc punktowa
     * \param [in] _status - status czy bloczek danego kursu był juz tworzony
     */
    Enemy(int interval, QString _name, int _ects, bool _status = false);

    /*!
     * \brief Zatrzymanie ruchu obiektu
     */
    inline void stopMove(){timer->stop();}

    /*!
     * \brief Wznowienie ruchu obiektu
     */
    inline void startMove(){timer->start();}

    /*!
     * \brief Obiekt klasy QGraphicsTextItem nazwy kursu
     */
    QGraphicsTextItem *nameText;

    /*!
     * \brief Obiekt klasy QGraphicsTextItem wartosci punktów
     */
    QGraphicsTextItem *ectsText;

    /*!
     * \brief Zmniejszenie interwału ruchu
     */
    void faster();

    /*!
     * \brief Zwiększenie interwału ruchu
     */
    void slower();

private slots:
    /*!
     * \brief Odpowiada za ruch bloczków
     */
    void move();
};

#endif // ENEMY_H
