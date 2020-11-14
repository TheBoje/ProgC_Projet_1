/********************************************************************
 * Module de Collection : corps
 * Auteurs : Vincent Commin & Louis Leenart
 ********************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "Collection.h"
#include "myassert.h"

/*----------*
 * définition de la structure
 *----------*/

typedef struct Element
{
    Voiture voiture;
    struct Element * precedent;
    struct Element * suivant;
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
    // Dans le cas ou la mémoire n'est pas allouée correctement, le programme échoue
    if (result == NULL)
    {
        fprintf(stderr,"Error:Collection - col_creer - mem alloc failed");
        exit(EXIT_FAILURE);
    }
    result->premier = NULL;
    result->dernier = NULL;
    result->nombreVoitures = 0;
    result->estTrie = true;
    return result;
}

// @brief Créé une collection a partir d'une autre collection (clone)
Collection col_creerCopie(const_Collection source)
{
    myassert(source != NULL, "col_creerCopie - Source is null");

    Collection result = malloc(sizeof(struct CollectionP));
    // Dans le cas ou la mémoire n'est pas allouée correctement, le programme échoue
    if (result == NULL)
    {
        fprintf(stderr,"Error:Collection - col_creer - mem alloc failed");
        exit(EXIT_FAILURE);
    }

    result->nombreVoitures = source->nombreVoitures;
    result->estTrie = source->estTrie;
    
    if (source->premier == NULL)
    {
        result->premier = NULL;
        result->dernier = NULL;
    }
    else
    {
        Element * elementActuel = source->premier;
        Element * elementPrecedent = NULL;
        for (int i = 0; i < result->nombreVoitures; i++)
        {
            Element * element = malloc(sizeof(Element)); // TODO Verifier le malloc NULL
            element->voiture = voi_creerCopie(elementActuel->voiture);

            element->precedent = elementPrecedent;
            if (elementPrecedent == NULL)
            {
                result->premier = element;
            }
            else 
            {
                elementPrecedent->suivant = element;
            }
            if (source->dernier == elementActuel)
            {
                result->dernier = element;
                element->suivant = NULL;
            }
            elementPrecedent = element;
            elementActuel = elementActuel->suivant;
        }

    }
    return result;
}

void col_detruire(Collection *pself)
{
    Element * element = (*pself)->premier;
    Element * elementSuivant = NULL;
    if (element != NULL && element->suivant != NULL)
    {
        elementSuivant = element->suivant;
    }
    for (int i = 0; i < (*pself)->nombreVoitures; i++)
    {
        voi_detruire(&(element->voiture));
        free(element);
        element = elementSuivant;
        if (elementSuivant != NULL)
        {
            elementSuivant = elementSuivant->suivant;
        }
    }
    free(*pself);
    *pself = NULL;
}

void col_vider(Collection self)
{
    Element * element = self->premier;
    Element * elementSuivant = element->suivant;
    for (int i = 0; i < self->nombreVoitures; i++)
    {
        voi_detruire(&(element->voiture));
        free(element);
        element = elementSuivant;
        if (elementSuivant != NULL)
        {
            elementSuivant = elementSuivant->suivant;
        }
    }
    self->premier = NULL;
    self->dernier = NULL;
    self->nombreVoitures = 0;
    self->estTrie = true;
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
        for(int i = 0; i < pos; i++)
        {
            element = element->suivant;
        }
        return voi_creerCopie(element->voiture);
    }
    else
    {
        Element * element = self->dernier;
        // On parcours la liste en partant de la fin
        for(int i = self->nombreVoitures - 1; i > pos; i--)
        {
            element = element->precedent;
        }
        return voi_creerCopie(element->voiture);
    }
    

}

// @brief Ajoute la voiture à la fin de la chaine
void col_addVoitureSansTri(Collection self, const_Voiture voiture)
{
    myassert(voiture != NULL, "col_addVoitureSansTri - Car is null");

    Element * element = malloc(sizeof(Element));
    
    // Dans le cas ou la mémoire n'est pas allouée correctement, le programme échoue
    if (element == NULL)
    {
        fprintf(stderr, "Error:Collection - addVoitureSansTri - mem alloc failed");
        exit(EXIT_FAILURE);
    }

    element->voiture = voi_creerCopie(voiture);

    
    
    if (self->nombreVoitures == 0)
    {
        element->suivant = NULL;
        element->precedent = NULL;
        self->premier = element;
        self->dernier = element;
    }
    else
    {
        self->dernier->suivant = element;
        element->suivant = NULL;
        element->precedent = self->dernier;
        self->dernier = element;
    }

    self->nombreVoitures++;
    if (self->nombreVoitures > 1)
    {
        self->estTrie = false;
    }
    else
    {
        self->estTrie = true;
    }
}


