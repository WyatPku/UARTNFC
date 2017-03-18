#include "sprtpack.h"

char SPRTpack::shortSum(short x)
{
    return (char)((x>>8) & 0xFF) + (char)(x & 0xFF);
}

void SPRTpack::updateCheckSum()
{
    LengthCheck = 0xFFFF - Length;
    HeadCheck = 0xFF - shortSum(Length) - shortSum(LengthCheck) -
            shortSum(toAddr) - shortSum(fromAddr) - shortSum(CommandType) -
            HeadCheck - DataCheck;
    DataCheck = (char)0xFF;

}

SPRTpack::SPRTpack(char PackType, char SubCmdType)
{
    //first init the head part, and set the length to zero
    Length = 0;
    toAddr = 0;
    fromAddr = 0;
    CommandType = ((short)PackType << 8) + SubCmdType;
    updateCheckSum();
}
SPRTpack::~SPRTpack() {

}

QString SPRTpack::toHexString()
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
    for (int i=0; i<Length; ++i) {
        x += toQS(unpackedData.at(i)) + " ";
    }
    return x;
}

QString SPRTpack::toQS(char c) {
    char str[6];
    sprintf(str, "0x%02X", (unsigned char)c);
    return QString(str);
}
