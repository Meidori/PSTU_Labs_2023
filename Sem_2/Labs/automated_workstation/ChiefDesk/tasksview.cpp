#include "tasksview.h"
#include "ui_tasksview.h"

TasksView::TasksView(QSqlDatabase& _db, QString _companyId, QWidget *parent) :
    QDialog(parent), db(_db), companyId(_companyId),
    ui(new Ui::TasksView)
{
    ui->setupUi(this);

    // Вывод таблицы задач
    modelTasks = new QSqlTableModel(this, db);
    modelTasks->setTable("Tasks");

    // Фильтрация по companyId
    modelTasks->setFilter("company_id = " + companyId);

    modelTasks->select();

    ui->tasksTableView->setModel(modelTasks);

    connect(ui->backBtn, &QPushButton::clicked, this, &TasksView::back);
    connect(ui->addBtn, &QPushButton::clicked, this, &TasksView::addTask);
    connect(ui->getReportBtn, &QPushButton::clicked, this, &TasksView::getReport);
}

TasksView::~TasksView()
{
    delete ui;
}

void TasksView::back()
{
    close();
}

void TasksView::addTask()
{
    // Получаем данные из интерфейса
    QString taskName = ui->taskNameLineEdit->text();
    QString empId = ui->idLineEdit->text();

    // Проверяем, чтобы оба поля были заполнены
    if (taskName.isEmpty() || empId.isEmpty())
    {
        qDebug() << "Task name и employee ID обязательны.";
        return;
    }

    // Создаем задачу со статусом 0 (не выполнена)
    QSqlQuery query;
    query.prepare("INSERT INTO Tasks (task_name, status, employee_id, company_id) VALUES (:taskName, 0, :employeeId, :companyId)");
    query.bindValue(":taskName", taskName);
    query.bindValue(":employeeId", empId.toInt());
    query.bindValue(":companyId", companyId);

    if (!query.exec()) {
        qDebug() << "Ошибка при добавлении задачи:" << query.lastError().text();
        return;
    }

    qDebug() << "Задача успешно добавлена.";

    // Обновляем task_id в таблице Employees
    QSqlQuery updateQuery;
    updateQuery.prepare("UPDATE Employees SET task_id = :taskId WHERE employee_id = :employeeId");
    updateQuery.bindValue(":taskId", query.lastInsertId().toInt());
    updateQuery.bindValue(":employeeId", empId.toInt());

    if (!updateQuery.exec()) {
        qDebug() << "Ошибка обновления для сотрудника:" << updateQuery.lastError().text();
        return;
    }

    qDebug() << "Id задачи успешно обновлен.";
}

void TasksView::getReport()
{
    QString taskId = ui->taskIdLineEdit->text();
    GetReport report(db, taskId);
    report.setModal(true);
    report.exec();
}
