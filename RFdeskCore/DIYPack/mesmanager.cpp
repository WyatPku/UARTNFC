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
            if (diyPack.ifLengthMatch() &&
                    diyPack.Length < diyPack.Max_Length &&
                    diyPack.Length > 0) {
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
        switch(step) {
        case 0:
            diyPack.toAddr = x;
            diyPack.toAddr <<= 8;
            break;
        case 1:
            diyPack.toAddr |= x;
            break;
        case 2:
            diyPack.fromAddr = x;
            diyPack.fromAddr <<= 8;
            break;
        case 3:
            diyPack.fromAddr |= x;
            break;
        case 4:
            diyPack.CommandType = x;
            diyPack.CommandType <<= 8;
            break;
        case 5:
            diyPack.CommandType |= x;
            break;
        case 6:
            diyPack.HeadCheck = x;
            break;
        case 7:
            diyPack.DataCheck = x;
            state = state_Body;
            step = -1;
            if (diyPack.Length == 0) {
                qDebug("received a diyPack!");
                if (diyPack.ifMatchAll()) {
                    qDebug("emit a received diyPack!");
                    emit receiveDiyPack(diyPack);
                } else {
                    qDebug("throw out a wrong diyPack!");
                    qDebug(diyPack.toHexString().toLatin1().data());
                }
                reset();
            }
            break;
        }
        ++step;
        break;
    case state_Body:
        if (step < diyPack.Length - 1) {
            diyPack.unpackedData.append(x);
            ++step;
        } else {
            //emit a signal
            diyPack.unpackedData.append(x);
            qDebug("received a diyPack!");
            if (diyPack.ifMatchAll()) {
                qDebug("emit a received diyPack!");
                emit receiveDiyPack(diyPack);
            } else {
                qDebug("throw out a wrong diyPack!");
                qDebug(diyPack.toHexString().toLatin1().data());
            }
            reset();
        }
        break;
    }
    qDebug(diyPack.toHexString().toLatin1().data());
}

void MesManager::reset() {
    state = state_Length;
    step = 0;
    diyPack.reset();
}
