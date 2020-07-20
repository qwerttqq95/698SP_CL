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
#include <QtWidgets/QTextEdit>
#include "ui_CollectionMonitoringClassObject.h"
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMessageBox>
#include "QTimer"

extern int globe_flag_6012;


namespace Ui {
    class FormCOLLECTIONMONITORINGCLASSOBJECT;
}


class CollectionMonitoringClass : public QDialog {
Q_OBJECT
public:
    explicit CollectionMonitoringClass(QWidget *parent = nullptr);

    void Tab_2_init();

    void Tab_3_init();

    void Tab_4_init();

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

    void method_4();

    void method_5();

    void method_6();

    void method_7();

    void method_8();

    void method_9();

    void method_10();

    void getData();

    void ClickedRead();

    void tab_3_add();

    void tab_3_del();

    void tab_3_clear();

    void tab_3_input();

    void tab_3_output();

    void tab_3_generate();

    void tab_3_generate_xml();

    bool tab_3_compose6012(QStringList *);

    void tab_3_send();

    void tab_4_add();

    void tab_4_add_froz();

    void tab_4_del();

    void tab_4_clear();

    void tab_4_input();

    void tab_4_output();

    void tab_4_generate();

    bool tab_4_compose6014(QStringList *);

    void tab_4_send();

    void tab_4_generate_xml();

signals:

    void send_message(QList<QString>);

private:
    Ui::FormCOLLECTIONMONITORINGCLASSOBJECT *ui;
    QTableWidget *compose6012;
    QTableWidget *compose6014;
    QTableWidget *compose601C;
};


#endif //INC_698SP_CL_COLLECTIONMONITORINGCLASSOBJECT_H
