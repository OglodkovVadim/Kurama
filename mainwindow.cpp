#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->scrollArea->setWidgetResizable(false);
    ui->scrollAreaWidgetContents->setGeometry(ui->scrollAreaWidgetContents->x(), ui->scrollAreaWidgetContents->y(), ui->scrollAreaWidgetContents->width(), 0);
    ui->tabWidget->hide();
    ui->tabWidget->removeTab(0);
}

Explorer* MainWindow::findExplorer(const Explorer* exp)
{
    for (auto& var : arrExplorer)
        if (exp == var)
            return var;

    return nullptr;
}

Explorer* MainWindow::findNextExplorer(const Explorer* exp)
{
    for (int i = 0; i < arrExplorer.size(); i++)
        if (arrExplorer[i] == exp && (i+1) < arrExplorer.size())
            return arrExplorer[i+1];

    return nullptr;
}

Explorer* MainWindow::findPreviousExplorer(const Explorer* exp)
{
    for (int i = 0; i < arrExplorer.size(); i++)
        if (arrExplorer[i] == exp && i != 0)
            return arrExplorer[i-1];

    return nullptr;
}

void MainWindow::addFileSlot(const Explorer* exp)
{
    //findExplorer(exp)->changeHeightWidget();
    ui->scrollAreaWidgetContents->setGeometry(ui->scrollAreaWidgetContents->x(), ui->scrollAreaWidgetContents->y(),
                                              ui->scrollAreaWidgetContents->width(), ui->scrollAreaWidgetContents->height() + exp->getQLabel()->height() * 1.5);
    while (findNextExplorer(exp) != nullptr) {
        findNextExplorer(exp)->setGeometry(findNextExplorer(exp)->geometry().x(), exp->geometry().y() + exp->geometry().height(),
                                           findNextExplorer(exp)->geometry().width(), findNextExplorer(exp)->geometry().height());
        exp = findNextExplorer(exp);
    }
}

void MainWindow::getSignal(const Explorer* exp, const bool checkHide)
{
    if (checkHide) {
        ui->scrollAreaWidgetContents->setGeometry(ui->scrollAreaWidgetContents->x(), ui->scrollAreaWidgetContents->y(),
                                                  ui->scrollAreaWidgetContents->width(), ui->scrollAreaWidgetContents->height() - exp->getWidget()->height());
        findExplorer(exp)->changeHeightEscape();
        while (findNextExplorer(exp) != nullptr) {
            findNextExplorer(exp)->setGeometry(findNextExplorer(exp)->geometry().x(), exp->geometry().y() + exp->geometry().height(),
                                               findNextExplorer(exp)->geometry().width(), findNextExplorer(exp)->geometry().height());
            exp = findNextExplorer(exp);
        }
    }
    else {
        findExplorer(exp)->changeHeightShow();
        ui->scrollAreaWidgetContents->setGeometry(ui->scrollAreaWidgetContents->x(), ui->scrollAreaWidgetContents->y(),
                                                  ui->scrollAreaWidgetContents->width(), ui->scrollAreaWidgetContents->height() + exp->getWidget()->height());
        while (findNextExplorer(exp) != nullptr) {
            findNextExplorer(exp)->setGeometry(findNextExplorer(exp)->geometry().x(), exp->geometry().y() + exp->geometry().height(),
                                               findNextExplorer(exp)->geometry().width(), findNextExplorer(exp)->geometry().height());
            exp = findNextExplorer(exp);
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::removeFileSlot(const Explorer* exp, const QWidget* wid)
{
    while (findNextExplorer(exp) != nullptr) {
        findNextExplorer(exp)->setGeometry(findNextExplorer(exp)->geometry().x(), exp->geometry().y() + exp->geometry().height(),
                                           findNextExplorer(exp)->geometry().width(), findNextExplorer(exp)->geometry().height());
        /*setGeometry(findNextExplorer(exp)->geometry().x(), findNextExplorer(exp)->geometry().y() - wid->height() * 1.5,
         *  findNextExplorer(exp)->geometry().width(), findNextExplorer(exp)->geometry().height());*/
        exp = findNextExplorer(exp);
    }
    ui->scrollAreaWidgetContents->setGeometry(ui->scrollAreaWidgetContents->x(), ui->scrollAreaWidgetContents->y(),
                                              ui->scrollAreaWidgetContents->width(), ui->scrollAreaWidgetContents->height() - wid->height());
}

void MainWindow::on_toolButton_clicked()
{
    arrExplorer.append(new Explorer(ui->scrollAreaWidgetContents));
    arrExplorer.back()->show();

    if (arrExplorer.size() > 1) {
        arrExplorer.back()->setStandartGeometry();
        arrExplorer.back()->setGeometry(arrExplorer.back()->geometry().x(),
                                        findPreviousExplorer(arrExplorer.back())->geometry().y() + findPreviousExplorer(arrExplorer.back())->geometry().height() * 1.25,
                                        arrExplorer.back()->geometry().width(), arrExplorer.back()->geometry().height());
    }
    else
        arrExplorer.back()->setStandartGeometry();

    ui->scrollAreaWidgetContents->setGeometry(ui->scrollAreaWidgetContents->x(), ui->scrollAreaWidgetContents->y(), ui->scrollAreaWidgetContents->width(),
                                              ui->scrollAreaWidgetContents->height() + arrExplorer.back()->geometry().height() * 1.25);

    connect(arrExplorer.back(), SIGNAL(escapeChange(const Explorer*, bool)), this, SLOT(getSignal(const Explorer*, bool)));
    connect(arrExplorer.back(), SIGNAL(addFile(const Explorer*)), this, SLOT(addFileSlot(const Explorer*)));
    connect(arrExplorer.back(), SIGNAL(removeFile(const Explorer*, const QWidget*)), this, SLOT(removeFileSlot(const Explorer*, const QWidget*)));
    connect(arrExplorer.back(), SIGNAL(clickedFile(const QPushButton*)), this, SLOT(clickedPushButton(const QPushButton*)));
}

bool MainWindow::findSameText(const QPushButton* pb)
{
    for (int i = 0; i < ui->tabWidget->count(); i++)
        if (ui->tabWidget->tabText(i) == pb->text())
            return false;

    return true;
}

void MainWindow::clickedPushButton(const QPushButton* pb)
{
    ui->tabWidget->show();
    if (findSameText(pb))
        ui->tabWidget->addTab(new QWidget(), pb->text());
    else {
        QMessageBox messageBox;
        messageBox.critical(0,"Error","An error has occured !");
        messageBox.setFixedSize(500,200);
    }

}

void MainWindow::on_tabWidget_tabCloseRequested(int index)
{
    ui->tabWidget->removeTab(index);
    if (ui->tabWidget->count() == 0)
        ui->tabWidget->hide();
}

