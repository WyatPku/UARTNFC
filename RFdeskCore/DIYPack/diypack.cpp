#include "diypack.h"

char DiyPack::shortSum(short x)
{
    return (char)((x>>8) & 0xFF) + (char)(x & 0xFF);
}

void DiyPack::updateCheckSum()
{
    Length = unpackedData.length();
    LengthCheck = - Length;
    HeadCheck = - shortSum(Length) - shortSum(LengthCheck) -
            shortSum(toAddr) - shortSum(fromAddr) - shortSum(CommandType);
    char DataSum = 0;
    for (int i=0; i<Length; ++i) {
        DataSum += unpackedData.at(i);
    }
    DataCheck = -DataSum;

}

DiyPack::DiyPack(char PackType, char SubCmdType)
{
    //first init the head part, and set the length to zero
    Length = 0;
    toAddr = 0;
    fromAddr = 0;
    CommandType = ((short)PackType << 8) + SubCmdType;
    updateCheckSum();
}

DiyPack::DiyPack(void* nouse)
{
    (void*) nouse;
    reset();
}
DiyPack::~DiyPack() {

}

QString DiyPack::toHexString()
{
    QString x;
    x += toQS(Length >> 8) + " ";
    x += toQS(Length) + " ";
    x += toQS(LengthCheck >> 8) + " ";
    x += toQS(LengthCheck) + " ";
    x += toQS(toAddr >> 8) + " ";
    x += toQS(toAddr) + " ";
    x += toQS(fromAddr >> 8) + " ";
    x += toQS(fromAddr) + " ";
    x += toQS(CommandType >> 8) + " ";
    x += toQS(CommandType) + " ";
    x += toQS(HeadCheck) + " ";
    x += toQS(DataCheck) + " ";
    int dataLen = unpackedData.length();
    for (int i=0; i<dataLen; ++i) {
        x += toQS(unpackedData.at(i)) + " ";
    }
    return x;
}

QByteArray DiyPack::generateByteArray()
{
    updateCheckSum();
    QByteArray a;
    a.append((char)(Length>>8));
    a.append((char)Length);
    a.append((char)(LengthCheck>>8));
    a.append((char)LengthCheck);
    a.append((char)(toAddr>>8));
    a.append((char)toAddr);
    a.append((char)(fromAddr>>8));
    a.append((char)fromAddr);
    a.append((char)(CommandType>>8));
    a.append((char)CommandType);
    a.append(HeadCheck);
    a.append(DataCheck);
    a.append(unpackedData);
    return a;
}

void DiyPack::unpackDataAppend(QByteArray a)
{
    unpackedData.append(a);
}

QString DiyPack::toQS(char c) {
    char str[6];
    sprintf(str, "0x%02X", (unsigned char)c);
    return QString(str);
}

void DiyPack::reset() {
    Length = 0;
    LengthCheck = 0;
    toAddr = 0;
    fromAddr = 0;
    CommandType = 0;
    HeadCheck = 0;
    DataCheck = 0;
    unpackedData.clear();
}

bool DiyPack::ifLengthMatch()
{
    return Length + LengthCheck == 0;
}

bool DiyPack::ifMatchAll()
{
    if (Length + LengthCheck != 0) {
        qDebug("长度校验和不匹配");
        return false;
    }
    if (HeadCheck + shortSum(Length) + shortSum(LengthCheck) +
            shortSum(toAddr) + shortSum(fromAddr) +
            shortSum(CommandType) != 0) {
        qDebug("头部校验和不匹配");
        return false;
    }
    char DataSum = 0;
    for (int i=0; i<Length; ++i) {
        DataSum += unpackedData.at(i);
    }
    if (DataCheck + DataSum != 0) {
        qDebug("数据校验和不匹配");
        return false;
    }
    return true;
}
