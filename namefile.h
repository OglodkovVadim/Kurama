#ifndef NAMEFILE_H
#define NAMEFILE_H

#include <QDialog>

namespace Ui {
class NameFile;
}

class NameFile : public QDialog
{
    Q_OBJECT

public:
    explicit NameFile(QWidget *parent = nullptr);
    ~NameFile();

    QString getText() const;

private slots:
    void on_buttonBox_accepted();

signals:
    void acceptFileName(const NameFile*);

private:
    Ui::NameFile *ui;
};

#endif // NAMEFILE_H
