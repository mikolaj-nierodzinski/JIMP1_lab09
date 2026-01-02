#include "gauss.h"
#include "backsubst.h"
#include "mat_io.h"
#include <stdlib.h>
#include <stdio.h>


int main(int argc, char ** argv) {
	Matrix *A = readFromFile(argv[1]);
	Matrix *b = readFromFile(argv[2]);

	if (A == NULL) return -1; 
	if (b == NULL) return -2;
	printToScreen(A, stdout);
	printToScreen(b, stdout);

	if((b->c != 1) || (A->r != A->c)) {
		fprintf(stderr, "can not solve this equation\n");
		return 1;
	}

	int res = eliminate(A, b);

	if(res == 1) {
		fprintf(stderr, "degenerate matrix\n");
		return 1;
	}

	double *x = malloc(A->r * sizeof(double));
	res = back_substitution(A, b, x);

	if(res == 1) {
		fprintf(stderr, "degenerate matrix\n");
		return 1;
	} else if(res == 2) {
		fprintf(stderr, "not appropriate size\n");
		return 2;
	}

	printf("solution:\n");
	for(int i = 0; i < A->r; i++) {
		printf("%6lf\n", x[i]);
	}

	freeMatrix(A);
	freeMatrix(b);

	return 0;
}
