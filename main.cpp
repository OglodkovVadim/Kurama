#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    qDebug() << QApplication::primaryScreen()->size().height();
    qDebug() << QApplication::primaryScreen()->size().width();
    w.show();
    return a.exec();
}

