#include "easyhard.h"
#include "ui_easyhard.h"
#include "gameai.h"
#include "ui_gameai.h"
#include "easy_ai.h"
#include "ui_easy_ai.h"

easyhard::easyhard(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::easyhard)
{
    ui->setupUi(this);
}

easyhard::~easyhard()
{
    delete ui;
}

void easyhard::on_easy_button_clicked()
{
    easy_ai easy_ai;
    easy_ai.setModal(true);
    easy_ai.exec();
}


void easyhard::on_hadr_button_clicked()
{
    GameAI gameai;
    gameai.setModal(true);
    gameai.exec();
}

