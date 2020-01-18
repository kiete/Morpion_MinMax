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

// Retourne 1 si la grille est pleine, 0 sinon
int jeuFini(morpion grille);

// modifie les cordonnees *i , *j pour qu'elles valent le meilleur coup
void alphabeta(morpion grille, int *i, int *j);

// Retourne le score en maximisant J1
int max_AB(morpion grille, int i, int j, int alpha, int beta);

// Retourne le score en minimisant J2
int min_AB(morpion grille, int i, int j, int alpha, int beta);