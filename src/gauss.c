#include "gauss.h"
#include <stdio.h>   // dla printf

/**
 * Zwraca 0 - elimnacja zakonczona sukcesem
 * Zwraca 1 - macierz osobliwa - dzielenie przez 0
 */
int eliminate(Matrix *mat, Matrix *b){  		
	
	int n = mat->r;                                

	for( int k= 0; k < n-1; k++ ) {
		int max = k;				// wybór elementu dominującego w kolumnie i zamiana równań miejscami
		for ( int w=k+1; w < n; w++)
			if( mat->data[w][k] > mat->data[mx][k])
				mx = w;
		if( mx != k){				// zamiana wierszy jeśli mx nie jest równe k
			double *tmp = mat->data[k];
			mat->data[k] = mat->data[mx];
			mat->data[mx] = tmp;
			double *tr = b->data[k];
			b->data[k] = b->data[mx];
			b->data[mx] = tr;
		}			
		for( int w= k+1; w < n; w++ ) {
			if((mat->data[k][k]) == 0) {
				printf("Błąd, dzielenie przez 0\n");
				return 1;
			}
			double q = mat->data[w][k] / mat->data[k][k];     
			for( int i= k; i < n; i++ )
				mat->data[w][i] -= q * mat->data[k][i];
			b->data[w][0] -= q*b->data[k][0] ;
		}
	}		    
						  	 
	return 0;
}

