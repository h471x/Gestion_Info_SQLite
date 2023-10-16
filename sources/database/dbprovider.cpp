#include "headers/database/dbprovider.h"

ProviderInit::ProviderInit(){}

void ProviderInit::initProvider(){
    tableProvider();
//    valueProvider();
}

void ProviderInit::tableProvider(){
    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS FOURNISSEUR (NomFournisseur TEXT NOT NULL ,PRIMARY KEY(NomFournisseur));");
}

void ProviderInit::valueProvider(){
    QSqlQuery query;
    query.exec("");
}
