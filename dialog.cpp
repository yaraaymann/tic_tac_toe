#include "Dialog.h"
#include "ui_Dialog.h"
#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QMessageBox>
#include <QLineEdit>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidget>
#include <QDialog>
#include <limits>
#include <unordered_map>
#include <QTextStream>
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QMessageBox>
#include <QtSql/QSql>
#include <unordered_map>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QTextEdit>
#include <QApplication>



Dialog::Dialog(QWidget *parent)
    : QDialog(parent),
     ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}
QString username2,password2;

void Dialog::on_btn2_reg_clicked()
{

    if (!username2.endsWith("@gmail.com"))
        QMessageBox::critical(this, "Error", "Username must end with @gmail.com");
    if (password2.length() != 6)
        QMessageBox::critical(this, "Error", "Password must be 6 characters long");

}


void Dialog::on_newName_textChanged(const QString &arg1)
{
    username2 =arg1;
}


void Dialog::on_newPassword_textChanged(const QString &arg1)
{
    password2=arg1;
}

