#include "namefile.h"
#include "ui_namefile.h"

NameFile::NameFile(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NameFile)
{
    ui->setupUi(this);
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
