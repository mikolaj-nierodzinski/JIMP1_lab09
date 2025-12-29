#include "mat_io.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * Zwraca <> NULL - udalo sie wczytac
 * Zwraca == NULL - podczas wczytywania wystapil blad
 */
Matrix *readFromFile(char *fname)
{
	int r, c;
	int ir, ic;
	FILE *fin = fopen(fname, "r");
	Matrix *mat = NULL;

	if (fin != NULL)
	{
		fscanf(fin, "%d %d", &r, &c);
		mat = createMatrix(r, c);
		if (mat != NULL)
		{
			for (ir = 0; ir < r; ir++)
				for (ic = 0; ic < c; ic++)
					fscanf(fin, "%lf", &(mat->data[ir][ic]));
		}
		else
		{
			fprintf(stderr, "Wystąpił problem podczas tworzenia macierzy o rozmiarach %d x %d dla danych z pliku: %s\n", r, c, fname);
		}

		fclose(fin);
	}
	else
	{
		fprintf(stderr, "Nie mogę otworzyć pliku o nazwie: %s\n", fname);
	}

	return mat;
}

void printToScreen(Matrix *mat, FILE *fo)
{
	int i, j;
	fprintf(fo, "[ \n");
	for (i = 0; i < mat->r; i++)
	{
		fprintf(fo, "  ");
		for (j = 0; j < mat->c; j++)
		{
			fprintf(fo, "%f ", mat->data[i][j]);
		}
		fprintf(fo, "; \n");
	}
	fprintf(fo, "]\n");
}

Matrix *createMatrix(int r, int c)
{
	int i;
	Matrix *mat = (Matrix *)malloc(sizeof(Matrix));
	if (mat != NULL)
	{
		mat->r = r;
		mat->c = c;
		mat->data = (double **)malloc(sizeof(double *) * r);
		for (i = 0; i < r; i++)
		{
			mat->data[i] = (double *)malloc(sizeof(double) * c);
		}
	}

	return mat;
}

void freeMatrix(Matrix *mat) {
	for(int i = 0; i < mat->r; i++)
		free(mat->data[i]);
	free(mat->data);
	free(mat);
}

void swap(int *a, int *b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}
