#include "gamewindow1.h"
#include "ui_gamewindow1.h"
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
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "GameManager.h"
QVector<QString> moves;
gameWindow1::gameWindow1(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::gameWindow1)
    , currentPlayer("X")
{
    ui->setupUi(this);
    resetGame();
    backgroundMusic.setSource(QUrl("qrc:/sounds/sounds/background_music.wav"));

    winSound.setSource(QUrl("qrc:/sounds/sounds/winner.wav"));
    loseSound.setSource(QUrl("qrc:/sounds/sounds/080047_lose_funny_retro_video-game-80925.wav"));
    drawSound.setSource(QUrl("qrc:/sounds/sounds/game_draw.wav"));


    backgroundMusic.setLoopCount(QSoundEffect::Infinite);
    backgroundMusic.play();

}

gameWindow1::~gameWindow1()
{
    delete ui;
}


void gameWindow1::resetGame() {
    // Reset all buttons to default state
    ui->pushButton1->setText("");
    ui->pushButton2->setText("");
    ui->pushButton3->setText("");
    ui->pushButton4->setText("");
    ui->pushButton5->setText("");
    ui->pushButton6->setText("");
    ui->pushButton7->setText("");
    ui->pushButton8->setText("");
    ui->pushButton9->setText("");
    if (!moves.isEmpty()) {
        QString movesString = moves.join(";");
        QSqlQuery query;
        query.prepare("INSERT INTO Games (username, moves) VALUES (:username, :moves)");
        query.bindValue(":username", gameManager.loggedInUsername);
        query.bindValue(":moves", movesString);
        query.exec();
    }
    moves.clear();
    backgroundMusic.play();
    // Reset the game board and the current player (X starts)
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            board[i][j] = ' ';
        }
    }
    currentPlayer = "X";
}

void gameWindow1::makeMove(QPushButton *button, int row, int col) {

    if (button->text() == "") {  // Only allow moves on empty buttons
        button->setText(currentPlayer);
        board[row][col] = currentPlayer.toStdString()[0];

        QString str = currentPlayer;  // Example QString with one character
        QChar qchar = str.at(0);  // Get the first character as QChar
        char ch = qchar.toLatin1();  // Convert QChar to char

        saveMove(row,col, ch);

        if (checkWin(currentPlayer.toStdString()[0])) {
            backgroundMusic.stop();
            winSound.play();
            QMessageBox::information(this, "Game Over", QString("%1 wins!").arg(currentPlayer));
            QStringList aiStringList;
            aiStringList << (currentPlayer+"Wins!");
            logGameResult(aiStringList);
            resetGame();
            return;
        } else if (checkTie()) {
            backgroundMusic.stop();
            drawSound.play();
            QMessageBox::information(this, "Game Over", "It's a tie!");
            QStringList aiStringList;
            aiStringList <<"It's a tie!" ;
            logGameResult(aiStringList);
            resetGame();
            return;
        }

        // Switch player
        currentPlayer = (currentPlayer == "X") ? "O" : "X";
    }
}

bool gameWindow1::checkWin(char player) {
    // Check rows and columns
    for (int i = 0; i < 3; ++i) {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player)
            return true; // Row win
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player)
            return true; // Column win
    }
    // Check diagonals
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player)
        return true; // Diagonal win
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player)
        return true; // Diagonal win
    return false;
}

bool gameWindow1::checkTie() {
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            if (board[row][col] == ' ')
                return false; // There are still empty cells, game is not a tie
        }
    }
    return true; // All cells are filled, game is a tie
}
void gameWindow1::logGameResult(QStringList result) {
    // Convert QStringList to QString
    QString resultString = result.join("\n");

    // Fetch the current user's history from the database
    QSqlQuery selectQuery;
    selectQuery.prepare("SELECT history FROM Users WHERE username = :username");
    selectQuery.bindValue(":username", gameManager.loggedInUsername);

    if (!selectQuery.exec()) {
        qDebug() << "Error fetching current history:" << selectQuery.lastError().text();
        return;
    }

    QString currentHistory;
    if (selectQuery.next()) {
        currentHistory = selectQuery.value("history").toString();
    }

    // Concatenate the new result with the existing history
    QString newHistory = currentHistory.isEmpty() ? resultString : currentHistory + "\n" + resultString;

    // Update loggedInhistory for the current user (if you need it in memory)
    gameManager.loggedInhistory = newHistory;

    // Update totalhistory if it needs to be updated for the current user
    gameManager.totalhistory = newHistory.split("\n");

    // Debug output to verify the new history list
    qDebug() << "Updated history:" << gameManager.loggedInhistory;

    // Prepare the SQL query to update the database
    QSqlQuery updateQuery;
    updateQuery.prepare("UPDATE Users SET history = :history WHERE username = :username");
    updateQuery.bindValue(":history", newHistory); // Update history
    updateQuery.bindValue(":username", gameManager.loggedInUsername); // Use the logged-in username

    // Execute the query and check for errors
    if (!updateQuery.exec()) {
        qDebug() << "Error updating history:" << updateQuery.lastError().text();
    } else {
        qDebug() << "History updated successfully in the database.";
    }
}

void gameWindow1::saveMove(int row, int col, char player)
{moves.append(QString("%1,%2,%3").arg(currentPlayer).arg(row).arg(col));
}


void gameWindow1::on_pushButton1_clicked()
{
    makeMove(ui->pushButton1, 0, 0);
}

void gameWindow1::on_pushButton2_clicked()
{
    makeMove(ui->pushButton2, 0, 1);
}

void gameWindow1::on_pushButton3_clicked()
{
    makeMove(ui->pushButton3, 0, 2);
}

void gameWindow1::on_pushButton4_clicked()
{
    makeMove(ui->pushButton4, 1, 0);
}

void gameWindow1::on_pushButton5_clicked()
{
    makeMove(ui->pushButton5, 1, 1);
}

void gameWindow1::on_pushButton6_clicked()
{
    makeMove(ui->pushButton6, 1, 2);
}

void gameWindow1::on_pushButton7_clicked()
{
    makeMove(ui->pushButton7, 2, 0);
}

void gameWindow1::on_pushButton8_clicked()
{
    makeMove(ui->pushButton8, 2, 1);
}

void gameWindow1::on_pushButton9_clicked()
{
    makeMove(ui->pushButton9, 2, 2);
}
