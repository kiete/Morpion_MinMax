#include <stdio.h>
#include <stdlib.h>

typedef enum case_t {VIDE = -1, J1 = 0, J2 = 1} Case;

//typedef enum Case case ;
typedef Case **morpion;

// création d'une grille vide
morpion creer_grille_vide(void);

// affichage de la grille de morpion
void affichage_grille(morpion grille);

// gère le jeu tour par tour
int jouer (int i, int j , morpion grille, int joueur);

// vérifie si le joueur ayant placé le dernier pion a gagné
int gagnant (morpion grille, int it, int jt);

void MinMax (morpion grille , int *ti , int* tj);

int Min(morpion grille, int i, int j);

int Max(morpion grille , int i , int j);

int jeuFini(morpion grille);
