#ifndef MAINAPP_H
#define MAINAPP_H

#include <QMainWindow>

#include "ui_mainapp.h"
#include "headers/database/show/product.h"
#include "headers/window/inscategory.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainApp; }
QT_END_NAMESPACE

class MainApp : public QMainWindow
{
    Q_OBJECT

public: //Constructor & Deconstructor
    MainApp(QWidget *parent = nullptr);
    ~MainApp();

private slots:
    void on_HomeBtn_clicked();
    void on_MenuBtn_clicked();
    void on_AdminBtn_clicked();
    void on_FindBtn_clicked();
    void on_FlowsBtn_clicked();
    void on_OptionsBtn_clicked();
    void on_HelpBtn_clicked();

    void on_LightBtn_clicked();

    void on_LightBtn_2_clicked();

    void on_NotifBtn_clicked();

    void on_pushButton_clicked();

private: //ui
    Ui::MainApp *MainUi;

public: //Methods
    void initMainApp();
    void focusHome();
    void focusMenu();
    void focusAdmin();
    void focusFind();
    void focusFlows();
    void focusOptions();
    void focusHelp();

public: //Methods
    void home();
    void menu();
    void admin();
    void find();
    void flows();
    void options();
    void help();

private: //data from database classes
    ProductShow product;

private: //table widget


};
#endif // MAINAPP_H
