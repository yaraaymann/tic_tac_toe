#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "ui_Dialog.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void on_btn2_reg_clicked();

    void on_newName_textChanged(const QString &arg1);

    void on_newPassword_textChanged(const QString &arg1);

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
