#include "resourcesview.h"
#include "ui_resourcesview.h"

ResourcesView::ResourcesView(QSqlDatabase& _db, QString _companyId, QWidget *parent) :
    QDialog(parent), db(_db), companyId(_companyId),
    ui(new Ui::ResourcesView)
{
    ui->setupUi(this);

    // Вывод таблицы задач
    modelRes = new QSqlTableModel(this, db);
    modelRes->setTable("Resources");

    // Фильтрация по companyId
    modelRes->setFilter("company_id = " + companyId);

    modelRes->select();

    ui->resTableView->setModel(modelRes);

    connect(ui->backBtn, &QPushButton::clicked, this, &ResourcesView::back);
    connect(ui->addBtn, &QPushButton::clicked, this, &ResourcesView::addRes);
    connect(ui->removeBtn, &QPushButton::clicked, this, &ResourcesView::removeRes);
}

ResourcesView::~ResourcesView()
{
    delete ui;
}

void ResourcesView::back()
{
    close();
}

void ResourcesView::addRes()
{
    // Получаем данные из интерфейса
    QString resName = ui->resNameLineEdit->text();
    QString amountStr = ui->amountLineEdit->text();

    // Проверяем, чтобы оба поля были заполнены
    if (resName.isEmpty() || amountStr.isEmpty())
    {
        qDebug() << "Resource name and amount are required.";
        return;
    }

    bool success = false;

    // Проверяем, существует ли ресурс с таким именем в базе данных
    QSqlQuery query;
    query.prepare("SELECT * FROM Resources WHERE res_name = :resName");
    query.bindValue(":resName", resName);
    if (query.exec() && query.next())
    {
        // Ресурс существует, обновляем его количество
        int currentAmount = query.value("res_amount").toInt();
        int amountToAdd = amountStr.toInt();
        int newAmount = currentAmount + amountToAdd;

        QSqlQuery updateQuery;
        updateQuery.prepare("UPDATE Resources SET res_amount = :newAmount WHERE res_name = :resName");
        updateQuery.bindValue(":newAmount", newAmount);
        updateQuery.bindValue(":resName", resName);
        success = updateQuery.exec();
    }
    else
    {
        // Ресурс не существует, добавляем его в базу данных
        QSqlQuery insertQuery;
        insertQuery.prepare("INSERT INTO Resources (res_name, res_amount, company_id) VALUES (:resName, :amount, :companyId)");
        insertQuery.bindValue(":resName", resName);
        insertQuery.bindValue(":amount", amountStr.toInt());
        insertQuery.bindValue(":companyId", companyId);
        success = insertQuery.exec();
    }

    if (success)
    {
        qDebug() << "Resource added/updated successfully.";
    }
    else
    {
        qDebug() << "Error adding/updating resource:" << query.lastError().text();
    }
}

void ResourcesView::removeRes()
{
    // Получаем данные из интерфейса
    QString resName = ui->resNameLineEdit->text();
    QString amountStr = ui->amountLineEdit->text();

    // Проверяем, чтобы оба поля были заполнены
    if (resName.isEmpty() || amountStr.isEmpty())
    {
        qDebug() << "Resource name and amount are required.";
        return;
    }

    // Получаем текущее количество ресурсов из базы данных
    QSqlQuery query;
    query.prepare("SELECT res_amount FROM Resources WHERE res_name = :resName");
    query.bindValue(":resName", resName);

    if (!query.exec())
    {
        qDebug() << "Error retrieving resource information:" << query.lastError().text();
        return;
    }

    if (!query.next())
    {
        qDebug() << "Resource not found.";
        return;
    }

    int currentAmount = query.value("res_amount").toInt();
    int amountToRemove = amountStr.toInt();

    // Проверяем, чтобы количество ресурсов после удаления не стало меньше нуля
    int newAmount = currentAmount - amountToRemove;
    if (newAmount < 0)
    {
        newAmount = 0;
    }

    // Обновляем количество ресурсов в базе данных
    QSqlQuery updateQuery;
    updateQuery.prepare("UPDATE Resources SET res_amount = :newAmount WHERE res_name = :resName");
    updateQuery.bindValue(":newAmount", newAmount);
    updateQuery.bindValue(":resName", resName);

    if (!updateQuery.exec())
    {
        qDebug() << "Error updating resource amount:" << updateQuery.lastError().text();
        return;
    }

    qDebug() << "Resource amount updated successfully.";
}

