#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include "homepage.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class login;
}
QT_END_NAMESPACE

class login : public QMainWindow
{
    Q_OBJECT

public:
    login(QWidget *parent = nullptr);
    ~login();

private slots:
    void on_theloginButton_clicked();

    void on_registerButton_clicked();

    void on_exitButton_clicked();

private:
    Ui::login *ui;
    Homepage *homepage;
};
#endif // LOGIN_H
