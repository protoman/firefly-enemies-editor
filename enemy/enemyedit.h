#ifndef ENEMYEDIT_H
#define ENEMYEDIT_H

#include <QMainWindow>

namespace Ui {
class EnemyEdit;
}

class EnemyEdit : public QMainWindow
{
    Q_OBJECT

public:
    explicit EnemyEdit(QWidget *parent = nullptr);
    ~EnemyEdit();
    void start();

private:
    Ui::EnemyEdit *ui;
};

#endif // ENEMYEDIT_H
