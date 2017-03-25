#include "mainwindow.h"
#include <QApplication>
#include "RFdeskCore/commucore.h"
#include "debugwindow.h"

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    CommuCore commuCore; //global core! will remain until the whole program is down

    DebugWindow d(commuCore);
    d.show();
    MainWindow w(commuCore);
    w.show();


    int returnValue = a.exec();

    //recycle or do some global functions here~ wy

    return returnValue;
}
