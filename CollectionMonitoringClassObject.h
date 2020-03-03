//
// Created by admin on 2019/11/21.
//

#ifndef INC_698SP_CL_COLLECTIONMONITORINGCLASSOBJECT_H
#define INC_698SP_CL_COLLECTIONMONITORINGCLASSOBJECT_H

#include <QDialog>
#include "QDebug"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include "ui_CollectionMonitoringClassObject.h"

namespace Ui {
    class FormCOLLECTIONMONITORINGCLASSOBJECT;
}

class CollectionMonitoringClass : public QDialog {
Q_OBJECT
public:
    explicit CollectionMonitoringClass(QWidget *parent = nullptr);

public slots:

    void sendmessage();

    void analysis6012();

    void analysis6014();

    void analysis601C();

signals:

    void send_message(QList<QString>);


private:
    Ui::FormCOLLECTIONMONITORINGCLASSOBJECT *ui;
};


#endif //INC_698SP_CL_COLLECTIONMONITORINGCLASSOBJECT_H
