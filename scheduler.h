#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <QMainWindow>
#include <QList>
#include <QDate>
#include <QTime>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QDebug>

namespace Ui {
class Scheduler;
}

struct Lecture {
    QString date;
    QString time;
    int duration;
    QString description;
};

struct Deadline {
    QString date;
    QString description;
};

class Scheduler : public QMainWindow {
    Q_OBJECT

public:
    explicit Scheduler(QWidget *parent = nullptr,const QString& username = "");
    ~Scheduler();

private slots:
    void on_add_lecture_button_clicked();
    void on_add_deadline_button_clicked();

    void on_pushButton_clicked();

private:
    Ui::Scheduler *ui;
    QString currentUser;
    QList<Lecture> lectures;
    QList<Deadline> deadlines;

    void checkDeadlines();
    void loadDataFromCSV(const QString &filename);
    void saveDataToCSV(const QString &filename);

};

#endif // ACADEMICSCHEDULER_H

