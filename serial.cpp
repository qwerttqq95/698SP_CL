#include "serial.h"
#include "ui_serial.h"

Serial::Serial(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    setWindowTitle("通讯配置");

}



Serial::~Serial() = default;
