#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    ui->scrollArea->setWidgetResizable(false);
//    ui->scrollAreaWidgetContents->setGeometry(ui->scrollAreaWidgetContents->x(), ui->scrollAreaWidgetContents->y(), ui->scrollAreaWidgetContents->width(), 0);
    ui->tabWidget->hide();
    ui->tabWidget->removeTab(0);
    explorer = new Explorer(ui->widget);
}


MainWindow::~MainWindow(void)
{
    delete ui;
}
