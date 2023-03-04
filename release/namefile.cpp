#include "namefile.h"
#include "ui_namefile.h"

NameFile::NameFile(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NameFile)
{
    ui->setupUi(this);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setStyleSheet("QPushButton { background-color: none; color: #55ff7f; border: 1px solid #55ff7f; }"
                                                               "QPushButton:hover { color: #359f4e; border: 1px solid #359f4e; }"
                                                               "QPushButton:pressed { color: #55ff7f; border: 1px solid #55ff7f; }");
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setStyleSheet("QPushButton { background-color: none; color: #ff3d3d; border: 1px solid #ff3d3d; }"
                                                                   "QPushButton:hover { color: #872020; border: 1px solid #872020; }"
                                                                   "QPushButton:pressed { color: #ff3d3d; border: 1px solid #ff3d3d; }");
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
