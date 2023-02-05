#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->scrollArea->setWidgetResizable(false);
    ui->scrollAreaWidgetContents->setGeometry(ui->scrollAreaWidgetContents->x(), ui->scrollAreaWidgetContents->y(), ui->scrollAreaWidgetContents->width(), 0);
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
    findExplorer(exp)->setGeometry(exp->geometry().x(), exp->geometry().y(), exp->geometry().width(), exp->geometry().height() + exp->getQLabel()->height() * 2);
    ui->scrollAreaWidgetContents->setGeometry(ui->scrollAreaWidgetContents->x(), ui->scrollAreaWidgetContents->y(), ui->scrollAreaWidgetContents->width(), ui->scrollAreaWidgetContents->height() + exp->getQLabel()->height() * 2);
    while (findNextExplorer(exp) != nullptr) {
        findNextExplorer(exp)->changeHeight();
        exp = findNextExplorer(exp);
    }
}

void MainWindow::getSignal(const Explorer* exp, const bool checkHide)
{
    if (checkHide) {
        Explorer::animationWidget(*findExplorer(exp), exp->geometry().x(), exp->geometry().y(), exp->geometry().width(), exp->getQLabel()->height() * 1.25, QEasingCurve::Linear, 200);
    }
    else {
        Explorer::animationWidget(*findExplorer(exp), exp->geometry().x(), exp->geometry().y(), exp->geometry().width(), height, QEasingCurve::Linear, 200);
    }

    if (findNextExplorer(exp) == nullptr) {
        if (checkHide)
            Explorer::animationWidget(*findExplorer(exp), exp->geometry().x(), exp->geometry().y(), exp->geometry().width(), exp->getQLabel()->height() * 1.25, QEasingCurve::Linear, 200);
        else
            Explorer::animationWidget(*findExplorer(exp), exp->geometry().x(), exp->geometry().y(), exp->geometry().width(), height, QEasingCurve::Linear, 200);
    }

    while (findNextExplorer(exp) != nullptr) {
        if (checkHide) {
            Explorer::animationWidget(*findNextExplorer(exp), exp->geometry().x(), exp->geometry().y() + exp->getQLabel()->height() * 1.25, exp->geometry().width(), height, QEasingCurve::Linear, 200);
            exp = findNextExplorer(exp);
        }
        else {
            Explorer::animationWidget(*findNextExplorer(exp), exp->geometry().x(), exp->geometry().y() + height, exp->geometry().width(), height, QEasingCurve::Linear, 200);
            exp = findNextExplorer(exp);
        }

    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_toolButton_clicked()
{
    arrExplorer.append(new Explorer(ui->scrollAreaWidgetContents));
    arrExplorer.back()->show();

    if (arrExplorer.size() > 1) {
        arrExplorer.back()->setStandartGeometry();
        arrExplorer.back()->setGeometry(arrExplorer.back()->geometry().x(), findPreviousExplorer(arrExplorer.back())->geometry().y() + findPreviousExplorer(arrExplorer.back())->geometry().height(), arrExplorer.back()->geometry().width(), arrExplorer.back()->geometry().height());
    }
    else
        arrExplorer.back()->setStandartGeometry();

    ui->scrollAreaWidgetContents->setGeometry(ui->scrollAreaWidgetContents->x(), ui->scrollAreaWidgetContents->y(), ui->scrollAreaWidgetContents->width(), ui->scrollAreaWidgetContents->height() + arrExplorer.back()->geometry().height());

    connect(arrExplorer.back(), SIGNAL(escapeChange(const Explorer*, bool)), this, SLOT(getSignal(const Explorer*, bool)));
    connect(arrExplorer.back(), SIGNAL(addFile(const Explorer*)), this, SLOT(addFileSlot(const Explorer*)));
}
