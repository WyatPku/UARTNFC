#ifndef DESKCORE_H
#define DESKCORE_H

#include <QString>
#include <QObject>
#include "DIYPack/diypack.h"
#include "DIYPack/mesmanager.h"

class DeskCore : public QObject
{
    Q_OBJECT
private:
    MesManager mesManager;
public:
    explicit DeskCore(QObject *parent = 0);
private slots:
    void readDiyPack(DiyPack p);
public slots:
    void read_ComByte(QByteArray byteArray);
signals:

};

#endif // DESKCORE_H
