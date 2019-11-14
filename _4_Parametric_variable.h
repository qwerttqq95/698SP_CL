//
// Created by admin on 2019/9/27.
//

#ifndef INC_698SP_CL__4_PARAMETRIC_VARIABLE_H
#define INC_698SP_CL__4_PARAMETRIC_VARIABLE_H


#include "QDebug"
#include "ui__4_Parametric_variable.h"
#include <QDialog>
#include "QStandardItemModel"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

namespace Ui
{
    class _4_Parametric_variableForm;
}

class _4_Parametric_variable : public QDialog
{
Q_OBJECT
public:
    _4_Parametric_variable(QWidget *parent = nullptr);

    void analy_database(QTreeWidgetItem *,QString);

    void att();

    void act();

    typedef struct
    {
        QTreeWidgetItem *left;
        QTreeWidgetItem *right;
    } PARAMETRIC;

    typedef struct
    {
        QString ItemName;
        QString TypeCode;
    }MENBER_ARRAY;

    typedef  struct {
        QTreeWidgetItem* pre_item;
        QString num;
    }MEMBER_PRE;

    QList<PARAMETRIC> Item_box;//左右对应

    QList<MENBER_ARRAY> ARRAY_box;//array处理

    QList<MEMBER_PRE> pre_stat;//array状态

private:
    Ui::_4_Parametric_variableForm *ui;
    bool flag = false;

signals:
    void send_write(QList<QString>);

public slots:

    void set();

    void read();

    void action();

    void add_item(QTreeWidgetItem *, QTreeWidgetItem *);

    void deal_box_att(QTreeWidgetItem *);

    void deal_box_act(QTreeWidgetItem *);

    static void EditFileFilter(QTreeWidgetItem *, int);

    void itemchanged(QTreeWidgetItem*,QTreeWidgetItem*);

    void check_cancel();

    void list_clear();


};


#endif //INC_698SP_CL__4_PARAMETRIC_VARIABLE_H
