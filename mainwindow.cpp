#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(CommuCore& commuCore_, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    commuCore(commuCore_)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_openPortBtn_clicked()
{
    if(ui->portNameComboBox->isEnabled())
    {
        if (commuCore.OpenComInit(ui->portNameComboBox->currentText())) {
            connect(&commuCore, SIGNAL(signal_ComByte(QByteArray)), this,
                    SLOT(read_ComByte(QByteArray)));
            ui->openPortBtn->setText("ClosePort");
            ui->portNameComboBox->setDisabled(true);
        } else {
            QMessageBox::information(NULL, QString("Error"), QString("打开串口失败"));
        }
    } else {
        ui->openPortBtn->setText("OpenPort");
        ui->portNameComboBox->setEnabled(true);
        commuCore.CloseCom();
        disconnect(&commuCore, SIGNAL(signal_ComByte(QByteArray)), this,
                   SLOT(read_ComByte(QByteArray)));
    }
}

void MainWindow::read_ComByte(QByteArray byteArray)
{
    mesManager.insertByteArray(byteArray);
    int size = byteArray.size();
    QByteArray hexArray = byteArray.toHex();
    for (int i=0; i<size; ++i) {
        ui->recvTextBrowser->insertPlainText("0x");
        QString str(hexArray.at(2*i));
        str += hexArray.at(2*i + 1);
        ui->recvTextBrowser->insertPlainText(str);
        ui->recvTextBrowser->insertPlainText(" ");
    }
    /*ui->recvTextBrowser->insertPlainText("0x");
    ui->recvTextBrowser->insertPlainText(byteArray.toHex());
    ui->recvTextBrowser->insertPlainText(" ");*/
}

void MainWindow::on_SendBtn_clicked()
{
    commuCore.serial_write(ui->sendTextEdit->toPlainText().toLatin1());
}
