#ifndef __HACHAGE_H__
#define __HACHAGE_H__
typedef struct cellnoeud CellNoeud;
#include "Reseau.h"

typedef struct{
  int nbElement; //pas necessaire ici
  int tailleMax;
  CellNoeud** T;
} TableHachage ;

double Cle(double x,double y);
int FonctionHachage(double k, int M);
void libererTableHachage(TableHachage *table);
#endif	