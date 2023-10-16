#include "headers/database/triggerup.h"

TriggerUpInit::TriggerUpInit(){}

void TriggerUpInit::initTriggerUp(){
    TriggerUp();
}

void TriggerUpInit::TriggerUp(){
    QSqlQuery query;
    query.exec("CREATE TRIGGER trigger_increment_materiel AFTER INSERT ON MATERIEL WHEN new.IdCategorie = (SELECT IdCategorie FROM CATEGORIE WHERE CATEGORIE.IdCategorie = new.IdCategorie) BEGIN UPDATE CATEGORIE SET NbeMateriel=NbeMateriel+1; END;");
}
