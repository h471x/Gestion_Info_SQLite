#include "header/mainwindow.h"
#include "header/loginwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    LoginWindow login;
    login.show();
//    MainWindow w;
//    w.showMaximized();
    return a.exec();
}
