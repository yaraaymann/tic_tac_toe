#include "register_dialog.h"
#include "ui_register_dialog.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QMessageBox>
#include "game_or_history.h"
#include "ui_game_or_history.h"
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

register_Dialog::register_Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::register_Dialog)
{
    ui->setupUi(this);
    db = QSqlDatabase::database();
}

register_Dialog::~register_Dialog()
{
    delete ui;
}
QString username2,password2;

void register_Dialog::on_newName_textChanged(const QString &arg1)
{
    username2 =arg1;

}


void register_Dialog::on_newPassword_textChanged(const QString &arg1)
{
    password2=arg1;
}


void register_Dialog::on_btn2_reg_clicked()
{
    if (!username2.endsWith("@gmail.com"))
        QMessageBox::critical(this, "Error", "Username must end with @gmail.com");
    else if (password2.length() != 6)
    { QMessageBox::critical(this, "Error", "Password must be 6 characters long");}
    else{
    QSqlQuery query(db);
    query.prepare("INSERT INTO Users (username, password, history) VALUES (:username, :password, :value)");
    query.bindValue(":username", username2);
    query.bindValue(":password", password2);
    query.bindValue(":value", "");
       if (query.exec()) {
        QMessageBox::information(this, "Registration", "Registered successfully!");
           accept();
           //MainWindow mainwindow;
       // mainwindow.setModal(true);
       // mainwindow.exec();
       }else {
        QMessageBox::critical(this, "Registration Error", "Failed to register.");
    }
}

}

