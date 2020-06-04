#ifndef SERIALPORT_H
#define SERIALPORT_H

/*!
 *\file
 *\brief Definicja klasy Serialport
 * Plik zawiera definicje klasy Serialport
 */

#include <QString>
#include <QByteArray>
#include <qtserialport/QSerialPort>
#include <qtserialport/QtSerialPort>
#include <string>
#include <sstream>
#include <iostream>
#include <QObject>
#include <QTimer>
#include <QList>

#define CRC_9 0x31
typedef unsigned char byte;

class serialPort: public QObject{
    Q_OBJECT

    /*!
     * \brief Interwał dodawania danych do wykresu
     */
    QTimer *timer;

    /*!
     * \brief Obiekt klasy QSerialPort
     */
    QSerialPort *device;

    /*!
     * \brief Metoda oblicza cykliczną sumę kontrolną
     * \param [in] pData - otrzymana ramka
     * \param [in] Len - długosc ramki
     * \return CRC8 - cykliczna wartość kontrolna danej ramki
     */
    byte CRC8_DataArray(byte *pData, byte Len);

    /*!
     * \brief Metoda wykonuje mnożenie binarne
     * \param [in] CRC_prev - poprzednio obliczonna wartosc
     * \param [in] Data - element ramki danych do obliczeń
     * \return CRC_prev - część cyklicznej sumy kontrolnej
     */
    byte CRC8_SingleByte(byte CRC_prev, byte Data);

    /*!
     * \brief Parsowanie danych z otrzymanej ramki
     * \param [in] data - otrzymana ramka
     * \param [out] tmp_x - odczytana wartosc X zwrócona przez referencje
     * \param [out] tmp_y - odczytana wartosc Y zwrócona przez referencje
     * \retval true - parsowanie się powiodło
     * \retval false - parsowanie się nie powiodło
     */
    bool parseData(const char *data, int &tmp_x, int &tmp_y);

    /*!
     * \brief Wartość obrotu w osi X
     */
    double move_x;

    /*!
     * \brief Wartość obrotu w osi Y
     */
    double move_y;

public:
    /*!
     * \brief Kontruktor inicjalizuje obeikt QSerialPort oraz łączy timer ze slotem addPoint
     */
    serialPort();

    /*!
     * \brief Flaga typu bool czy utworzono obiekt klasu QSerialPort
     */
    bool created = false;

private slots:
    /*!
    * \brief Slot odczytuje ramkę wysłaną przez port szeregowy
    */
    void readFromPort();

    /*!
     * \brief Slot ustawia paramtery połączenia
     */
    void setConnection();

    //Wykrywanie braku polaczenia
    /*!
     * \brief Slot sprawdza czy nie wsytapił błąd połączenia
     * \param [in] errorMessage - wiadomosć o błędzie
     */
    void serialErrorHandler(QSerialPort::SerialPortError errorMessage);

    /*!
    * \brief Wywułuje metodę addPoint obiektu globalnego
    * klasy Game z parametrami, które są wartościami obrotu
    * kontrolera w osiach X i Y
    */
    void addPoint();

public slots:
    /*!
     * \brief Nawiązanie połaczenia oraz połączenie
     * sygnału readyRead ze slotem readFromPort
     */
     void UART();

    /*!
     * \brief Odpowiedzialny za sprawdzanie połączenia z kontrolerem
     * \retval false - rozłączono
     * \retval true - połączono
     */
     bool checkConn();

    /*!
     * \brief Zwraca ostatnią odczytną wartosć obrotu w osi X
     * w zakresie -1024 do 1024 gdzie jest to odpowiednio -90* do 90*
     * \return move_x - wartość obrotu w osiX
     */
     inline double getX() const {return move_x;}

    /*!
     * \brief Zwraca ostatnią odczytną wartosć obrotu w osi Y
     *  zakresie -1024 do 1024 gdzie jest to odpowiednio -90* do 90*
     * \return move_y - wartość obrotu w osi Y
     */
     inline double getY() const {return move_y;}
};

#endif // SERIALPORT_H
