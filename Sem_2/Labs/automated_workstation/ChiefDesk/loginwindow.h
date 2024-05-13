#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QDialog>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

#include "chiefdesk.h"
#include "employeedesk.h"

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QDialog
{
    Q_OBJECT

public:
    explicit LoginWindow(QSqlDatabase& _db, QWidget *parent = nullptr);
    ~LoginWindow();

public slots:
    void login();

private:
    QSqlDatabase db;
    Ui::LoginWindow *ui;
};

#endif // LOGINWINDOW_H
