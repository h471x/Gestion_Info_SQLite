#include "header/dbconfig.h"
#include "header/dbconnect.h"
#include <QCoreApplication>
#include <QHeaderView>
#include <QTableWidgetItem>
#include <QHBoxLayout>
#include "ui_mainwindow.h"
#include <QDialog>
#include <QApplication>

DatabaseManager::DatabaseManager(QObject* parent)
    : QObject(parent){
}

DatabaseManager::DatabaseManager(Ui::MainWindow* ui)
    : ui(ui), isDarkIcon(false)
{
}

DatabaseManager::~DatabaseManager(){
    if (mydb.isOpen()) {
        mydb.close();
    }
}

void DatabaseManager::changeIcon(){
    if(isDarkIcon){
        editBtn->setIcon(QIcon(":/darkicon/icons/dark/edit-2.svg"));
        deleteBtn->setIcon(QIcon(":/darkicon/icons/dark/trash.448x512.png"));
        isDarkIcon = false;
    }else if(!isDarkIcon){
        editBtn->setIcon(QIcon(":/darkicon/icons/dark/edit-2.svg"));
        deleteBtn->setIcon(QIcon(":/darkicon/icons/dark/trash.448x512.png"));
        isDarkIcon = true;
    }
}

void DatabaseManager::initTables(){
    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS CATEGORIE (IdCategorie INTEGER NOT NULL ,NomCategorie TEXT NOT NULL ,NbeMateriel INTEGER NOT NULL DEFAULT 0 ,PRIMARY KEY(IdCategorie));");
    query.exec("CREATE TABLE IF NOT EXISTS FOURNISSEUR (NomFournisseur TEXT NOT NULL ,PRIMARY KEY(NomFournisseur));");
    query.exec("CREATE TABLE IF NOT EXISTS ADMIN (UsernameAdmin TEXT NOT NULL UNIQUE ,Password TEXT NOT NULL ,NomAdmin TEXT NOT NULL ,PrenomAdmin TEXT NOT NULL ,TelephoneAdmin TEXT NOT NULL ,AdresseAdmin TEXT NOT NULL ,PRIMARY KEY(UsernameAdmin));");
    query.exec("CREATE TABLE IF NOT EXISTS UTILISATEUR (IdUtilisateur  INTEGER NOT NULL ,NomUtilisateur TEXT NOT NULL ,PrenomUtilisateur TEXT ,AdresseUtilisateur TEXT  NOT NULL ,TelephoneUtilisateur TEXT NOT NULL,PRIMARY KEY(IdUtilisateur));");
    query.exec("CREATE TABLE IF NOT EXISTS MATERIEL (IdMateriel INTEGER NOT NULL, NomMateriel TEXT NOT NULL, Marque TEXT NOT NULL, Etat TEXT NOT NULL, DEnregistrement TEXT NOT NULL, IdCategorie INTEGER NOT NULL, NomFournisseur TEXT, UsernameAdmin TEXT, IdUtilisateur INTEGER, PRIMARY KEY(IdMateriel), FOREIGN KEY(IdCategorie) REFERENCES CATEGORIE(IdCategorie) ON UPDATE CASCADE ON DELETE CASCADE, FOREIGN KEY(NomFournisseur) REFERENCES FOURNISSEUR(NomFournisseur) ON UPDATE SET NULL ON DELETE SET NULL, FOREIGN KEY(UsernameAdmin) REFERENCES ADMIN(UsernameAdmin) ON UPDATE CASCADE ON DELETE SET NULL, FOREIGN KEY(IdUtilisateur) REFERENCES UTILISATEUR(IdUtilisateur) ON UPDATE SET NULL ON DELETE SET NULL);");
}

void DatabaseManager::initValues(){
    QSqlQuery query;
    query.prepare("INSERT INTO ADMIN(UsernameAdmin, Password, NomAdmin, PrenomAdmin, TelephoneAdmin, AdresseAdmin) VALUES(:usernameadmin, :passwordadmin, :nameadmin, :prenom, :phone, :adresse)");
    query.bindValue(":usernameadmin", "admin");
    query.bindValue(":passwordadmin", "admin");
    query.bindValue(":nameadmin", "admin");
    query.bindValue(":prenom", "admin");
    query.bindValue(":phone", "033333333");
    query.bindValue(":adresse", "Fianarantsoa");
    query.exec();

    query.prepare("INSERT INTO CATEGORIE(NomCategorie, NbeMateriel) VALUES(:nom, :nbre)");
    query.bindValue(":nom", "ORDINATEUR");
    query.bindValue(":nbre", 10);
    query.exec();

    for(int i = 0; i < 20; i++){
        // Get the current date
        QDate currentDate = QDate::currentDate();
        query.prepare("INSERT OR IGNORE INTO MATERIEL(IdMateriel, NomMateriel, Marque, Etat, DEnregistrement, IdCategorie) VALUES(:idmat, :nomat, :marque, :etat, :date, :id)");
        query.bindValue(":idmat", i);
        query.bindValue(":nomat", "DELL INSPIRON");
        query.bindValue(":marque", "DELL");
        query.bindValue(":etat", "3");
        query.bindValue(":date", currentDate);
        query.bindValue(":id", i);
        query.exec();
    }

}

void DatabaseManager::createdb(){
    initTables();
    initValues();
}

bool DatabaseManager::initializeDatabase(){
    // Database init
    DatabaseConnection& dbInstance = DatabaseConnection::getInstance();
    QSqlDatabase db = dbInstance.getConnection();
    // here to init the database
    pragma(); // Activate pragma to avoid foreign keys conflicts
    createdb(); // Initiate the database
    return true;
}

