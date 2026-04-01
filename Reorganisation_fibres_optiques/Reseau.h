#ifndef __RESEAU_H__
#define __RESEAU_H__
#include "Chaine.h"
#include "Hachage.h"
#include "ArbreQuat.h"

typedef struct noeud Noeud;

/* Liste chainee de noeuds (pour la liste des noeuds du reseau ET les listes des voisins de chaque noeud) */
typedef struct cellnoeud {
    Noeud *nd;                      /* Pointeur vers le noeud stock\'e */
    struct cellnoeud *suiv;         /* Cellule suivante dans la liste */
} CellNoeud;

/* Noeud du reseau */
struct noeud{
   int num;                        /* Numero du noeud */
   double x, y;                    /* Coordonnees du noeud*/
   CellNoeud *voisins;             /* Liste des voisins du noeud */
};

/* Liste chainee de commodites */
typedef struct cellCommodite {
    Noeud *extrA, *extrB;       /* Noeuds aux extremites de la commodite */
    struct cellCommodite *suiv;     /* Cellule suivante dans la liste */
} CellCommodite;

/* Un reseau */
typedef struct {
    int nbNoeuds;                   /* Nombre de noeuds du reseau */
    int gamma;                      /* Nombre maximal de fibres par cable */
    CellNoeud *noeuds;              /* Liste des noeuds du reseau */
    CellCommodite *commodites;      /* Liste des commodites a relier */
} Reseau;

//Fonctions provenant de ManipReseau.c et permettant de manipuler un réseau
int estDejaVoisin(Noeud* n1, Noeud* n2);
void ajouterVoisinSiNonExistant(Noeud* n1, Noeud* n2);
int nbLiaisons(Reseau *R);
int nbCommodites(Reseau *R);
void afficheReseauSVG(Reseau *R, char* nomInstance);
void libererCellNoeud(CellNoeud *liste_noeuds);
void libererCellCommodite(CellCommodite *liste_commodites);
void libererReseau(Reseau *reseau);
Noeud* creerNoeud(double x, double y, int num);
void ajouterNoeudReseau(Reseau* R, Noeud* n);

//Fonctions provenant de Reseau_Lc.c
Noeud* rechercheCreeNoeudListe(Reseau *R, double x, double y);
Reseau* reconstitueReseauListe(Chaines *C);
void ecrireReseau(Reseau *R, FILE *f);

//Fonctions provenant de ReseauHach.c
Noeud* rechercheCreeNoeudHachage(Reseau* R, TableHachage* H, double x, double y);
Reseau* reconstitueReseauHachage(Chaines *C, int M);

//Fonctions provenant de ReseauAQ.c
Noeud* rechercheCreeNoeudArbre(Reseau* R, ArbreQuat** a, ArbreQuat* parent, double x, double y);
Reseau* reconstitueReseauArbre(Chaines* C);
#endif

