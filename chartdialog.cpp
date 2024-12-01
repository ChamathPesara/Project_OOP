#include "chartdialog.h"
#include "ui_chartdialog.h"

chartDialog::chartDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::chartDialog)
{
    ui->setupUi(this);
}

chartDialog::~chartDialog()
{
    delete ui;
}
