#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


/*--------------------------------------------------------------------------------------------------------------------------------*/

// Morpion NxN 1 joueur ( humain vs ordi ) avec algorithme alphabeta

/*--------------------------------------------------------------------------------------------------------------------------------*/


int saisir_N() ;									// Permet de saisir N la taille du morpion

void initialisation( char grille[], int N ) ;			// Initialise la grille à vide

void afficher_grille( char grille[], int N ) ;			// Affiche la grille

void tour_humain( char grille[], int N ) ;				// Demande au joueur la case à jouer
												// Marque celle-ci si valide

char gagnant( char grille[], int N ) ;					// Renvoie 'x' si joueur(x) a gagné
												// 'o' si joueur(o) a gagné 
												// 'n' si match nul
												// 'c' sinon

void tour_ordi( char grille[], int N ) ;				// Simule le tour de l'ordinateur

int commenceur() ;									// Determine qui commence en demandant au joueur

void jouer( int N ) ;								// Lance une partie NxN ( humain vs ordinateur ) 

int max_AB( char grille[], int N, int alpha, int beta ) ;	// fonction max dans alphabeta

int min_AB( char grille[], int N, int alpha, int beta ) ;	// fonction min dans alphabeta

int alphabeta( char grille[], int N ) ;					// Realise l'algo alphabeta dans le cas du jeu du morpion


/*--------------------------------------------------------------------------------------------------------------------------------*/


int main()
{
	int N ;
	N = saisir_N() ;
	jouer(N) ;
	return 0 ;
}


/*--------------------------------------------------------------------------------------------------------------------------------*/




// Permet de saisir N la taille du morpion
int saisir_N()
{
	int N ;
	printf( "Saisir N: " ) ;
	scanf( "%d", &N ) ;
	return N ;
}




// Initialise la grille à vide
void initialisation( char grille[], int N )
{
	int i, j ;
	
	for( i=0 ; i<N ; i++ ) {
		for( j=0 ; j<N ; j++ ) grille[ i*N+j ] = '-' ;
	}
}




// Affiche la grille
void afficher_grille( char grille[], int N )
{
	int i, j, k ;

	printf("      ") ;
	for( j=0 ; j<N ; j++ ) {
		if( j/10==0) printf( "%d   ",j ) ;
		else printf( "%d  ", j ) ;
	}

	for( i=0 ; i<N ; i++ ) 
	{		
		printf("\n    |") ;
		for( k=0 ; k<(4*N-1) ; k++ ) printf("―") ;	
		if( i/10==0) printf( "|\n  %d |",i ) ;
		else printf( "|\n %d |",i ) ;
		for( j=0 ; j<N ; j++ ) {
			if( grille[ i*N+j ] == 'o' ) 	 	printf( " o |") ;
			else if( grille[ i*N+j ] == 'x' )  printf( " x |") ;
			else if( grille[ i*N+j ] == '-' )  printf( "   |") ;
			else 						printf( " pas normal... \n") ;	
		}		
	}

	printf("\n    |") ;
	for( int k=0 ; k<(4*N-1) ; k++ ) printf("―") ;
	printf("|\n\n\n") ;
}




// Demande au joueur la case à jouer
// Marque celle-ci si valide
void tour_humain( char grille[], int N )
{
	int i, j, joueur ;	
	
	do {
		printf( "Au tour du joueur \n" ) ;
		printf( "Saisir la ligne de la case : " ) ;
		scanf( "%d", &i ) ;
		printf( "Saisir la colonne de la case : " ) ;
		scanf( "%d", &j ) ;	
	} while(  ( grille[i*N+j]!='-' ) || (i>=N) || (i<0) || (j>=N) || (j<0)  ) ;
	
	grille[ i*N+j ] = 'x' ;
	afficher_grille( grille, N ) ;
	
	return ;
}




// Renvoie 'x' si un (x) a gagné
// 'o' si un (o) a gagné 
// 'n' si match nul
// 'c' sinon
char gagnant( char grille[], int N )
{
	int i, j ;
	char c ;

	// test lignes														
	for( i=0 ; i<N ; i++ ) {					
		c = grille[ i*N+0 ] ;
		if( c!='-' ) {
			j = 1 ;
			while(  (j!=N) && ( grille[i*N+j]==c )  ) j++ ;
			if( j==N ) return c ;
		}
	}

	// test colonnes
	for( j=0 ; j<N ; j++ ) {						
		c = grille[ 0*N+j ] ;
		if( c!='-' ) {
			i = 1 ;
			while(  (i!=N) && ( grille[i*N+j]==c )  ) i++ ;	
			if( i==N ) return c ;
		}
	}

	// test diagonal de haut_gauche à bas_droite
	c = grille[ 0*N+0 ] ;										
	if( c!='-' ) {
		i = 1 ;
		while(  (i!=N) && ( grille[i*N+i]==c )  ) i++ ;
		if( i==N ) return c ;
	}

	// test diagonal de haut_droite à bas_gauche
	c = grille[ 0*N+(N-1) ] ;								
	if( c!='-' ) {
		i = 1 ;
		while(  (i!=N) && ( grille[ i*N+(N-1-i) ] == c )  ) i++ ;
		if( i==N ) return c ;
	}

	// test match nul
	i=0 ;
	while( ( grille[i]!='-' )  &&  ( i<(N*N) )  ) i++ ;	
	if( i==(N*N) ) return 'n' ;

	// la partie continue
	return 'c' ;												
}




