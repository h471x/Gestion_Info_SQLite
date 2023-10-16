#include "headers/database/dbproduct.h"

ProductInit::ProductInit(){}

void ProductInit::initProduct(){
    tableProduct();
    valueProduct();
}

void ProductInit::tableProduct(){
    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS MATERIEL (IdMateriel INTEGER NOT NULL, NomMateriel TEXT NOT NULL, Marque TEXT NOT NULL, Etat TEXT NOT NULL, DEnregistrement TEXT NOT NULL, IdCategorie INTEGER NOT NULL, NomFournisseur TEXT, UsernameAdmin TEXT, IdUtilisateur INTEGER, PRIMARY KEY(IdMateriel), FOREIGN KEY(IdCategorie) REFERENCES CATEGORIE(IdCategorie) ON UPDATE CASCADE ON DELETE CASCADE, FOREIGN KEY(NomFournisseur) REFERENCES FOURNISSEUR(NomFournisseur) ON UPDATE SET NULL ON DELETE SET NULL, FOREIGN KEY(UsernameAdmin) REFERENCES ADMIN(UsernameAdmin) ON UPDATE CASCADE ON DELETE SET NULL, FOREIGN KEY(IdUtilisateur) REFERENCES UTILISATEUR(IdUtilisateur) ON UPDATE SET NULL ON DELETE SET NULL);");
}

void ProductInit::valueProduct(){
    QSqlQuery query;
    query.prepare("INSERT OR IGNORE INTO MATERIEL(IdMateriel, NomMateriel, Marque, Etat, DEnregistrement, IdCategorie) VALUES(:idmat, :nomat, :marque, :etat, :date, :id)");
    query.bindValue(":idmat", 1);
    query.bindValue(":nomat", "DELL INSPIRON");
    query.bindValue(":marque", "DELL");
    query.bindValue(":etat", "3");
    query.bindValue(":date", currentDate);
    query.bindValue(":id", 1);
    query.exec();
}
