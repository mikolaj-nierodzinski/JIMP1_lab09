#include "gauss.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/**
 * Zwraca 0 - elimnacja zakonczona sukcesem
 * Zwraca 1 - macierz osobliwa - dzielenie przez 0
 */
int eliminate(Matrix *mat, Matrix *b) {
    int n = mat->r;
    const double eps = 1e-10;
    double *scale = (double *)malloc(n * sizeof(double));
    
    if (scale == NULL) {
		fprintf(stderr, "bad alloc\n");
        exit(EXIT_FAILURE);
    }
    
    // Tính hệ số tỉ lệ cho mỗi hàng
    // calculate scale for each row
    for (int i = 0; i < n; i++) {
        scale[i] = 0.0;
        for (int j = 0; j < n; j++) {
            double abs_val = fabs(mat->data[i][j]);
            if (abs_val > scale[i]) {
                scale[i] = abs_val;
            }
        }
        
        // Kiểm tra hàng toàn 0
        // all-zeros row check
        if (scale[i] < eps) {
            free(scale);
            return 1;
        }
    }
    
    // Eliminacja xuôi với scaled partial pivoting
    // forward elimination with scaled partial pivoting 
    for (int k = 0; k < n - 1; k++) {
        // find row that has ratio |a[i][k]| / scale[i] largest 
        int pivot_row = k;
        double max_ratio = fabs(mat->data[k][k]) / scale[k];
        
        for (int i = k + 1; i < n; i++) {
            double ratio = fabs(mat->data[i][k]) / scale[i];
            if (ratio > max_ratio) {
                max_ratio = ratio;
                pivot_row = i;
            }
        }
        
        // check if pivot equals 0
        if (fabs(mat->data[pivot_row][k]) < eps) {
            free(scale);
            return 1;
        }
        
        // swap k-th row and pivot-row
        if (pivot_row != k) {
            // Đổi hàng trong ma trận A
            double *temp_row = mat->data[k];
            mat->data[k] = mat->data[pivot_row];
            mat->data[pivot_row] = temp_row;
            
            // Đổi hàng trong vector b
            double temp_b = b->data[k][0];
            b->data[k][0] = b->data[pivot_row][0];
            b->data[pivot_row][0] = temp_b;
            
            // Đổi scale
            double temp_scale = scale[k];
            scale[k] = scale[pivot_row];
            scale[pivot_row] = temp_scale;
        }
        
        // eliminate elements below pivot
        for (int i = k + 1; i < n; i++) {
            double factor = mat->data[i][k] / mat->data[k][k];
            
            // update matrix A's i-th row 
            for (int j = k; j < n; j++) {
                mat->data[i][j] -= factor * mat->data[k][j];
            }
            
            // update vector b
            b->data[i][0] -= factor * b->data[k][0];
        }
    }
    
    // Kiểm tra phần tử cuối cùng trên đường chéo
    // check the last element on diagonal 
    if (fabs(mat->data[n-1][n-1]) < eps) {
        free(scale);
        return 1;
    }
    
    free(scale);
    return 0;
}