// Determine qui commence en demandant au joueur
int commenceur()
{
	int reponse ;
	
	do {
		printf( "Voulez vous commencez ? ( 1 si oui 0 si non )  " ) ;
		scanf( "%d", &reponse ) ;
	} while(  (reponse!=1) && (reponse!=0)  ) ;

	printf( "\n" ) ;
	return reponse ;
}




// Lance une partie NxN ( humain vs ordinateur )
void jouer( int N )
{
	char grille[N*N] ;
	int tour0, nb_tour, gagnant0, commence ;
	
	initialisation( grille, N ) ;
	afficher_grille( grille, N ) ;
	tour0 = 1 ;
	nb_tour = N*N ;
	commence = commenceur() ;

	while( tour0 <= nb_tour ) 
	{
		if( commence==1 ) {									// l'humain commence
			if( (tour0%2)==1 ) tour_humain( grille, N ) ;
			else tour_ordi( grille, N ) ;
		} 
		else {											// ordi commence
			if( (tour0%2)==1 ) tour_ordi( grille, N ) ;
			else tour_humain( grille, N ) ;
		}
		tour0++ ;
		gagnant0 = gagnant( grille, N ) ;
		switch( gagnant0 ) {
			case 'o': {  printf( "L'ordi a gagné \n\n\n" ) ; return ;  }
			case 'x': {  printf( "Le joueur a gagné \n\n\n" ) ; return ;  }
			case 'n': {  printf( "match nul \n\n\n" ) ; return ;  }
		}
	}

	return ;
}




// Simule le tour de l'ordinateur
void tour_ordi( char grille[], int N )
{
	int pos, ij ;
	
	ij = 0 ;
	while( ( grille[ij] == '-' ) && ( ij<N*N ) ) ij++ ;	
	if( ij == (N*N) ) pos = (N/2)*N + (N/2) ;				// si la grille est vide, on joue au milieu ( optimisation )
	else pos = alphabeta(grille,N) ;						// sinon, on utilise alphabeta

	grille[ pos ] = 'o' ;
	afficher_grille( grille, N ) ;
	return ;
}




// Realise l'algo alphabeta dans le cas du jeu du morpion
int alphabeta( char grille[], int N )
{
	int score, coordonnee, ij, valeur ;
	
	score = INT_MAX ;
	coordonnee = 0 ;
	for( ij=0 ; ij<(N*N) ; ij++ ) 
	{
		if( grille[ij] == '-' ) 							// si case vide
		{			
			grille[ij] = 'o' ;
			valeur = max_AB( grille, N, INT_MIN, INT_MAX ) ;
			if( score > valeur ) {
				score = valeur ;
				coordonnee = ij ;
			}
			grille[ij] = '-' ;
		}
	}

	return coordonnee ;
}




// Fonction max de l'algo alphabeta
int max_AB( char grille[], int N, int alpha, int beta )
{
	int score, ij, valeur ;

	if( gagnant(grille,N) == 'x' ) return 1 ;
	if( gagnant(grille,N) == 'o' ) return -1 ;
	if( gagnant(grille,N) == 'n' ) return 0 ;

	score = INT_MIN ;
	for( ij=0 ; ij<(N*N) ; ij++ ) 
	{
		if( grille[ij] == '-' ) 							// si case vide
		{			
			grille[ij] = 'x' ;
			valeur = min_AB( grille, N, alpha, beta ) ;
			grille[ij] = '-' ;
			if( score < valeur ) score = valeur ;
			if( score >= beta ) {
//				printf( "coupure \n" ) ;
				return score ;
			}
			if( score > alpha ) alpha = score ;
			if( alpha >= beta ) return alpha ;			
		}
	}

	return score ;
}




// Fonction min de l'algo alphabeta
int min_AB( char grille[], int N, int alpha, int beta )
{
	int score, ij, valeur ;

	if( gagnant(grille,N) == 'x' ) return 1 ;
	if( gagnant(grille,N) == 'o' ) return -1 ;
	if( gagnant(grille,N) == 'n' ) return 0 ;

	score = INT_MAX ;
	for( ij=0 ; ij<(N*N) ; ij++ ) 
	{
		if( grille[ij] == '-' ) 							// si case vide
		{					
			grille[ij] = 'o' ;
			valeur = max_AB( grille, N, alpha, beta ) ;
			grille[ij] = '-' ;
			if( score > valeur ) score = valeur ;
			if( score <= alpha ) {
//				printf( "coupure \n" ) ;
				return score ;
			}
			if( score < beta ) beta = score ;
			if( alpha >= beta ) return alpha ;			
		}
	}

	return score ;
}