#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->menubar->hide();
//    ui->plainTextEdit->hide();
//    ui->plainTextEdit->setGeometry(QRect(main_x, main_y, main_width, main_height));

}

MainWindow::~MainWindow()
{
    delete ui;
}

