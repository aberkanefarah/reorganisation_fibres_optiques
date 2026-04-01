#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Chaine.h"
#include "Reseau.h"
#include "Hachage.h"


/* Question 4.2 */
double Cle(double x,double y){
  return y + (double)((x+y)*(x+y+1))/2;//Retourne une clé
}

/* Question 4.3 */
int FonctionHachage(double k, int M){//Retourne la valeur hachée à partir de la clé
  double A = (sqrt(5)-1)/2;
  return (int)(M*((k*A)-(long int)(k*A)));
}

void libererTableHachage(TableHachage *table) {
    if (table == NULL) // Vérification si la table est déjà NULL
        return;
    for (int i = 0; i < table->tailleMax; i++) {
        CellNoeud *courant = table->T[i]; // Récupération de l'élément courant
        // Parcours et libération de chaque liste chaînée de CellNoeud
        while (courant != NULL) {
            CellNoeud *temp = courant; 
            courant = courant->suiv;
            free(temp); // Libération de la mémoire de l'élément courant
        }
    }
    // Libération du tableau T
    free(table->T);
    free(table);
}

/* Question 4.4 */
Noeud* rechercheCreeNoeudHachage(Reseau* R, TableHachage* H, double x, double y){
    double k =  Cle(x,y);
    int i = FonctionHachage(k, H->tailleMax);
    CellNoeud *curr = H->T[i];
    CellNoeud *prec=NULL; //pour pouvoir ajouter un élément à la fin de liste s'il y a une collision
    while(curr){
        if(curr->nd->x == x && curr->nd->y == y){
            return curr->nd;
        }
        prec = curr;
        curr = curr->suiv;
    }

    // on crée un nouveau noeud si on l'a pas trouvé
    Noeud * newNd = (Noeud *) malloc(sizeof(Noeud));
    newNd->x=x;
    newNd->y=y;
    newNd->num = ++(R->nbNoeuds);
    newNd->voisins = NULL;

    // on crée une nouvelle CellNoeud pour l'ajouter à la Tab de Hachage
    CellNoeud *newCellTabH = (CellNoeud *)malloc(sizeof(CellNoeud));
    newCellTabH->nd = newNd;
    newCellTabH -> suiv = NULL;
    if (prec == NULL) {
        H->T[i] = newCellTabH; // Premier élément dans cette entrée de hachage
    } else {
        prec->suiv = newCellTabH; // Ajout à la fin dans la liste de collision
    }

    //on insère le newNd dans le Reseau
    CellNoeud *newCellReseau = (CellNoeud *)malloc(sizeof(CellNoeud));
    newCellReseau -> nd = newNd;
    newCellReseau->suiv = R->noeuds; // on insére la nouvelle CellNoeud en tête du noeud de Reseau
    R->noeuds = newCellReseau;

    return newNd; 
}

/* Question 4.5 */
Reseau* reconstitueReseauHachage(Chaines *C, int M){
    //Création du réseau
    Reseau *R = (Reseau*)malloc(sizeof(Reseau));
    R->nbNoeuds = 0;
    R->gamma = C->gamma;
    R->noeuds = NULL;
    R->commodites = NULL;
    CellChaine *ch = C->chaines;

    //Création de la table de hachage
    TableHachage *tabHash=(TableHachage*)malloc(sizeof(TableHachage));
    tabHash->nbElement = 0;
    tabHash->tailleMax = M;
    tabHash->T = (CellNoeud**)malloc(sizeof(CellNoeud*) * M); 

    // Initialisation du tableau de la table de hachage
    for (int i = 0; i < M; i++) {
        tabHash->T[i] = NULL;
    }


    while (ch != NULL) {
        Noeud *prevNd = NULL; //pour stocker le voisin precedent
        Noeud *firstNd = NULL; // Pour stocker le premier noeud de la chaîne (extrA)
        CellPoint *pt = ch->points;
        while(pt != NULL) {
            Noeud *currNd = rechercheCreeNoeudHachage(R, tabHash, pt->x, pt->y);
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
    libererTableHachage(tabHash);//Libération de la table de hachage
    return R;
}

