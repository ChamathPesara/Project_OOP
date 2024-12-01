#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QMainWindow>
#include "incomeExpense.h"
#include "scheduler.h"

namespace Ui {
class Homepage;
}

class Homepage : public QMainWindow
{
    Q_OBJECT

public:
    explicit Homepage(QWidget *parent = nullptr,const QString& username = "");
    ~Homepage();

private slots:
    void on_tracherButton_clicked();

    void on_schedularButton_clicked();

    void on_closeButton_clicked();

private:
    Ui::Homepage *ui;
    IncomeExpense *inexp;
    Scheduler *schedular;
    QString currentUsername;
};

#endif // HOMEPAGE_H
