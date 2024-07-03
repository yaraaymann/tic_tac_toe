#ifndef EASY_AI_H
#define EASY_AI_H

#include <QDialog>
#include <QPushButton>
#include <QSoundEffect>
#include <QSqlQuery>
#include <QSqlDatabase>

namespace Ui {
class easy_ai;
}

class easy_ai : public QDialog
{
    Q_OBJECT

public:
    explicit easy_ai(QWidget *parent = nullptr);
    ~easy_ai();
    Ui::easy_ai *getUi() const;
private slots:
    void on_pushButton1_clicked();
    void on_pushButton2_clicked();
    void on_pushButton3_clicked();
    void on_pushButton4_clicked();
    void on_pushButton5_clicked();
    void on_pushButton6_clicked();
    void on_pushButton7_clicked();
    void on_pushButton8_clicked();
    void on_pushButton9_clicked();


private:
    Ui::easy_ai *ui;
    QSqlDatabase db;
    char currentPlayer;
    char board[3][3];

    void initializeBoard();
    void handleButtonClick(int row, int col);
    void updateButton(int row, int col);
    void makeAiMove();
    int minimax(int depth, bool maximizingPlayer);
    bool checkWin(char player);
    bool checkTie();
    void resetGame();
    void logGameResult(QStringList result);
    void saveMove(int row, int col, char currentPlayer);
    QSoundEffect backgroundMusic;
    QSoundEffect loseSound;
    QSoundEffect winSound;
    QSoundEffect drawSound;

};

#endif // EASY_AI_H
