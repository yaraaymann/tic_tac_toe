#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <QString> // Include necessary headers as needed
#include <QObject>
#include <QStringList>

class GameManager: public QObject
{
    Q_OBJECT

public:
    explicit GameManager(QObject *parent = nullptr);

    QString loggedInUsername;
    QString loggedInhistory;
    QStringList totalhistory;
public slots:
    void updateHistory(const QString &newHistoryItem); // Method to update history


signals:
    void historyUpdated(const QStringList &historyItems);
};

extern GameManager gameManager;

#endif // GAMEMANAGER_H
