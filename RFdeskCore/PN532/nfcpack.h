#ifndef NFCPACK_H
#define NFCPACK_H

#include <QByteArray>
#include <QString>

/*
 * This file is created by WY on 2017/3/19
 * To generate control frames to PN532 by simple functions
 *
 * It contains:
 * Preamble, Start of Packet Code, Packet Length, Packet Length Checksum,
 *      Specific PN532 Frame Identifier, Packet Data, Packet Data Checksum, Postamble
 *
 */


class NFCpack
{
private:
    char packType; //

    QByteArray NFCdata; //data
    const char preamble = 0x00;
    const short startPack = 0x00FF;
    char Len; //Length
    char LCS; //Length Checksum
    char TFI; //Specific PN532 Frame Identifier
    char DCS; //Packet Data Checksum
    const char postamle = 0x00;

public:
    static const char type_ACK = 'A';
    static const char type_NACK = 'N';
    static const char type_ERRORFrame = 'E';
    static const char type_StdPack = 'S';
    static const char type_LongerPack = 'L';

    NFCpack();
};

#endif // NFCPACK_H
