#include "homepage.h"
#include "ui_homepage.h"
#include "login.h"
#include "incomeExpense.h"

Homepage::Homepage(QWidget *parent,const QString &username)
    : QMainWindow(parent)
    , ui(new Ui::Homepage)
{
    ui->setupUi(this);
    currentUsername = username;
}

Homepage::~Homepage()
{
    delete ui;
}

void Homepage::on_tracherButton_clicked()
{
    IncomeExpense *inexp = new IncomeExpense(this,currentUsername);
    inexp -> show();
}


void Homepage::on_schedularButton_clicked()
{
    Scheduler *schedular = new Scheduler(this,currentUsername);
    schedular -> show();
}


void Homepage::on_closeButton_clicked()
{
    close();
}

