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
private:
    QString toQS(char c);
public:
    QByteArray unpackedData; //data without head
    short Length;
    short LengthCheck;
    short toAddr; //0,1
    short fromAddr; //2,3
    short CommandType; //4,5
    char HeadCheck; //6
    char DataCheck; //7
    char shortSum(short x);
    void updateCheckSum();

    static const char Pack_PN532 = 'N'; //NFC 0x4E
    static const char Pack_PWR = 'P'; //Power 0x50

    static const short Max_Length = 1500; //max 1500 byte

    DiyPack(char PackType, char SubCmdType = 0x00);
    DiyPack(void* nouse);
    ~DiyPack();
    QString toHexString(); //return in hex string
    QByteArray generateByteArray();
    void unpackDataAppend(QByteArray a);
    void reset();

    //judge the check
    bool ifLengthMatch();
    bool ifMatchAll();
};

#endif // DIYPACK_H
