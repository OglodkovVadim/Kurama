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
    ui->widget->setGeometry(QRect(x, y, width, ui->widget->height()+ui->label->height() * 1.5));

// connecting to mainwindow
    connect(arrTb.back(), SIGNAL(clicked()),
            this, SLOT(remove_File()));
    qDebug() << "adding...";
    emit addFile(this);
}

QLabel* Explorer::getQLabel() const
{
    return ui->label;
}

void Explorer::changeHeight()
{
    this->setGeometry(this->geometry().x(), this->geometry().y() + ui->label->height() * 2, this->geometry().width(), this->geometry().height());
}

void Explorer::changeHeightWidget()
{
    this->setGeometry(this->geometry().x(), this->geometry().y(), this->geometry().width(), ui->widget->height()+ui->label->height() * 1.25);
}

QWidget* Explorer::getWidget() const { return ui->widget; }

bool Explorer::getStatus() const { return checkHide; }

void Explorer::remove_File()
{
    qDebug() << "remove";
    for (int i = 0; i < arrLayout.size(); i++)
        if (qobject_cast<QWidget*>(sender()->parent()) == arrWidButt[i]) {
//            animationWidget(*arrWidButt[i], arrWidButt[i]->x(), arrWidButt[i]->y(), 0, arrWidButt[i]->height(), QEasingCurve::Linear, 200);
            arrWidButt[i]->hide();
            arrPb[i]->hide();
            arrTb[i]->hide();
            arrLayout.remove(i);
            arrPb.remove(i);
            arrTb.remove(i);
            arrWidButt.remove(i);
        }

    ui->verticalLayout->addStretch();
}

void Explorer::on_toolButton_2_clicked()
{
    emit escapeChange(this, checkHide);

    if (checkHide)
        checkHide = false;
    else
        checkHide = true;
}

void Explorer::setStandartGeometry()
{
    this->setGeometry(0, 0, width, 60);
}

// 1) при удалении файлов сдвигать оставшиеся
// 2) при развертывании/свертывании подкорректировать сдвижение элементов
// 3) изменить кнопку развертывания/свертывания на стрелочку
// 4) добавить кнопку добавлениня каталога в каталог
