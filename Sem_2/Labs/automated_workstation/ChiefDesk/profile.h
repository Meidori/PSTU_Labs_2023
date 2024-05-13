#ifndef PROFILE_H
#define PROFILE_H

#include <QDialog>
#include <QClipboard>
#include <QTimer>

namespace Ui {
class Profile;
}

class Profile : public QDialog
{
    Q_OBJECT

public:
    explicit Profile(QList<QString> _profileData, QWidget *parent = nullptr);
    ~Profile();

public slots:
    void getInvCode();
    void back();

private:
    QList<QString> profileData;
    Ui::Profile *ui;
};

#endif // PROFILE_H
