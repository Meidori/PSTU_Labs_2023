#ifndef TASKSVIEWFOREMPLOYEE_H
#define TASKSVIEWFOREMPLOYEE_H

#include <QDialog>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QSqlError>

#include "createreport.h"

namespace Ui {
class TasksViewForEmployee;
}

class TasksViewForEmployee : public QDialog
{
    Q_OBJECT

public:
    explicit TasksViewForEmployee(QSqlDatabase& _db, QString _companyId, QString _employeeId, QWidget *parent = nullptr);
    ~TasksViewForEmployee();

public slots:
    void back();
    void complete();
    void createReport();

private:
    QSqlDatabase db;
    QString companyId;
    QString employeeId;
    QSqlTableModel *modelTasks;
    Ui::TasksViewForEmployee *ui;
};

#endif // TASKSVIEWFOREMPLOYEE_H
