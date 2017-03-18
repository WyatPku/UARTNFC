#ifndef SPRTPACK_H
#define SPRTPACK_H

#include <QByteArray>
#include <QString>

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


class SPRTpack
{
private:
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

    SPRTpack(char PackType, char SubCmdType = 0x00);
    ~SPRTpack();
    QString toHexString(); //return in hex string
};

#endif // SPRTPACK_H
