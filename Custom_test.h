//
// Created by admin on 16/7/2019.
//

#ifndef INC_698SP_CL_CUSTOM_TEST_H
#define INC_698SP_CL_CUSTOM_TEST_H

#include <QtCore>
#include <QString>
#include <QDialog>
#include <ui_Custom_test.h>

namespace Ui
{
    class myCustom_test;
}
class Custom_test
        : public QDialog
{
Q_OBJECT
public:
    explicit Custom_test(QString add, QWidget *parent = nullptr);

private:
    Ui::myCustom_test *ui;
};


#endif //INC_698SP_CL_CUSTOM_TEST_H
