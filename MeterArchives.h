//
// Created by admin on 5/7/2019.
//

#ifndef INC_698SP_CL_METERARCHIVES_H
#define INC_698SP_CL_METERARCHIVES_H

#include <QtCore>
#include <QString>
#include <QDialog>

namespace Ui {
    class myMeterArchives;
}
class MeterArchives : public QDialog {
Q_OBJECT
public:
    explicit MeterArchives(QString add, QWidget *parent = nullptr);


    typedef struct {
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

    QString add_;
    int row_count = 0;
public slots:

    void show_meter_message(QList<QString>);

    void Get_6000200();

private:
    Ui::myMeterArchives *ui;


signals:

    void send_write(QString);


};

typedef struct {
    QString value;
    QList<QString> left;
} VALUE_LEFT;

#endif //INC_698SP_CL_METERARCHIVES_H
