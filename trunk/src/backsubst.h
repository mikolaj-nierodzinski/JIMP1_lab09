#ifndef _BACKSUBST_H
#define _BACKSUBST_H

#include "mat_io.h"

/**
 * Zwraca 0 - wsteczne podstawienie zakonczone sukcesem
 * Zwraca 1 - błąd dzielenia przez 0 (element na diagonali = 0)
 * Zwraca 2 - błąd nieprawidłowych rozmiarów macierzy
 */
/// should be int instead of void function ()
/// có vẻ mình chưa hiểu hết về cái gauss's elimination này để mà 
int back_substitution(Matrix *mat, Matrix *b, double *x);

#endif
