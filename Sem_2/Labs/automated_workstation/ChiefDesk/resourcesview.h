#ifndef RESOURCESVIEW_H
#define RESOURCESVIEW_H

#include <QDialog>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlError>
#include <QSqlQuery>

namespace Ui {
class ResourcesView;
}

class ResourcesView : public QDialog
{
    Q_OBJECT

public:
    explicit ResourcesView(QSqlDatabase& _db, QString _companyId, QWidget *parent = nullptr);
    ~ResourcesView();

public slots:
    void back();
    void addRes();
    void removeRes();

private:
    QSqlDatabase db;
    QString companyId;
    QSqlTableModel *modelRes;
    Ui::ResourcesView *ui;
};

#endif // RESOURCESVIEW_H
