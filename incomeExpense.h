#ifndef INCOMEEXPENSE_H
#define INCOMEEXPENSE_H

#include <QMainWindow>
#include "thebudget.h"

namespace Ui {
class IncomeExpense;
}

class IncomeExpense : public QMainWindow
{
    Q_OBJECT

public:
    explicit IncomeExpense(QWidget *parent = nullptr, const QString& username = "");
    ~IncomeExpense();

private slots:
    void on_add_income_clicked();

    void on_add_expense_clicked();

    void on_endButtton_clicked();

    void on_BudgetButton_clicked();

    void saveDataToCSV();
    void loadDataFromCSV();

    void on_reportButton_clicked();



    void on_bargraphbutton_clicked();

private:
    Ui::IncomeExpense *ui;
    QMap<QString, double> budgets;
    TheBudget *budgetManager;
    QString currentUsername;
    void updateReport();
};

#endif // INCOMEEXPENSE_H
