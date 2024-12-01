#include "incomeExpense.h"
#include "ui_incomeExpense.h"
#include <QFile>
#include <QTextStream>
#include <QTableWidgetItem>
#include <QDebug>
#include<QMessageBox>
#include<QDate>
#include "homepage.h"
#include "thebudget.h"

IncomeExpense::IncomeExpense(QWidget *parent, const QString& username)
    : QMainWindow(parent)
    , ui(new Ui::IncomeExpense)
    , currentUsername(username)
{
    ui->setupUi(this);

    // Setup Income Table
    ui->table_income->setColumnCount(4);
    QStringList incomeHeaders = {"Date", "Description", "Source", "Amount"};
    ui->table_income->setHorizontalHeaderLabels(incomeHeaders);

    // Setup Expense Table
    ui->table_expenses->setColumnCount(4);
    QStringList expenseHeaders = {"Date", "Description", "Category", "Amount"};
    ui->table_expenses->setHorizontalHeaderLabels(expenseHeaders);

    loadDataFromCSV();

    budgetManager = new TheBudget(currentUsername,this);
    budgetManager->loadBudgets();
}

IncomeExpense::~IncomeExpense()
{ 
    delete ui;
}

void IncomeExpense::saveDataToCSV()
{
    QString incomeFilePath = currentUsername + "_income.csv";
    QString expenseFilePath = currentUsername + "_expense.csv";
    QFile incomeFile(incomeFilePath);
    if (incomeFile.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        QTextStream out(&incomeFile);
        out << "Date,Description,Source,Amount\n";
        for (int row = 0; row < ui->table_income->rowCount(); ++row) {
            QString date = ui->table_income->item(row, 0)->text();
            QString description = ui->table_income->item(row, 1)->text();
            QString source = ui->table_income->item(row, 2)->text();
            QString amount = ui->table_income->item(row, 3)->text();
            out << date << "," << description << "," << source << "," << amount << "\n";
        }
        incomeFile.close();
        qDebug() << "Income data saved to" << incomeFilePath;
    } else {
        qDebug() << "Failed to save income data to" << incomeFilePath;
    }

    QFile expenseFile(expenseFilePath);
    if (expenseFile.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        QTextStream out(&expenseFile);
        out << "Date,Description,Category,Amount\n";
        for (int row = 0; row < ui->table_expenses->rowCount(); ++row) {
            QString date = ui->table_expenses->item(row, 0)->text();
            QString description = ui->table_expenses->item(row, 1)->text();
            QString category = ui->table_expenses->item(row, 2)->text();
            QString amount = ui->table_expenses->item(row, 3)->text();
            out << date << "," << description << "," << category << "," << amount << "\n";
        }
        expenseFile.close();
        qDebug() << "Expense data saved to" << expenseFilePath;
    } else {
        qDebug() << "Failed to save expense data to" << expenseFilePath;
    }
}

void IncomeExpense::loadDataFromCSV()
{
    QString incomeFilePath = currentUsername + "_income.csv";
    QString expenseFilePath = currentUsername + "_expense.csv";

    QFile incomeFile(incomeFilePath);
    if (incomeFile.exists() && incomeFile.open(QIODevice::ReadOnly)) {
        QTextStream in(&incomeFile);
        QString line = in.readLine();
        while (!in.atEnd()) {
            line = in.readLine();
            QStringList fields = line.split(',');
            if (fields.size() == 4) {
                int row = ui->table_income->rowCount();
                ui->table_income->insertRow(row);
                ui->table_income->setItem(row, 0, new QTableWidgetItem(fields[0]));
                ui->table_income->setItem(row, 1, new QTableWidgetItem(fields[1]));
                ui->table_income->setItem(row, 2, new QTableWidgetItem(fields[2]));
                ui->table_income->setItem(row, 3, new QTableWidgetItem(fields[3]));
            }
        }
        incomeFile.close();
        qDebug() << "Income data loaded from" << incomeFilePath;
    } else {
        qDebug() << "No income data found for user" << currentUsername;
    }

    QFile expenseFile(expenseFilePath);
    if (expenseFile.exists() && expenseFile.open(QIODevice::ReadOnly)) {
        QTextStream in(&expenseFile);
        QString line = in.readLine();
        while (!in.atEnd()) {
            line = in.readLine();
            QStringList fields = line.split(',');
            if (fields.size() == 4) {
                int row = ui->table_expenses->rowCount();
                ui->table_expenses->insertRow(row);
                ui->table_expenses->setItem(row, 0, new QTableWidgetItem(fields[0]));
                ui->table_expenses->setItem(row, 1, new QTableWidgetItem(fields[1]));
                ui->table_expenses->setItem(row, 2, new QTableWidgetItem(fields[2]));
                ui->table_expenses->setItem(row, 3, new QTableWidgetItem(fields[3]));
            }
        }
        expenseFile.close();
        qDebug() << "Expense data loaded from" << expenseFilePath;
    } else {
        qDebug() << "No expense data found for user" << currentUsername;
    }
}


