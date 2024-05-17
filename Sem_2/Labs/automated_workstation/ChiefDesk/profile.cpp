#include "profile.h"
#include "ui_profile.h"

Profile::Profile(QList<QString> _profileData, QWidget *parent) :
    QDialog(parent), profileData(_profileData),
    ui(new Ui::Profile)
{
    ui->setupUi(this);

    // Обновляем информацию профиля:
    QString outputInfo = "Имя профиля: " + profileData[0] + "\nПрава доступа: " + profileData[1] +
            "\nНазвание компании: " + profileData[2] + "\nКоличество сотрудников: " + profileData[4];
    ui->infoLabel->setText(outputInfo);

    connect(ui->getInvCodeBtn, &QPushButton::clicked, this, &Profile::getInvCode);
    connect(ui->backBtn, &QPushButton::clicked, this, &Profile::back);
}

Profile::~Profile()
{
    QList<QTimer*> timers = this->findChildren<QTimer*>();
    for (QTimer* timer : timers) {
        timer->stop();
    }
    delete ui;
}

void Profile::getInvCode()
{
    QString role = profileData[1];
    QString code = profileData[3];

    if (role == "chief")
    {
        QClipboard *clipboard = QApplication::clipboard();
        clipboard->setText(code);
        ui->getInvCodeBtn->setText("Скопировано!");
        QTimer::singleShot(1000, [&]() {
            ui->getInvCodeBtn->setText("Получить код\nприглашения");
        });
    }
    else if (role == "employee")
    {
        ui->getInvCodeBtn->setText("Нет прав\nдоступа!");
        QTimer::singleShot(1000, [&]() {
            ui->getInvCodeBtn->setText("Получить код\nприглашения");
        });
    }
}

void Profile::back()
{
    close();
}


