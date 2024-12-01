#include "scheduler.h"
#include "ui_scheduler.h"

Scheduler::Scheduler(QWidget *parent,const QString& username)
    : QMainWindow(parent), ui(new Ui::Scheduler), currentUser(username) {
    ui->setupUi(this);

    ui->table_schedule->setColumnCount(4);
    QStringList headers = {"Date", "Time", "Duration", "Description"};
    ui->table_schedule->setHorizontalHeaderLabels(headers);

    QString userSpecificFilename = currentUser + "_lectures.csv";
    loadDataFromCSV(userSpecificFilename);
    checkDeadlines();
}

Scheduler::~Scheduler() {

    delete ui;
}

void Scheduler::on_add_lecture_button_clicked() {
    QString date = ui->date_lecture->date().toString("yyyy-MM-dd");
    QString time = ui->time_lecture->time().toString("hh:mm");
    int duration = ui->duration_lecture->value();
    QString description = ui->lecture_description->text();

    Lecture newLecture = { date, time, duration, description };

    lectures.append(newLecture);

    int row = ui->table_schedule->rowCount();
    ui->table_schedule->insertRow(row);
    ui->table_schedule->setItem(row, 0, new QTableWidgetItem(date));
    ui->table_schedule->setItem(row, 1, new QTableWidgetItem(time));
    ui->table_schedule->setItem(row, 2, new QTableWidgetItem(QString::number(duration)));
    ui->table_schedule->setItem(row, 3, new QTableWidgetItem(description));

    ui->lecture_description->clear();
}

void Scheduler::on_add_deadline_button_clicked() {

    QString date = ui->date_deadline->date().toString("yyyy-MM-dd");
    QString description = ui->deadline_description->text();

    Deadline newDeadline = { date, description };

    deadlines.append(newDeadline);

    ui->deadline_description->clear();

    QMessageBox::information(this, "Success", "Deadline added successfully.");
}

void Scheduler::checkDeadlines() {
    QDate today = QDate::currentDate();
    for (const Deadline &deadline : deadlines) {
        QDate deadlineDate = QDate::fromString(deadline.date, "yyyy-MM-dd");
        if (deadlineDate.isValid() && deadlineDate == today) {
            QMessageBox::warning(this, "Deadline Reminder", "Today is the deadline for : " + deadline.description);
        }
    }
}

void Scheduler::loadDataFromCSV(const QString &filename) {
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    lectures.clear();
    ui->table_schedule->setRowCount(0);

    while (!file.atEnd()) {
        QByteArray line = file.readLine();
        QStringList fields = QString(line).split(',');

        if (fields.size() == 4) {
            Lecture lecture;
            lecture.date = fields[0].trimmed();
            lecture.time = fields[1].trimmed();
            lecture.duration = fields[2].trimmed().toInt();
            lecture.description = fields[3].trimmed();
            lectures.append(lecture);

            int row = ui->table_schedule->rowCount();
            ui->table_schedule->insertRow(row);
            ui->table_schedule->setItem(row, 0, new QTableWidgetItem(lecture.date));
            ui->table_schedule->setItem(row, 1, new QTableWidgetItem(lecture.time));
            ui->table_schedule->setItem(row, 2, new QTableWidgetItem(QString::number(lecture.duration)));
            ui->table_schedule->setItem(row, 3, new QTableWidgetItem(lecture.description));
        }
    }
}

void Scheduler::saveDataToCSV(const QString &filename) {
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);
    for (const Lecture &lecture : lectures) {
        out << lecture.date << "," << lecture.time << "," << lecture.duration << "," << lecture.description << "\n";
    }
}

void Scheduler::on_pushButton_clicked()
{
    QString userSpecificFilename = currentUser + "_lectures.csv";
    saveDataToCSV(userSpecificFilename);
    close();
}


