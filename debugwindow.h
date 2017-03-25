#ifndef DEBUGWINDOW_H
#define DEBUGWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <iostream>
using namespace std;
#include "RFdeskCore/commucore.h"
#include "RFdeskCore/DIYPack/diypack.h"

namespace Ui {
class DebugWindow;
}

class DebugWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit DebugWindow(CommuCore& commuCore_, QWidget *parent = 0);
    ~DebugWindow();

private slots:
    void on_pushButton_singleHexByte_clicked();

    void on_pushButton_sendNFCmessage_clicked();

private:
    Ui::DebugWindow *ui;
    CommuCore& commuCore;
};

#endif // DEBUGWINDOW_H
