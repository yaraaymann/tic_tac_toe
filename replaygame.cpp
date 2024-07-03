#include "ReplayGame.h"
//QVector<QString> moves;
ReplayGame::ReplayGame(QWidget *parent) : QDialog(parent), currentMoveIndex(0)
{
    mainLayout = new QVBoxLayout(this); // Create the main layout
    setupBoard();
    mainLayout->addLayout(gridLayout); // Add the grid layout to the main layout

    QPushButton *replayButton = new QPushButton("Replay Last Game", this); // Create the replay button
    mainLayout->addWidget(replayButton); // Add the replay button to the main layout

    moveTimer = new QTimer(this);
    connect(moveTimer, &QTimer::timeout, this, &ReplayGame::playNextMove);
    connect(replayButton, &QPushButton::clicked, this, &ReplayGame::replayLastGame);
}

void ReplayGame::setDatabase(QSqlDatabase &database)
{
    db = database;
}

void ReplayGame::setupBoard()
{
    gridLayout = new QGridLayout(this); // Create the grid layout on the current widget

    // Apply custom style sheet
    QString buttonStyle = "\
        QPushButton {\
            background: rgb(79, 200, 154);\
            border-radius: 30px;\
            font-size: 50px;\
            color: black;\
    }";

        // Apply style sheet to all buttons
        for (int i = 0; i < 9; ++i) {
        QPushButton *button = new QPushButton(this);
        button->setStyleSheet(buttonStyle); // Set custom style sheet for QPushButton
        button->setEnabled(false); // Ensure buttons are initially disabled if needed
        boardButtons.append(button);
        gridLayout->addWidget(button, i / 3, i % 3);
        board[i / 3][i % 3] = button;
    }

    // Set layout on the widget
    setLayout(gridLayout);
}

void ReplayGame::loadMovesFromDatabase()
{
    QSqlQuery query;
    query.prepare("SELECT id FROM Games WHERE username = :username");
    query.bindValue(":username", gameManager.loggedInUsername);
    if (query.exec()) {
        gameIds.clear(); // Clear existing game IDs
        while (query.next()) {
            gameIds.append(query.value(0).toInt());
        }
    } else {
        qDebug() << "Error fetching game IDs:" << query.lastError().text();
    }
}
QVector<QString> moving;
void ReplayGame::replayLastGame()
{
    loadMovesFromDatabase();
    if (gameIds.isEmpty()) {
        qDebug() << "No game IDs found for user:" << gameManager.loggedInUsername;
        return;
    }

    bool ok;
    QStringList gameIdsStringList;
    for (int id : gameIds) {
        gameIdsStringList.append(QString::number(id));
    }

    QString selectedGameId = QInputDialog::getItem(this, "Select Game ID", "Select a game ID to replay:",
                                                   gameIdsStringList, 0, false, &ok);

    if (!ok) return; // User canceled or closed the dialog

    int gameId = selectedGameId.toInt();

    QSqlQuery query;
    query.prepare("SELECT moves FROM Games WHERE id = :gameId");
    query.bindValue(":gameId", gameId);
    if (query.exec() && query.next()) {
        QString movesString = query.value(0).toString();
        moving = movesString.split(';');
    } else {
        qDebug() << "Error fetching moves for game ID:" << gameId << query.lastError().text();
        return;
    }

    currentMoveIndex = 0;
    for (QPushButton *button : boardButtons) {
        button->setText("");
    }
    qDebug() << "Replaying game with" << moving.size() << "moves.";
    if (!moving.isEmpty()) {
        moveTimer->start(1000); // 1 second per move
    }
}
void ReplayGame::playNextMove()
{
    if (currentMoveIndex < moving.size()) {
        QString move = moving[currentMoveIndex];
        QStringList parts = move.split(",");
        char player = parts[0].toLatin1()[0];
        int row = parts[1].toInt();
        int col = parts[2].toInt();
        qDebug() << "Playing move:" << row << col << player;
        board[row][col]->setText(QString(player));
        ++currentMoveIndex;
    } else {
        moveTimer->stop();
        qDebug() << "Finished replaying moves.";

    }
}

