#include "GameManager.h"
GameManager gameManager;

GameManager::GameManager(QObject *parent) : QObject(parent)
{

}


void GameManager::updateHistory(const QString &newHistoryItem) {
    totalhistory << newHistoryItem; // Add new history item
    emit historyUpdated(totalhistory); // Emit signal with updated history
}
