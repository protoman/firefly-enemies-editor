#include "enemyedit.h"
#include "ui_enemyedit.h"

EnemyEdit::EnemyEdit(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::EnemyEdit)
{
    ui->setupUi(this);
}

EnemyEdit::~EnemyEdit()
{
    delete ui;
}

void EnemyEdit::start()
{
    this->show();
}
