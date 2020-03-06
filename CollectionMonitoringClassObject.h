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

    typedef struct {
        int ID;
        QString freq;
        QString style;
        int No;
        QString start_time;
        QString end_time;
        QString delay;
        QString prio;
        QString stat;
        QString run_style;
        QString meter_times;
    } analy_6012;

    typedef struct {
        int No;
        QString deep;
        QString coll_style;
        QString CSD;
        int METERGATHER;
        int SAVEDTIME;
    } analy_6014;

    typedef struct {
        int No;
        QString report_way;
        QString timeout;
        QString report_time;
        QString report_times;
        QString report_content;
    } analy_601C;
public slots:

    void sendmessage();

    void analysis6012(QList<QString>);

    void analysis6014(QList<QString>);

    void analysis601C(QList<QString>);

    void clearlist();


signals:

    void send_message(QList<QString>);


private:
    Ui::FormCOLLECTIONMONITORINGCLASSOBJECT *ui;

};


#endif //INC_698SP_CL_COLLECTIONMONITORINGCLASSOBJECT_H
