#ifndef PLAYER_H
#define PLAYER_H

/*!
 *\file
 *\brief Definicja klasy Player
 *
 * Klasa tworzy postac gracza, dodaje skin, odpowiada
 * za ruch oraz połączenie z mikrokontrolerem
 */

#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QGraphicsScene>
#include <QObject>
#include <QGraphicsTextItem>
#include <QTimer>
#include <QString>
#include <QByteArray>

#include "Enemy.h"
#include "Serialport.h"

class Player: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT

    /*!
     * \brief Interwał ruchu
     */
    QTimer *timer1;

    /*!
     * \brief Interwał sprawdzania połaczenia
     */
    QTimer *timer2;

    /*!
     * \brief Obiekt klasy serialPort - połączenie z portem
     */
    serialPort *device;

    /*!
     * \brief Skala obrazów skinu
     */
    double scale = 0.5;

    /*!
     * \brief Obsługa klawiatury
     * \param [in] event naciśnięty przycisk
     */
    void keyPressEvent(QKeyEvent *event);

public:
        /*!
         *\brief Konstrukor inicjalizujacy nowy obiekt klasy SerialPort.
         * Łaczy slot move z timer1 oraz slot checkConn z timer2
         */
        Player();

        /*!
         * \brief Sprawdza połaczenie z portem
         * \retval true - połączono
         * \retval false - rozłączono
         */
        bool checkConn();

        /*!
         * \brief Zatrzymanie ruchu obiektu
         */
        inline void stopMove(){timer1->stop();}

        /*!
         * \brief Wznowienie ruchu obiektu
         */
        inline void startMove(){timer1->start();}

        /*!
         * \brief Zwraca wartosc uzytej skali
         */
        inline double getScale() const {return scale;}

        /*!
         * \brief Usuwanie obiekt u klasy SerialPort
         */
        void cleanPort();

private slots:
        /*!
         * \brief Odpowiada za ruch obiektu
         */
        void move();

public slots:
        /*!
         * \brief Zmienia skin gracza
         * \param [in] n - numer skinu
         */
        void changeSkin(int n);
};

#endif // PLAYER_H
