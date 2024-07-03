#ifndef EASYHARD_H
#define EASYHARD_H

#include <QDialog>
#include "easy_ai.h"
#include "ui_easy_ai.h"

namespace Ui {
class easyhard;
}

class easyhard : public QDialog
{
    Q_OBJECT

public:
    explicit easyhard(QWidget *parent = nullptr);
    ~easyhard();

private slots:
    void on_easy_button_clicked();

    void on_hadr_button_clicked();

private:
    Ui::easyhard *ui;
};

#endif // EASYHARD_H
