#include "gauss.h"
#include "backsubst.h"
#include "mat_io.h"
#include <stdlib.h>
#include <stdio.h>


int main(int argc, char ** argv) {
	Matrix *A = readFromFile(argv[1]);
	Matrix *b = readFromFile(argv[2]);
	
	if(argc > 3 && fopen(argv[3], "w")) {

		freopen(argv[3], "w", stdout);
	}

	if (A == NULL) return -1; 
	if (b == NULL) return -2;
	printToScreen(A);
	printToScreen(b);

	if((b->c != 1) || (A->r != A->c)) {
		fprintf(stderr, "can not solve this equation\n");
		return 1;
	}
	int res = eliminate(A, b);
	double *x = malloc(A->r * sizeof(double));
	back_substitution(A, b, x);

	printf("Nghiem: x = %.6f, y = %.6f, z = %.6f\n", x[0], x[1], x[2]);

	freeMatrix(A);
	freeMatrix(b);

	return 0;
}
