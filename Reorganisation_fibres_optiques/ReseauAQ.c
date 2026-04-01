#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Chaine.h"
#include "Reseau.h"
#include "ArbreQuat.h"

/*---------------La_suite_du_fichier_répond_aux_questions---------------------*/

/* Question 5.2 */
ArbreQuat* creerArbreQuat(double xc, double yc, double coteX, double coteY){
  // On alloue l'espace
  ArbreQuat* AQ = malloc(sizeof(ArbreQuat));
  AQ->xc = xc;
  AQ->yc = yc;
  AQ->coteX = coteX;
  AQ->coteY = coteY;
  AQ->se = AQ->so = AQ->ne = AQ->no = NULL;
  AQ->noeud = NULL;
  return AQ;
}

void libereArbreQuat(ArbreQuat *a){

    if(a == NULL) 
        return; //si l'arbre est déjà vide, pas besoin de libérer
        
    //On désalloue les sous-arbres récursivement
    libereArbreQuat(a->so);
    libereArbreQuat(a->se);
    libereArbreQuat(a->no);
    libereArbreQuat(a->ne);    
    free(a);  
}

void afficheArbreQuat(ArbreQuat* a) {
    if (a == NULL) {
        return;
    }

    // Informations du nœud de l'arbre
    printf("NdAb (xc, yc) : [%.2lf, %.2lf] (coteX, coteY) : [%.2lf, %.2lf]\t", a->xc, a->yc, a->coteX, a->coteY);
    if (a->noeud != NULL) {
        printf("NdRes: [%d, (%.2lf, %.2lf)]\n", a->noeud->num, a->noeud->x, a->noeud->y);
    } else {
        printf("NdAb interne\n");
    }

    // Appels récursifs pour les sous-arbres
    printf("Nord-Ouest -> ");afficheArbreQuat(a->no);printf("\n");
    printf("Nord-Est -> ");afficheArbreQuat(a->ne);printf("\n");
    printf("Sud-Ouest -> ");afficheArbreQuat(a->so);printf("\n");
    printf("Sud-Est -> ");afficheArbreQuat(a->se);printf("\n");

}

/* Question 5.3 */
void insererNoeudArbre(Noeud* n, ArbreQuat** a, ArbreQuat* parent) {
    // Arbre vide
    if (*a == NULL) {
        double coteX = parent ? parent->coteX / 2 : 1;  // Demi-largeur de la cellule du parent
        double coteY = parent ? parent->coteY / 2 : 1;  // Demi-hauteur de la cellule du parent
        double xc, yc;

        if (parent) {
            // Calculer le nouveau centre en fonction de la position du nœud par rapport au centre du parent
            xc = parent->xc + (n->x < parent->xc ? -coteX / 2 : coteX / 2);
            yc = parent->yc + (n->y < parent->yc ? -coteY / 2 : coteY / 2);
        } else {
            // Si aucun parent, utiliser les coordonnées du nœud comme centre
            xc = n->x;
            yc = n->y;
        }

        *a = creerArbreQuat(xc, yc, coteX, coteY);
        (*a)->noeud = n;
        return;
    }

    // Feuille
    if ((*a)->noeud != NULL) {
        Noeud* ancienNoeud = (*a)->noeud;
        (*a)->noeud = NULL; // Convertir ce noeud en une cellule interne
        insererNoeudArbre(ancienNoeud, a, *a);
        insererNoeudArbre(n, a, *a);
        return;
    }

    // Cellule interne
    if (n->x < (*a)->xc) {
        if (n->y < (*a)->yc) {
            insererNoeudArbre(n, &((*a)->so), *a); // Sud-Ouest
        } else {
            insererNoeudArbre(n, &((*a)->no), *a); // Nord-Ouest
        }
    } else {
        if (n->y < (*a)->yc) {
            insererNoeudArbre(n, &((*a)->se), *a); // Sud-Est
        } else {
            insererNoeudArbre(n, &((*a)->ne), *a); // Nord-Est
        }
    }
}

