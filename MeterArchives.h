//
// Created by admin on 5/7/2019.
//

#ifndef INC_698SP_CL_METERARCHIVES_H
#define INC_698SP_CL_METERARCHIVES_H

#include <QtCore>
#include <QString>
#include <QDialog>
#include <AddMeter.h>
#include <QFileDialog>
#include <BasicExcel/BasicExcel.h>
#include <minwindef.h>

namespace Ui
{
    class myMeterArchives;
}
class MeterArchives : public QDialog
{
Q_OBJECT
public:
    explicit MeterArchives(QWidget *parent = nullptr);

    bool GetExcelValue(YExcel::BasicExcelCell *pCell, QString &str);


    typedef struct
    {
        QString NUM;
        QString TSA;
        QString baud_rate;
        QString meter_style;
        QString port;
        QString password;
        QString fee_count;
        QString user_style;
        QString connect_way;
        QString Rated_Voltage;
        QString Rated_Electric_current;

        QString collect_TSA;
        QString detail_num;
        QString PT;
        QString CT;

    } Archives_Configuration_Table;

    int row_count = 0;
public slots:

    void show_add();

    void show_meter_message(QList<QString>);

    void add_new(QList<QString> a);

    void select_all_checkbox();

    void Get_6000200();

    void send();

    void clearlist();

    void all();

    void output();

    void input();

    void clear_6000200();

    void del();


private:
    Ui::myMeterArchives *ui;
    AddMeters *addmeter;

signals:

    void send_write(QList<QString>);

};

typedef struct
{
    QString value;
    QList<QString> left;
} VALUE_LEFT;

#endif //INC_698SP_CL_METERARCHIVES_H
