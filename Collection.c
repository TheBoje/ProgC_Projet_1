/********************************************************************
 * Module de Collection : corps
 * Auteurs : Vincent Commin & Louis Leenart
 ********************************************************************/

#include <stdlib.h>

#include "Collection.h"
#include "myassert.h"

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
    Collection result = malloc(sizeof(struct CollectionP));
    result->premier = NULL;
    result->dernier = NULL;
    result->nombreVoitures = 0;
    result->estTrie = true;
    return result;
}

// @brief Créé une collection a partir d'une autre collection (clone)
Collection col_creerCopie(const_Collection source)
{
    Collection result = malloc(sizeof(struct CollectionP));
    result->nombreVoitures = source->nombreVoitures;
    result->estTrie = source->estTrie;
    
    if (source->premier == NULL)
    {
        result->premier = NULL;
        result->dernier = NULL;
    }
    else
    {
        Element * elementSuivant = source->premier;
        while (elementSuivant != NULL)
        {
            col_addVoitureSansTri(result, elementSuivant->voiture);
            elementSuivant = elementSuivant->suivant;
        }
    }
    return result;
}

void col_detruire(Collection *pself)
{
    // TODO This
}

void col_vider(Collection self)
{
    // TODO This
}


/*----------*
 * accesseurs
 *----------*/
int col_getNbVoitures(const_Collection self)
{
    return self->nombreVoitures;   
}


// on récupère une copie de la voiture
Voiture col_getVoiture(const_Collection self, int pos)
{
    myassert((pos >= 0) && (pos < self->nombreVoitures), "col_getVoiture - Position not valid");
    

    // On regarde si la position est dans la première ou deuxième moitié de la liste afin d'effectuer le minimum d'opérations
    if(pos < (self->nombreVoitures / 2))
    {
        Element * element = self->premier;
        for(int i = 0; i <= pos; i++)
        {
            element = element->suivant;
        }
        return element->voiture;
    }
    else
    {
        Element * element = self->dernier;
        // On parcours la liste en partant de la fin
        for(int i = self->nombreVoitures - 1; i >= pos; i--)
        {
            element = element->precedent;
        }
        return element->voiture
    }
    

}

// @brief Ajoute la voiture à la fin de la chaine
void col_addVoitureSansTri(Collection self, const_Voiture voiture)
{
    Element * element = malloc(sizeof(Element)); // TODO Ajouter un free
    
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


void col_addVoitureAvecTri(Collection self, const_Voiture voiture)
{
    myassert(self->estTrie, "col_addVoitureSansTri - Collection not sorted");
    myassert(voiture != NULL, "col_addVoitureSansTri - Car is null");

    if(voi_getAnnee(self->premier->voiture) > voi_getAnnee(voiture))
    {

    }
    else if(voi_getAnnee(self->dernier->voiture) < voi_getAnnee(voiture))
    {

    }
    else
    {
        
    }
}

void col_supprVoitureSansTri(Collection self, int pos)
{
    // TODO This
}

void col_supprVoitureAvecTri(Collection self, int pos)
{
    // TODO This
}

void col_trier(Collection self)
{
    // TODO This
}


/*----------*
 * méthode secondaire d'affichage
 *----------*/

// @brief Affiche les éléments de la collection et de toutes les voitures qu'elle contient
void col_afficher(const_Collection self)
{
    printf("Collection :\n");
    printf("\tEst trié : %s\n", self->estTrie ? "Vrai" : "Faux");
    printf("\tNombre de voitures : %d\n", self->nombreVoitures);

    Element * elementSuivant = self->premier;
    while(elementSuivant != NULL)
    {
        voi_afficher(elementSuivant);
        elementSuivant = elementSuivant->suivant;
    }
}


/*----------*
 * entrées-sorties fichiers
 * note : le paramètre est un fichier déjà ouvert
 *----------*/
void col_ecrireFichier(const_Collection self, FILE *fd)
{
    // TODO This
}

void col_lireFichier(Collection self, FILE *fd)
{
    // TODO This
}