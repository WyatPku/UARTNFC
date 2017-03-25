#include "deskcore.h"

DeskCore::DeskCore(QObject *parent) : QObject(parent)
{
    connect(&mesManager, SIGNAL(receiveDiyPack(DiyPack)), this,
            SLOT(readDiyPack(DiyPack)));
}

void DeskCore::readDiyPack(DiyPack p)
{
    qDebug("desk core get a diyPack!");
    qDebug(p.toHexString().toLatin1().data());
}

void DeskCore::read_ComByte(QByteArray byteArray)
{
    mesManager.insertByteArray(byteArray);
}

