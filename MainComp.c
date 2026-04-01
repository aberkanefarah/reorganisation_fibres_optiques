#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "time.h"
#include "Chaine.h"
#include "Reseau.h"
#include "Hachage.h"
#include "ArbreQuat.h"

/* Question 6.1 */
int main() {
    FILE* file = fopen("temps_de_calcul_LC.txt", "w"); // Fichier pour enregistrer les temps
    FILE* file2 = fopen("temps_de_calcul_Hash_Arbre.txt", "w"); // Fichier pour enregistrer les temps

    int nbPointsChaine = 100; // Nombre de points par chaîne
    int xmax = 500; // Valeur maximale de x
    int ymax = 500; // Valeur maximale de y

    clock_t start, end;
    double cpu_time_used;

    for (int nbChaines = 0; nbChaines <= 1000; nbChaines += 100) {
        Chaines* C = generationAleatoire(nbChaines, nbPointsChaine, xmax, ymax);

        // Mesurer le temps pour la liste chaînée
        printf("En cours (ListeChainée), nbChaine : %d\n", nbChaines);
        start = clock();
        Reseau* R_liste = reconstitueReseauListe(C);
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        fprintf(file, "%d %f\n", nbChaines, cpu_time_used);
        libererChainesCompletes(C);
        libererReseau(R_liste);

    }

    for (int nbChaines = 0; nbChaines <= 1000; nbChaines += 100) {

        Chaines* C = generationAleatoire(nbChaines, nbPointsChaine, xmax, ymax);
        // Mesurer le temps pour la table de hachage
        //printf("Avec %d chaines\n", nbChaines);
        fprintf(file2, "%d ", nbChaines); //pour adfficher nb Chaines
        int M=128;
        for(int i = 1; i <= 3; i ++){
            M = M*i; //taille de table
            start = clock();
            printf("En cours (TabHachage M=%d), nbChaine: %d\n", M, nbChaines);
            Reseau* R_hash = reconstitueReseauHachage(C, M);
            end = clock();
            cpu_time_used = (((double) (end - start)) / CLOCKS_PER_SEC);
            fprintf(file2, "%f ", cpu_time_used);
            libererReseau(R_hash);
        }

        start = clock();
        printf("En cours (Arbre), nbChaine: %d\n", nbChaines);
        Reseau* R_arbre = reconstitueReseauArbre(C);
        end = clock();
        cpu_time_used = (((double) (end - start)) / CLOCKS_PER_SEC);
        fprintf(file2, "%f\n", cpu_time_used);
        libererReseau(R_arbre);
        libererChainesCompletes(C);
    }
    
    fclose(file);
    fclose(file2);


    //pour voir l'affichage des données en tant que curves, 
    //il faut taper cette commande dans le terminal: gnuplot -p < plotfile.txt
    
    return 0;
}

