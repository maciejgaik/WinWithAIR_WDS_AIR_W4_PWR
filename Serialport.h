#ifndef SERIALPORT_H
#define SERIALPORT_H

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

    QSerialPort *device;
    byte CRC8_DataArray(byte *pData, byte Len);
    byte CRC8_SingleByte(byte CRC_prev, byte Data);
    bool parseData(const char *data, int &tmp_x, int &tmp_y);
    double move_x;
    double move_y;
    QTimer *timer1;

public:
    serialPort();
    bool created = false;
    bool isData = false;

private slots:
        //Slot odczytujacy dane z portu
        void readFromPort();

        //Slot nawiazujacy polaczenie z portem
        void connectRead();

        //Wykrywanie braku polaczenia
        void serialErrorHandler(QSerialPort::SerialPortError errorMessage);

        void addPoint();

public slots:
        //Nawiazaywanie polaczenia po porcie szeregowym
        void UART();

        //Sprawdzanie polaczenia
        bool checkConn();
        double getX() const {return move_x;}
        double getY() const {return move_y;}
};

#endif // SERIALPORT_H
