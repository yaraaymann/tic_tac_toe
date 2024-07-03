#ifndef REGISTER_DIALOG_H
#define REGISTER_DIALOG_H

#include <QDialog>
#include <QSqlQuery>
#include <QSqlDatabase>

namespace Ui {
class register_Dialog;
}

class register_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit register_Dialog(QWidget *parent = nullptr);
    ~register_Dialog();

private slots:
    void on_newName_textChanged(const QString &arg1);

    void on_newPassword_textChanged(const QString &arg1);

    void on_btn2_reg_clicked();

private:
    Ui::register_Dialog *ui;
    QSqlDatabase db;
};

#endif // REGISTER_DIALOG_H
