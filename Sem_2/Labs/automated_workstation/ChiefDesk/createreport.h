#ifndef CREATEREPORT_H
#define CREATEREPORT_H

#include <QDialog>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

namespace Ui {
class CreateReport;
}

class CreateReport : public QDialog
{
    Q_OBJECT

public:
    explicit CreateReport(QSqlDatabase& _db, QString _companyId, QString _employeeId, QString _taskId, QWidget *parent = nullptr);
    ~CreateReport();

public slots:
    void addReport();

private:
    QSqlDatabase db;
    QString companyId;
    QString employeeId;
    QString taskId;
    Ui::CreateReport *ui;
};

#endif // CREATEREPORT_H
