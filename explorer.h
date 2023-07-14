#ifndef EXPLORER_H
#define EXPLORER_H

#include <QWidget>
#include <QMessageBox>
#include "folder.h"

namespace Ui {
class Explorer;
}

class Explorer : public QWidget
{
    Q_OBJECT

public:
    explicit Explorer(QWidget *parent = nullptr);
    ~Explorer();

    Explorer();

    Folder* findFolder(const Folder*);
    Folder* findNextFolder(const Folder*);
    Folder* findPreviousFolder(const Folder*);

//    bool findSameText(const QPushButton *);

private:
    Ui::Explorer *ui;

    QVector<Folder*> arrFolder;
    QWidget* contents;
    QVBoxLayout* contentsLayout;

    int height;
    int countExpl = 0;

public slots:
    void getSignal(const Folder *, const bool);
    void addFileSlot(const Folder*);
    void removeFileSlot(const Folder*);
    void clickedPushButton(const QPushButton*);

private slots:
    void on_toolButton_clicked();
//    void on_accept_clicked();
//    void on_tabWidget_tabCloseRequested(int index);

};

#endif // EXPLORER_H
