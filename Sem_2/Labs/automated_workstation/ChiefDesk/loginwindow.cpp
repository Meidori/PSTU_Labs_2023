#include "loginwindow.h"
#include "ui_loginwindow.h"

LoginWindow::LoginWindow(QSqlDatabase& _db, QWidget *parent) :
    QDialog(parent), db(_db),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);

    connect(ui->loginBtn, &QPushButton::clicked, this, &LoginWindow::login);
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::login()
{
    QString log = ui->loginLineEdit->text();
    QString pass = ui->passLineEdit->text();
    qDebug() << log << ":" << pass;
    if (!log.isEmpty() && !pass.isEmpty())
    {
        // Проверка наличия пользователя в базе данных
        QSqlQuery query;
        query.prepare("SELECT * FROM Employees WHERE login = :login AND password = :password");
        query.bindValue(":login", log);
        query.bindValue(":password", pass);
        if (!query.exec())
        {
            qDebug() << "Ошибка поиска пользователя:" << query.lastError().text();
            return; // Выйти из функции при ошибке
        }

        // Проверка роли пользователя
        if (query.next())
        {
            int employeeId = query.value("employee_id").toInt(); // Получаем employee_id из результата запроса
            QString role = query.value("role").toString();
            if (role == "chief")
            {
                // Открыть основное окно класса ChiefDesk
                hide();
                ChiefDesk *chiefDesk = new ChiefDesk(db, employeeId);
                chiefDesk->show();

            }
            else if (role == "employee")
            {
                // Открыть основное окно класса EmployeeDesk
                hide();
                EmployeeDesk *employeeDesk = new EmployeeDesk(db, employeeId);
                employeeDesk->show();
            }
        }
        else
        {
            qDebug() << "Пользователь не найден.";
        }
    }
}
