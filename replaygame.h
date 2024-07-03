#ifndef REPLAYGAME_H
#define REPLAYGAME_H

#include <QDialog>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QTimer>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QInputDialog> // Ensure QInputDialog is included for user input

#include "GameManager.h" // Make sure this includes gameManager.loggedInUsername

class ReplayGame : public QDialog
{
    Q_OBJECT

public:
    explicit ReplayGame(QWidget *parent = nullptr); void playNextMove();
    void setDatabase(QSqlDatabase &database); // Correct declaration of setDatabase



private slots:
    void replayLastGame();


private:QPushButton * board[3][3]; // Game board
    QVBoxLayout *mainLayout;
    QGridLayout *gridLayout;
    QVector<QPushButton *> boardButtons;
    QTimer *moveTimer;
    QVector<int> gameIds;
    int currentMoveIndex;
    QSqlDatabase db; // Database connection object

    void setupBoard();
    void loadMovesFromDatabase();

signals:

};

#endif // REPLAYGAME_H

