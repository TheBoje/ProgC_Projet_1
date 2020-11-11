/********************************************************************
 * Module de Voiture : entête
 ********************************************************************/

#ifndef VOITURE_H
#define VOITURE_H

#include <stdio.h>

struct VoitureP;
typedef struct VoitureP * Voiture;
typedef const struct VoitureP * const_Voiture;

/*----------*
 * Statistiques
 *----------*/
int voi_stat_getNbInitialisations();
int voi_stat_getNbImmatriculations();
int voi_stat_getAnneeMin();
int voi_stat_getAnneeMax();


/*----------*
 * Constructeurs, destructeur, autre
 *----------*/
Voiture voi_creer(const char *marque, int annee, int kilometrage,
                  int nbImmatriculations, const char * immatriculations[]);

Voiture voi_creerCopie(const_Voiture source);

// à partir d'un fichier écrit par voi_ecrireFichier
Voiture voi_creerFromFichier(FILE *fd);

void voi_detruire(Voiture *pself);

void voi_swap(Voiture v1, Voiture v2);


/*----------*
 * accesseurs
 *----------*/
// le tableau marque doit être suffisamment grand
void voi_getMarque(const_Voiture self, char *marque);
int voi_getAnnee(const_Voiture self);
int voi_getKilometrage(const_Voiture self);
void voi_setKilometrage(Voiture self, int kilometrage);
int voi_getNbImmatriculations(const_Voiture self);
// le tableau immatirculation doit être suffisamment grand
void voi_getImmatriculation(const_Voiture self, int pos, char *immatriculation);
void voi_addImmatriculation(Voiture self, const char *immatriculation);


/*----------*
 * méthode secondaire d'affichage
 *----------*/
void voi_afficher(const_Voiture self);


/*----------*
 * entrées-sorties fichiers
 * note : le paramètre est un fichier déjà ouvert
 *----------*/
void voi_ecrireFichier(const_Voiture self, FILE *fd);
void voi_lireFichier(Voiture self, FILE *fd);

#endif
