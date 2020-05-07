#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsRectItem>
#include <QKeyEvent>
#include <QGraphicsScene>
#include <QObject>
#include <QThread>
#include <qtserialport/QSerialPort>
#include <qtserialport/QtSerialPort>
#include <QGraphicsTextItem>
#include <QTimer>
#include <QString>
#include <QByteArray>

#include "Enemy.h"

#define CRC_9 0x31
typedef unsigned char byte;

class Player: public QObject, public QGraphicsRectItem{
    Q_OBJECT
    int flag = 0;
    QSerialPort *device;
    QTimer *timer1;
    double move_x;
    double move_y;

    //Obslga klawiatury
    void keyPressEvent(QKeyEvent * event);
    byte CRC8_DataArray(byte *pData, byte Len);
    byte CRC8_SingleByte(byte CRC_prev, byte Data);
    bool parseData(const char *data, int &tmp_x, int &tmp_y);
public:
        //Konstrukor tworzacy nowy QSerialport
        Player();

private slots:
        //Slot odczytujacy dane z portu
        void readFromPort();

        //Slot nawiazujacy polaczenie z portem
        void connectRead();

        //Wykrywanie braku polaczenia
        void serialErrorHandler(QSerialPort::SerialPortError errorMessage);

public slots:
        //Nawiazaywanie polaczenia po porcie szeregowym
        void UART();

        //Sprawdzanie polaczenia
        bool checkConn();

        //Dodawanie punktow do wykresu
        void addPoint();
};

#endif // PLAYER_H
