#include "folder.h"
#include "ui_folder.h"

Folder::Folder(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Folder)
{
    ui->setupUi(this);

    width = 260;
    height = 60;
    checkHide = true;

    ui->widget->setGeometry(ui->widget->x(), ui->widget->y(), width, height);
    ui->widget->setLayout(ui->verticalLayout);
    ui->escape->setEnabled(false);
}

Folder::~Folder()
{
    delete ui;
}

void Folder::acceptFileNameSlot(const NameFile* nameFile)
{
    qDebug() << "accept explorer slot";
    arrPb.back()->setText(nameFile->getText());
    arrWidButt.back()->show();
}

void Folder::on_addFile_clicked()
{
    ui->escape->setEnabled(true);
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
        ui->escape->setStyleSheet("QToolButton#escape {image: url(:/image/arrowDown.png);} "
                                  "QToolButton#escape:hover {image: url(:/image/arrowDownHover.png);} "
                                  "QToolButton#escape:pressed {image: url(:/image/arrowDown.png);}");
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

void Folder::clicked_File()
{
    emit clickedFile(qobject_cast<QPushButton*>(sender()));
}

QLabel* Folder::getQLabel() const
{
    return ui->label;
}

void Folder::changeNextPosAdd()
{
    this->setGeometry(this->geometry().x(), this->geometry().y() + ui->label->height() * 1.5, this->geometry().width(), this->geometry().height());
}

void Folder::changeNextPosRemove()
{
    this->setGeometry(this->geometry().x(), this->geometry().y() - ui->label->height() * 1.5, this->geometry().width(), this->geometry().height());
}

void Folder::changeHeightWidget()
{
    this->setGeometry(this->geometry().x(), this->geometry().y(), this->geometry().width(), ui->widget->height() + ui->label->height() * 1.5);
}

void Folder::changeHeightEscape()
{
    this->setGeometry(this->geometry().x(), this->geometry().y(), this->geometry().width(), ui->widget->y());
}

void Folder::changeHeightShow()
{
    this->setGeometry(this->geometry().x(), this->geometry().y(), this->geometry().width(), this->geometry().height() + ui->widget->height());
}

QWidget* Folder::getWidget() const { return ui->widget; }

bool Folder::getStatus() const { return checkHide; }

void Folder::remove_File()
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
        ui->escape->setEnabled(false);
        checkHide = true;
        ui->escape->setStyleSheet("QToolButton#escape {image: url(:/image/arrowRight.png);} "
                                  "QToolButton#escape:hover {image: url(:/image/arrowRightHover.png);} "
                                  "QToolButton#escape:pressed {image: url(:/image/arrowRight.png);}");
    }
    emit removeFile(this);
}

void Folder::on_escape_clicked()
{
    if (checkHide) {
        ui->escape->setStyleSheet("QToolButton#escape {image: url(:/image/arrowDown.png);} "
                                  "QToolButton#escape:hover {image: url(:/image/arrowDownHover.png);} "
                                  "QToolButton#escape:pressed {image: url(:/image/arrowDown.png);}");
        checkHide = false;
    }
    else {
        checkHide = true;
        ui->escape->setStyleSheet("QToolButton#escape {image: url(:/image/arrowRight.png);} "
                                  "QToolButton#escape:hover {image: url(:/image/arrowRightHover.png);} "
                                  "QToolButton#escape:pressed {image: url(:/image/arrowRight.png);}");
    }

    emit escapeChange(this, checkHide);

}

void Folder::setStandartGeometry()
{
    this->setGeometry(0, 0, width, ui->widget->y());
    ui->widget->setGeometry(ui->widget->x(), ui->widget->y(), ui->widget->width(),0);
}

int Folder::getCountFiles() const
{
    return arrWidButt.size();
}


void Folder::on_addFolder_clicked()
{
    arrLocalExplorer.append(new Folder());
    ui->verticalLayout->insertWidget(0, arrLocalExplorer.back());

    ui->widget->setGeometry(ui->widget->x(), ui->widget->y(), ui->widget->width() + 60, ui->widget->height() + 60);
    this->setGeometry(this->geometry().x(), this->geometry().y(), this->geometry().width() + 60, this->geometry().height());
    if (checkHide) {
        checkHide = false;
        emit escapeChange(this, checkHide);
        ui->escape->setStyleSheet("QToolButton#escape {image: url(:/image/arrowDown.png);}"
                                        " QToolButton#escape:hover {image: url(:/image/arrowDownHover.png);}"
                                        " QToolButton#escape:pressed {image: url(:/image/arrowDown.png);}");
    }
    else
        this->setGeometry(this->geometry().x(), this->geometry().y(), this->geometry().width() + 60, this->geometry().height() + 60);

    emit addFile(this);
}

// подредактировать пересещение папок при удаление файла
// связать добавление локальных папок с корневыми
