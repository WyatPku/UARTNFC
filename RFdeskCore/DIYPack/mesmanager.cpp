#include "mesmanager.h"

MesManager::MesManager(QObject *parent) : QObject(parent),
    diyPack((void *)NULL)
{
    reset();
}

void MesManager::insertByteArray(QByteArray byteArray)
{
    int arrayLen = byteArray.count();
    for (int i=0; i < arrayLen; ++i) {
        char x = byteArray.at(i);
        insertByte(x);
    }
}

void MesManager::insertByte(char cx) {
    unsigned char x = cx;
    //qDebug(diyPack.toHexString().toLatin1().data());
    //qDebug("state:%d, step:%d\n", state, step);
    switch (state) {
    case state_Length:
        if (step < 2) {
            diyPack.Length <<= 8;
            diyPack.Length |= x;
            ++step;
        } else if (step == 2) {
            diyPack.LengthCheck = x;
            diyPack.LengthCheck <<= 8;
            ++step;
        } else {
            diyPack.LengthCheck |= x;
            //then testwhether it fit
            if (diyPack.ifLengthMatch()) {
                //next state
                step = 0;
                state = state_Head;
            } else {
                //next choice
                diyPack.Length <<= 8;
                unsigned char highc = ((diyPack.LengthCheck >> 8) & 0x00FF);
                diyPack.Length |= highc;
                diyPack.LengthCheck <<= 8;
            }
        }
        break;
    case state_Head:
        break;
    case state_Body:
        break;
    }
    qDebug(diyPack.toHexString().toLatin1().data());
}

void MesManager::reset() {
    state = state_Length;
    step = 0;
    diyPack.reset();
}
