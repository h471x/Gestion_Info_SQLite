#include "header/mainwindow.h"
#include "ui_mainwindow.h"
#include "header/theme.h"
#include "header/dbconfig.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , Mainui(new Ui::MainWindow)
{
    Mainui->setupUi(this);

    Mainui->Content->setCurrentIndex(0); // Display the home page at startup
    Mainui->HomeBtn->setFocus(); //Focus the home button at startup

    // theme switcher object
    ThemeSwitcher* themeSwitcher = new ThemeSwitcher(Mainui);

    // Connect the button click signal to the themeSwitcher slot
    connect(Mainui->LightBtn, &QPushButton::clicked, themeSwitcher, &ThemeSwitcher::toggleTheme);

    // Create an instance of DatabaseManager to handle database operations
    DatabaseManager* dbManager = new DatabaseManager(this);

    // Initialize the database
    if (dbManager->initializeDatabase()) {
        // Database initialization successful
        // Create the user table model and use it with your QTableWidget
        // Insert the data PRODUCT in Mainui->tableWidget
        dbManager->createUserTableModel(Mainui->tableWidget);
        dbManager->createUserTableModel(Mainui->findWidget);
    } else {
        // Handle the case where database initialization fails
        return;
    }
}

MainWindow::~MainWindow()
{
    delete Mainui;
}

void MainWindow::on_HomeBtn_clicked(){ Mainui->Content->setCurrentIndex(0);}
void MainWindow::on_MenuBtn_clicked(){ Mainui->Content->setCurrentIndex(1);}
void MainWindow::on_AdminBtn_clicked(){ Mainui->Content->setCurrentIndex(2);}
void MainWindow::on_FindBtn_clicked(){Mainui->Content->setCurrentIndex(3);}
void MainWindow::on_FlowsBtn_clicked(){Mainui->Content->setCurrentIndex(4);}
void MainWindow::on_OptionsBtn_clicked(){Mainui->Content->setCurrentIndex(5);}
void MainWindow::on_HelpBtn_clicked(){Mainui->Content->setCurrentIndex(6);}

