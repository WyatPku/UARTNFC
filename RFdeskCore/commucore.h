#ifndef COMMUCORE_H
#define COMMUCORE_H

#include <QtSerialPort/QSerialPort>
#include <QByteArray>
#include <QString>
#include <QObject>

class CommuCore : public QObject
{
    Q_OBJECT
private:
    QSerialPort serial;
public:
    explicit CommuCore(QObject *parent = 0);
    bool OpenComInit(QString COM); //return if success
    void CloseCom(); //close the serial
    qint64 serial_write(QByteArray byteArray); //all name with "serial"
        // is a direct package of the origin function
private slots:
    void read_Com();
signals:
    void signal_ComByte(QByteArray byteArray);
};

#endif // COMMUCORE_H
