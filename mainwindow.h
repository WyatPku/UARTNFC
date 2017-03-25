#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QDebug>
#include "RFdeskCore/commucore.h"
#include "RFdeskCore/deskcore.h"

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
    CommuCore& commuCore;

private slots:

    void read_ComByte(QByteArray byteArray);

    void on_openPortBtn_clicked();

    void on_SendBtn_clicked();
};

#endif // MAINWINDOW_H
