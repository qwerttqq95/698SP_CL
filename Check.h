//
// Created by admin on 30/7/2019.
//

#ifndef INC_698SP_CL_CHECK_H
#define INC_698SP_CL_CHECK_H

#include <QDialog>
#include <QDebug>
#include <QtGui/QStandardItem>
#include <QtWidgets/QDirModel>

namespace Ui
{
    class CheckDialog;
}

class Check : public QDialog
{
Q_OBJECT
public:
    explicit Check(QString add, QWidget *parent = nullptr);


    QString add_;
private:
    Ui::CheckDialog *ui;
};


#endif //INC_698SP_CL_CHECK_H
