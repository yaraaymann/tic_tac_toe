#ifndef GAME_HISTORY_H
#define GAME_HISTORY_H


#include <QDialog>
#include <QWidget>
#include <QListWidgetItem>
#include "GameManager.h"





namespace Ui { class game_history; }


class game_history : public QDialog
{
    Q_OBJECT

public:
    explicit game_history(QWidget *parent = nullptr);
    ~game_history();

public slots:
    void updateHistory(const QStringList &historyItems);
private slots:
    void on_listWidget_history_itemEntered(QListWidgetItem *item);

    void on_listWidget_itemClicked(QListWidgetItem *item);

private:
    Ui::game_history *ui;


};

#endif // GAME_HISTORY_H
