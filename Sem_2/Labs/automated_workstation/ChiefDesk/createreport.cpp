#include "createreport.h"
#include "ui_createreport.h"

CreateReport::CreateReport(QSqlDatabase& _db, QString _companyId, QString _employeeId, QString _taskId, QWidget *parent) :
    QDialog(parent), db(_db), companyId(_companyId), employeeId(_employeeId), taskId(_taskId),
    ui(new Ui::CreateReport)
{
    ui->setupUi(this);

    connect(ui->submitBtn, &QPushButton::clicked, this, &CreateReport::addReport);
}

CreateReport::~CreateReport()
{
    delete ui;
}

void CreateReport::addReport()
{
    QString reportText = ui->reportTextEdit->toPlainText();

    // Проверяем, что в таблице Tasks есть задача с указанным taskId и employeeId
    QSqlQuery query;
    query.prepare("SELECT * FROM Tasks WHERE task_id = :taskId AND employee_id = :employeeId");
    query.bindValue(":taskId", taskId);
    query.bindValue(":employeeId", employeeId);

    if (!query.exec())
    {
        qDebug() << "Ошибка проверки информации задачи:" << query.lastError().text();
        return;
    }

    if (!query.next())
    {
        qDebug() << "Задача не найдена для данного сотрудика.";
        return;
    }

    // Обновляем значение столбца report на reportText
    QSqlQuery updateQuery;
    updateQuery.prepare("UPDATE Tasks SET report = :reportText WHERE task_id = :taskId");
    updateQuery.bindValue(":reportText", reportText);
    updateQuery.bindValue(":taskId", taskId);

    if (!updateQuery.exec())
    {
        qDebug() << "Ошибка обновления отчета:" << updateQuery.lastError().text();
        return;
    }

    qDebug() << "Отчет добавлен/обновлен.";
    close();
}

