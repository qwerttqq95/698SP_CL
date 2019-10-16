#include "mainwindow.h"
#include <QApplication>
#include <QMetaType>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    qRegisterMetaType<QList<QString> >("QList<QString>");
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
