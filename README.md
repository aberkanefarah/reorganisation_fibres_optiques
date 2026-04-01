# Reorganisation d'un reseau de fibres optiques

Ce projet a ete realise dans le cadre de la Licence Informatique a Sorbonne Universite. Il porte sur l'optimisation des connexions au sein d'un reseau de telecommunications en utilisant des structures de donnees en langage C.

## Objectifs du projet
L'outil developpe permet de :
- Modeliser un reseau de fibres optiques sous forme de graphe.
- Analyser et parser des jeux de donnees complexes.
- Proposer une reorganisation des connexions pour reduire les couts d'infrastructure tout en maintenant la connectivite.

## Technologies et Outils
- Langage : C (Norme C11).
- Analyse : GDB (Debogage) et Valgrind (Gestion memoire).
- Visualisation : Gnuplot pour le rendu des resultats.

## Resultats et Performance
- Note obtenue : 15,5 / 20.
- Algorithmique : Mise en oeuvre de parcours de graphes optimises.
- Fiabilite : Verification de l'absence de fuites memoire via Valgrind.

## Installation et Utilisation
1. Compilation (via gcc) :
   ```bash
   gcc -o opti_fibres *.c -Wall