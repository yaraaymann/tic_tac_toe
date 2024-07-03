#include "mainwindow.h"
#include "./ui_mainwindow.h"
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
#include<QPixmap>
#include "register_dialog.h"
#include "game_or_history.h"
#include "ui_game_or_history.h"

#include "GameManager.h"






MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    db = QSqlDatabase::database();

}


MainWindow::~MainWindow()
{
    delete ui;
}
Ui::MainWindow* MainWindow::getUi() const {
    return ui; // Return the private UI member
}
QString username1,password1;





void MainWindow::on_userName_textChanged(const QString &arg1)
{
    username1 =arg1;
}


void MainWindow::on_PassWord_textChanged(const QString &arg1)
{
    password1 =arg1;
}


void MainWindow::on_Register_clicked()
{
    register_Dialog register_dialog;
    register_dialog.setModal(true);
    register_dialog.exec();
}
void MainWindow::someFunctionToShowDialog()
{
    register_Dialog dialog(this);
    dialog.setModal(true);
    dialog.exec();
}

void MainWindow::on_Login_clicked()
{
    if (!username1.endsWith("@gmail.com")) {
        QMessageBox::critical(this, "Error", "Username must end with @gmail.com");
        return;
    }
    if (password1.length() != 6) {
        QMessageBox::critical(this, "Error", "Password must be 6 characters long");
        return;
    }

    QSqlQuery query(db);
    query.prepare("SELECT * FROM Users WHERE username = :username AND password = :password");
    query.bindValue(":username", username1);
    query.bindValue(":password", password1);

    if (!query.exec()) {
        QMessageBox::critical(this, "Database Error", "Failed to execute login query");
        qDebug() << "Query error:" << query.lastError().text();
        return;
    }

    if (query.next()) {
        // Successful login
        QMessageBox::information(this, "Success", "Login successful!");

        gameManager.loggedInUsername = username1; // Capture the logged-in username

        QString history = query.value(2).toString(); // Assuming history is in column 2
        gameManager.loggedInhistory = history; // Update logged-in user's history in gameManager
        //QStringList historyItems = history.split(",");

        // history = "Updated history"; // Example: Replace with actual history update logic
        gameManager.totalhistory << history;
        //emit gameManager.historyUpdated(gameManager.totalhistory);



        // Update history in the database
        QSqlQuery updateQuery(db);
        updateQuery.prepare("UPDATE Users SET history = :history WHERE username = :username");
        updateQuery.bindValue(":history", gameManager.loggedInhistory); // Update with the actual history
        updateQuery.bindValue(":username", username1);

        if (!updateQuery.exec()) {
            QMessageBox::critical(this, "Database Error", "Failed to update user's history");
            qDebug() << "Update query error:" << updateQuery.lastError().text();
            return;
        }

        qDebug() << "User's history updated successfully";
        // Display the game or history dialog
        game_or_history game_or_history;
        game_or_history.setModal(true);
        game_or_history.exec();
    } else {
        // Failed login
        QMessageBox::critical(this, "Error", "Invalid username or password");
    }
}
