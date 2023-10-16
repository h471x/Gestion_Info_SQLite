#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QMainWindow>
#include <QWidget>
#include <QKeyEvent>
#include <QString>
#include <QLineEdit>

#include "headers/window/mainapp.h"
#include "headers/database/dbadmin.h"
#include "headers/database/dbprovider.h"
#include "headers/database/dbcategory.h"
#include "headers/database/dbuser.h"
#include "headers/database/triggerup.h"
#include "headers/database/triggerdown.h"
#include "headers/database/dbproduct.h"

namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public: //constructor
    explicit Login(QWidget *parent = nullptr);
    ~Login();

private slots:
    void on_LoginBtn_clicked();

private: //ui
    Ui::Login *LoginUi;

private: //methods
    void dbinitAdmin();
    void windowConfig();
    void keyConfig();
    void success();
    void fail();
    void keyPressEvent(QKeyEvent *event) override;

private: //variables
    bool isLoggedIn = false;

private: //db classes Instances
    ProviderInit provider;
    UserInit user;
    CategoryInit category;
    TriggerUpInit triggerup;
    TriggerDownInit triggerdown;
    ProductInit product;
};

#endif // LOGIN_H
