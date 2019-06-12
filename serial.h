#ifndef INC_698SP_CL_SERIAL_H
#define INC_698SP_CL_SERIAL_H

#include <QDialog>

namespace Ui {
    class Dialog;
}
class Serial : public QDialog {
    Q_OBJECT
public:
    explicit Serial(QWidget *parent = nullptr);
    ~Serial() override;

private:
    Ui::Dialog *ui;
};


#endif //INC_698SP_CL_SERIAL_H
