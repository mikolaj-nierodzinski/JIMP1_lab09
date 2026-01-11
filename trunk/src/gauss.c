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
        
        if (mat->data[k][k]==1) {
            return 1;
        }

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
