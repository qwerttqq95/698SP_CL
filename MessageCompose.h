#ifndef INC_698SP_CL_MESSAGECOMPOSE_H
#define INC_698SP_CL_MESSAGECOMPOSE_H

#include <QtCore>
#include <QDialog>

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
};


#endif //INC_698SP_CL_MESSAGECOMPOSE_H


