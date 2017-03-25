#ifndef MESMANAGER_H
#define MESMANAGER_H

#include <QByteArray>
#include <QString>
#include <QObject>
#include "diypack.h"

/*
 * This class is the manager of all NFC or smart table control messages
 *
 *
 */
class MesManager : public QObject
{
    Q_OBJECT
private:
    DiyPack diyPack;
#define state_Length 1
#define state_Head 2
#define state_Body 3
    int step;
    int state; //
    void reset();
public:
    explicit MesManager(QObject *parent = 0);
    void insertByte(char x);
    void insertByteArray(QByteArray byteArray);
signals:
    void receiveDiyPack(DiyPack p);
};

#endif // MESMANAGER_H
