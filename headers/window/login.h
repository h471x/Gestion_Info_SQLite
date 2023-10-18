#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QMainWindow>
#include <QWidget>
#include <QKeyEvent>
#include <QString>
#include <QLineEdit>

#include "headers/window/mainapp.h"
#include "headers/database/init/dbadmin.h"
#include "headers/database/init/dbprovider.h"
#include "headers/database/init/dbcategory.h"
#include "headers/database/init/dbproduct.h"
#include "headers/database/init/dbuser.h"
#include "headers/database/init/triggerup.h"
#include "headers/database/init/triggerdown.h"

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
    void dbinit();
    void windowConfig();
    void keyConfig();
    void success();
    void fail();
    void keyPressEvent(QKeyEvent *event) override;

private: //variables
    bool isLoggedIn = false;

private: //db classes Instances
    AdminInit admin;
    CategoryInit category;
    ProductInit product;
    ProviderInit provider;
    UserInit user;
    TriggerUpInit triggerup;
    TriggerDownInit triggerdown;
    QSqlQuery query;

};

#endif // LOGIN_H
