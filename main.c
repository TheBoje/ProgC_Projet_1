#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "myassert.h"

#include "Voiture.h"
#include "Collection.h"

static void usage(const char *exe)
{
    fprintf(stdout, "usage %s [full]\n", exe);
    exit(EXIT_FAILURE);
}


/*=================================================================*
 * Manipulation de voitures
 *=================================================================*/

// on ne gère pas plus finement ici
#define MAX_LEN 1000

void testVoitures(bool full)
{
    printf("\n");
    printf("=============================================================\n");
    printf("= Voitures \n");
    printf("=============================================================\n");
    printf("\n");

    Voiture v1, v2, v3;
    char tmpMarque[MAX_LEN+1];
    char tmpImmatriculation[MAX_LEN+1];

    const char *tmp[2] = {"1234 AE 75", "VH 529 FE"};
    v1 = voi_creer("Trombine", 2005, 34587, 2, tmp);
    v2 = voi_creerCopie(v1);
    v3 = voi_creerCopie(v1);
    voi_addImmatriculation(v2, "VY 749 RT");
    voi_setKilometrage(v2, 38951);
    //voi_setKilometrage(v2, 38950);   // boom !
    voi_swap(v1, v2);

    printf("v1 :\n");
    voi_getMarque(v1, tmpMarque);
    printf("  v1 a pour marque %s (Trombine normalement)\n", tmpMarque);
    printf("  v1 a pour année %d (2005 normalement)\n",
           voi_getAnnee(v1));
    printf("  v1 a pour kilométrage %d (38951 normalement)\n",
           voi_getKilometrage(v1));
    printf("  v1 a %d immatriculations (3 normalement)\n",
           voi_getNbImmatriculations(v1));
    for (int i = 0; i < voi_getNbImmatriculations(v1); i++)
    {
        voi_getImmatriculation(v1, i, tmpImmatriculation);
        printf("    [%d] %s\n", i+1, tmpImmatriculation);
    }

    printf("\n");
    printf("v2 :\n");
    voi_afficher(v2);

    if (full)
    {
        FILE *fd;

        fd = fopen("voiture_test.save", "w");
        myassert(fd != NULL, "probleme ouverture fichier écriture");
        voi_ecrireFichier(v1, fd);
        fclose(fd);

        fd = fopen("voiture_test.save", "r");
        myassert(fd != NULL, "probleme ouverture fichier lecture");
        voi_lireFichier(v3, fd);
        fclose(fd);
        printf("\n");
        printf("v3 :\n");
        voi_afficher(v3);
    }

    voi_detruire(&v1);
    voi_detruire(&v2);
    voi_detruire(&v3);
}


/*=================================================================*
 * Manipulation de collections
 *=================================================================*/
