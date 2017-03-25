#include "debugwindow.h"
#include "ui_debugwindow.h"

DebugWindow::DebugWindow(CommuCore& commuCore_, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DebugWindow),
    commuCore(commuCore_)
{
    ui->setupUi(this);
}

DebugWindow::~DebugWindow()
{
    delete ui;
}

inline bool judgeWhetherHex(const char& x) {
    return (x >= '0' && x <= '9') || (x >= 'a' && x <= 'f') ||
            (x >= 'A' && x <= 'F');
}

void DebugWindow::on_pushButton_singleHexByte_clicked()
{
    QString str = ui->plainTextEdit_singleHexByte->
            toPlainText();
    if (str.length() != 4 || str.at(0) != '0' || str.at(1) != 'x' ||
            !judgeWhetherHex(str.at(2).toLatin1()) ||
            !judgeWhetherHex(str.at(3).toLatin1())) {
        qDebug("输入不是0x00格式的十六进制树");
        return;
    }
    QString hexStr(str.at(2));
    hexStr += str.at(3);
    QByteArray byteArray = QByteArray::fromHex(hexStr.toLatin1());
    commuCore.serial_write(byteArray);
}
