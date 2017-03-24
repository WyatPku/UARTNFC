#ifndef DESKCORE_H
#define DESKCORE_H

#include <QtSerialPort/QSerialPort>
#include <QByteArray>
#include <QString>
#include <QObject>

class deskCore : public QObject
{
    Q_OBJECT
private:
    QSerialPort serial;
public:
    explicit deskCore(QObject *parent = 0);
    bool OpenComInit(QString COM); //return if success
private slots:
    void read_Com();
signals:

};

#endif // DESKCORE_H
