#include "authorization.h"
#include "ui_authorization.h"

Authorization::Authorization(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Authorization)
{
    ui->setupUi(this);

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("/home/meidori/Рабочий стол/main/Sem_2/Labs/automated_workstation/Database/chiefdesk.db");
    if (db.open())
    {
        ui->statusbar->showMessage("Успешное подключение к базе данных: " + db.databaseName());
    }
    else
    {
        ui->statusbar->showMessage("Ошибка при подключении к базе данных: " + db.lastError().databaseText());
    }

    connect(ui->logInBtn, &QPushButton::clicked, this, &Authorization::login);
    connect(ui->signUpBtn, &QPushButton::clicked, this, &Authorization::signUp);
}

Authorization::~Authorization()
{
    delete ui;
}

void Authorization::login()
{
    hide();

    LoginWindow loginWindow(db);
    loginWindow.setModal(true);
    loginWindow.exec();
}

void Authorization::signUp()
{
    hide();

    RegistrationWindow regWindow(db);
    regWindow.setModal(true);
    regWindow.exec();

    show();
}
