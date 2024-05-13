#include "profile.h"
#include "ui_profile.h"

Profile::Profile(QList<QString> _profileData, QWidget *parent) :
    QDialog(parent), profileData(_profileData),
    ui(new Ui::Profile)
{
    ui->setupUi(this);

    // Обновляем информацию профиля:
    QString outputInfo = "Profile name: " + profileData[0] + "\nAccess rights: " + profileData[1] +
            "\nCompany name: " + profileData[2] + "\nAmount of employees: " + profileData[4];
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
        ui->getInvCodeBtn->setText("Copied!");
        QTimer::singleShot(1000, [&]() {
            ui->getInvCodeBtn->setText("Get invitation\ncode");
        });
    }
    else if (role == "employee")
    {
        ui->getInvCodeBtn->setText("No access!");
        QTimer::singleShot(1000, [&]() {
            ui->getInvCodeBtn->setText("Get invitation\ncode");
        });
    }
}

void Profile::back()
{
    close();
}


