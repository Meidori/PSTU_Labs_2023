#ifndef EMPLOYEEDESK_H
#define EMPLOYEEDESK_H

#include <QMainWindow>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

#include "profile.h"
#include "employeesview.h"
#include "resourcesview.h"
#include "tasksviewforemployee.h"

namespace Ui {
class EmployeeDesk;
}

class EmployeeDesk : public QMainWindow
{
    Q_OBJECT

public:
    explicit EmployeeDesk(QSqlDatabase& _db, int employeeId, QWidget *parent = nullptr);
    ~EmployeeDesk();

public slots:
    void viewProfile();
    void viewEmployees();
    void viewResources();
    void viewTasks();

private:
    QSqlDatabase db;
    int id;
    Ui::EmployeeDesk *ui;
};

#endif // EMPLOYEEDESK_H
