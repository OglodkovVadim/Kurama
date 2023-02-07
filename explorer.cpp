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

    width = 260;
    height = 60;
    checkHide = true;

    ui->widget->setGeometry(ui->widget->x(), ui->widget->y(), width, height);
    ui->widget->setLayout(ui->verticalLayout);
    ui->toolButton_2->setEnabled(false);
}

Explorer::~Explorer()
{
    delete ui;
}

void Explorer::acceptFileNameSlot(const NameFile* nameFile)
{
    qDebug() << "accept explorer slot";
    arrPb.back()->setText(nameFile->getText());
    arrWidButt.back()->show();
}

void Explorer::on_toolButton_clicked()
{
    ui->toolButton_2->setEnabled(true);
    NameFile* nameFileWidget = new NameFile(this);
    connect(nameFileWidget, SIGNAL(acceptFileName(const NameFile*)), this, SLOT(acceptFileNameSlot(const NameFile*)));
    nameFileWidget->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    nameFileWidget->show();

// adding new file
    arrWidButt.append(new QWidget());
    arrWidButt.back()->hide();
    arrPb.append(new QPushButton(fileName));
    arrTbRemoveFile.append(new QToolButton());
    arrTbRemoveFile.back()->setStyleSheet("QToolButton { border:none; background-color:none; image: url(:/image/closeRed); max-width: 25px; max-height: 25px; }"
                                          " QToolButton:hover { image: url(:/image/closeRedHover); }"
                                          "QToolButton:pressed { image: url(:/image/closeRed); }");
    arrLayout.append(new QHBoxLayout(arrWidButt.back()));
    arrLayout.back()->addWidget(arrPb.back());
    arrLayout.back()->addWidget(arrTbRemoveFile.back());
    arrLayout.back()->addStretch();
    ui->verticalLayout->insertWidget(0, arrWidButt.back());

// changing widget height
    ui->widget->setGeometry(ui->widget->x(), ui->widget->y(), ui->widget->width(), ui->widget->height() + 60);

    if (checkHide) {
        checkHide = false;
        emit escapeChange(this, checkHide);
        ui->toolButton_2->setStyleSheet("QToolButton#toolButton_2 {image: url(:/image/arrowDown.png);} QToolButton#toolButton_2:hover {image: url(:/image/arrowDownHover.png);} QToolButton#toolButton_2:pressed {image: url(:/image/arrowDown.png);}");
    }
    else
        this->setGeometry(this->geometry().x(), this->geometry().y(), this->geometry().width(), this->geometry().height() + 60);

// connecting to mainwindow
    connect(arrTbRemoveFile.back(), SIGNAL(clicked()),
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
    this->setGeometry(this->geometry().x(), this->geometry().y() - ui->label->height() * 1.5, this->geometry().width(), this->geometry().height());
}

void Explorer::changeHeightWidget()
{
    this->setGeometry(this->geometry().x(), this->geometry().y(), this->geometry().width(), ui->widget->height() + ui->label->height() * 1.5);
}

void Explorer::changeHeightEscape()
{
    this->setGeometry(this->geometry().x(), this->geometry().y(), this->geometry().width(), ui->widget->y());
}

void Explorer::changeHeightShow()
{
    this->setGeometry(this->geometry().x(), this->geometry().y(), this->geometry().width(), this->geometry().height() + ui->widget->height());
}

QWidget* Explorer::getWidget() const { return ui->widget; }

bool Explorer::getStatus() const { return checkHide; }

void Explorer::remove_File()
{
    for (int i = 0; i < arrLayout.size(); i++)
        if (qobject_cast<QWidget*>(sender()->parent()) == arrWidButt[i]) {
            arrWidButt[i]->hide();
            arrPb[i]->hide();
            arrTbRemoveFile[i]->hide();
            arrLayout.remove(i);
            arrPb.remove(i);
            arrTbRemoveFile.remove(i);
            arrWidButt.remove(i);
        }

    ui->verticalLayout->addStretch();
    ui->widget->setGeometry(ui->widget->x(), ui->widget->y(), ui->widget->width(), ui->widget->height() - 60);
    this->setGeometry(this->geometry().x(), this->geometry().y(), this->geometry().width(), this->geometry().height() - 60);

    if (arrWidButt.size() == 0) {
        ui->toolButton_2->setEnabled(false);
        checkHide = true;
        ui->toolButton_2->setStyleSheet("QToolButton#toolButton_2 {image: url(:/image/arrowRight.png);} QToolButton#toolButton_2:hover {image: url(:/image/arrowRightHover.png);} QToolButton#toolButton_2:pressed {image: url(:/image/arrowRight.png);}");
    }
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
    this->setGeometry(0, 0, width, ui->widget->y());
    ui->widget->setGeometry(ui->widget->x(), ui->widget->y(), ui->widget->width(),0);
}

int Explorer::getCountFiles() const
{
    return arrWidButt.size();
}


void Explorer::on_addFolder_clicked()
{
    arrLocalExplorer.append(new Explorer());
    ui->verticalLayout->insertWidget(0, arrLocalExplorer.back());

    ui->widget->setGeometry(ui->widget->x(), ui->widget->y(), ui->widget->width() + 60, ui->widget->height() + 60);
    this->setGeometry(this->geometry().x(), this->geometry().y(), this->geometry().width() + 60, this->geometry().height());
    if (checkHide) {
        checkHide = false;
        emit escapeChange(this, checkHide);
        ui->toolButton_2->setStyleSheet("QToolButton#toolButton_2 {image: url(:/image/arrowDown.png);}"
                                        " QToolButton#toolButton_2:hover {image: url(:/image/arrowDownHover.png);}"
                                        " QToolButton#toolButton_2:pressed {image: url(:/image/arrowDown.png);}");
    }
    else
        this->setGeometry(this->geometry().x(), this->geometry().y(), this->geometry().width() + 60, this->geometry().height() + 60);

    emit addFile(this);
}

// подредактировать пересещение папок при удаление файла
// связать добавление локальных папок с корневыми
