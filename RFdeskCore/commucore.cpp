#include "commucore.h"

CommuCore::CommuCore(QObject *parent) : QObject(parent)
{

}

bool CommuCore::OpenComInit(QString COM)
{
    serial.setPortName(COM); //like "COM6"
    serial.setBaudRate(QSerialPort::Baud115200, QSerialPort::AllDirections);
    serial.setDataBits(QSerialPort::Data8);
    serial.setFlowControl(QSerialPort::NoFlowControl);
    serial.setParity(QSerialPort::NoParity);
    serial.setStopBits(QSerialPort::OneStop);
    serial.close();
    if(serial.open(QIODevice::ReadWrite))
    {
        connect(&serial,SIGNAL(readyRead()), this, SLOT(read_Com()));
        return true;
    } else {
        return false;
    }
}

void CommuCore::read_Com()
{
    QByteArray temp=serial.read(1); //maxSize, if not that match, just return an empty QByteArray
    if(!temp.isEmpty())
    {
        emit signal_ComByte(temp);
    }
}

void CommuCore::CloseCom()
{
    serial.close();
}

qint64 CommuCore::serial_write(QByteArray byteArray)
{
    return serial.write(byteArray);
}
