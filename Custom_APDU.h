#ifndef INC_698SP_CL_CUSTOM_APDU_H
#define INC_698SP_CL_CUSTOM_APDU_H

#include <QDialog>
#include <QDebug>

namespace Ui
{
    class myDialog;
}
class Custom_APDU : public QDialog
{
Q_OBJECT
public:
    explicit Custom_APDU(QWidget *parent = nullptr);


public slots:

    void send();

signals:

    void send_write(QList<QString>);

private:
    Ui::myDialog *ui;
};


#endif //INC_698SP_CL_CUSTOM_APDU_H
