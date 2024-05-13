#include "getreport.h"
#include "ui_getreport.h"

GetReport::GetReport(QSqlDatabase& _db, QString _taskId, QWidget *parent) :
    QDialog(parent), db(_db), taskId(_taskId),
    ui(new Ui::GetReport)
{
    ui->setupUi(this);

    connect(ui->printBtn, &QPushButton::clicked, this, &GetReport::getReport);
    connect(ui->backBtn, &QPushButton::clicked, this, &GetReport::back);
}

GetReport::~GetReport()
{
    delete ui;
}

void GetReport::back()
{
    close();
}

void GetReport::getReport()
{
    // Выполнить запрос к базе данных для получения текста из поля report для указанного taskId
    QSqlQuery query;
    query.prepare("SELECT report FROM Tasks WHERE task_id = :taskId");
    query.bindValue(":taskId", taskId);

    if (!query.exec())
    {
        qDebug() << "Error fetching report from database:" << query.lastError().text();
        return;
    }

    // Проверить, есть ли данные
    if (query.next())
    {
        // Получить текст из поля report
        QString reportText = query.value(0).toString();

        // Установить текст в QTextEdit
        ui->reportTextEdit->setPlainText(reportText);
    }
    else
    {
        qDebug() << "No report found for the specified task ID.";
    }
}
