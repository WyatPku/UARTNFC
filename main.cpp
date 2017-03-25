#include "mainwindow.h"
#include <QApplication>
#include "RFdeskCore/commucore.h"
#include "debugwindow.h"
#include "RFdeskCore/deskcore.h"
#include "RFdeskCore/usercore.h"

#define As_Desk
//#define AS_User

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    CommuCore commuCore; //global core! will remain until the whole program is down

    DebugWindow d(commuCore);
    d.show();
    MainWindow w(commuCore);
    w.show();

#ifdef As_Desk
    DeskCore deskCore;
    deskCore.connect(&commuCore, SIGNAL(signal_ComByte(QByteArray)),
            &deskCore, SLOT(read_ComByte(QByteArray)));
#endif

    int returnValue = a.exec();

    //recycle or do some global functions here~ wy

    return returnValue;
}
