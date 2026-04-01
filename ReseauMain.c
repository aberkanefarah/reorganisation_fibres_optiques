#include <stdio.h>
#include <stdlib.h>
#include "Chaine.h"
#include "Reseau.h"
#include "Hachage.h"
#include "SVGwriter.h"

int main(){

    /*Cette partie a pour but de vérifier la validité des fonctions de manipulation d'un réseau*/

    /* Manipulation d'un réseau*/

    FILE * ChLec = fopen("00014_burma.cha","r");//Changer le nom de ce fichier pour experimenter
    FILE * ResEc = fopen("ResEcr.res","w");
    Chaines * C = generationAleatoire(20,15,5000,5000);//On crée la chaîne 
    Reseau * R = reconstitueReseauListe(C);//on reconstitue le réseau à partir de la chaine
    ecrireReseau(R,ResEc);
    afficheReseauSVG(R,"Reseau_SVG");

/* ------------------jeux d'essais : liste chaînée --------------------------*/
    
    /* Question 2.2 */

    printf("Debut de la recherche d'un noeud via liste chaîneée");

    Chaines *ch = generationAleatoire(2000,20,5000,5000);//Valeurs à modifier pour les tests
    Reseau *RLC = reconstitueReseauListe(ch);
    Noeud * ndLC = rechercheCreeNoeudListe(RLC,120,-123);//on insère un point quelconque
    afficheChainesSVG(ch,"Grande chaine\n");
    if( ndLC!=NULL ){
        printf("le point appartient à la liste des noeuds\n");
    }else{
        printf("Le point n'appartien pas\n");
    }
    printf("Fin de la recherche d'un noeud via liste chaîneée\n");

    /* Vérification de la disparité des clés pour la table de hachage */

    printf("Cle 1 : %f\n",Cle(12.3,34.8));//Meme valeur à la ligne suivante mais inversé
    printf("Cle 2 : %f\n",Cle(34.8,12.3));
    printf("Cle 3 : %f\n",Cle(-12.3,-34.8));
    printf("Cle 4 : %f\n",Cle(-41.3,9.8));
    printf("Cle 5 : %f\n",Cle(91.3,-3.8));

    return 0;

}