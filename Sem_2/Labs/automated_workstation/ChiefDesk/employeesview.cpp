#include "employeesview.h"
#include "ui_employeesview.h"

EmployeesView::EmployeesView(QSqlDatabase& _db, QString _companyId, QWidget *parent) :
    QDialog(parent), db(_db), companyId(_companyId),
    ui(new Ui::EmployeesView)
{
    ui->setupUi(this);

    // Вывод таблицы сотрудников
    modelEmpl = new QSqlTableModel(this, db);
    modelEmpl->setTable("Employees");

    // Фильтрация по companyId
    modelEmpl->setFilter("company_id = " + companyId);

    // Скрытие столбца password
    modelEmpl->removeColumn(modelEmpl->fieldIndex("password"));

    modelEmpl->select();

    ui->employeesTableView->setModel(modelEmpl);

    // Вывод таблицы задач
    modelTasks = new QSqlTableModel(this, db);
    modelTasks->setTable("Tasks");

    // Фильтрация по companyId
    modelTasks->setFilter("company_id = " + companyId);

    modelTasks->select();

    ui->tasksTableView->setModel(modelTasks);

    connect(ui->backBtn, &QPushButton::clicked, this, &EmployeesView::back);
}

EmployeesView::~EmployeesView()
{
    delete ui;
    delete modelEmpl;
    delete modelTasks;
}

void EmployeesView::back()
{
    close();
}


