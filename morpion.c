#include <stdio.h>
#include <stdlib.h>
#include "morpion.h"
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


int Max(morpion grille , int i , int j){
    int score = -10;
    if (gagnant(grille, i, j) == 0) return 10;
    if (gagnant(grille, i, j) == 1) return -10;
    if (jeuFini(grille)) return 0 ;
    int valeur;
    valeur = 11;
    for (i=0 ; i<SIZE ; i++){
        for (j=0 ; j<SIZE ; j++){
            if (grille[i][j] == -1){
                grille[i][j] = 0;
                valeur = Min(grille,i,j);
                if (score < valeur) score = valeur;
                grille[i][j] = -1;
            }
        }
    }
    return score;
}

int Min(morpion grille, int i, int j)
{
    int score = 10;
    if (gagnant(grille, i, j) == 0) return 10;
    if (gagnant(grille, i, j) == 1) return -10;
    if (jeuFini(grille) == 1) return 0 ;
    int valeur;
    valeur = 11;
    for (i = 0; i < SIZE; i++)
    {
        for (j = 0; j < SIZE; j++)
        {
            if (grille[i][j] == -1){
                grille[i][j] = 1;
                valeur = Max(grille, i, j);
                if (score > valeur) score = valeur;
                grille[i][j] = -1;
            }
        }
    }
    return score;
}

void MinMax (morpion grille , int *ti , int* tj){
    int score = 10;
    int valeur;

    int i,j;
    for (i=0 ; i<SIZE ; i++){
        for (j=0 ; j<SIZE ; j++){
            if (grille[i][j] == -1){
                grille[i][j] = 1;
                valeur = Max(grille , i ,j);
                if (score > valeur){
                    score = valeur;
                    *ti = i;
                    *tj = j;
                }
                printf("i=%d , j=%d , valeur= %d\n", i,j,valeur);
                grille[i][j] = -1;
            }
        }
    }
    printf("score = %d\n" , score);
    // printf("i=%d , j=%d\n", *ti, *tj);
    return;
}

int main (){
    int IA_i , IA_j;
    int nb_tour , joueur , dois_jouer, i , j;
    morpion grille;
    do{
        printf("Choisissez la taille de la grille : ");
        scanf("%d", &SIZE);
    }while (SIZE<3);

    printf("\n\nC'EST PARTI !\n");
    grille = creer_grille_vide () ;
    // printf("La grille est cree !\n");
    affichage_grille (grille) ;
    // printf("La grille est affichée !\n");

    nb_tour = 0;
    do {
        joueur = nb_tour % 2 ;
        dois_jouer = 1;
        printf("C'est au tour de J%d !\n", joueur);
        if (joueur == 1){
            MinMax(grille, &i, &j);
            jouer(i, j, grille, nb_tour % 2);
            nb_tour++;
        }else{
            while (dois_jouer)
            {   
                do{
                    printf("Numéro de ligne : ");
                    scanf("%d",&i);
                    printf("Numéro de colonne : ");
                    scanf("%d",&j);
                } while(i>SIZE || j> SIZE);
                dois_jouer = !jouer (i, j , grille, joueur);
            }
            nb_tour++;
        }
        affichage_grille(grille);
    } while (gagnant(grille, i, j) == -1 && nb_tour < SIZE * SIZE);

    if(gagnant(grille, i, j) != -1){
        printf("\tLe joueur %d a gagné, BRAVO !\n\n", joueur);
    }else{
        printf("La grille est pleine, pas de gagant...\n");
    }
    
    printf(" ----- PARTIE TERMINEE ----- \n");
    return 0;
}
