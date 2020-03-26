#include "mainwindow.h"
#include <QApplication>
#include <QtWidgets/QStyleFactory>

int main(int argc, char *argv[])
{
    QApplication::setStyle(QStyleFactory::create("Fusion"));
    qRegisterMetaType<QList<QString> >("QList<QString>");
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
