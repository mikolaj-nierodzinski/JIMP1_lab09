#include "gauss.h"
#include "backsubst.h"
#include "mat_io.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


char *toString(int num) {
    int n = num;
    int dg = (n == 0) ? 1 : 0;
    int neg = (n < 0);

    if (neg) n = -n;

    int tmp = n;
    while(tmp > 0) {
        tmp /= 10;
        dg++;
    }

    char *ret = malloc(dg + neg + 1);
    if(!ret) return NULL;

    ret[dg + neg] = '\0';

    for(int i = dg + neg - 1; i >= neg; i--) {
        ret[i] = '0' + (n % 10);
        n /= 10;
    }

    if(neg)
        ret[0] = '-';

    return ret;
}

void append(char **s, char *t) {
    const char *tmp = ".txt";
    char *ret = malloc(strlen(t) + strlen(*s) + strlen(tmp) + 1); 
    if(!ret) {
        fprintf(stderr, "bad alloc at addChar func\n");
        exit(EXIT_FAILURE);
    }

    memcpy(ret, *s, strlen(*s));
    memcpy(ret + strlen(*s), t, strlen(t));
    memcpy(ret + strlen(*s) + strlen(t), tmp, strlen(tmp) + 1);
    *s = ret;
}

int main(int argc, char ** argv) {
    int tc = 0;
    while(1) {
        tc++;
        char *num = toString(tc);
        char *inFileA = strdup("./dane/A");
        char *inFileB = strdup("./dane/b");
        append(&inFileA, num);
        append(&inFileB, num);

        if(!fopen(inFileA, "r")) {
            fprintf(stderr, "file scanning stopped at %s\n", inFileA);
            free(num);
            free(inFileA);
            free(inFileB);
            break;
        }
        Matrix *A = readFromFile(inFileA);

        if(!fopen(inFileB, "r")) {
            fprintf(stderr, "file scanning stopped at %s\n", inFileB);
            free(num);
            free(inFileA);
            free(inFileB);
            break;
        }
        Matrix *B = readFromFile(inFileB);

        if(!A || !B) {
            fprintf(stderr, "input file has incorrect format: %s && %s\n", inFileA, inFileB);
            free(num);
            free(inFileA);
            free(inFileB);
            return 1;
        }

        char *outFile = "./outputSample/sample";
        append(&outFile, num);
        FILE *fo = fopen(outFile, "w");
        if(!fo) {
            fprintf(stderr, "can not open file %s\n", outFile);
            free(num);
            free(inFileA);
            free(inFileB);
            free(outFile);
            continue;
        }

        printToScreen(A, fo);
        printToScreen(B, fo);

        if((B->c != 1) || (A->r != A->c)) {
            fprintf(stderr, "can not solve this equation system at %s && %s\n", inFileA, inFileB);
            fprintf(fo, "can not solve this equation system at %s && %s\n", inFileA, inFileB);
            free(num);
            free(inFileA);
            free(inFileB);
            free(outFile);
            continue;
        }

        int res = eliminate(A, B);
        if(res == 1) {
            fprintf(fo, "Macierz osobliwa\n");
            free(num);
            free(inFileA);
            free(inFileB);
            free(outFile);
            continue;
        }

        double *x = malloc(A->r * sizeof(double));
        res = back_substitution(A, B, x);
        if(res == 1) {
            fprintf(stderr, "degenerate matrix at %s && %s\n", inFileA, inFileB);
            free(num);
            free(inFileA);
            free(inFileB);
            free(outFile);
            continue;
        } else if(res == 2) {
            fprintf(stderr, "not appropriate size at %s && %s\n", inFileA, inFileB);
            free(num);
            free(inFileA);
            free(inFileB);
            free(outFile);
            continue;
        }

        fprintf(fo, "solution:\n");
        for(int i = 0; i < A->r; i++) {
            fprintf(fo, "x[%d] = %.6lf\n", i, x[i]);
        }

        printf("succeeded solving %s %s\n", inFileA, inFileB);

        freeMatrix(A);
        freeMatrix(B);
        free(num);
        free(inFileA);
        free(inFileB);
        free(outFile);
        fclose(fo);
    }
}
