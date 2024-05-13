#include "tasksviewforemployee.h"
#include "ui_tasksviewforemployee.h"

TasksViewForEmployee::TasksViewForEmployee(QSqlDatabase& _db, QString _companyId, QString _employeeId, QWidget *parent) :
    QDialog(parent), db(_db), companyId(_companyId), employeeId(_employeeId),
    ui(new Ui::TasksViewForEmployee)
{
    ui->setupUi(this);

    // Вывод таблицы задач
    modelTasks = new QSqlTableModel(this, db);
    modelTasks->setTable("Tasks");

    // Фильтрация по companyId
    modelTasks->setFilter("company_id = " + companyId);

    modelTasks->select();

    ui->tasksTableView->setModel(modelTasks);

    connect(ui->backBtn, &QPushButton::clicked, this, &TasksViewForEmployee::back);
    connect(ui->completeBtn, &QPushButton::clicked, this, &TasksViewForEmployee::complete);
    connect(ui->reportBtn, &QPushButton::clicked, this, &TasksViewForEmployee::createReport);
}

TasksViewForEmployee::~TasksViewForEmployee()
{
    delete ui;
}

void TasksViewForEmployee::back()
{
    close();
}

void TasksViewForEmployee::complete()
{
    QString taskId = ui->idLineEdit->text();

    // Проверяем, что taskId не пустой
    if (taskId.isEmpty())
    {
        qDebug() << "Task ID is required.";
        return;
    }

    // Проверяем, что в таблице Tasks есть задача с указанным taskId и employeeId
    QSqlQuery query;
    query.prepare("SELECT * FROM Tasks WHERE task_id = :taskId AND employee_id = :employeeId");
    query.bindValue(":taskId", taskId);
    query.bindValue(":employeeId", employeeId);

    if (!query.exec())
    {
        qDebug() << "Error checking task information:" << query.lastError().text();
        return;
    }

    if (!query.next())
    {
        qDebug() << "Task not found for the current employee.";
        return;
    }

    // Обновляем значение столбца status на 1
    QSqlQuery updateQuery;
    updateQuery.prepare("UPDATE Tasks SET status = 1 WHERE task_id = :taskId");
    updateQuery.bindValue(":taskId", taskId);

    if (!updateQuery.exec())
    {
        qDebug() << "Error updating task status:" << updateQuery.lastError().text();
        return;
    }

    qDebug() << "Task completed successfully.";
}

void TasksViewForEmployee::createReport()
{
    QString taskId = ui->idLineEdit->text();
    CreateReport report(db, companyId, employeeId, taskId);
    report.setModal(true);
    report.exec();
}
