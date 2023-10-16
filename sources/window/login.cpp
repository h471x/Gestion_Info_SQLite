#include "headers/window/login.h"
#include "ui_login.h"

Login::Login(QWidget *parent) :
    QWidget(parent),
    LoginUi(new Ui::Login)
{
    LoginUi->setupUi(this);
    dbinitAdmin();
    windowConfig();
    keyConfig();
}

void Login::dbinitAdmin(){
    AdminInit admin;
    admin.initAdmin();
}

void Login::windowConfig(){
    Login::setWindowFlags(Qt::Window | Qt::WindowCloseButtonHint | Qt::WindowMinimizeButtonHint);
    Login::setFixedSize(600, 600);
}

void Login::keyConfig(){
    // Connect returnPressed() signal of UsernameLineEdit to switch focus to PasswordLineEdit
    connect(LoginUi->Username, &QLineEdit::returnPressed, this, [=]() {
        LoginUi->Password->setFocus();
    });

    // Connect returnPressed() signal of PasswordLineEdit to trigger the login button
    connect(LoginUi->Password, &QLineEdit::returnPressed, this, &Login::on_LoginBtn_clicked);

    // Connect the clicked() signal of the LoginButton to your login function
    connect(LoginUi->LoginBtn, &QPushButton::clicked, this, &Login::on_LoginBtn_clicked);

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

void setRedBorder(QLineEdit* lineEdit) {
    QString styleSheet = "QLineEdit { border-bottom: 1px solid red; }";
    lineEdit->setStyleSheet(styleSheet);
}

// Detects the arrow keys to change focus within the LoginUi
void Login::keyPressEvent(QKeyEvent *event) {
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

void Login::on_LoginBtn_clicked(){

    // Check if already logged in to prevent multiple windows
    if (isLoggedIn) {
        return;
    }

    DbInit& dbInit = DbInit::getInstance();
    QSqlDatabase db = dbInit.getConnection();
    QSqlQuery query(db);

    QString username = LoginUi->Username->text();
    QString password = LoginUi->Password->text();

    // Use placeholders in the query
    query.prepare("SELECT * FROM ADMIN WHERE UsernameAdmin = :username AND Password = :password");
    query.bindValue(":username", QVariant(username));
    query.bindValue(":password", QVariant(password));

    if (query.exec()) {
        if (query.next()) {
            // Login successful
            success();

        } else {
            // Incorrect username or password
            fail();
        }
    } else {
        return;
    }
}

void Login::success(){
    // Call the initProduct() function
    product.initProduct();
    provider.initProvider();
    user.initUser();
    category.initCategory();
    triggerup.initTriggerUp();
    triggerdown.initTriggerDown();

    isLoggedIn = true; // Set the login boolean
    this->close(); //close the login window
    MainApp *app = new MainApp(); // create the Main App Instance
    app->showMaximized();
}

void Login::fail(){
    LoginUi->Username->clear();
    LoginUi->Password->clear();
    setRedBorder(LoginUi->Username);
    setRedBorder(LoginUi->Password);
    LoginUi->Username->setFocus();
}

Login::~Login()
{
    delete LoginUi;
}
