#include "game_history.h"
#include "ui_game_history.h"
#include "mainwindow.h"
#include<QMessageBox>
#include<QListWidget>

#include "GameManager.h" // Include GameManager header

extern GameManager gameManager;

game_history::game_history(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::game_history)
{
    ui->setupUi(this);
    connect(&gameManager, &GameManager::historyUpdated, this, &game_history::updateHistory);
   updateHistory(gameManager.totalhistory);
}

game_history::~game_history()
{
    delete ui;
}

void game_history::updateHistory(const QStringList &historyItems)
{
    //ui->listWidget_history->clear(); // Clear existing items
    //ui->listWidget_history->addItems(gameManager.totalhistory); // Add updated history
}





void game_history::on_listWidget_itemClicked(QListWidgetItem *item)
{


}

