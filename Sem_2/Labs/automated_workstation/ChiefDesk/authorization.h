#ifndef AUTHORIZATION_H
#define AUTHORIZATION_H

#include "loginwindow.h"
#include "registrationwindow.h"

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlError>

namespace Ui {
class Authorization;
}

class Authorization : public QMainWindow
{
    Q_OBJECT

public:
    explicit Authorization(QWidget *parent = nullptr);
    ~Authorization();

public slots:
    void login();
    void signUp();

private:
    QSqlDatabase db;
    Ui::Authorization *ui;
};

#endif // AUTHORIZATION_H
