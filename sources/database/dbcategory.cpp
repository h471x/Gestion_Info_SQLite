#include "headers/database/dbcategory.h"

CategoryInit::CategoryInit(){}

void CategoryInit::initCategory(){
    tableCategory();
    valueCategory();
}

void CategoryInit::tableCategory(){
    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS CATEGORIE (IdCategorie INTEGER NOT NULL ,NomCategorie TEXT NOT NULL ,NbeMateriel INTEGER NOT NULL DEFAULT 0 ,PRIMARY KEY(IdCategorie));");
}

void CategoryInit::valueCategory(){
    QSqlQuery query;
    query.prepare("INSERT INTO CATEGORIE(IdCategorie, NomCategorie) VALUES(:idcat, :nom)");
    query.bindValue(":idcat", 1);
    query.bindValue(":nom", "ORDINATEUR");
    query.exec();
}
