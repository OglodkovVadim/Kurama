#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "explorer.h"
#include <QVBoxLayout>
#include <QMessageBox>

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

    bool findSameText(const QPushButton *);

public slots:
    void getSignal(const Explorer *, const bool);
    void addFileSlot(const Explorer*);
    void removeFileSlot(const Explorer*);
    void clickedPushButton(const QPushButton*);

private slots:
    void on_toolButton_clicked();

    void on_tabWidget_tabCloseRequested(int index);

private:
    Ui::MainWindow *ui;

    QVector<Explorer*> arrExplorer;
    QWidget* contents;
    QVBoxLayout* contentsLayout;

    int height;
    int countExpl = 0;
};
#endif // MAINWINDOW_H
