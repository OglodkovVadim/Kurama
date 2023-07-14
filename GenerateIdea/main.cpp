#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
//    w.showFullScreen();
    w.showMaximized();

    QPlainTextEdit* plainText = new QPlainTextEdit(&w);
    plainText->setGeometry(w.x(), -15, w.width(), QApplication::primaryScreen()->size().height()+30);
    plainText->setPlaceholderText("Wording here ...");
    plainText->show();

    QToolButton* close = new QToolButton(&w);
    close->setText("X");
    close->setGeometry(QApplication::primaryScreen()->size().width() - close->width() - 10,
                        5, close->width(), close->height());
    close->show();

    QToolButton* hide = new QToolButton(&w);
    hide->setText("-");
    hide->setGeometry(QApplication::primaryScreen()->size().width() - hide->width() - 50,
                        5, close->width(), hide->height());
    hide->show();

    MainWindow::connect(close, SIGNAL(clicked()), &w, SLOT(on_close_clicked_slot()));
    MainWindow::connect(hide, SIGNAL(clicked()), &w, SLOT(on_hide_clicked_slot()));

    w.setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    w.show();

    return a.exec();
}

void MainWindow::on_close_clicked_slot()
{
    this->close();
}

void MainWindow::on_hide_clicked_slot()
{
    this->showMinimized();
}
