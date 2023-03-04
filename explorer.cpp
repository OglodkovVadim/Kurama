#include "explorer.h"
#include "ui_explorer.h"

Explorer::Explorer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Explorer)
{
    ui->setupUi(this);
}

Explorer::~Explorer()
{
    delete ui;
}

Folder* Explorer::findFolder(const Folder* exp)
{
    for (auto& var : arrFolder)
        if (exp == var)
            return var;

    return nullptr;
}

Folder* Explorer::findNextFolder(const Folder* folder)
{
    for (int i = 0; i < arrFolder.size(); i++)
        if (arrFolder[i] == folder && (i+1) < arrFolder.size())
            return arrFolder[i+1];

    return nullptr;
}

Folder* Explorer::findPreviousFolder(const Folder* exp)
{
    for (int i = 0; i < arrFolder.size(); i++)
        if (arrFolder[i] == exp && i != 0)
            return arrFolder[i-1];

    return nullptr;
}

void Explorer::addFileSlot(const Folder* folder)
{
    ui->scrollAreaWidgetContents->setGeometry(ui->scrollAreaWidgetContents->x(), ui->scrollAreaWidgetContents->y(),
                                              ui->scrollAreaWidgetContents->width(), ui->scrollAreaWidgetContents->height() + 60);
    while (findNextFolder(folder) != nullptr) {
        findNextFolder(folder)->setGeometry(findNextFolder(folder)->geometry().x(), folder->geometry().y() + folder->geometry().height(),
                                           findNextFolder(folder)->geometry().width(), findNextFolder(folder)->geometry().height());
        folder = findNextFolder(folder);
    }
}

void Explorer::getSignal(const Folder* folder, const bool checkHide)
{
    if (checkHide) {
        ui->scrollAreaWidgetContents->setGeometry(ui->scrollAreaWidgetContents->x(), ui->scrollAreaWidgetContents->y(),
                                                  ui->scrollAreaWidgetContents->width(), ui->scrollAreaWidgetContents->height() - folder->getWidget()->height());
        findFolder(folder)->changeHeightEscape();
        while (findNextFolder(folder) != nullptr) {
            findNextFolder(folder)->setGeometry(findNextFolder(folder)->geometry().x(), folder->geometry().y() + folder->geometry().height(),
                                               findNextFolder(folder)->geometry().width(), findNextFolder(folder)->geometry().height());
            folder = findNextFolder(folder);
        }
    }
    else {
        findFolder(folder)->changeHeightShow();
        ui->scrollAreaWidgetContents->setGeometry(ui->scrollAreaWidgetContents->x(), ui->scrollAreaWidgetContents->y(),
                                                  ui->scrollAreaWidgetContents->width(), ui->scrollAreaWidgetContents->height() + folder->getWidget()->height());
        while (findNextFolder(folder) != nullptr) {
            findNextFolder(folder)->setGeometry(findNextFolder(folder)->geometry().x(), folder->geometry().y() + folder->geometry().height(),
                                               findNextFolder(folder)->geometry().width(), findNextFolder(folder)->geometry().height());
            folder = findNextFolder(folder);
        }
    }
}

void Explorer::removeFileSlot(const Folder* folder)
{
    while (findNextFolder(folder) != nullptr) {
        findNextFolder(folder)->setGeometry(findNextFolder(folder)->geometry().x(), folder->geometry().y() + folder->geometry().height(),
                                           findNextFolder(folder)->geometry().width(), findNextFolder(folder)->geometry().height());
        folder = findNextFolder(folder);
    }
    ui->scrollAreaWidgetContents->setGeometry(ui->scrollAreaWidgetContents->x(), ui->scrollAreaWidgetContents->y(),
                                              ui->scrollAreaWidgetContents->width(), ui->scrollAreaWidgetContents->height() - folder->getQLabel()->height() * 1.5);
}

void Explorer::on_toolButton_clicked()
{
    arrFolder.append(new Folder(ui->scrollAreaWidgetContents));
    arrFolder.back()->show();

    if (arrFolder.size() > 1) {
        arrFolder.back()->setStandartGeometry();
        arrFolder.back()->setGeometry(arrFolder.back()->geometry().x(),
                                        findPreviousFolder(arrFolder.back())->geometry().y() + findPreviousFolder(arrFolder.back())->geometry().height(),
                                        arrFolder.back()->geometry().width(), arrFolder.back()->geometry().height());
    }
    else
        arrFolder.back()->setStandartGeometry();

    ui->scrollAreaWidgetContents->setGeometry(ui->scrollAreaWidgetContents->x(), ui->scrollAreaWidgetContents->y(), ui->scrollAreaWidgetContents->width(),
                                              ui->scrollAreaWidgetContents->height() + arrFolder.back()->geometry().height());

    connect(arrFolder.back(), SIGNAL(escapeChange(const Folder*, bool)), this, SLOT(getSignal(const Folder*, bool)));
    connect(arrFolder.back(), SIGNAL(addFile(const Folder*)), this, SLOT(addFileSlot(const Folder*)));
    connect(arrFolder.back(), SIGNAL(removeFile(const Folder*)), this, SLOT(removeFileSlot(const Folder*)));
    connect(arrFolder.back(), SIGNAL(clickedFile(const QPushButton*)), this, SLOT(clickedPushButton(const QPushButton*)));
}

//bool Explorer::findSameText(const QPushButton* pb)
//{
//    for (int i = 0; i < ui->tabWidget->count(); i++)
//        if (ui->tabWidget->tabText(i) == pb->text())
//            return false;

//    return true;
//}

void Explorer::clickedPushButton(const QPushButton* pb)
{
//    ui->tabWidget->show();
//    if (findSameText(pb)) {
//        ui->tabWidget->addTab(new QPlainTextEdit(), pb->text());

//    }
//    else {
        QMessageBox messageBox;
        messageBox.critical(0,"Error","An error has occured !");
        messageBox.setFixedSize(500,200);
//    }

}

//void Explorer::on_tabWidget_tabCloseRequested(int index)
//{
//    ui->tabWidget->removeTab(index);
//    if (ui->tabWidget->count() == 0)
//        ui->tabWidget->hide();
//}
