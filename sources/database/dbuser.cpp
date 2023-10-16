#include "headers/database/dbuser.h"

UserInit::UserInit(){}

void UserInit::initUser(){
    tableUser();
//    valueUser();
}

void UserInit::tableUser(){
    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS UTILISATEUR (IdUtilisateur  INTEGER NOT NULL ,NomUtilisateur TEXT NOT NULL ,PrenomUtilisateur TEXT ,AdresseUtilisateur TEXT  NOT NULL ,TelephoneUtilisateur TEXT NOT NULL,PRIMARY KEY(IdUtilisateur));");
}

void UserInit::valueUser(){
    QSqlQuery query;
    query.exec("");
}
