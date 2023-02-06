#include "explorer.h"
#include "ui_explorer.h"

void Explorer::animationWidget(QWidget &widget, double x, double y, double width, double heigth, QEasingCurve::Type t, int _time)
{
    QPropertyAnimation* animation = new QPropertyAnimation(&widget, "geometry");
    animation->setDuration(_time);
    animation->setEasingCurve(t);
    animation->setEndValue(QRect(x, y, width, heigth));
    animation->start();
}

Explorer::Explorer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Explorer)
{
    ui->setupUi(this);

    x = 40;
    y = 55;
    width = 260;
    height = 50;
    checkHide = true;

    ui->widget->setGeometry(x, y, width, height);
    ui->widget->setLayout(ui->verticalLayout);
}

Explorer::~Explorer()
{
    delete ui;
}

void Explorer::on_toolButton_clicked()
{
// adding new file
    arrWidButt.append(new QWidget());
    arrPb.append(new QPushButton("New"));
    arrTb.append(new QToolButton());
    arrTb.back()->setText("-");
    arrLayout.append(new QHBoxLayout(arrWidButt.back()));
    arrLayout.back()->addWidget(arrPb.back());
    arrLayout.back()->addWidget(arrTb.back());
    ui->verticalLayout->insertWidget(0, arrWidButt.back());

// changing scroll area height

    ui->widget->setGeometry(QRect(x, y, width, ui->widget->height()+ui->label->height() * 1.25));

    if (checkHide) {
        checkHide = false;
        emit escapeChange(this, checkHide);
        ui->toolButton_2->setStyleSheet("QToolButton#toolButton_2 {image: url(:/image/arrowDown.png);} QToolButton#toolButton_2:hover {image: url(:/image/arrowDownHover.png);} QToolButton#toolButton_2:pressed {image: url(:/image/arrowDown.png);}");
    }

// connecting to mainwindow
    connect(arrTb.back(), SIGNAL(clicked()),
            this, SLOT(remove_File()));

    connect(arrPb.back(), SIGNAL(clicked()),
            this, SLOT(clicked_File()));

    emit addFile(this);

}

void Explorer::clicked_File()
{
    emit clickedFile(qobject_cast<QPushButton*>(sender()));
}

QLabel* Explorer::getQLabel() const
{
    return ui->label;
}

void Explorer::changeNextPosAdd()
{
    this->setGeometry(this->geometry().x(), this->geometry().y() + ui->label->height() * 1.5, this->geometry().width(), this->geometry().height());
}

void Explorer::changeNextPosRemove()
{
    this->setGeometry(this->geometry().x(), this->geometry().y() - ui->label->height() * 2, this->geometry().width(), this->geometry().height());
}

void Explorer::changeHeightWidget()
{
    this->setGeometry(this->geometry().x(), this->geometry().y(), this->geometry().width(), ui->widget->height()+ui->label->height() * 1.25);
}

void Explorer::changeHeightEscape()
{
    this->setGeometry(this->geometry().x(), this->geometry().y(), this->geometry().width(), ui->label->height() * 1.25);
}

void Explorer::changeHeightShow()
{
    this->setGeometry(this->geometry().x(), this->geometry().y(), this->geometry().width(), ui->widget->height() * 1.25);
}

QWidget* Explorer::getWidget() const { return ui->widget; }

bool Explorer::getStatus() const { return checkHide; }

void Explorer::remove_File()
{
    int index = 0;
    qDebug() << "remove";
    for (int i = 0; i < arrLayout.size(); i++)
        if (qobject_cast<QWidget*>(sender()->parent()) == arrWidButt[i]) {
            index = i;
            arrWidButt[i]->hide();
            arrPb[i]->hide();
            arrTb[i]->hide();
            arrLayout.remove(i);
            arrPb.remove(i);
            arrTb.remove(i);
            arrWidButt.remove(i);
        }

    ui->verticalLayout->addStretch();
    ui->widget->setGeometry(ui->widget->x(), ui->widget->y(), ui->widget->width(), ui->widget->height() - arrWidButt[index]->height());
    emit removeFile(this);
}

void Explorer::on_toolButton_2_clicked()
{
    if (checkHide) {
        ui->toolButton_2->setStyleSheet("QToolButton#toolButton_2 {image: url(:/image/arrowDown.png);} QToolButton#toolButton_2:hover {image: url(:/image/arrowDownHover.png);} QToolButton#toolButton_2:pressed {image: url(:/image/arrowDown.png);}");
        checkHide = false;
    }
    else {
        checkHide = true;
        ui->toolButton_2->setStyleSheet("QToolButton#toolButton_2 {image: url(:/image/arrowRight.png);} QToolButton#toolButton_2:hover {image: url(:/image/arrowRightHover.png);} QToolButton#toolButton_2:pressed {image: url(:/image/arrowRight.png);}");
    }

    emit escapeChange(this, checkHide);

}

void Explorer::setStandartGeometry()
{
    this->setGeometry(0, 0, width, 60);
}


// 1) подредактировать удаление файлов
// 2) добавить кнопку добавлениня каталога в каталог