void IncomeExpense::on_add_income_clicked()
{
    QString date = ui->date_income->date().toString("yyyy-MM-dd");
    QString description = ui->income_description->text();
    QString source = ui->income_source->currentText();
    double amount = ui->income_amount->value();

    int row = ui->table_income->rowCount();
    ui->table_income->insertRow(row);
    ui->table_income->setItem(row, 0, new QTableWidgetItem(date));
    ui->table_income->setItem(row, 1, new QTableWidgetItem(description));
    ui->table_income->setItem(row, 2, new QTableWidgetItem(source));
    ui->table_income->setItem(row, 3, new QTableWidgetItem(QString::number(amount, 'f', 2)));

    saveDataToCSV();

    ui->income_description->clear();
    ui->income_amount->setValue(0.0);

}

void IncomeExpense::on_add_expense_clicked()
{
    QString date = ui->dateEdit_expense->date().toString("yyyy-MM-dd");
    QString description = ui->expense_description->text();
    QString category = ui->expense_category->currentText();
    double amount = ui->expense_amount->value();

    double currentTotal = budgetManager->calculateTotalExpensesForCategory(category, ui->table_expenses);
    double budgetLimit = budgetManager->getBudgetForCategory(category);

    if (currentTotal > budgetLimit) {
        QMessageBox::warning(this, "Budget Exceeded", "You have exceeded your budget limit for " + category);
    }

    int row = ui->table_expenses->rowCount();
    ui->table_expenses->insertRow(row);
    ui->table_expenses->setItem(row, 0, new QTableWidgetItem(date));
    ui->table_expenses->setItem(row, 1, new QTableWidgetItem(description));
    ui->table_expenses->setItem(row, 2, new QTableWidgetItem(category));
    ui->table_expenses->setItem(row, 3, new QTableWidgetItem(QString::number(amount, 'f', 2)));

    saveDataToCSV();

    ui->expense_description->clear();
    ui->expense_amount->setValue(0.0);
    ui->expense_category->setCurrentIndex(0);

}

void IncomeExpense::on_endButtton_clicked()
{
    saveDataToCSV();
    close();
}

void IncomeExpense::on_BudgetButton_clicked()
{
    TheBudget *budget = new TheBudget(currentUsername, this);

    if (budget->exec() == QDialog::Accepted) {
        budgets = budget->getBudgets();
    }

    budget->deleteLater();
}


void IncomeExpense::updateReport()
{
    double totalIncome = 0.0;
    double totalExpenses = 0.0;

    // Calculate total income
    for (int row = 0; row < ui->table_income->rowCount(); ++row) {
        totalIncome += ui->table_income->item(row, 3)->text().toDouble();
    }

    // Calculate total expenses
    for (int row = 0; row < ui->table_expenses->rowCount(); ++row) {
        totalExpenses += ui->table_expenses->item(row, 3)->text().toDouble();
    }

    double totalSavings = totalIncome - totalExpenses;

    QString reportMessage = QString(
                                "Total Income :   $%1\n"
                                "Total Expenses : $%2\n"
                                "Total Savings :  $%3\n")
                                .arg(totalIncome, 0, 'f', 2)
                                .arg(totalExpenses, 0, 'f', 2)
                                .arg(totalSavings, 0, 'f', 2);

    QMessageBox::information(this, "Financial Report", reportMessage);
}

void IncomeExpense::on_reportButton_clicked() {
    updateReport();
}






void IncomeExpense::on_bargraphbutton_clicked()
{
    QMessageBox::information(this,"Generating Bargraph","Welcome to nothing !!!");
}

