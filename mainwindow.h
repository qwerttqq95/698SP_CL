#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#define WIN32_LEAN_AND_MEAN
#include "serial.h"
#include "Custom_APDU.h"
#include <QMainWindow>
#include "CollectionMonitoringClassObject.h"
#include "Analysis.h"
#include <QList>
#include <QDebug>
#include <QString>
#include <time.h>
#include <fstream>
#include <Check.h>
#include "QMdiSubWindow"
#include "_4_Parametric_variable.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include "Online.h"
#include "SaveLog.h"
#include "MeterArchives.h"
#define DATA_NULL                        0
#define DATA_ARRAY                        1
#define DATA_STRUCT                    2
#define DATA_BOOL                        3
#define DATA_BITSTRING                    4
#define DATA_DOUBLE_LONG                5
#define DATA_DOUBLE_LONG_UNSIGNED        6
#define DATA_OCT_STRING                9
#define DATA_VISIBLE_STRING            10
#define DATA_UTF8_STRING                12
#define DATA_INTEGER                    15
#define DATA_LONG                        16
#define DATA_UNSIGNED                    17
#define DATA_LONG_UNSIGNED                18
#define DATA_LONG64                        20
#define DATA_LONG64_UNSIGNED            21
#define DATA_ENUM                        22
#define DATA_FLOAT32                    23
#define DATA_FLOAT64                    24
#define DATA_DATE_TIME                    25
#define DATA_DATE                        26
#define DATA_TIME                        27
#define DATA_DATE_TIME_S                28
#define DATA_OI                            80
#define DATA_OAD                        81
#define DATA_ROAD                        82
#define DATA_OMD                        83
#define DATA_TI                            84
#define DATA_TSA                        85
#define DATA_MAC                        86
#define DATA_RN                            87
#define DATA_REGION                        88
#define DATA_SCALER_UNIT                89
#define DATA_RSD                        90
#define DATA_CSD                        91
#define DATA_MS                            92
#define DATA_SID                        93
#define DATA_SID_MAC                    94
#define DATA_COMDCB                        95
#define DATA_RCSD                        96


namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
Q_OBJECT

public:
    int current = 0;
    int times = 0;
    QSqlDatabase database;

    QMdiSubWindow *Custom_point;
    QMdiSubWindow *MeterArchive_point;
    QMdiSubWindow *Parametric_variable_point;
    QMdiSubWindow *CollectionMonitoring_point;

    QString DARType(int);

    explicit MainWindow(QWidget *parent = nullptr);

    void closeEvent(QCloseEvent *event);


    QString analysis(QString a);

    void Communication_parameters();

    QString deal_data(QStringList);

    ~MainWindow() override;

    QString revert_add;

    typedef struct
    {
        QString PIIDACD;
        QString LINK_REQUSET_TYPE;
        QString HEART_BEAT_INTERVAL;
        QString REQUEST_TIMEDATE_TIME;
    } LINK_REQUEST;

    typedef struct
    {
        QString PIIDACD;
        QString OAD;
        QString GET_RESULT_TYPE;
        QStringList DATA;
    } GET_RESPOND_NORMAL;

    typedef struct
    {
        QString PIIDACD;
        QString is_last_frame;
        QString slicing_index;
        QString GetResponseNextType;
        QString SequenceOf_ResultNormal;
        QString OAD;
        QString GET_RESULT_TYPE;
        QStringList DATA;
    } GetResponseNext;

    typedef struct
    {
        QString PIIDACD;
        QString SequenceOfLen;
        QString OAD;
        QString RCSD;
    } ReportNotificationRecordList;

    typedef struct
    {
        QString PIIDACD;
        QString SequenceOfLen;
        QString OAD;
        QString GetResultType;
    } ReportNotificationList;
private:
    SaveLog *logging;
    Ui::MainWindow *ui;
    Serial *serial;
    Custom_APDU *Custom;
    MeterArchives *MeterArchive;
    Check *check;
    Analysis *analy;
    CollectionMonitoringClass *CollectionMonitoring;
    _4_Parametric_variable *Parametric_variable;
    Online *online;

signals:

    void send_analysis(QString);

    void deal_with_meter(QList<QString>);

    void deal_6012(QList<QString>);
    void deal_6014(QList<QString>);
    void deal_601C(QList<QString>);

public slots:

    void move_Cursor();

    void show_message_send(QList<QString>);

    void show_message_receive(QString);

    void set_ip();

    void set_add();

    void about();

    void serial_config();

    void custom();

    void open_MeterArchives();

    void send_find_add();

    void custom_test();

    void compare(QString);

    void function();

    void open_attach();

    void clear_view();

    void add_change_event(QString);

    void double_click_analysis(const QModelIndex &index);

    void op_analy();

    void copy_message();

    void OnlineModel();

};

#endif // MAINWINDOW_H
