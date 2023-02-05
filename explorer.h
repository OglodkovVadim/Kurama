#ifndef EXPLORER_H
#define EXPLORER_H

#include <QWidget>
#include <QPushButton>
#include <QLayout>
#include <QPropertyAnimation>
#include <QLabel>


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

    void changeHeight();

    void setStandartGeometry();

    void changeHeightWidget();

    QWidget* getWidget() const;

private slots:
    void on_toolButton_clicked();
    void remove_File();
    void on_toolButton_2_clicked();

signals:
    void escapeChange(const Explorer* exp, const bool);
    void addFile(const Explorer*);

private:
    Ui::Explorer *ui;

    QVector<QPushButton*> arrPb;
    QVector<QToolButton*> arrTb;
    QVector<QWidget*> arrWidButt;
    QVector<QHBoxLayout*> arrLayout;

    int x;
    int y;
    int width;
    int height;

    bool checkHide;
};

#endif // EXPLORER_H
