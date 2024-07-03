#ifndef GAME_OR_HISTORY_H
#define GAME_OR_HISTORY_H

#include <QDialog>
#include <QSqlQuery>
#include <QSqlDatabase>
namespace Ui {
class game_or_history;
}

class game_or_history : public QDialog
{
    Q_OBJECT

public:
    explicit game_or_history(QWidget *parent = nullptr);
    ~game_or_history();
    QSqlDatabase db;
private slots:
    void on_play_new_game_clicked();

    void on_view_game_history_clicked();

    void on_replay_button_clicked();

private:
    Ui::game_or_history *ui;
};

#endif // GAME_OR_HISTORY_H
