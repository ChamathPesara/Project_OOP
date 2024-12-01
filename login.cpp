#include "login.h"
#include "ui_login.h"
#include <QFile>
#include <QTextStream>
#include <QCryptographicHash>
#include <QMessageBox>
#include "homepage.h"

login::login(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::login)
{
    ui->setupUi(this);
}

login::~login()
{
    delete ui;
}

QString hashPassword(const QString &password) {
    return QString(QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256).toHex());
}

QString currentUsername;

void login::on_theloginButton_clicked()
{
    QString username = ui->usernamelineEdit->text();
    QString password = ui->passwordlineEdit->text();

    QFile file("user1.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList fields = line.split(':');
            if (fields[0] == username && fields[1] == hashPassword(password)) {
                QMessageBox::information(this, "Logged Successfully", "Welcome, " + username + " !!!");

                Homepage *homepage = new Homepage(this,username);
                homepage -> show();

                file.close();
                return;
            }
        }
        file.close();
    }

    QMessageBox::warning(this, "Login Failed", "Invalid username or password.");
}


void login::on_registerButton_clicked()
{
    QString username = ui->usernamelineEdit->text();
    QString password = ui->passwordlineEdit->text();

    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Enter your Username and password.");
        return;
    }

    QFile file("user1.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList fields = line.split(':');
            if (fields[0] == username) {
                QMessageBox::warning(this, "Registration Error", "Username already exists.");
                file.close();
                return;
            }
        }
        file.close();
    }

    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        out << username << ":" << hashPassword(password) << "\n";
        file.close();

        // Create separate CSV files for the new user
        QFile incomeFile(username + "_income.csv");
        QFile expensesFile(username + "_expenses.csv");

        if (incomeFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&incomeFile);
            out << "Date,Amount,Source\n";
            incomeFile.close();
        }

        if (expensesFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&expensesFile);
            out << "Date,Amount,Category\n";
            expensesFile.close();
        }

        QMessageBox::information(this, "Registration Successful", "Account created successfully !!! ");
    } else {
        QMessageBox::critical(this, "File Error", "Unable to open file for writing.");
    }
}

void login::on_exitButton_clicked()
{
    close();
}


