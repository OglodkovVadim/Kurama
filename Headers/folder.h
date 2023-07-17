#ifndef FOLDER_H
#define FOLDER_H

#include <QWidget>
#include <QPushButton>
#include <QLayout>
#include <QPropertyAnimation>
#include <QLabel>
#include <QGraphicsScene>
#include <QGraphicsProxyWidget>

#include "namefile.h"

namespace Ui {
class Folder;
}

class Folder : public QWidget
{
    Q_OBJECT

public:
    explicit Folder(QWidget *parent = nullptr);
    ~Folder();

    static void animationWidget(QWidget&, double, double, double, double, QEasingCurve::Type, int);

    QLabel* getQLabel() const;

    bool getStatus() const;

    void changeNextPosAdd();

    void changeNextPosRemove();

    void setStandartGeometry();

    void changeHeightWidget();

    void changeHeightEscape();

    void changeHeightShow();

    QWidget* getWidget() const;

    QPushButton* getPushButton() const;

    int getCountFiles() const;

private slots:
    void on_addFile_clicked();
    void remove_File();
    void on_escape_clicked();
    void clicked_File();

    void on_addFolder_clicked();
    void acceptFileNameSlot(const NameFile*);

signals:
    void escapeChange(const Folder* exp, const bool);
    void addFile(const Folder*);
    void removeFile(const Folder*);
    void clickedFile(const QPushButton*);

private:
    Ui::Folder *ui;

    QVector<QPushButton*> arrPb;
    QVector<QToolButton*> arrTbRemoveFile;
    QVector<Folder*> arrLocalExplorer;
    QVector<QWidget*> arrWidButt;
    QVector<QHBoxLayout*> arrLayout;

    int x;
    int y;
    int width;
    int height;

    bool checkHide;
    int count = 0;

    QString fileName;
};

#endif // FOLDER_H