void col_addVoitureAvecTri(Collection self, const_Voiture voiture)
{
    myassert(self->estTrie, "col_addVoitureSansTri - Collection not sorted");
    myassert(voiture != NULL, "col_addVoitureSansTri - Car is null");


    Element * element = malloc(sizeof(Element));
    // Dans le cas ou la mémoire n'est pas allouée correctement, le programme échoue
    if (element == NULL)
    {
        fprintf(stderr, "Error:Collection - addVoitureSansTri - mem alloc failed");
        exit(EXIT_FAILURE);
    }

    element->voiture = voi_creerCopie(voiture);

    if(voi_getAnnee(self->premier->voiture) > voi_getAnnee(voiture))
    {
        // On ajoute la voiture au début de la liste chaînée
        self->premier->precedent = element;
        element->precedent = NULL;
        element->suivant = self->premier;
        self->premier = element;
    }
    else if(voi_getAnnee(self->dernier->voiture) < voi_getAnnee(voiture))
    {
        // On ajoute la voiture à la fin de la liste chaînée
        self->dernier->suivant = element;
        element->suivant = NULL;
        element->precedent = self->dernier;
        self->dernier = element;
    }
    else
    {
        // On ajoute la voiture entre 2 autres voitures de la liste chaînée
        Element * temp = self->premier;
        while(temp != NULL)
        {
            // On arrete la boucle quand on trouve un élément qui est plus grand que l'élément qu'on veut placer
            // L'élément temp est donc l'élément qui suit l'élément qu'on veut placer dans un ordre trié
            if (voi_getAnnee(element->voiture) < voi_getAnnee(temp->voiture))
            {
                break;
            }
            else
            {
                temp = temp->suivant;
            }
        }
        // On créé alors tous les liens entre les différents éléments de la liste chaînée
        temp->precedent->suivant = element;
        element->precedent = temp->precedent;
        temp->precedent = element;
        element->suivant = temp;
    }
    self->nombreVoitures++;
}


void col_supprVoitureSansTri(Collection self, int pos)
{
    Element * aSupprimer;
    if (pos == 0)
    {
        aSupprimer = self->premier;
        aSupprimer->suivant->precedent = NULL;
        self->premier = aSupprimer->suivant;
        voi_detruire(&(aSupprimer->voiture));
        free(aSupprimer);
    }
    else if (pos == self->nombreVoitures - 1)
    {
        aSupprimer = self->dernier;
        aSupprimer->precedent->suivant = NULL;
        self->dernier = aSupprimer->precedent;
        voi_detruire(&(aSupprimer->voiture));
        free(aSupprimer);
    }
    else
    {
        aSupprimer = self->premier;
        for (int i = 0; i < pos; i++)
        {
            aSupprimer = aSupprimer->suivant;
        }
        aSupprimer->suivant->precedent = aSupprimer->precedent;
        aSupprimer->precedent->suivant = aSupprimer->suivant;
        voi_detruire(&(aSupprimer->voiture));
        free(aSupprimer);
    }
    self->nombreVoitures--;
}

void col_supprVoitureAvecTri(Collection self, int pos)
{
    col_supprVoitureSansTri(self, pos);
}

void col_trier(Collection self)
{
    if (self == NULL)
    {
        fprintf(stderr, "Error:Collection - col_trier - collection is null");
        exit(EXIT_FAILURE);
    }

    for(int i = self->nombreVoitures - 1; i >= 0; i--)
    {
        Element * element = self->premier;
        for(int j = 0; j < i; j++)
        {
            
            if(element == NULL)
                break;
            else if(element->suivant == NULL)
                break;

            if(voi_getAnnee(element->suivant->voiture) < voi_getAnnee(element->voiture))
            {
                voi_swap(element->voiture, element->suivant->voiture);
            }

            element = element->suivant;
        }
    }
    self->estTrie = true;
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
        voi_afficher(elementSuivant->voiture);
        elementSuivant = elementSuivant->suivant;
    }
}


/*----------*
 * entrées-sorties fichiers
 * note : le paramètre est un fichier déjà ouvert
 *----------*/
void col_ecrireFichier(const_Collection self, FILE *fd)
{
    if(self == NULL || fd == NULL)
    {
        fprintf(stderr, "Error:Collection - col_ecrireFichier - collection or file is null");
        exit(EXIT_FAILURE);
    }

    fseek(fd, 0, SEEK_SET);
    fwrite(&(self->estTrie), sizeof(bool), 1, fd);
    fwrite(&(self->nombreVoitures), sizeof(int), 1, fd);
    
    Element * element = self->premier;

    while(element != NULL)
    {
        voi_ecrireFichier(element->voiture, fd);
        element = element->suivant;
    }
}

void col_lireFichier(Collection self, FILE *fd)
{
    if(self == NULL || fd == NULL)
    {
        fprintf(stderr, "Error:Collection - col_lireFichier - collection or file is null");
        exit(EXIT_FAILURE);
    }

    col_vider(self);
    fseek(fd, 0, SEEK_SET);

    fread(&(self->estTrie), sizeof(bool), 1, fd);
    fread(&(self->nombreVoitures), sizeof(int), 1, fd);

    if(self->nombreVoitures == 1)
    {
        Element * element = (Element *)malloc(sizeof(struct Element));
        if(element == NULL)
        {
            fprintf(stderr, "Error:Collection - col_lireFichier - element is null");
            exit(EXIT_FAILURE);
        }

        element->voiture = voi_creerFromFichier(fd);
        element->precedent = NULL;
        element->suivant = NULL;

        self->premier = element;
        self->dernier = element;
    }
    else
    {
        Element * element = (Element *)malloc(sizeof(struct Element));

        if(element == NULL)
        {
            fprintf(stderr, "Error:Collection - col_lireFichier - element is null");
            exit(EXIT_FAILURE);
        }

        for(int i = 0; i < self->nombreVoitures - 1; i++)
        {
            Element * elementSuivant = (Element *)malloc(sizeof(struct Element));

            if(elementSuivant == NULL)
            {
                fprintf(stderr, "Error:Collection - col_lireFichier - elementSuivant is null");
                exit(EXIT_FAILURE);
            }

            element->voiture = voi_creerFromFichier(fd);
            if(i == 0)
            {
                
                element->precedent = NULL;

                self->premier = element; 
            }
            else if(i == self->nombreVoitures - 2)
            {
                elementSuivant->voiture = voi_creerFromFichier(fd);
                elementSuivant->suivant = NULL;

                self->dernier = elementSuivant;
            }

            elementSuivant->precedent = element;
            element->suivant = elementSuivant;
            element = elementSuivant;
        }
    }
}