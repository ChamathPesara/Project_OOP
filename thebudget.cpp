#include "theBudget.h"
#include "ui_theBudget.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QDebug>

TheBudget::TheBudget(const QString &username, QWidget *parent)
    : QDialog(parent),
    ui(new Ui::TheBudget),
    username(username)
{
    ui->setupUi(this);
    loadBudgets();

    ui->spinBox_food->setValue(budgets.value("Food", 0.0));
    ui->spinBox_entertainment->setValue(budgets.value("Entertainment", 0.0));
    ui->spinBox_traveling->setValue(budgets.value("Traveling", 0.0));
    ui->spinBox_clothing->setValue(budgets.value("Clothing", 0.0));
    ui->spinBox_education->setValue(budgets.value("Education Equipment", 0.0));
    ui->spinBox_fees->setValue(budgets.value("University Fees", 0.0));
}

TheBudget::~TheBudget()
{
    delete ui;
}


void TheBudget::loadBudgets()
{
    QString filePath = username + "_budget.csv";
    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList fields = line.split(",");
            if (fields.size() == 2) {
                budgets[fields[0]] = fields[1].toDouble();
            }
        }
        file.close();
    } else {
        qDebug() << "Failed to open budget file for user" << username;
    }
}

void TheBudget::saveBudgets()
{
    QString filePath = username + "_budget.csv";
    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        QTextStream out(&file);
        for (const QString &category : budgets.keys()) {
            out << category << "," << budgets[category] << "\n";
        }
        file.close();
    } else {
        qDebug() << "Failed to save budget file for user" << username;
    }
}

QMap<QString, double> TheBudget::getBudgets() const
{
    return budgets;
}

double TheBudget::calculateTotalExpensesForCategory(const QString &category, QTableWidget *expenseTable) const {
    double totalExpenses = 0.0;

    for (int row = 0; row < expenseTable->rowCount(); ++row) {
        QString currentCategory = expenseTable->item(row, 2)->text();
        double amount = expenseTable->item(row, 3)->text().toDouble();

        if (currentCategory == category) {
            totalExpenses += amount;
        }
    }

    return totalExpenses;
}

double TheBudget::getBudgetForCategory(const QString &category) const {
    return budgets.value(category, 0.0);
}


void TheBudget::on_saveButton_clicked()
{
    budgets["Food"] = ui->spinBox_food->value();
    budgets["Entertainment"] = ui->spinBox_entertainment->value();
    budgets["Traveling"] = ui->spinBox_traveling->value();
    budgets["Clothing"] = ui->spinBox_clothing->value();
    budgets["Education Equipment"] = ui->spinBox_education->value();
    budgets["University Fees"] = ui->spinBox_fees->value();

    saveBudgets();
    QMessageBox::information(this, "Success", "Budget limits added successfully.");

    accept();
}

void TheBudget::on_cancelButton_clicked(){
    close();
}



