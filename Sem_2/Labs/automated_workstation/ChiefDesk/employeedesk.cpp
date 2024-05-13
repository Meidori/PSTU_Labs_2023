#include "employeedesk.h"
#include "ui_employeedesk.h"

EmployeeDesk::EmployeeDesk(QSqlDatabase& _db, int employeeId, QWidget *parent) :
    QMainWindow(parent), db(_db), id(employeeId),
    ui(new Ui::EmployeeDesk)
{
    ui->setupUi(this);

    connect(ui->viewProfileBtn, &QPushButton::clicked, this, &EmployeeDesk::viewProfile);
    connect(ui->viewEmployeesBtn, &QPushButton::clicked, this, &EmployeeDesk::viewEmployees);
    connect(ui->resControlBtn, &QPushButton::clicked, this, &EmployeeDesk::viewResources);
    connect(ui->viewTasksBtn, &QPushButton::clicked, this, &EmployeeDesk::viewTasks);
}

EmployeeDesk::~EmployeeDesk()
{
    delete ui;
}

void EmployeeDesk::viewProfile()
{
    // Запрос для получения данных профиля сотрудника
    QSqlQuery profileQuery;
    profileQuery.prepare("SELECT Employees.login, Employees.role, Companies.company_name, Companies.company_code "
                         "FROM Employees "
                         "JOIN Companies ON Employees.company_id = Companies.company_id "
                         "WHERE employee_id = :id");
    profileQuery.bindValue(":id", id);
    if (!profileQuery.exec())
    {
        qDebug() << "Error retrieving profile data:" << profileQuery.lastError().text();
        return;
    }

    // Извлечение данных профиля сотрудника
    QString login, role, companyName, invitationCode;
    if (profileQuery.next())
    {
        login = profileQuery.value("login").toString();
        role = profileQuery.value("role").toString();
        companyName = profileQuery.value("company_name").toString();
        invitationCode = profileQuery.value("company_code").toString();
    }
    else
    {
        qDebug() << "Profile data not found for employee with ID:" << id;
        return;
    }

    // Запрос для подсчета количества сотрудников, принадлежащих той же компании
    QSqlQuery countQuery;
    countQuery.prepare("SELECT COUNT(*) AS amountOfEmployees "
                       "FROM Employees "
                       "WHERE company_id = (SELECT company_id FROM Companies WHERE company_name = :companyName)");
    countQuery.bindValue(":companyName", companyName);
    if (!countQuery.exec())
    {
        qDebug() << "Error counting employees:" << countQuery.lastError().text();
        return;
    }

    // Извлечение количества сотрудников
    QString amountOfEmployees;
    if (countQuery.next())
    {
        amountOfEmployees = countQuery.value("amountOfEmployees").toString();
    }
    else
    {
        qDebug() << "Error: Count query returned no results";
        return;
    }

    // Вывод в консоль
    qDebug() << "Profile data retrieved successfully:";
    qDebug() << "Login:" << login;
    qDebug() << "Role:" << role;
    qDebug() << "Company Name:" << companyName;
    qDebug() << "Invitation Code:" << invitationCode;
    qDebug() << "Amount of Employees in the Same Company:" << amountOfEmployees;

    QList<QString> profileData;
    profileData.append(login);
    profileData.append(role);
    profileData.append(companyName);
    profileData.append(invitationCode);
    profileData.append(amountOfEmployees);

    Profile prof (profileData);
    prof.setModal(true);
    prof.exec();
}

void EmployeeDesk::viewEmployees()
{
    // Запрос для получения company_id сотрудника по его id
    QSqlQuery companyIdQuery;
    companyIdQuery.prepare("SELECT company_id FROM Employees WHERE employee_id = :id");
    companyIdQuery.bindValue(":id", id);
    if (!companyIdQuery.exec())
    {
        qDebug() << "Error retrieving company_id:" << companyIdQuery.lastError().text();
        return;
    }

    QString companyId; // Переменная для хранения company_id сотрудника
    if (companyIdQuery.next())
    {
        companyId = companyIdQuery.value("company_id").toString();
    }
    else
    {
        qDebug() << "Error: company_id not found for employee with ID:" << id;
        return;
    }

    // Открывает окно сотрудников с полученным company_id
    EmployeesView empl(db, companyId);
    empl.setModal(true);
    empl.exec();
}

void EmployeeDesk::viewResources()
{
    // Запрос для получения company_id сотрудника по его id
    QSqlQuery companyIdQuery;
    companyIdQuery.prepare("SELECT company_id FROM Employees WHERE employee_id = :id");
    companyIdQuery.bindValue(":id", id);
    if (!companyIdQuery.exec())
    {
        qDebug() << "Error retrieving company_id:" << companyIdQuery.lastError().text();
        return;
    }

    QString companyId; // Переменная для хранения company_id сотрудника
    if (companyIdQuery.next())
    {
        companyId = companyIdQuery.value("company_id").toString();
    }
    else
    {
        qDebug() << "Error: company_id not found for employee with ID:" << id;
        return;
    }

    // Открывает окно сотрудников с полученным company_id
    ResourcesView res(db, companyId);
    res.setModal(true);
    res.exec();
}

void EmployeeDesk::viewTasks()
{
    // Запрос для получения company_id сотрудника по его id
    QSqlQuery companyIdQuery;
    companyIdQuery.prepare("SELECT company_id FROM Employees WHERE employee_id = :id");
    companyIdQuery.bindValue(":id", id);
    if (!companyIdQuery.exec())
    {
        qDebug() << "Error retrieving company_id:" << companyIdQuery.lastError().text();
        return;
    }

    QString companyId; // Переменная для хранения company_id сотрудника
    if (companyIdQuery.next())
    {
        companyId = companyIdQuery.value("company_id").toString();
    }
    else
    {
        qDebug() << "Error: company_id not found for employee with ID:" << id;
        return;
    }

    QString employeeId = QString::number(id);

    // Открывает окно сотрудников с полученным company_id
    TasksViewForEmployee tasks(db, companyId, employeeId);
    tasks.setModal(true);
    tasks.exec();
}
