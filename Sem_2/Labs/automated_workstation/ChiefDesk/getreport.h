#ifndef GETREPORT_H
#define GETREPORT_H

#include <QDialog>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

namespace Ui {
class GetReport;
}

class GetReport : public QDialog
{
    Q_OBJECT

public:
    explicit GetReport(QSqlDatabase& _db, QString _taskId, QWidget *parent = nullptr);
    ~GetReport();

public slots:
    void back();
    void getReport();

private:
    QSqlDatabase db;
    QString taskId;
    Ui::GetReport *ui;
};

#endif // GETREPORT_H
