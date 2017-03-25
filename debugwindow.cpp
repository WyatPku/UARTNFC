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
