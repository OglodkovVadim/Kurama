#include "namefile.h"
#include "ui_namefile.h"

NameFile::NameFile(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NameFile)
{
    ui->setupUi(this);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setStyleSheet("QPushButton { background-color: #55ff7f; color: rgb(33, 34, 35); border: 1px solid rgb(33, 34, 35); }"
                                                               "QPushButton:hover { background-color: #359f4e; }"
                                                               "QPushButton:pressed { background-color: #55ff7f; }");
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setStyleSheet("QPushButton { background-color:#ff3d3d; color: rgb(33, 34, 35); border: 1px solid rgb(33, 34, 35); }"
                                                                   "QPushButton:hover { background-color:#872020 }"
                                                                   "QPushButton:pressed { background-color: #ff3d3d; }");
}

NameFile::~NameFile()
{
    delete ui;
}

void NameFile::on_buttonBox_accepted()
{
    qDebug() << "emit signal";
    emit acceptFileName(this);
}

QString NameFile::getText() const { return ui->lineEdit->text(); }
