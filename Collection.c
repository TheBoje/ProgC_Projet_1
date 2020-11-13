/********************************************************************
 * Module de Collection : corps
 * Auteurs : Vincent Commin & Louis Leenart
 ********************************************************************/

#include <stdlib.h>

#include <Collection.h>

/*----------*
 * définition de la structure
 *----------*/

typedef struct Element
{
    Voiture voiture;
    Element * precedent;
    Element * suivant;
} Element;

struct CollectionP
{
    Element * premier;
    Element * dernier;
    int nombreVoitures;
    bool estTrie;
};

/*----------*
 * initialisation de la structure
 *----------*/

// @brief Créé une collection initialisée en tant que collection vide
Collection col_creer()
{
    Collection result;
    result->premier = NULL;
    result->dernier = NULL;
    result->nombreVoitures = 0;
    result->estTrie = true;
    return result;
}

// @brief Créé une collection a partir d'une autre collection (clone)
Collection col_creerCopie(const_Collection source)
{
    Collection result;
}

void col_detruire(Collection *pself); 

void col_vider(Collection self);


/*----------*
 * accesseurs
 *----------*/
int col_getNbVoitures(const_Collection self);
// on récupère une copie de la voiture
Voiture col_getVoiture(const_Collection self, int pos);

// @brief Ajoute la voiture à la fin de la chaine
void col_addVoitureSansTri(Collection self, const_Voiture voiture)
{
    Element * element = malloc(sizeof(Element));
    
    // Dans le cas ou la mémoire n'est pas allouée correctement, le programme échoue
    if (element == NULL)
    {
        fprintf(stderr, "Error:Collection - addVoitureSansTri - mem alloc failed");
        exit(EXIT_FAILURE);
    }

    element->voiture = voi_creerCopie(voiture);

    element->suivant = NULL;
    
    if (self->dernier != NULL)
    {
        (self->dernier)->suivant = element;
        self->dernier = element;

        element->precedent = self->dernier;
    }
    else
    {
        self->premier = element;
        self->dernier = element;
        element->precedent = NULL;
    }

    self->nombreVoitures++;
    if (self->nombreVoitures > 1)
    {
        self->estTrie = false;
    }
}
void col_addVoitureAvecTri(Collection self, const_Voiture voiture);

void col_supprVoitureSansTri(Collection self, int pos);
void col_supprVoitureAvecTri(Collection self, int pos)
{
    
}

void col_trier(Collection self);


/*----------*
 * méthode secondaire d'affichage
 *----------*/
void col_afficher(const_Collection self);


/*----------*
 * entrées-sorties fichiers
 * note : le paramètre est un fichier déjà ouvert
 *----------*/
void col_ecrireFichier(const_Collection self, FILE *fd);
void col_lireFichier(Collection self, FILE *fd);