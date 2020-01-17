#include <stdio.h>
#include <stdlib.h>
#include "morpion.h"
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define DBUG                  \
    affichage_grille(grille); \
    exit(1);

int SIZE ;

morpion creer_grille_vide(void){
    int i,j;

    morpion grille;
    grille = malloc(SIZE * sizeof(Case*));

    for (int i = 0; i < SIZE; ++i)
    {
        grille[i] = malloc(SIZE * sizeof(Case));
    }

    for(j=0 ; j<SIZE ; j++){
        for(i=0 ; i<SIZE ; i++){
            grille[i][j] = VIDE;
            // printf("j = %d ; i = %d ; G = %d ; add = %p\n", j, i, grille[i][j] , &grille[i][j] );
        }
    }
    return grille;
}


static void printL (void){
    int i;
    for (i=0 ; i<4*SIZE+1 ; i++) printf("_");
    printf("\n");
}


void affichage_grille(morpion grille){
    int i,j;
    for(i=0 ; i<SIZE ; i++){
        printL();
        for(j=0 ; j<SIZE ; j++){

            //printf("add = %p\n", &grille[i][j]);

            printf("|");
            switch(grille[i][j]){
                case VIDE : printf("   ");
				break;
				case J1 : printf(" O ");
				break;
				case J2 : printf(" X ");
				break;
                default: printf(" E ");
            }
        }
        printf("|");
        printf("\n");
    }
    printL();
    printf("\n");
}

int jouer (int i, int j , morpion grille, int joueur){
    if (grille[i][j] == VIDE){
        grille[i][j] = joueur;
        return 1;
    } else return 0;
}


int gagnant (morpion grille, int it, int jt){
    int cpt = 1;
    int i,j;
    i=it;
    j=jt;
    int joueur = grille[i][j];

    static int w = 0;
    if (w==11){
        printf("i=%d , j=%d \n", it, jt);
        w++;
        printf("win = %d\n" , gagnant(grille , i ,j));
        DBUG
    }
    //w++;
    // printf("Gjoueur = %d\n" , joueur);


    //On verifie les colonnes
    while((i+1)<SIZE && i>=0 && grille[i+1][j] == joueur) i++;
    while(i-1>=0 && grille[i-1][j] == joueur) {
        cpt++;
        i--;
        }

        if (w==13) printf("Column CPT = %d\n", cpt);

    if(cpt>=SIZE) 
    {
        return joueur;
    }

    //On verifie les lignes
    i = it;
    j = jt;
    cpt=1;
    while((j+1)<SIZE && j>=0 && grille[i][j+1] == joueur) j++;
    while(j-1>=0 && grille[i][j-1] == joueur) {
        cpt++;
        j--;
        }

    if (w==13) printf("Ligne CPT = %d\n", cpt);

    if(cpt>=SIZE) return joueur;

    //On verifie une diagonales
    cpt=1;
    i = it;
    j = jt;
    while ((j + 1) < SIZE && (i+1) < SIZE && j >= 0 && i>=0 && grille[i + 1][j + 1] == joueur) {
        i++;
        j++;
    }
    while (j - 1 >= 0 && i-1 >= 0 && grille[i-1][j - 1] == joueur)
    {
        cpt++;
        j--;
        i--;
    }
    if (w==13) printf("Diag1 CPT = %d\n", cpt);

    if(cpt>=SIZE) return joueur;

    //On verifie l'autre diagonale i- j+
    cpt=1;
    i = it;
    j = jt;
    while ((j + 1) < SIZE && i-1 >= 0 && grille[i - 1][j + 1] == joueur) {
        i--;
        j++;
    }
    while (j - 1 >= 0 && i + 1 < SIZE && grille[i + 1][j - 1] == joueur)
    {
        cpt++;
        j--;
        i++;
    }
    
    
    if (w==13) printf("Diag2 CPT = %d\n", cpt);

    //printf("cpt=%d\n" , cpt);
    if (cpt >= SIZE)
    {
        return joueur;
    }
    
    // printf("Pas de Winner cette fois ci...\n");
    return -1;
}
// J1 est IA

int jeuFini (morpion grille){
    int i,j;
    for(i = 0 ; i<SIZE ; i++){
        for(j = 0 ; j < SIZE ; j++){
            if (grille[i][j] == -1) return 0;
        }
    }
    return 1 ;
}

int alphaBeta(morpion grille , int a , int b , int i , int j , int profondeur){
    if (gagnant(grille, i, j) == 0)
        return 10;
    if (gagnant(grille, i, j) == 1)
        return -10;
    if (jeuFini(grille))
        return 0;
    
    int alpha = -10;
    int beta = 10;

    //printf("ab profondeur = %d\n", profondeur);
    //affichage_grille(grille);
    //exit(1);

    int i_p,j_p;
    int v;
    if (profondeur%2 == 1){ // Noeud MIN
        v = 11;
        for (i_p = 0 ; i_p < SIZE ; i_p++){
            for (j_p = 0 ; j_p < SIZE ; j_p++){
                if (grille[i_p][j_p] == -1){
                    grille[i_p][j_p] = 1;
                    v = MIN(beta , alphaBeta(grille , alpha , beta , i_p , j_p , profondeur + 1));
                    grille[i_p][j_p] = -1;
                    if (alpha >= v)
                        return v ;
                    beta = MIN(beta , v);
                }
            }
        }
    }else{ // Noeud MAX
        v = -11;
        for (i_p = 0 ; i_p < SIZE ; i_p++){
            for (j_p = 0 ; j_p < SIZE ; j_p++){
                if (grille[i_p][j_p] == -1){
                    grille[i_p][j_p] = 0;
                    v = MAX(v, alphaBeta(grille, alpha, beta, i_p, j_p, profondeur + 1));
                    grille[i_p][j_p] = -1;
                    if (v >= beta)
                        return v;
                    alpha = MAX(alpha , v);
                }
            }
        }
    }
    return v ;
}

