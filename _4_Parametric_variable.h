//
// Created by admin on 2019/9/27.
//

#ifndef INC_698SP_CL__4_PARAMETRIC_VARIABLE_H
#define INC_698SP_CL__4_PARAMETRIC_VARIABLE_H


#include "QDebug"
#include "ui__4_Parametric_variable.h"
#include <QDialog>
#include "QStandardItemModel"


namespace Ui
{
    class _4_Parametric_variableForm;
}

class _4_Parametric_variable : public QDialog
{
Q_OBJECT
public:
    explicit _4_Parametric_variable(QWidget *parent = nullptr);

    QStandardItemModel *model;
private:
    Ui::_4_Parametric_variableForm *ui;
};


#endif //INC_698SP_CL__4_PARAMETRIC_VARIABLE_H
