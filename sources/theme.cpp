#include "header/theme.h"
#include <QApplication>

ThemeSwitcher::ThemeSwitcher(Ui::MainWindow* ui)
    : ui(ui), isDark(false)
{
}

void ThemeSwitcher::toggleTheme()
{
    if (isDark) {
        // Switch to light mode
        ui->LightBtn->setIcon(QIcon(":/darkicon/icons/dark/toggle-off.512x342.png"));
        ui->Body->setStyleSheet("background-color: #c5cad6; color: black;");
        ui->Menu->setStyleSheet("background-color: #eaeff5; color: black;");
        ui->Content->setStyleSheet("QTableWidget::item{color: #000;}QHeaderView::section{background-color: #a2a6ae;border-radius:3px;}QTableWidget::item{background-color: #c5cad6;}QTableWidget::item:Alternate{background-color: #a2a6ae;}#Content QTableWidget::item:Hover{background-color: #eaeff5;}");
        ui->SubMenu->setStyleSheet("QPushButton:Hover{background: #d4d8e2;}QPushButton:Focus{background: #c5cad6; color: black; border-left: 8px solid #202020;}");

        //change icons
        ui->HomeBtn->setIcon(QIcon(":/darkicon/icons/dark/estate.461x512.png"));
        ui->MenuBtn->setIcon(QIcon(":/darkicon/icons/dark/menu.svg"));
        ui->AdminBtn->setIcon(QIcon(":/darkicon/icons/dark/user-circle.511x512.png"));
        ui->FindBtn->setIcon(QIcon(":/darkicon/icons/dark/search.512x512.png"));
        ui->SearchBtn->setIcon(QIcon(":/darkicon/icons/dark/search.512x512.png"));
        ui->FlowsBtn->setIcon(QIcon(":/darkicon/icons/dark/location-arrow.512x512.png"));
        ui->OptionsBtn->setIcon(QIcon(":/darkicon/icons/dark/gear.512x512.png"));
        ui->HelpBtn->setIcon(QIcon(":/darkicon/icons/dark/question-circle.512x512.png"));
        ui->NotifBtn->setIcon(QIcon(":/darkicon/icons/dark/bell.448x512.png"));

        for (int row = 0; row < ui->tableWidget->rowCount(); ++row) {
            // Set up the columns you want to display manually
            QList<int> selectedColumns = {0, 1, 2, 3, 4}; // Replace with the column indexes you want to display
            int tableColumnCount = selectedColumns.size();
            if (row % 2 == 0) {
                ui->tableWidget->cellWidget(row, tableColumnCount)->setStyleSheet("background-color: #c5cad6;");
                ui->findWidget->cellWidget(row, tableColumnCount)->setStyleSheet("background-color: #c5cad6;");
            } else {
                ui->tableWidget->cellWidget(row, tableColumnCount)->setStyleSheet("background-color: #a2a6ae;");
                ui->findWidget->cellWidget(row, tableColumnCount)->setStyleSheet("background-color: #a2a6ae;");
            }
        }

        isDark = false;

    } else if(!isDark){
        // Switch to dark mode
        ui->LightBtn->setIcon(QIcon(":/icons/icons/toggle-on.512x342.png"));
        ui->Body->setStyleSheet("background-color: #272727; color: white;");
        ui->Menu->setStyleSheet("background-color: #000; color: white;");
        ui->Content->setStyleSheet("QTableWidget::item{color: #fff;}QHeaderView::section{background-color: #1f1f1f;border-radius:3px;}QTableWidget::item{background-color: #272727;}QTableWidget::item:Alternate{background-color: #1f1f1f;}#Content QTableWidget::item:Hover{background-color: #000;}");
        ui->SubMenu->setStyleSheet("QPushButton:Hover{background: #202020;}QPushButton:Focus{background: #272727;color: white; border-left: 8px solid white;}");
        //change icon
        ui->HomeBtn->setIcon(QIcon(":/icons/icons/estate.461x512.png"));
        ui->MenuBtn->setIcon(QIcon(":/icons/icons/menu.svg"));
        ui->AdminBtn->setIcon(QIcon(":/icons/icons/user-circle.511x512.png"));
        ui->FindBtn->setIcon(QIcon(":/icons/icons/search.512x512.png"));
        ui->SearchBtn->setIcon(QIcon(":/icons/icons/search.512x512.png"));
        ui->FlowsBtn->setIcon(QIcon(":/icons/icons/location-arrow.512x512.png"));
        ui->OptionsBtn->setIcon(QIcon(":/icons/icons/gear.512x512.png"));
        ui->HelpBtn->setIcon(QIcon(":/icons/icons/question-circle.512x512.png"));
        ui->NotifBtn->setIcon(QIcon(":/icons/icons/bell.448x512.png"));

        for (int row = 0; row < ui->tableWidget->rowCount(); ++row) {
            // Set up the columns you want to display manually
            QList<int> selectedColumns = {0, 1, 2, 3, 4}; // Replace with the column indexes you want to display
            int tableColumnCount = selectedColumns.size();
            if (row % 2 == 0) {
                ui->tableWidget->cellWidget(row, tableColumnCount)->setStyleSheet("background-color: #272727;");
                ui->findWidget->cellWidget(row, tableColumnCount)->setStyleSheet("background-color: #272727;");
            } else {
                ui->tableWidget->cellWidget(row, tableColumnCount)->setStyleSheet("background-color: #1f1f1f;");
                ui->findWidget->cellWidget(row, tableColumnCount)->setStyleSheet("background-color: #1f1f1f;");
            }
        }

        isDark = true;
    }
}

