#ifndef INC_698SP_CL_MESSAGECOMPOSE_H
#define INC_698SP_CL_MESSAGECOMPOSE_H

#include <QtCore>
#include <QDialog>
#include<vector>
#include "iostream"

namespace Ui
{
    class MESSAGECOMPOSEForm;
}

class MessageCompose : public QDialog
{
Q_OBJECT
public:
    explicit MessageCompose(QWidget *parent = nullptr);

private:
    Ui::MESSAGECOMPOSEForm *ui;

public slots:

    void inset_line();

    void delLine();

    void done_save();

    void add_line();

    void add_delay();

    void para_init();

    void data_init();

    void compare();

    void save_place();
};


#endif //INC_698SP_CL_MESSAGECOMPOSE_H


