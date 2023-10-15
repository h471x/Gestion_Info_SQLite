CREATE TABLE "MATERIEL" (
	"IdMateriel" INTEGER NOT NULL ,
	"NomMateriel" TEXT NOT NULL ,
	"Marque" TEXT NOT NULL ,
	"Etat" TEXT NOT NULL ,
	"DEnregistrement" TEXT NOT NULL , --DATE
	/*FOREIGN KEYS*/
	"IdCategorie" INTEGER NOT NULL ,
	"NomFournisseur" TEXT  ,
	"UsernameAdmin" TEXT ,
	"IdUtilisateur" INTEGER ,
	PRIMARY KEY("IdMateriel"),
	FOREIGN KEY("IdCategorie")
	REFERENCES "CATEGORIE" ("IdCategorie")
	ON UPDATE CASCADE
	ON DELETE CASCADE
	FOREIGN KEY("NomFournisseur")
	REFERENCES "FOURNISSEUR" ("NomFournisseur")
	ON UPDATE SET NULL
	ON DELETE SET NULL
	FOREIGN KEY("UsernameAdmin")
	REFERENCES "ADMIN" ("UsernameAdmin")
	ON UPDATE CASCADE
	ON DELETE SET NULL
	FOREIGN KEY ("IdUtilisateur")
	REFERENCES "UTILISATEUR" ("IdUtilisateur")
	ON UPDATE SET NULL
	ON DELETE SET NULL


);
CREATE TABLE "CATEGORIE" (
	"IdCategorie" INTEGER NOT NULL ,
	"NomCategorie" TEXT NOT NULL ,
	"NbeMateriel" INTEGER NOT NULL DEFAULT 0 ,
	PRIMARY KEY("IdCategorie")
);
CREATE TABLE "FOURNISSEUR" (
	"NomFournisseur" TEXT NOT NULL ,
	PRIMARY KEY("NomFournisseur")
);
CREATE TABLE "ADMIN" (
	"UsernameAdmin" TEXT NOT NULL UNIQUE ,
	"Password" TEXT NOT NULL ,
	"NomAdmin" TEXT NOT NULL ,
	"PrenomAdmin" TEXT ,
	"TelephoneAdmin" INTEGER NOT NULL ,
	"AdresseAdmin" TEXT NOT NULL ,
	PRIMARY KEY("UsernameAdmin")
);
CREATE TABLE "UTILISATEUR" (
	"IdUtilisateur"  INTEGER NOT NULL ,
	"NomUtilisateur" TEXT NOT NULL ,
	"PrenomUtilisateur" TEXT ,
	"AdresseUtilisateur" TEXT  NOT NULL ,
	"TelephoneUtilisateur" TEXT NOT NULL,
	PRIMARY KEY("IdUtilisateur")
	);

