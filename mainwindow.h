#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//#include <QtSerialPort/QSerialPort>
#include <QMessageBox>
#include <QDebug>
#include "RFdeskCore/commucore.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(CommuCore& commuCore_, QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    //QSerialPort serial;
    CommuCore& commuCore;

private slots:

    void read_ComByte(QByteArray byteArray);

    void on_openPortBtn_clicked();

    //void read_Com();

    void on_SendBtn_clicked();
};

#endif // MAINWINDOW_H
