#include "headers/database/triggerdown.h"
#include <QDebug>

TriggerDownInit::TriggerDownInit(){}

void TriggerDownInit::initTriggerDown(){
    TriggerDown();
}

void TriggerDownInit::TriggerDown(){
    QSqlQuery query;
    query.exec("CREATE TRIGGER trigger_decrement_nbe_materiel AFTER DELETE ON MATERIEL WHEN old.IdCategorie =(SELECT IdCategorie FROM CATEGORIE WHERE CATEGORIE.IdCategorie = old.IdCategorie) BEGIN UPDATE CATEGORIE SET NbeMateriel = NbeMateriel -1; END;");
}
