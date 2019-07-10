#ifndef ADDMETER_H
#define ADDMETER_H

#include <QtCore>
#include <QString>
#include <QDialog>


namespace Ui {
    class myAddMeter;
}

class AddMeters : public QDialog {
Q_OBJECT
public:
    explicit AddMeters(QWidget *parent = nullptr);

public slots:

    void ok();

private:
    Ui::myAddMeter *ui;
};

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

#endif
