#ifndef CHIEFDESK_H
#define CHIEFDESK_H

#include <QMainWindow>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

#include "profile.h"
#include "employeesview.h"
#include "resourcesview.h"
#include "tasksview.h"

namespace Ui {
class ChiefDesk;
}

class ChiefDesk : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChiefDesk(QSqlDatabase& _db, int employeeId, QWidget *parent = nullptr);
    ~ChiefDesk();

public slots:
    void viewProfile();
    void viewEmployees();
    void viewResources();
    void viewTasks();

private:
    QSqlDatabase db;
    int id;
    Ui::ChiefDesk *ui;
};

#endif // CHIEFDESK_H