void DatabaseManager::pragma(){
    QSqlQuery query;
    query.exec("PRAGMA foreign_keys = ON;");
    // Set this to ON to make Foreign Keys Work
}

void DatabaseManager::toggleBtn(){
    return;
}

QSqlTableModel* DatabaseManager::createUserTableModel(QTableWidget* tableWidget){
    QSqlTableModel* model = new QSqlTableModel(tableWidget, mydb);
    model->setTable("MATERIEL");

    // Populate the model with data
    model->select();

    // Set up the columns you want to display manually
    QList<int> selectedColumns = {0, 1, 2, 3, 4}; // Replace with the column indexes you want to display

    // Set up the QTableWidget with the model's data
    int tableColumnCount = selectedColumns.size();
    tableWidget->setColumnCount(tableColumnCount);
    tableWidget->setAlternatingRowColors(true);

    // Write the header of the table widget according to the columns name in the database
    for (int column = 0; column < tableColumnCount; ++column) {
        QTableWidgetItem* headerItem = new QTableWidgetItem(model->headerData(column, Qt::Horizontal).toString());
        tableWidget->setHorizontalHeaderItem(column, headerItem);
    }

    // Count the rows of the table
    int tableRowCount = model->rowCount();
    tableWidget->setRowCount(tableRowCount);

    // Some adjustements for the QTableView
    QFont tableFont;
    tableFont.setPointSize(11);
    tableWidget->horizontalHeader()->setFont(tableFont);
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableWidget->verticalHeader()->setVisible(false);
    tableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    tableWidget->setMouseTracking(true);
    tableWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // Add The Actions columns within the table widget
    tableWidget->setColumnCount(tableColumnCount + 1);
    tableWidget->setHorizontalHeaderItem(tableColumnCount, new QTableWidgetItem("Actions"));
    // Active les couleurs alternatives pour les lignes
    tableWidget->setAlternatingRowColors(true);

    // Parcourt toutes les lignes de la table
    for (int row = 0; row < tableWidget->rowCount(); ++row) {
        editBtn = new QPushButton(" Edit");
        deleteBtn = new QPushButton(" Delete");

        // Experimental : show the data of the current row by clicking on Edit
        connect(editBtn, &QPushButton::clicked, this, [tableWidget, row]() {
            QString id = tableWidget->item(row, 0)->data(Qt::DisplayRole).toString();
            QString nom = tableWidget->item(row, 1)->data(Qt::DisplayRole).toString();
            qDebug() << "Data of row" << row+1 << ": Id=" << id << " , NomMateriel=" << nom;
        });

        // Some adjustemts for the buttons

        //Tool Tips
        editBtn->setToolTip("Edit");
        deleteBtn->setToolTip("Delete");

        editBtn->setStyleSheet("QToolTip{background-color: #eaeff5;}");
        deleteBtn->setStyleSheet("QToolTip{background-color: #eaeff5;}");

        // Change the icons of the Buttons here
        editBtn->setIcon(QIcon(":/darkicon/icons/dark/edit-2.svg"));
        editBtn->setIconSize(QSize(30, 30));

        deleteBtn->setIcon(QIcon(":/darkicon/icons/dark/trash.448x512.png"));
        deleteBtn->setIconSize(QSize(30, 30));

        // Set the focud Policy to No focus
        editBtn->setFocusPolicy(Qt::NoFocus);
        deleteBtn->setFocusPolicy(Qt::NoFocus);

        QFont actionFont;
        actionFont.setPointSize(9);
        editBtn->setFont(actionFont);
        deleteBtn->setFont(actionFont);
        // Crée un widget pour le layout des boutons
        QWidget* actionsWidget = new QWidget();
        QHBoxLayout* actionsLayout = new QHBoxLayout(actionsWidget);
        actionsLayout->addWidget(editBtn);
        actionsLayout->addWidget(deleteBtn);
        actionsLayout->setContentsMargins(0, 0, 0, 0);
        actionsWidget->setLayout(actionsLayout);
        // Ajoute le widget de layout des boutons à chaque cellule de la colonne d'actions
        tableWidget->setCellWidget(row, tableColumnCount, actionsWidget);

        // Applique les couleurs alternatives aux lignes de la colonne d'actions
        if (row % 2 == 0) {
            tableWidget->cellWidget(row, tableColumnCount)->setStyleSheet("background-color: #c5cad6;");
        } else {
            tableWidget->cellWidget(row, tableColumnCount)->setStyleSheet("background-color: #a2a6ae;");
        }

        // Add delete button
        QTableWidgetItem* deleteItem = new QTableWidgetItem("Delete");
        tableWidget->setItem(row, tableColumnCount, deleteItem);

        //Define the Row Height here in order to make the edit & delete icon fit inside
        tableWidget->setRowHeight(row, 60);
    }


//    }

    for (int column = 0; column < tableColumnCount; ++column) {
        int selectedColumn = selectedColumns[column];
        QTableWidgetItem* headerItem = new QTableWidgetItem(model->headerData(selectedColumn, Qt::Horizontal).toString());
        tableWidget->setHorizontalHeaderItem(column, headerItem);

        for (int row = 0; row < tableRowCount; ++row) {
            QModelIndex index = model->index(row, selectedColumn);
            QString data = model->data(index).toString();
            QTableWidgetItem* item = new QTableWidgetItem(data);
            tableWidget->setItem(row, column, item);

            if (item) {
                item->setTextAlignment(Qt::AlignCenter);
                item->setFont(tableFont);
            }
        }
    }

    return model;
}
