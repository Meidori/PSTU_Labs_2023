#ifndef REGISTRATIONWINDOW_H
#define REGISTRATIONWINDOW_H

#include <QDialog>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

namespace Ui {
class RegistrationWindow;
}

class RegistrationWindow : public QDialog
{
    Q_OBJECT

public:
    explicit RegistrationWindow(QSqlDatabase& _db, QWidget *parent = nullptr);
    ~RegistrationWindow();

    QString generateRandomCode(int length);

public slots:
    void changeMode(int state);
    void reg();

private:
    QSqlDatabase db;
    Ui::RegistrationWindow *ui;
};

#endif // REGISTRATIONWINDOW_H
