#include <stdio.h>
#include <stdlib.h>
#include "Chaine.h"
#include "Reseau.h"

/* Question 2.1 */
Noeud* rechercheCreeNoeudListe(Reseau *R, double x, double y){
    CellNoeud * curr = R->noeuds;
    CellNoeud * prec = NULL;
    while(curr){
        Noeud *nd = curr->nd;
        if(nd->x == x && nd->y == y)
            return nd; // Si le noeud existe déjà, le retourner
        prec = curr;
        curr = curr->suiv;
    }
    // on crée un nouveau noeud si on l'a pas trouvé
    Noeud * newNd = (Noeud *) malloc(sizeof(Noeud));
    newNd->x=x;
    newNd->y=y;
    newNd->num = ++(R->nbNoeuds);
    newNd->voisins = NULL;

    // on crée une nouvelle CellNoeud pour l'ajouter à la liste dans Reseau
    CellNoeud *newCell = (CellNoeud *)malloc(sizeof(CellNoeud));
    newCell->nd = newNd;
    newCell->suiv = R->noeuds; // on insére la nouvelle CellNoeud en tête
    R->noeuds = newCell;

    return newNd; 
}

/* Question 2.2 */
Reseau* reconstitueReseauListe(Chaines *C) {
    Reseau *R = (Reseau*)malloc(sizeof(Reseau));
    R->nbNoeuds = 0;
    R->gamma = C->gamma;
    R->noeuds = NULL;
    R->commodites = NULL;

    CellChaine *ch = C->chaines;
    while (ch != NULL) {
        Noeud *prevNd = NULL; //pour stocker le voisin precedent
        Noeud *firstNd = NULL; // Pour stocker le premier noeud de la chaîne (extrA)
        CellPoint *pt = ch->points;
        while(pt != NULL) {
            Noeud *currNd = rechercheCreeNoeudListe(R, pt->x, pt->y);
            if (!firstNd) {
                firstNd = currNd; //le premier noeud comme extrA
            }
            if (prevNd != NULL) { //si prevNd existe, on l'ajoute dans la liste de voisins de nd courant
                ajouterVoisinSiNonExistant(prevNd, currNd);
            }
            prevNd = currNd;
            pt = pt->suiv;
        }
        // On ajoute la commodité correspondante à la chaîne courante
        CellCommodite *newCommodite = (CellCommodite*)malloc(sizeof(CellCommodite));
        newCommodite->extrA = firstNd;
        newCommodite->extrB = prevNd; // Le dernier noeud est extrB de commodite
        newCommodite->suiv = R->commodites;
        R->commodites = newCommodite;

        ch = ch->suiv;
    }

    return R;
}


