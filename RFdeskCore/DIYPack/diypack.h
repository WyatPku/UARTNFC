#ifndef DIYPACK_H
#define DIYPACK_H

/*
 * This file is created by WY on 2017/3/18
 * To package control frames to PN532 or to indicate the processor to do something
 *
 * The protocal V1.0 contains a header with fixed length of 12byte
 * (considering that most of messages should to be realize a unrelable message, we don't prepare spaces for TCP)
 * Length(short) LengthCheck(short) toAddr(short) fromAddr(short) CommandType(short) HeadCheck(byte) DataCheck(byte)
 *             2                  2             2               2                  2               1               1     12
 *
 *
 */

#include <QByteArray>
#include <QString>

class DiyPack
{
public:
    QByteArray unpackedData; //data without head
    short Length;
    short LengthCheck;
    short toAddr;
    short fromAddr;
    short CommandType;
    char HeadCheck;
    char DataCheck;
    char shortSum(short x);
    void updateCheckSum();
    QString toQS(char c);

public:
    static const char Pack_PN532 = 'N'; //NFC 0x4E
    static const char Pack_PWR = 'P'; //Power 0x50

    DiyPack(char PackType, char SubCmdType = 0x00);
    DiyPack(void* nouse);
    ~DiyPack();
    QString toHexString(); //return in hex string
    void reset();

    //judge the check
    bool ifLengthMatch();
};

#endif // DIYPACK_H