/* Question 5.4 */
Noeud* rechercheCreeNoeudArbre(Reseau* R, ArbreQuat** a, ArbreQuat* parent, double x, double y) {
    // Arbre vide
    if (*a == NULL) {
        Noeud *nd = creerNoeud(x, y, ++(R->nbNoeuds));
        insererNoeudArbre(nd, a, parent);
        ajouterNoeudReseau(R, nd);
        return nd;
    }

    // Si c'est une feuille et les coordonnées correspondent, retourner le nœud existant
    if ((*a)->noeud != NULL) {
        if ((*a)->noeud->x == x && (*a)->noeud->y == y) {
            return (*a)->noeud;
        } else {
            // Sinon, diviser la feuille
            Noeud *ancienNd = (*a)->noeud;
            (*a)->noeud = NULL; // Transforme cette feuille en cellule interne
            Noeud *newNd = creerNoeud(x, y, ++(R->nbNoeuds));
            ajouterNoeudReseau(R, newNd);
            insererNoeudArbre(ancienNd, a, parent);
            insererNoeudArbre(newNd, a, parent);
            return newNd;
        }
    }

    // Cellule interne
    if ((*a)->noeud == NULL) {
        // Sélection du sous-arbre approprié selon les coordonnées
        ArbreQuat** targetSubtree = x < (*a)->xc ? (y < (*a)->yc ? &((*a)->so) : &((*a)->no)) : (y < (*a)->yc ? &((*a)->se) : &((*a)->ne));
        return rechercheCreeNoeudArbre(R, targetSubtree, *a, x, y);
    }

    return NULL; // En cas de situation inattendue
}

/* Question 5.5 */
Reseau* reconstitueReseauArbre(Chaines* C){
    if(C == NULL) return NULL;

    double xmin, ymin, xmax, ymax;
    chaineCoordMinMax(C, &xmin, &ymin, &xmax, &ymax);

    //Création du réseau
    Reseau *reseau = (Reseau *)malloc(sizeof(Reseau));
    if(reseau == NULL) {
        printf("Erreur d'allocation mémoire.\n");
        exit(1);
    }
    reseau->commodites = NULL;
    reseau->gamma = C->gamma;
    reseau->nbNoeuds = 0;
    reseau->noeuds = NULL;


    double xc = (xmin + xmax) / 2;
    double yc = (ymin + ymax) / 2;
    double coteX = xmax - xmin;
    double coteY = ymax - ymin;

    ArbreQuat *A = creerArbreQuat(xc, yc, coteX, coteY);

    ArbreQuat *parent = creerArbreQuat(xc, yc, coteX, coteY);

    CellChaine *couranteChaine = C->chaines;
    
    //Parcours des noeuds
    while(couranteChaine){
        CellPoint *courantPoint = couranteChaine->points;
        Noeud *precedent = NULL;

        //Création de la commodité
        CellCommodite *commodite = (CellCommodite *)malloc(sizeof(CellCommodite));
        if(commodite==NULL){
            printf("Erreur d'allocation mémoire.\n");
            exit(2);        
        }
        commodite->extrA = NULL;
        commodite->extrB = NULL;
        commodite->suiv = NULL;

        //Parcours des points dans une cellule de chaîne
        while(courantPoint){
            //Le noeud est ajouté au réseau et à l'arbre quaternaire s'il n'est pas déjà présent
            Noeud *noeud = rechercheCreeNoeudArbre(reseau, &A, parent, courantPoint->x, courantPoint->y);
            
            //Si un noeud précédent existe, on ne se trouve pas au premier élément, donc on l'ajoute aux voisins
            if(precedent){
                ajouterVoisinSiNonExistant(precedent, noeud);
            }
            //Cas du premier élement, elle sera le premier extremité du commodité
            else{
                commodite->extrA = noeud;
            }

            precedent = noeud;
            courantPoint = courantPoint->suiv;
        }
        couranteChaine = couranteChaine->suiv;

        //Ajout à la liste des commodités, extrB est le dernier extremité du commodité
        commodite->extrB = precedent;
        commodite->suiv = reseau->commodites;
        reseau->commodites = commodite;
    }
    //afficheArbreQuat(A);

    //Dèsalloue l'arbre quaternaire
    libereArbreQuat(A);
    libereArbreQuat(parent);

    return reseau;
}