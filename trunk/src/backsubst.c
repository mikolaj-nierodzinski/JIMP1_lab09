#include "backsubst.h"
#include <math.h>
/**
 * Zwraca 0 - wsteczne podstawienie zakonczone sukcesem
 * Zwraca 1 - błąd dzielenia przez 0 (element na diagonali = 0)
 * Zwraca 2 - błąd nieprawidłowych rozmiarów macierzy
 */
int back_substitution(Matrix *mat, Matrix *b, double *x) {
    const double eps = 1e-10; // Tolerancja dla sprawdzenia zera
    
    // check if the size is appropriate
    if (mat->r != mat->c) {
        return 2; // Macierz A musi być kwadratowa
    }
    if (b->r != mat->r || b->c != 1) {
        return 2; // Vector b musi mieć odpowiedni rozmiar
    }
    
    int n = mat->r;
    
    // Kiểm tra phần tử cuối cùng trên đường chéo
    if (fabs(mat->data[n-1][n-1]) < eps) {
        return 1; 
    }
    
    // Tính x[n-1]
    x[n-1] = b->data[n-1][0] / mat->data[n-1][n-1];
    
    // Tính ngược từ x[n-2] đến x[0]
    for (int i = n - 2; i >= 0; i--) {
        // check the element on the diagonal
        if (fabs(mat->data[i][i]) < eps) {
            return 1; 
        }
        
        double sum = 0.0;
        for (int j = i + 1; j < n; j++) {
            sum += mat->data[i][j] * x[j];
        }
        x[i] = (b->data[i][0] - sum) / mat->data[i][i];
    }
    
    return 0; 
}
