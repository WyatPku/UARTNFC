#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sprtpack.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    SPRTpack x(SPRTpack::Pack_PWR);
    printf("%s", x.toHexString().toStdString().data());
}

void MainWindow::on_openPortBtn_clicked()
{
    if(ui->portNameComboBox->isEnabled())
    {
        serial.setPortName(ui->portNameComboBox->currentText()); //like "COM6"
        serial.setBaudRate(QSerialPort::Baud115200, QSerialPort::AllDirections);
        serial.setDataBits(QSerialPort::Data8);
        serial.setFlowControl(QSerialPort::NoFlowControl);
        serial.setParity(QSerialPort::NoParity);
        serial.setStopBits(QSerialPort::OneStop);
        serial.close();
        if(serial.open(QIODevice::ReadWrite))
        {
            connect(&serial,SIGNAL(readyRead()), this, SLOT(read_Com()));
            ui->openPortBtn->setText("ClosePort");
            ui->portNameComboBox->setDisabled(true);
        } else {
            QMessageBox::information(NULL, QString("Error"), QString("打开串口失败"));
        }
    } else {
        ui->openPortBtn->setText("OpenPort");
        ui->portNameComboBox->setEnabled(true);
        serial.close();
    }
}

void MainWindow::read_Com()
{
    QByteArray temp=serial.read(1); //maxSize, if not that match, just return an empty QByteArray
    if(!temp.isEmpty())
    {
        ui->recvTextBrowser->insertPlainText("0x");
        ui->recvTextBrowser->insertPlainText(temp.toHex());
        ui->recvTextBrowser->insertPlainText(" ");
    }
}

void MainWindow::on_SendBtn_clicked()
{
    serial.write(ui->sendTextEdit->toPlainText().toLatin1());
}
