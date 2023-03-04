#ifndef EXPLORER_H
#define EXPLORER_H

#include <QWidget>
#include <QPushButton>
#include <QLayout>
#include <QPropertyAnimation>
#include <QLabel>
#include <QGraphicsScene>
#include <QGraphicsProxyWidget>

#include <namefile.h>

namespace Ui {
class Explorer;
}

class Explorer : public QWidget
{
    Q_OBJECT

public:
    explicit Explorer(QWidget *parent = nullptr);
    ~Explorer();

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
    void on_toolButton_clicked();
    void remove_File();
    void on_toolButton_2_clicked();
    void clicked_File();

    void on_addFolder_clicked();
    void acceptFileNameSlot(const NameFile*);

signals:
    void escapeChange(const Explorer* exp, const bool);
    void addFile(const Explorer*);
    void removeFile(const Explorer*);
    void clickedFile(const QPushButton*);

private:
    Ui::Explorer *ui;

    QVector<QPushButton*> arrPb;
    QVector<QToolButton*> arrTbRemoveFile;
    QVector<Explorer*> arrLocalExplorer;
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

#endif // EXPLORER_H
