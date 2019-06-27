#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "serial.h"
#include <QList>
#include <QDebug>
#include <QString>
#include <time.h>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    bool analysis(QString a);

    ~MainWindow() override;

    QString revert_add;

    typedef struct {
        QString PIIDACD;
        QString OAD;
        QString GET_RESULT_TYPE;
        QString DATA;
    } GET_RESPOND_NORMAL;

private:
    Ui::MainWindow *ui;
    Serial *serial;
signals:


public slots:

    void show_message_send(QString);

    void show_message_receive(QString);

    void about();

    void serial_config();

    void send_find_add();
};

#endif // MAINWINDOW_H
