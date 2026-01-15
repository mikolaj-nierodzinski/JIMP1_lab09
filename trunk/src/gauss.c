#include "gauss.h"
#include <math.h>

/**
 * Zwraca 0 - eliminacja zakończona sukcesem
 * Zwraca 1 - macierz osobliwa - dzielenie przez 0
 */
int eliminate(Matrix *mat, Matrix *b) {
    int n = mat->r;
    int i, j, k;
    double factor;
	
    for (k = 0; k < n - 1; k++) {
	//Wybór elementu głównego
    int maksw = k;
    double maks = fabs(mat->data[k][k]);
    for (int l = k + 1; l < n; l++) {
        if (fabs(mat->data[l][k]) > maks) {
            maks = fabs(mat->data[l][k]);
            maksw = l;
        }
    }

    //Zamiana wierszy
    if (maksw != k) {
        double *tempRow = mat->data[k];
        mat->data[k] = mat->data[maksw];
        mat->data[maksw] = tempRow;

        double tempB = b->data[k][0];
        b->data[k][0] = b->data[maksw][0];
        b->data[maksw][0] = tempB;
    }
        if (fabs(mat->data[k][k])<0.00001) {
            return 1;
        }
	//eliminacja
        for (i = k + 1; i < n; i++) {
            factor = mat->data[i][k] / mat->data[k][k];

            for (j = k; j < mat->c; j++) {
                mat->data[i][j] -= factor * mat->data[k][j];
            }
            
            b->data[i][0] -= factor * b->data[k][0];
        }
    }

    return 0;
}
