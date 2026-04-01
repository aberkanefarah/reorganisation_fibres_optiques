#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "Chaine.h"
#include "SVGwriter.h"

/*---------Les_fonctions_qui_suivent_aident_à_la_manipulation_des_chaînes---------*/

//Cette fonction pemet de créer un cellPoint ) partir des coordonnées x et y
CellPoint *creerCellPoint(double x,double y){
	CellPoint *cp = (CellPoint*) malloc(sizeof(CellPoint));
	cp->x = x;
	cp->y = y;
	cp->suiv = NULL;
	return cp;
}

//cette fonction permet de créer une cellChaine et d'initialiser la liste des cellPoint
CellChaine *creerCellChaine(int numero, CellPoint *cellpts){
	CellChaine *cch = (CellChaine*) malloc(sizeof(CellChaine));
	cch->numero = numero;
	cch->points = cellpts;
	cch->suiv = NULL;
	return cch;

}

//Cette fonction permet de créer et insérer un cellPoint dans une cellChaine
void insererPoint(CellChaine *cch, double x,double y){
	CellPoint* newCp = creerCellPoint(x, y); 
	if(cch->points == NULL){
		cch->points = newCp;
	}else{
		newCp->suiv = cch->points;
		cch->points=newCp;
	}
}

//Cette fonction permet de créer une chaine 
Chaines *creerChaines(int nbChaines , int gamma){
	Chaines *ch = (Chaines*) malloc(sizeof(Chaines));
	ch->nbChaines=nbChaines;
	ch->gamma = gamma;
	ch->chaines = NULL;
	return ch;
}

//Cette fonction permet d'insérer une cellChaine dans une chaine
void insererCellChaine(Chaines *ch, CellChaine *cCh){
	if(ch->chaines == NULL){
		ch->chaines = cCh;
	}else{
		cCh->suiv = ch->chaines;
		ch->chaines = cCh;
	}
}

//La suite des fonctions permettent la libération de la mémoire
void libererPoints(CellPoint *points) {
    CellPoint *tmp;
    while (points != NULL) {
        tmp = points;
        points = points->suiv;
        free(tmp);
    }
}

void libererChaines(CellChaine *chaines) {
    CellChaine *tmp;
    while (chaines != NULL) {
        tmp = chaines;
        chaines = chaines->suiv;
        libererPoints(tmp->points);
        free(tmp);
    }
}

void libererChainesCompletes(Chaines *ensembleChaines) {
    libererChaines(ensembleChaines->chaines);
    free(ensembleChaines);
}

//Permet de générer une chaîne de manière aléatoire
/* Question 6.2 */
Chaines* generationAleatoire(int nbChaines, int nbPointsChaine, int xmax, int ymax) {
    srand(time(NULL)); // Initialisation du générateur de nombres aléatoires

    Chaines* Ch = (Chaines*)malloc(sizeof(Chaines));
    Ch->gamma = nbPointsChaine/3;
    if (!Ch) return NULL;

    Ch->nbChaines = nbChaines;
    Ch->chaines = NULL;

    for (int i = 0; i < nbChaines; i++) {
        CellChaine* CellChn = creerCellChaine(i, NULL);
        for (int j = 0; j < nbPointsChaine; j++) {
            insererPoint(CellChn, (rand() % (xmax + 1)), (rand() % (ymax + 1)));
        }
        insererCellChaine(Ch, CellChn);
    }

    return Ch;
}

/* Question 5.1 */
void chaineCoordMinMax(Chaines* C, double* xmin, double* ymin, double* xmax, double* ymax) {
  if (C == NULL || C->chaines == NULL) return;  // Rien à faire si C est vide

  // Initialisation avec la première valeur trouvée pour éviter tout problème avec les valeurs extrêmes
  CellChaine* chaine = C->chaines;
  CellPoint* point = chaine->points;
  if (point != NULL) {
    *xmin = *xmax = point->x;
    *ymin = *ymax = point->y;
  }

  // Parcourir toutes les chaînes
  for (; chaine != NULL; chaine = chaine->suiv) {
    // Parcourir tous les points de la chaîne
    for (point = chaine->points; point != NULL; point = point->suiv) {
        if (point->x < *xmin) *xmin = point->x;
        if (point->x > *xmax) *xmax = point->x;
        if (point->y < *ymin) *ymin = point->y;
        if (point->y > *ymax) *ymax = point->y;
    }
  }
}

/*---------------La_suite_du_fichier_répond_aux_questions---------------------*/

