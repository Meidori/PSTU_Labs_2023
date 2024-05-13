#include "registrationwindow.h"
#include "ui_registrationwindow.h"

RegistrationWindow::RegistrationWindow(QSqlDatabase& _db, QWidget *parent) :
    QDialog(parent), db(_db),
    ui(new Ui::RegistrationWindow)
{
    ui->setupUi(this);

    connect(ui->modeCheckBox, &QCheckBox::stateChanged, this, &RegistrationWindow::changeMode);
    connect(ui->signupBtn, &QPushButton::clicked, this, &RegistrationWindow::reg);
}

RegistrationWindow::~RegistrationWindow()
{
    delete ui;
}

void RegistrationWindow::changeMode(int state)
{
    if (state == Qt::Checked)
    {
        ui->companyLabel->setText("Company");
    }
    else
    {
        ui->companyLabel->setText("Invitation");
    }
}

void RegistrationWindow::reg()
{
    QString log = ui->loginLineEdit->text();
    QString pass = ui->passLineEdit->text();
    QString comp = ui->companyLineEdit->text();
    bool modeChecked = ui->modeCheckBox->isChecked();
    if (!log.isEmpty() && !pass.isEmpty() && !comp.isEmpty() && modeChecked)
    {
        // Генерация company_code
        QString companyCode = comp + "-" + generateRandomCode(7);

        // Создание компании
        QSqlQuery query;
        query.prepare("INSERT INTO Companies (company_name, company_code) VALUES (:name, :code)");
        query.bindValue(":name", comp);
        query.bindValue(":code", companyCode);
        if (!query.exec())
        {
            qDebug() << "Error inserting company:" << query.lastError().text();
            return; // Выйти из функции при ошибке
        }

        // Получение company_id
        int companyId = query.lastInsertId().toInt();

        // Создание главного сотрудника
        query.prepare("INSERT INTO Employees (login, password, role, company_id) VALUES (:login, :password, :role, :companyId)");
        query.bindValue(":login", log);
        query.bindValue(":password", pass);
        query.bindValue(":role", "chief");
        query.bindValue(":companyId", companyId);
        if (!query.exec())
        {
            qDebug() << "Error inserting chief:" << query.lastError().text();
            return; // Выйти из функции при ошибке
        }

        // Успешно завершено
        qDebug() << "Registration successful!";
        close();
    }
    else if (!log.isEmpty() && !pass.isEmpty() && !comp.isEmpty() && !modeChecked)
    {
        // Поиск company_id по company_code
        QSqlQuery query;
        query.prepare("SELECT company_id FROM Companies WHERE company_code = :code");
        query.bindValue(":code", comp);
        if (!query.exec())
        {
            qDebug() << "Error searching for company:" << query.lastError().text();
            return; // Выйти из функции при ошибке
        }

        int companyId = -1;
        if (query.next())
        {
            companyId = query.value(0).toInt();
        }
        else
        {
            qDebug() << "Company with code" << comp << "not found!";
            return; // Выйти из функции, если компания не найдена
        }

        // Создание сотрудника с ролью "employee"
        query.prepare("INSERT INTO Employees (login, password, role, company_id) VALUES (:login, :password, :role, :companyId)");
        query.bindValue(":login", log);
        query.bindValue(":password", pass);
        query.bindValue(":role", "employee");
        query.bindValue(":companyId", companyId);
        if (!query.exec())
        {
            qDebug() << "Error inserting employee:" << query.lastError().text();
            return; // Выйти из функции при ошибке
        }

        // Успешно завершено
        qDebug() << "Employee registration successful!";
        close();
    }

}

// Функция для генерации случайного кода указанной длины
QString RegistrationWindow::generateRandomCode(int length)
{
    QString possibleCharacters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    QString randomString;
    for(int i = 0; i < length; i++)
    {
        int index = qrand() % possibleCharacters.length();
        QChar nextChar = possibleCharacters.at(index);
        randomString.append(nextChar);
    }
    return randomString;
}