void testCollections(bool full)
{
    printf("\n");
    printf("=============================================================\n");
    printf("= Collections \n");
    printf("=============================================================\n");
    printf("\n");

    Collection c1, c2, c3;
    Voiture v;
    const char * plaques[] = {
            "ZA 123 AZ",
            "ZF 874 FZ",
            "ZM 111 MZ",
            "ZC 642 CZ",
            "ZK 914 KZ",
            "ZX 547 XZ",
            "ZH 733 HZ",
            "ZP 283 PZ",
            "ZB 881 BZ",
            "ZL 313 LZ"
        };

    // initialisation à vide de c1
    c1 = col_creer();

    // ajout de 5 voitures
    v = voi_creer("Trombine", 2015, 34587, 2, plaques);
    col_addVoitureSansTri(c1, v);
    voi_detruire(&v);

    v = voi_creer("Loopile", 2006, 115233, 1, plaques+2);
    col_addVoitureSansTri(c1, v);
    voi_detruire(&v);

    v = voi_creer("Ondine", 2018, 0, 0, NULL);
    col_addVoitureSansTri(c1, v);
    voi_detruire(&v);

    v = voi_creer("Pixile", 1963, 225844, 1, plaques+3);
    col_addVoitureSansTri(c1, v);
    voi_detruire(&v);

    v = voi_creer("Cosmosine", 1999, 12571, 1, plaques+4);
    //col_addVoitureAvecTri(c1, v);  // boom !
    col_addVoitureSansTri(c1, v);
    voi_detruire(&v);

    // recopie de c1 dans c2
    c2 = col_creerCopie(c1);

    printf("c1 avant tri ===========================================\n");
    printf("      5 voitures : Trombine, Loopile, Ondine, Pixile, Cosmosine\n");
    col_afficher(c1);

    col_trier(c1);

    printf("\nc1 après tri ===========================================\n");
    printf("      5 voitures : Pixile, Cosmosine, Loopile, Trombine, Ondine\n");
    col_afficher(c1);

    // ajout de 3 voitures en respectant le tri
    v = voi_creer("Orchidile", 2011, 8513, 2, plaques+5);
    col_addVoitureAvecTri(c1, v);
    voi_detruire(&v);

    v = voi_creer("Orwelline", 1984, 433813, 1, plaques+7);
    col_addVoitureAvecTri(c1, v);
    voi_detruire(&v);

    v = voi_creer("Colectine", 1902, 37, 1, plaques+8);
    col_addVoitureAvecTri(c1, v);
    voi_detruire(&v);

    printf("\nIl y a %d voitures dans c1 (8 normalement)\n", col_getNbVoitures(c1));
    printf("La voiture 2 (Orwelline normalement):\n");
    v = col_getVoiture(c1, 2);
    voi_afficher(v);
    voi_detruire(&v);

    printf("\nc1 après ajouts en tri =================================\n");
    printf("      8 voitures : Colectine, Pixile, Orwelline, Cosmosine, Loopile, Orchidile, Trombine, Ondine\n");
    col_afficher(c1);

    if (full)
    {
        FILE *fd;
        
        fd = fopen("collection_test.save", "w");
        myassert(fd != NULL, "probleme ouverture fichier écriture");
        col_ecrireFichier(c1, fd);
        fclose(fd);
    }

    // une suppression en respectant le tri
    col_supprVoitureAvecTri(c1, 2);
    printf("\nc1 après suppr en tri ==================================\n");
    printf("      7 voitures : Colectine, Pixile, Cosmosine, Loopile, Orchidile, Trombine, Ondine\n");
    col_afficher(c1);

    // un ajout dans c2 sans tri (pas le choix à moins de trier avant)
    v = voi_creer("Champioline", 1998, 1577, 1, plaques+9);
    col_addVoitureSansTri(c2, v);
    voi_detruire(&v);

    printf("\nc2 =====================================================\n");
    printf("      6 voitures : Trombine, Loopile, Ondine, Pixile, Cosmosine, Champioline\n"); 
    col_afficher(c2);

    // une suppression dans c2 sans tri (pas le choix à moins de trier avant)
    //col_supprVoitureAvecTri(c2, 2);   //boom
    col_supprVoitureSansTri(c2, 2);

    printf("\nc2 après suppr =========================================\n");
    printf("      5 voitures (ordre indéterminé) : Trombine, Loopile, Pixile, Cosmosine, Champioline\n"); 
    col_afficher(c2);

    col_vider(c2);
    printf("\nc2 après vidage ========================================\n");
    col_afficher(c2);

    if (full)
    {
        FILE *fd;

        fd = fopen("collection_test.save", "r");
        myassert(fd != NULL, "probleme ouverture fichier lecture");
        c3 = col_creer(); // car lireFichier prend une collection existante
        col_lireFichier(c3, fd);
        fclose(fd);
        printf("\nc3 après lecture sur disque ============================\n");
        printf("      8 voitures : Colectine, Pixile, Orwelline, Cosmosine, Loopile, Orchidile, Trombine, Ondine\n");
        col_afficher(c3);
        col_detruire(&c3);
    }

    col_detruire(&c1);
    col_detruire(&c2);
}


/*=================================================================*
 * Affichage des statistiques
 *=================================================================*/
void testStatistiques()
{
    printf("\n");
    printf("=============================================================\n");
    printf("= Statistiques \n");
    printf("=============================================================\n");
    printf("\n");

    printf("Nb initialisations  : %d\n", voi_stat_getNbInitialisations());
    printf("Nb immatriculations : %d\n", voi_stat_getNbImmatriculations());
    printf("Année minimale      : %d\n", voi_stat_getAnneeMin());
    printf("Année maximale      : %d\n", voi_stat_getAnneeMax());
}


/*=================================================================*
 * Programme principal
 *=================================================================*/
int main(int argc, char *argv[])
{
    if (argc > 2)
        usage(argv[0]);
    else if ((argc == 2) && (strcmp(argv[1], "full") != 0))
        usage(argv[0]);

    testStatistiques();
    testVoitures(argc == 2);
    testCollections(argc == 2);
    testStatistiques();

    return EXIT_SUCCESS;
}

