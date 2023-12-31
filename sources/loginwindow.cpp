#include "header/loginwindow.h"
#include "ui_loginwindow.h"
#include "header/mainwindow.h"
#include "header/dbconnect.h"
#include "header/dbconfig.h"

// Add a member variable to track login status
bool isLoggedIn = false;

LoginWindow::LoginWindow(QWidget *parent) :
    QWidget(parent),
    LoginUi(new Ui::LoginWindow)
{
    LoginUi->setupUi(this);
    LoginWindow::setWindowFlags(Qt::Window | Qt::WindowCloseButtonHint | Qt::WindowMinimizeButtonHint);
    LoginWindow::setFixedSize(600, 600);

    // Assuming you have two QLineEdit widgets named UsernameLineEdit and PasswordLineEdit,
    // and a QPushButton named LoginButton in your UI.

    // Connect returnPressed() signal of UsernameLineEdit to switch focus to PasswordLineEdit
    connect(LoginUi->Username, &QLineEdit::returnPressed, this, [=]() {
        LoginUi->Password->setFocus();
    });

    // Connect returnPressed() signal of PasswordLineEdit to trigger the login button
    connect(LoginUi->Password, &QLineEdit::returnPressed, this, &LoginWindow::on_LoginBtn_clicked);

    // Connect the clicked() signal of the LoginButton to your login function
    connect(LoginUi->LoginBtn, &QPushButton::clicked, this, &LoginWindow::on_LoginBtn_clicked);

    connect(LoginUi->Username, &QLineEdit::textChanged, this, [=]() {
        if (!isLoggedIn) {
            // Reset the border when user starts typing
            LoginUi->Username->setStyleSheet("");
        }
    });

    connect(LoginUi->Password, &QLineEdit::textChanged, this, [=]() {
        if (!isLoggedIn) {
            // Reset the border when user starts typing
            LoginUi->Password->setStyleSheet("");
        }
    });



}

LoginWindow::~LoginWindow()
{
    delete LoginUi;
}

// Detects the arrow keys to change focus within the LoginUi
void LoginWindow::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Up) {
        //if Password as focus then focus on Username
        if (LoginUi->Password->hasFocus()) {
            LoginUi->Username->setFocus();
        }
    } else if (event->key() == Qt::Key_Down) {
        //if Username has focus then focus on Password
        if (LoginUi->Username->hasFocus()) {
            LoginUi->Password->setFocus();
        }
    }
}

void setRedBorder(QLineEdit* lineEdit) {
    QString styleSheet = "QLineEdit { border-bottom: 1px solid red; }";
    lineEdit->setStyleSheet(styleSheet);
}

void LoginWindow::on_LoginBtn_clicked()

{

    // Check if already logged in to prevent multiple windows
    if (isLoggedIn) {
        return;
    }

    // Connect db
    DatabaseConnection& dbInstance = DatabaseConnection::getInstance();
    QSqlDatabase db = dbInstance.getConnection();

    // Call the database creation here
    DatabaseManager* dbm = new DatabaseManager(this);
    dbm->createdb();

    QString username = LoginUi->Username->text();
    QString password = LoginUi->Password->text();

    // hashed passwords
    QString hashedPassword = password;

    QSqlQuery query;

    query.prepare("INSERT OR IGNORE INTO ADMIN(UsernameAdmin, Password, NomAdmin, TelephoneAdmin, AdresseAdmin) VALUES(:usernameadmin, :passwordadmin, :nameadmin, :phone, :adresse)");
    query.bindValue(":usernameadmin", "admin");
    query.bindValue(":passwordadmin", "admin");
    query.bindValue("nameadmin", "admin");
    query.bindValue(":phone", "033333333");
    query.bindValue(":adresse", "Fianarantsoa");
    query.exec();

    // Use placeholders in the query
    query.prepare("SELECT * FROM ADMIN WHERE UsernameAdmin = :username AND Password = :password");
    query.bindValue(":username", username);
    query.bindValue(":password", hashedPassword);

    if (query.exec()) {
        if (query.next()) {
            // Login successful
            isLoggedIn = true; // Set the login flag
            this->close();
            MainWindow *app = new MainWindow();
            app->showMaximized();
        } else {
            // Incorrect username or password
            LoginUi->Username->clear();
            LoginUi->Password->clear();
            setRedBorder(LoginUi->Username);
            setRedBorder(LoginUi->Password);
            LoginUi->Username->setFocus();
        }
    } else {
        return;
    }

}

