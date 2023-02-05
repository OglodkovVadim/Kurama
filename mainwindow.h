#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "explorer.h"
#include <QVBoxLayout>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    Explorer* findExplorer(const Explorer*);
    Explorer* findNextExplorer(const Explorer*);
    Explorer* findPreviousExplorer(const Explorer*);

public slots:
    void getSignal(const Explorer *, const bool);
    void addFileSlot(const Explorer*);

private slots:
    void on_toolButton_clicked();

private:
    Ui::MainWindow *ui;

    QVector<Explorer*> arrExplorer;
    QPushButton arr[30];
    QWidget* contents;
    QVBoxLayout* contentsLayout;

    int height;
    int countExpl = 0;
};
#endif // MAINWINDOW_H
