#ifndef CHARTDIALOG_H
#define CHARTDIALOG_H

#include <QDialog>

namespace Ui {
class chartDialog;
}

class chartDialog : public QDialog
{
    Q_OBJECT

public:
    explicit chartDialog(QWidget *parent = nullptr);
    ~chartDialog();

private:
    Ui::chartDialog *ui;
};

#endif // CHARTDIALOG_H
