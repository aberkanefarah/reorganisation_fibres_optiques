#include <stdio.h>
#include <stdlib.h>
#include "Chaine.h"
#include "Reseau.h"
#include "Hachage.h"
#include "ArbreQuat.h"
#include "SVGwriter.h"

int main(int argc, char **argv) {
    // On vérifie qu'il y a bien un nom de fichier et un entier
    if (argc != 3) {
        printf("Usage: <NomFichier.cha> <entier entre 1 et 3>");
        exit(-1);
    }

    FILE *ficherdonne = fopen(argv[1], "r"); // Ouverture en mode lecture du fichier passé en paramètre
    if (ficherdonne == NULL) {
        printf("Impossible d'ouvrir le fichier %s.\n", argv[1]);
        exit(-1);
    }

    // Choix d'une action en fonction de la valeur de argv[2]
    if (atoi(argv[2]) == 1) {
        printf("Construction du Reseau en utilisant Liste-Chaînée...\n");
        FILE *ResLC = fopen("ResEcr.res", "w");
        Chaines *ch = lectureChaines(ficherdonne);
        Reseau *Res = reconstitueReseauListe(ch);
        printf("Ecriture dans le fichier  ResEcr.res...\n");
        ecrireReseau(Res, ResLC);
        printf("Libération de la mémoire allouée...\n");
        libererReseau(Res);
        libererChainesCompletes(ch);
        fclose(ResLC);
        printf("Tout tache est tériminé comme prévu. Merci\n");
    } else if (atoi(argv[2]) == 2) {
        printf("Construction du Reseau en utilisant Tab-Hachage...\n");
        FILE *ResHach = fopen("ResEcr.res", "w");
        Chaines *ch = lectureChaines(ficherdonne);
        Reseau *Res = reconstitueReseauHachage(ch, 100);
        printf("Ecriture dans le fichier  ResEcr.res...\n");
        ecrireReseau(Res, ResHach);
        printf("Libération de la mémoire allouée...\n");
        libererReseau(Res);
        libererChainesCompletes(ch);
        fclose(ResHach);
        printf("Tout tache est tériminé comme prévu. Merci\n");
    } else if (atoi(argv[2]) == 3) {
        printf("Construction du Reseau en utilisant Arbre...\n");
        FILE *ResAbr = fopen("ResEcr.res", "w");
        Chaines *ch = lectureChaines(ficherdonne);
        Reseau *Res = reconstitueReseauArbre(ch);
        printf("Ecriture dans le fichier  ResEcr.res...\n");
        ecrireReseau(Res, ResAbr);
        printf("Libération de la mémoire allouée...\n");
        libererReseau(Res);
        libererChainesCompletes(ch);
        fclose(ResAbr);
        printf("Tout tache est tériminé comme prévu. Merci\n");

    }
    fclose(ficherdonne);
    return 0;
}
