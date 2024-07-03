#include "easy_ai.h"
#include "ui_easy_ai.h"
#include <QMessageBox>
#include <limits>
#include "GameManager.h"
#include <QStringList>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include "gamewindow1.h"

easy_ai::easy_ai(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::easy_ai)
    , currentPlayer('X')

{
    ui->setupUi(this);
    initializeBoard();
    backgroundMusic.setSource(QUrl("qrc:/sounds/sounds/background_music.wav"));
    loseSound.setSource(QUrl("qrc:/sounds/sounds/080047_lose_funny_retro_video-game-80925.wav"));
    winSound.setSource(QUrl("qrc:/sounds/sounds/winner.wav"));
    drawSound.setSource(QUrl("qrc:/sounds/sounds/game_draw.wav"));

    backgroundMusic.setLoopCount(QSoundEffect::Infinite);
    backgroundMusic.play();

}

easy_ai::~easy_ai()
{
    delete ui;
}
Ui::easy_ai *easy_ai::getUi() const
{
    return ui;
}
void easy_ai::initializeBoard() {
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            board[row][col] = ' ';
        }
    }
    backgroundMusic.play();
}

void easy_ai::on_pushButton1_clicked() { handleButtonClick(0, 0); }
void easy_ai::on_pushButton2_clicked() { handleButtonClick(0, 1); }
void easy_ai::on_pushButton3_clicked() { handleButtonClick(0, 2); }
void easy_ai::on_pushButton4_clicked() { handleButtonClick(1, 0); }
void easy_ai::on_pushButton5_clicked() { handleButtonClick(1, 1); }
void easy_ai::on_pushButton6_clicked() { handleButtonClick(1, 2); }
void easy_ai::on_pushButton7_clicked() { handleButtonClick(2, 0); }
void easy_ai::on_pushButton8_clicked() { handleButtonClick(2, 1); }
void easy_ai::on_pushButton9_clicked() { handleButtonClick(2, 2); }

void easy_ai::handleButtonClick(int row, int col) {
    if (board[row][col] == ' ') {
        board[row][col] = currentPlayer;
        saveMove( row,  col, currentPlayer);
        updateButton(row, col);

        if (checkWin(currentPlayer)) {
            backgroundMusic.stop();
            winSound.play();
            QMessageBox::information(this, "Game Over", QString("%1 wins!").arg(currentPlayer));
            QStringList aiStringList;
            aiStringList << "You Win!";
            logGameResult(aiStringList);

            resetGame();
        } else if (checkTie()) {
            backgroundMusic.stop();
            drawSound.play();
            QMessageBox::information(this, "Game Over", "It's a tie!");
            QStringList aiStringList;
            aiStringList << "It's a tie!";
            logGameResult(aiStringList);
            resetGame();
        } else {
            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
            if (currentPlayer == 'O') {
                makeAiMove();
            }
        }
    }
}

void easy_ai::updateButton(int row, int col) {
    QString buttonName = QString("pushButton%1").arg(row * 3 + col + 1);
    QPushButton *button = findChild<QPushButton *>(buttonName);
    if (button) {
        button->setText(QString(board[row][col]));
    }
}

void easy_ai::makeAiMove() {
    int bestScore = std::numeric_limits<int>::min();
    int bestMoveRow = -1;
    int bestMoveCol = -1;

    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            if (board[row][col] == ' ') {
                board[row][col] = 'O';
                int score = minimax(0, false);
                board[row][col] = ' ';
                if (score > bestScore) {
                    bestScore = score;
                    bestMoveRow = row;
                    bestMoveCol = col;
                }
            }
        }
    }

    if (bestMoveRow != -1 && bestMoveCol != -1) {
        board[bestMoveRow][bestMoveCol] = 'O';
        updateButton(bestMoveRow, bestMoveCol);
        saveMove(bestMoveRow, bestMoveCol, 'O');
        if (checkWin('O')) {
            backgroundMusic.stop();
            loseSound.play();

            QMessageBox::information(this, "Game Over", "AI wins!");
            QStringList aiStringList;
            aiStringList << "AI wins!";
            logGameResult(aiStringList);
            resetGame();
        } else if (checkTie()) {
            backgroundMusic.stop();
            drawSound.play();
            QMessageBox::information(this, "Game Over", "It's a tie!");
            QStringList aiStringList;
            aiStringList << "tie";
            logGameResult(aiStringList);
            resetGame();
        } else {
            currentPlayer = 'X';
        }
    }
}

int easy_ai::minimax(int depth, bool maximizingPlayer) {

        const int maxDepth = 2; // Limit the depth for simplicity

        if (checkWin('X')) return -10 + depth;
        if (checkWin('O')) return 10 - depth;
        if (checkTie()) return 0;
        if (depth >= maxDepth) return 0; // Stop searching deeper

        if (maximizingPlayer) {
            int bestScore = std::numeric_limits<int>::min();
            for (int row = 0; row < 3; ++row) {
                for (int col = 0; col < 3; ++col) {
                    if (board[row][col] == ' ') {
                        board[row][col] = 'O';
                        int score = minimax(depth + 1, false);
                        board[row][col] = ' ';
                        bestScore = std::max(score, bestScore);
                    }
                }
            }
            return bestScore;
        } else {
            int bestScore = std::numeric_limits<int>::max();
            for (int row = 0; row < 3; ++row) {
                for (int col = 0; col < 3; ++col) {
                    if (board[row][col] == ' ') {
                        board[row][col] = 'X';
                        int score = minimax(depth + 1, true);
                        board[row][col] = ' ';
                        bestScore = std::min(score, bestScore);
                    }
                }
            }
            return bestScore;
        }
    }

bool easy_ai::checkWin(char player) {
    for (int i = 0; i < 3; ++i) {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player)
            return true;
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player)
            return true;
    }
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player)
        return true;
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player)
        return true;
    return false;
}

bool easy_ai::checkTie() {
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            if (board[row][col] == ' ')
                return false;
        }
    }
    return true;
}

void easy_ai::resetGame() {
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
    // Reset the game board and the current player (X starts)
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            board[i][j] = ' ';
        }
    }
    backgroundMusic.play();
    currentPlayer = 'X';
}

void easy_ai::logGameResult(QStringList result) {
    QString resultString = result.join("\n");
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


    // Update loggedInhistory and totalhistory
    gameManager.loggedInhistory = newHistory;
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
void easy_ai::saveMove(int row, int col, char currentPlayer)
{moves.append(QString("%1,%2,%3").arg(currentPlayer).arg(row).arg(col));
}

