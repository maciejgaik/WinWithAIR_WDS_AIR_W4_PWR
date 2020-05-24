#include "Serialport.h"
#include "Game.h"

//globalny obiekt
extern Game *game;

serialPort::serialPort(){
    device = new QSerialPort(this);
    timer1 =  new QTimer();
    connect(timer1, SIGNAL(timeout()), this, SLOT(addPoint()));
    timer1->start(100);
}

void serialPort::readFromPort(){
   if(device->canReadLine()){
        isData = true;
        int tmp_x = 0;
        int tmp_y = 0;
        QString data = device->readLine();
        qDebug() << data;
        QByteArray pDataFrame = data.toLocal8Bit();
        if(parseData((char*)pDataFrame.constData(), tmp_x, tmp_y)){
            move_x = tmp_x;
            move_y = tmp_y;
        }
        //qDebug() << "x = " << move_x << " y = " << move_y;
    }
   //else isData = false;
}

void serialPort::connectRead(){
    device->setPortName("/dev/cu.SLAB_USBtoUART");
    if(device->open(QSerialPort::ReadOnly)){
        device->setBaudRate(QSerialPort::Baud115200);
        device->setDataBits(QSerialPort::Data8);
        device->setParity(QSerialPort::NoParity);
        device->setStopBits(QSerialPort::OneStop);
        device->setFlowControl(QSerialPort::NoFlowControl);
    }
}

byte serialPort::CRC8_DataArray(byte *pData, byte Len){
    byte CRC_final = 0xff;

    for(int i = 0; i < Len; ++i){
        CRC_final = CRC8_SingleByte(CRC_final, pData[i]);
    }
return CRC_final;
}

byte serialPort::CRC8_SingleByte(byte CRC_prev, byte Data){
    CRC_prev ^= Data;
    for(int i = 0; i < 8; ++i){
        if((CRC_prev & 0x80) != 0){
            CRC_prev = (byte)((CRC_prev << 1) ^ CRC_9);}
        else{
            CRC_prev = (byte)(CRC_prev << 1);}
    }
    return CRC_prev;
}

bool serialPort::parseData(const char *data, int &tmp_x, int &tmp_y){
    std::istringstream IStr(data);
    char header;
    int CRC8;

    IStr >> header >> tmp_x >> tmp_y >> std::hex >> CRC8;
    if(IStr.fail() || header != 'X') return false;
    return (byte)CRC8 == CRC8_DataArray((byte*)data, strlen(data)-6);
}

void serialPort::UART(){
    if(checkConn()){
        connectRead();
        connect(device, SIGNAL(readyRead()), this, SLOT(readFromPort()));
        created = true;
    }
}

bool serialPort::checkConn(){
    QSerialPortInfo *info = new QSerialPortInfo;
    QList<QSerialPortInfo> list = info->availablePorts();
    connect(device, SIGNAL(errorOccurred(QSerialPort::SerialPortError)), this, SLOT(serialErrorHandler(QSerialPort::SerialPortError)));
    for (QSerialPortInfo &port : list) {
        if (port.portName() == "cu.SLAB_USBtoUART")
            return true;
        }
    return false;
}

void serialPort::addPoint(){
    game->addPoint(move_x/1000.0*90.0,move_y/1000.0*90.0);
}

void serialPort::serialErrorHandler(QSerialPort::SerialPortError errorMessage){
     if (errorMessage == QSerialPort::ResourceError) {
         if(device->isOpen()){
            device->close();
            device->clearError();
         }
     }
}

