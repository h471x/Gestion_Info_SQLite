#include "headers/window/mainapp.h"
#include "ui_mainapp.h"

MainApp::MainApp(QWidget *parent)
    : QMainWindow(parent)
    , MainUi(new Ui::MainApp)
{
    MainUi->setupUi(this);
    initMainApp();
}

void MainApp::initMainApp(){
    MainUi->Content->setCurrentIndex(0); // Display the home page at startup
    MainUi->HomeBtn->setFocus(); //Focus the home button at startup
}

MainApp::~MainApp()
{
    delete MainUi;
}

void MainApp::on_HomeBtn_clicked(){ MainUi->Content->setCurrentIndex(0);}
void MainApp::on_MenuBtn_clicked(){ MainUi->Content->setCurrentIndex(1);}
void MainApp::on_AdminBtn_clicked(){ MainUi->Content->setCurrentIndex(2);}
void MainApp::on_FindBtn_clicked(){MainUi->Content->setCurrentIndex(3);}
void MainApp::on_FlowsBtn_clicked(){MainUi->Content->setCurrentIndex(4);}
void MainApp::on_OptionsBtn_clicked(){MainUi->Content->setCurrentIndex(5);}
void MainApp::on_HelpBtn_clicked(){MainUi->Content->setCurrentIndex(6);}
