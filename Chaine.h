#ifndef __CHAINE_H__
#define __CHAINE_H__	
#include<stdio.h>

/* Liste chainee de points */
typedef struct cellPoint{
  double x,y;                   /* Coordonnees du point */
  struct cellPoint *suiv;       /* Cellule suivante dans la liste */
} CellPoint;

/* Celllule d une liste (chainee) de chaines */
typedef struct cellChaine{
  int numero;                   /* Numero de la chaine */
  CellPoint *points;            /* Liste des points de la chaine */
  struct cellChaine *suiv;      /* Cellule suivante dans la liste */
} CellChaine;

/* L'ensemble des chaines */
typedef struct {
  int gamma;                    /* Nombre maximal de fibres par cable */
  int nbChaines;                /* Nombre de chaines */
  CellChaine *chaines;          /* La liste chainee des chaines */
} Chaines;

/*Fonctions utiles*/
CellPoint *creerCellPoint(double x,double y);
CellChaine *creerCellChaine(int numero, CellPoint *cellpts);
void insererPoint(CellChaine *cch, double x,double y);
Chaines *creerChaines(int nbChaines , int gamma);
void insererCellChaine(Chaines *ch, CellChaine *cCh);
void libererPoints(CellPoint *points);
void libererChaines(CellChaine *chaines);
void libererChainesCompletes(Chaines *ensembleChaines);
Chaines* generationAleatoire(int nbChaines, int nbPointsChaine, int xmax, int ymax);
void chaineCoordMinMax(Chaines* C, double* xmin, double* ymin, double* xmax, double* ymax);

/*Fonctions demandées dans les questions*/
Chaines* lectureChaines(FILE *f);
void ecrireChaines(Chaines *C, FILE *f);
void afficheChainesSVG(Chaines *C, char* nomInstance);
double longueurTotale(Chaines *C);
int comptePointsTotal(Chaines *C);
int comptePoints(Chaines *C);

#endif	
