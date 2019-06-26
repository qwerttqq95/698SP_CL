#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "serial.h"
#include <QList>
#include <QDebug>
#include <QString>


namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;


private:
    Ui::MainWindow *ui;
    Serial *serial;
signals:


public slots:
    void show_message(QString);
    void about();

    void serial_config();

    void send_find_add();
};

#endif // MAINWINDOW_H
