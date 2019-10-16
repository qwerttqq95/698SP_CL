///参变量(4)

#include "_4_Parametric_variable.h"


_4_Parametric_variable::_4_Parametric_variable(QWidget *parent) : QDialog(parent),
                                                                  ui(new Ui::_4_Parametric_variableForm)
{
    ui->setupUi(this);
    model = new QStandardItemModel(nullptr);

}

