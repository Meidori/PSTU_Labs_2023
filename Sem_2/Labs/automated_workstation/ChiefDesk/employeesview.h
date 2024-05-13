#ifndef EMPLOYEESVIEW_H
#define EMPLOYEESVIEW_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QDebug>
#include <QSqlTableModel>
#include <QTableView>

namespace Ui {
class EmployeesView;
}

class EmployeesView : public QDialog
{
    Q_OBJECT

public:
    explicit EmployeesView(QSqlDatabase& _db, QString _companyId, QWidget *parent = nullptr);
    ~EmployeesView();

    void printTable();

public slots:
    void back();

private:
    QSqlDatabase db;
    QString companyId;
    QSqlTableModel *modelEmpl;
    QSqlTableModel *modelTasks;
    Ui::EmployeesView *ui;
};

#endif // EMPLOYEESVIEW_H
