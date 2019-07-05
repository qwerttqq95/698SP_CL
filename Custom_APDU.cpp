#include "Custom_APDU.h"
#include <ui_Custom_APDU.h>
#include <Qt>
#include <QString>

extern QString BuildMessage(QString apdu, QString SA);

Custom_APDU::Custom_APDU(QString add, QWidget *parent) :
        QDialog(parent),
        ui(new Ui::myDialog) {
    ui->setupUi(this);
    add_ = std::move(add);
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::MSWindowsFixedSizeDialogHint);
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(send()), Qt::UniqueConnection);
    ui->textEdit->setText("05 01 03 40 01 02 00 00");
}

void Custom_APDU::send() {
    QString a = ui->textEdit->toPlainText().remove(' ');
    QString re_message;
    if (a[0] != '6') {
        qDebug() << "发送add" << add_;
        re_message = BuildMessage(a, add_);
    }
    emit send_write(re_message);
}
