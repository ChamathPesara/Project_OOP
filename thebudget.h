#ifndef THEBUDGET_H
#define THEBUDGET_H

#include <QDialog>
#include <QMap>
#include <QString>
#include <QTableWidget>

namespace Ui {
class TheBudget;
}

class TheBudget : public QDialog
{
    Q_OBJECT

public:
    explicit TheBudget(const QString &username, QWidget *parent = nullptr);
    ~TheBudget();

    void loadBudgets();
    void saveBudgets();
    QMap<QString, double> getBudgets() const;
    double calculateTotalExpensesForCategory(const QString &category, QTableWidget *expenseTable) const;
    double getBudgetForCategory(const QString &category) const;

private slots:
    void on_saveButton_clicked();
    void on_cancelButton_clicked();

private:
    Ui::TheBudget *ui;
    QMap<QString, double> budgets;
    QString username;
    QString getFileName() const;
};

#endif // THEBUDGET_H