/* Question 1.1 */
Chaines * lectureChaines (FILE *f) {
    if (f == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        exit(EXIT_FAILURE);
    }
	int NbChain, Gamma;
    int numero, nombreCoordonnees;
    double x, y;

    fscanf(f, "NbChain : %d\n", &NbChain);//On lit le nombre de chaînes
    fscanf(f, "Gamma : %d", &Gamma);//On lit le gamma

	Chaines *ch = creerChaines(NbChain, Gamma);

    while (fscanf(f, "%d %d", &numero, &nombreCoordonnees) == 2) {//On lit les deux premières valeurs d'une ligne d'une cellChaîne  
		CellChaine *cCh = creerCellChaine(numero, NULL);
        for (int i = 0; i < nombreCoordonnees; i++) {
            fscanf(f, "%lf %lf", &x, &y);//A chaque itération on lit l'abscisses et l'ordonné d'un point
			insererPoint(cCh, x, y);//On crée et insère le point lu
        }
		insererCellChaine(ch, cCh);//On joint la cellChaine lue à la chaîne
    }	
    return ch;
}

/* Question 1.2 */
void ecrireChaines (Chaines *C ,FILE * f) {
	if(C == NULL) return;

	fprintf(f, "NbChain: %d\n", C->nbChaines);
	fprintf(f, "Gamma: %d\n", C->gamma);

	CellChaine *currCCh = C->chaines;/*On récupère la tête de la liste chaînées de CellChaine*/
	CellPoint * currP;
    
	while(currCCh){
        CellPoint * pt = currCCh->points;
        int nbCoord = 0;
        while(pt){ //on compte le nb de points d'une cell chaine
            nbCoord++;
            pt = pt->suiv; 
        }
		fprintf(f, "%d %d ", currCCh->numero,nbCoord); //On écrit le numéro de la chaîne et le nombre de coordonnées 
		currP = currCCh->points; /*On récupère la tête de la liste chaînées de CellPoints*/
		while(currP){
			fprintf(f, "%.2lf %.2lf ", currP->x, currP->y);
			currP=currP->suiv;
		} 
		fprintf(f, "\n");
		currCCh=currCCh->suiv;
	}
}

/* Question 1.3 */
//Affiche la chaine sous forme d'image
void afficheChainesSVG(Chaines *C, char* nomInstance){
    int i;
    double maxx=0,maxy=0,minx=1e6,miny=1e6;
    CellChaine *ccour;
    CellPoint *pcour;
    double precx,precy;
    SVGwriter svg;
    ccour=C->chaines;
    while (ccour!=NULL){
        pcour=ccour->points;
        while (pcour!=NULL){
            if (maxx<pcour->x) maxx=pcour->x;
            if (maxy<pcour->y) maxy=pcour->y;
            if (minx>pcour->x) minx=pcour->x;
            if (miny>pcour->y) miny=pcour->y;  
            pcour=pcour->suiv;
        }
    ccour=ccour->suiv;
    }
    SVGinit(&svg,nomInstance,500,500);
    ccour=C->chaines;
    while (ccour!=NULL){
        pcour=ccour->points;
        SVGlineRandColor(&svg);
        SVGpoint(&svg,500*(pcour->x-minx)/(maxx-minx),500*(pcour->y-miny)/(maxy-miny)); 
        precx=pcour->x;
        precy=pcour->y;  
        pcour=pcour->suiv;
        while (pcour!=NULL){
            SVGline(&svg,500*(precx-minx)/(maxx-minx),500*(precy-miny)/(maxy-miny),500*(pcour->x-minx)/(maxx-minx),500*(pcour->y-miny)/(maxy-miny));
            SVGpoint(&svg,500*(pcour->x-minx)/(maxx-minx),500*(pcour->y-miny)/(maxy-miny));
            precx=pcour->x;
            precy=pcour->y;    
            pcour=pcour->suiv;
        }
        ccour=ccour->suiv;
    }
    SVGfinalize(&svg);
}

/* Question 1.4 */
//Calcule la longueur physique d'une chaine
double longueurChaine(CellChaine *c){
    CellPoint * pt = c->points;
    int nbCoord = 0;
    while(pt){
        nbCoord++;
        pt = pt->suiv; 
    }
    CellPoint *cp = c->points;
    if(nbCoord == 1) return 0.0;
    CellPoint *A = cp;
    CellPoint *B = A->suiv;
    double xA, yA, xB, yB;
    double d=0;
    while(B != NULL){
        xA = A->x;
        yA = A->y;
        xB = B->x;
        yB = B->y;
        d += sqrt((xB-xA)*(xB-xA) + (yB-yA)*(yB-yA));
        A=B;
        B=B->suiv;
    }
    return d;
}

//Calcule la longueur totale de la liste des chaines
double longueurTotale(Chaines *C){
    double disTotale = 0;
    CellChaine *CCh = C->chaines;
    while (CCh){
        disTotale += longueurChaine(CCh);
        CCh = CCh->suiv;    
    }

    return disTotale;
}

/* Question 1.5 */
//Compte le nombre de points d'une chaine
int comptePoints(Chaines *C){
    CellChaine * CCh = C->chaines;
    int nbOcc = 0;
    while(CCh){
        CellPoint * pt = CCh->points;
        int nbCoord = 0;
        while(pt){
            nbCoord++;
            pt = pt->suiv; 
        }
        nbOcc += nbCoord;
        CCh = CCh->suiv;
    }
    return nbOcc;
}

