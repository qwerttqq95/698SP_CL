#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "serial.h"
#include <QList>
#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    Ui::MainWindow *ui;
    Serial *serial;

public slots:
    void about();
    void serial_config();
};

#endif // MAINWINDOW_H
