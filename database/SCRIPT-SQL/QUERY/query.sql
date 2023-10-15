/*Activation des contraints des cles etrangeres */
PRAGMA foreign_keys = ON;

/*pour la page materiel disponible*/
SELECT MATERIEL.IdMateriel AS Id,MATERIEL.NomMateriel AS Nom,MATERIEL.Marque AS marque,MATERIEL.Etat AS Etat,CATEGORIE.NomCategorie AS Categorie,MATERIEL.DEnregistrement AS "Date d'acquisition",ADMIN.UsernameAdmin AS Admin,FOURNISSEUR.NomFournisseur AS Fournisseur
FROM MATERIEL 
INNER JOIN CATEGORIE ON CATEGORIE.IdCategorie = MATERIEL.IdCategorie
INNER JOIN ADMIN ON ADMIN.UsernameAdmin = MATERIEL.UsernameAdmin
INNER JOIN FOURNISSEUR ON FOURNISSEUR.NomFournisseur = MATERIEL.NomFournisseur;
