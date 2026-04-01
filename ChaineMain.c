#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Chaine.h"
#include "SVGwriter.h"

/*---Main pour le jeux de test sur la manipulation de la "liste chaînée---*/

int main(){

    //On initialise deux fichiers
    FILE *fichier1 = fopen("ChLec.cha", "r");//Pour le test vous pouvez modifier les données de ce fichier
    FILE *fichier2 = fopen("ChEcr.cha", "w");//Fichier pour l'écriture de la chaîne

    //Utilisation des fonctions de lécture et écriture
    Chaines* ch = lectureChaines(fichier1);//Création de la chaine à partir des données d'un fichier
    ecrireChaines(ch,fichier2);//On écris la chaine crée dans un fichier

    //Affichage visuel de la chaine
    afficheChainesSVG(ch, "Chaine_SVG");

    fclose(fichier1);
    fclose(fichier2);

    //Fonctions mathématiques
    double disTotale = longueurTotale(ch);
    printf("distance totale : %.2f\n", disTotale);
    int nbOcc = comptePoints(ch);
    printf("Nombre de Points de la chaîne : %d\n",nbOcc );

    //libération de la mémoire
    libererChainesCompletes(ch);
}