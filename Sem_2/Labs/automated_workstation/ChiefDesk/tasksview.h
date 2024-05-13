#ifndef TASKSVIEW_H
#define TASKSVIEW_H

#include <QDialog>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlTableModel>
#include <QSqlQuery>

#include "getreport.h"

namespace Ui {
class TasksView;
}

class TasksView : public QDialog
{
    Q_OBJECT

public:
    explicit TasksView(QSqlDatabase& _db, QString _companyId, QWidget *parent = nullptr);
    ~TasksView();

public slots:
    void back();
    void addTask();
    void getReport();

private:
    QSqlDatabase db;
    QString companyId;
    QSqlTableModel *modelTasks;
    Ui::TasksView *ui;
};

#endif // TASKSVIEW_H
