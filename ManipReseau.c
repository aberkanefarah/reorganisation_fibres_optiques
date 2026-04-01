#include <stdio.h>
#include <stdlib.h>
#include "Chaine.h"
#include "Reseau.h"
#include "SVGwriter.h"

/*---------Les_fonctions_qui_suivent_aident_pour_la_reconstitution---------*/

//Cette fonction vérifié si deux noeuds sont déjà voisins ou pas
int estDejaVoisin(Noeud* n1, Noeud* n2) {
    CellNoeud *courant = n1->voisins;
    while (courant != NULL) { 
        if (courant->nd == n2) {
            return 1; // Vrai si n2 est déjà voisin de n1
        }
        courant = courant->suiv;
    }
    return 0; // Faux si n2 n'est pas voisin de n1
}

//Cette fonction vérifie si les noeuds sont mututellment voisins si ce n'est pas le cas on crée ce lien
void ajouterVoisinSiNonExistant(Noeud* n1, Noeud* n2) {
    if (!n1 || !n2) return;

    // Ajouter n2 comme voisin de n1 si c'est pas déjà le cas
    if (!estDejaVoisin(n1, n2)) {
        CellNoeud* newVoisin1 = (CellNoeud*)malloc(sizeof(CellNoeud));
        newVoisin1->nd = n2;
        newVoisin1->suiv = n1->voisins;
        n1->voisins = newVoisin1;
    }

    // Ajouter n1 comme voisin de n2 si c'est pas déjà le cas
    if (!estDejaVoisin(n2, n1)) {
        CellNoeud* newVoisin2 = (CellNoeud*)malloc(sizeof(CellNoeud));
        newVoisin2->nd = n1;
        newVoisin2->suiv = n2->voisins;
        n2->voisins = newVoisin2;
    }
}



void libererCellNoeud(CellNoeud *liste_noeuds) {
    CellNoeud *temp;
    while (liste_noeuds != NULL) {
        temp = liste_noeuds;
        liste_noeuds = liste_noeuds->suiv;
        CellNoeud *voisinsNd = temp->nd->voisins;
        CellNoeud *voisinTemp;
        while(voisinsNd){
            voisinTemp = voisinsNd;
            voisinsNd = voisinsNd->suiv;
            free(voisinTemp);
        }
        free(temp->nd); // Libérer le noeud
        free(temp);     // Libérer la cellule
    }
}

void libererCellCommodite(CellCommodite *liste_commodites) {
    CellCommodite *temp;
    while (liste_commodites != NULL) {
        temp = liste_commodites;
        liste_commodites = liste_commodites->suiv;
        free(temp); // Libérer la cellule de commodité
    }
}

void libererReseau(Reseau *reseau) {
    libererCellNoeud(reseau->noeuds);         // Libérer la liste des noeuds
    libererCellCommodite(reseau->commodites); // Libérer la liste des commodités
    free(reseau);                              // Libérer la structure du réseau
}

Noeud* creerNoeud(double x, double y, int num) {
    Noeud* n = malloc(sizeof(Noeud));
    if (!n) return NULL;
    n->x = x;
    n->y = y;
    n->num = num;
    n->voisins = NULL;
    return n;
}

void ajouterNoeudReseau(Reseau* R, Noeud* n) {
    CellNoeud* newCell = malloc(sizeof(CellNoeud));
    if (!newCell) return;
    newCell->nd = n;
    newCell->suiv = R->noeuds;
    R->noeuds = newCell;
}

/*---------------La_suite_du_fichier_répond_aux_questions---------------------*/

/* Question 3.1 */
//Compte le nombre de commodités d'un réseau
int nbCommodites(Reseau *R){
    int nb=0;
    CellCommodite *cmdt = R->commodites;
    while(cmdt!=NULL){
        nb++;
        cmdt=cmdt->suiv;
    }
    return nb;
}

//Compte le nombre de liasions d'un Réseau
int nbLiaisons(Reseau *R) {
    int nb = 0;
    CellNoeud *cNd = R->noeuds;
    while (cNd != NULL) {
        CellNoeud *voisins = cNd->nd->voisins;
        while (voisins) {
            nb++;
            voisins = voisins->suiv;
        }
        cNd = cNd->suiv;
    }
    return nb / 2; // Chaque liaison est comptée deux fois
}

/* Question 3.2 */
//Ecrit les données du réseau dans un fichier
void ecrireReseau(Reseau *R, FILE *f){
    fprintf(f,"NbNoeuds: %d\n", R->nbNoeuds);
    fprintf(f,"NbLiaisons: %d\n", nbLiaisons(R));
    fprintf(f,"NbCommodites: %d\n", nbCommodites(R));
    fprintf(f,"Gamma: %d\n", R->gamma);

    fprintf(f, "\n");

    CellNoeud *cNd = R->noeuds;
    while(cNd != NULL){
        Noeud *Nd = cNd->nd;
        fprintf(f,"v %d %f %f\n", Nd->num, Nd->x, Nd->y);
        cNd=cNd->suiv;
    }
    fprintf(f, "\n");
    

    cNd = R->noeuds;
    while(cNd != NULL) {
        Noeud *Nd = cNd->nd;
        CellNoeud *voisins = Nd->voisins;
        while (voisins) {
            if (Nd->num < voisins->nd->num) { // Éviter le double comptage
                fprintf(f, "l %d %d\n", Nd->num, voisins->nd->num);
            }
            voisins = voisins->suiv;
        }
        cNd = cNd->suiv;
    }


    fprintf(f, "\n");
    CellCommodite *cmdts = R->commodites;
    while(cmdts!=NULL){
        fprintf(f, "k %d %d\n", cmdts->extrA->num, cmdts->extrB->num);
        cmdts=cmdts->suiv;
    }


}

void afficheReseauSVG(Reseau *R, char* nomInstance){
    CellNoeud *courN,*courv;
    SVGwriter svg;
    double maxx=0,maxy=0,minx=1e6,miny=1e6;

    courN=R->noeuds;
    while (courN!=NULL){
        if (maxx<courN->nd->x) maxx=courN->nd->x;
        if (maxy<courN->nd->y) maxy=courN->nd->y;
        if (minx>courN->nd->x) minx=courN->nd->x;
        if (miny>courN->nd->y) miny=courN->nd->y;
        courN=courN->suiv;
    }
    SVGinit(&svg,nomInstance,500,500);
    courN=R->noeuds;
    while (courN!=NULL){
        SVGpoint(&svg,500*(courN->nd->x-minx)/(maxx-minx),500*(courN->nd->y-miny)/(maxy-miny));
        courv=courN->nd->voisins;
        while (courv!=NULL){
            if (courv->nd->num<courN->nd->num)
                SVGline(&svg,500*(courv->nd->x-minx)/(maxx-minx),500*(courv->nd->y-miny)/(maxy-miny),500*(courN->nd->x-minx)/(maxx-minx),500*(courN->nd->y-miny)/(maxy-miny));
            courv=courv->suiv;
        }
        courN=courN->suiv;
    }
    SVGfinalize(&svg);
}