int abPlus(morpion grille , int profondeur , int* i , int* j ){
    int value = 10;
    int var = 0;
    int i_p, j_p;
    //printf("abPlus profondeur = %d\n" , profondeur);
    for (i_p = 0; i_p < SIZE; i_p++){
        for (j_p = 0; j_p < SIZE; j_p++){
            if (grille[i_p][j_p] == -1){
                grille[i_p][j_p] = profondeur % 2;
                var = alphaBeta(grille, -11, 11, i_p, j_p, profondeur + 1);
                grille[i_p][j_p] = -1;
                if (value > var)
                {
                    value = var;
                    *i = i_p;
                    *j = j_p;
                }
                if (value==-10){
                    return 0 ;
                }
                printf("i=%d , j=%d , score=%d\n", i_p, j_p, var);
            }
        }
    }
}

/*
int Max(morpion grille, int i, int j, int alpha, int beta)
{
    int score = -10;
    if (gagnant(grille, i, j) == 0)
        return 10;
    if (gagnant(grille, i, j) == 1)
        return -10;
    if (jeuFini(grille))
        return 0;
    int valeur;
    valeur = 11;

    int alpha_p = -11;
    int beta_p = 11;

    for (i = 0; i < SIZE; i++)
    {
        for (j = 0; j < SIZE; j++)
        {
            if (grille[i][j] == -1)
            {
                grille[i][j] = 0;
                int val = Min(grille, i, j, MAX(alpha_p, alpha), beta);
                alpha_p = MAX(alpha_p, val);
                grille[i][j] = -1;
                if (beta <= alpha_p)
                    return alpha_p;
            }
        }
    }
    return alpha_p;
}

int Min(morpion grille, int i, int j, int alpha, int beta)
{
    int score = 10;
    if (gagnant(grille, i, j) == 0)
        return 10;
    if (gagnant(grille, i, j) == 1)
        return -10;
    if (jeuFini(grille) == 1)
        return 0;
    int valeur;
    valeur = 11;

    int alpha_p = -11;
    int beta_p = 11;

    for (i = 0; i < SIZE; i++)
    {
        for (j = 0; j < SIZE; j++)
        {
            if (grille[i][j] == -1)
            {
                grille[i][j] = 1;
                int val = Max(grille, i, j, alpha, MIN(beta, beta_p));
                beta_p = MIN(beta_p, val);
                grille[i][j] = -1;
                if (beta_p <= alpha)
                    return beta_p;
            }
        }
    }
    return beta;
}

void MinMax(morpion grille, int *ti, int *tj)
{
    int alpha = -11;
    int beta = 11;
    int valeur;

    int i, j;
    for (i = 0; i < SIZE; i++)
    {
        for (j = 0; j < SIZE; j++)
        {
            if (grille[i][j] == -1)
            {
                grille[i][j] = 1;
                valeur = Max(grille, i, j, alpha, beta);
                if (alpha < valeur)
                {
                    alpha = valeur;
                    *ti = i;
                    *tj = j;
                }
                printf("i=%d , j=%d , valeur= %d\n", i, j, valeur);
                grille[i][j] = -1;
            }
        }
    }
    printf("score = %d\n", alpha);
    printf("i=%d , j=%d\n", *ti, *tj);
    return;
}
*/

int main()
{
    int IA_i, IA_j;
    int nb_tour, joueur, dois_jouer, i, j;
    morpion grille;
    do
    {
        printf("Choisissez la taille de la grille : ");
        scanf("%d", &SIZE);
    } while (SIZE < 3);

    printf("\n\nC'EST PARTI !\n");
    grille = creer_grille_vide();
    // printf("La grille est cree !\n");
    affichage_grille(grille);
    // printf("La grille est affichée !\n");

    nb_tour = 0;
    do
    {
        joueur = nb_tour % 2;
        dois_jouer = 1;
        printf("C'est au tour de J%d !\n", joueur);
        if (joueur == 1)
        {
            //MinMax(grille, &i, &j);
            i = -11;
            j = 11;
            abPlus(grille , nb_tour , &i , &j);
            jouer(i, j, grille, nb_tour % 2);
            nb_tour++;
        }
        else
        {
            while (dois_jouer)
            {
                do
                {
                    printf("Numéro de ligne : ");
                    scanf("%d", &i);
                    printf("Numéro de colonne : ");
                    scanf("%d", &j);
                } while (i > SIZE || j > SIZE);
                dois_jouer = !jouer(i, j, grille, joueur);
            }
            nb_tour++;
        }
        affichage_grille(grille);
    } while (gagnant(grille, i, j) == -1 && nb_tour < SIZE * SIZE);

    if (gagnant(grille, i, j) != -1)
    {
        printf("\tLe joueur %d a gagné, BRAVO !\n\n", joueur);
    }
    else
    {
        printf("La grille est pleine, pas de gagant...\n");
    }

    printf(" ----- PARTIE TERMINEE ----- \n");
    return 0;
}
