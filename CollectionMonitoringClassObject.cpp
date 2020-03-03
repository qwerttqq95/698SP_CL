//
// 采集监控类
//

#include "CollectionMonitoringClassObject.h"
#include "QAction"

extern QString BuildMessage(QString apdu, const QString &SA, const QString &ctrl_zone);


extern QString re_rever_add();

CollectionMonitoringClass::CollectionMonitoringClass(QWidget *parent) : QDialog(parent),
                                                                        ui(new Ui::FormCOLLECTIONMONITORINGCLASSOBJECT) {
    ui->setupUi(this);
    this->setWindowTitle("采集监控");
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(sendmessage()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(sendmessage()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(sendmessage()));
}

void CollectionMonitoringClass::analysis6012() {

}

void CollectionMonitoringClass::analysis6014() {

}

void CollectionMonitoringClass::analysis601C() {

}

void CollectionMonitoringClass::sendmessage() {
    QAction *action = (QAction *) sender();
    QString add = re_rever_add();
    qDebug() << action->objectName();
    if (action->objectName() == "pushButton")
            emit send_message({BuildMessage("05010060120200", add, "43"), ""});
    else {
        if (action->objectName() == "pushButton_3")
                emit send_message({BuildMessage("05010060140200", add, "43"), ""});
        else
                emit send_message({BuildMessage("050100601c0200", add, "43"), ""});
    }
}
