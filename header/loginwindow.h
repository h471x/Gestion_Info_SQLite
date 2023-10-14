#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QWidget>
#include <QMainWindow>
#include <QSqlDatabase>

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

private slots:


    void on_LoginBtn_clicked();

private:
    Ui::LoginWindow *LoginUi;
    QSqlDatabase mydbadmin;
    void keyPressEvent(QKeyEvent *event) override;
};

#endif // LOGINWINDOW_H
