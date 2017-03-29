#include <stdio.h>
#include <stdlib.h>

#define matSize 2000
#define maxTest 1

/* Row-major order (Same as Fortran). */
#define ind(i,j) (j)*matSize+i


/* Statically allocate the matrices.  This can improve the compiler's
   ability to optimize operations on these variables.  This will be discussed
   in more detail later in the course. */
double matA[matSize*matSize], matB[matSize*matSize], matC[matSize*matSize];

double mysecond(void);
void dummy(double *a, double *b, double *c);

int main(int argc, char *argv[])
{
    double sum, tStart, tEnd, tLoop, rate, t;
    int    i, j, k, tests;

    /* Initialize the matrics */
    /* Note that this is *not* in the best order with respect to cache;
       this will be discussed later in the course. */
    for (i=0; i<matSize; i++)
        for (j=0; j<matSize; j++) {
            matA[ind(i,j)] = 1.0 + i;
            matB[ind(i,j)] = 1.0 + j;
            matC[ind(i,j)] = 0.0;
        }

    tLoop = 1.0e10;
    for (tests=0; tests<maxTest; tests++) {
        tStart = mysecond();
        for (i=0; i<matSize; i++)
            for (j=0; j<matSize; j++) {
                sum = 0.0;
                for (k=0; k<matSize; k++)
                    sum += matA[ind(i,k)] * matB[ind(k,j)];
                matC[ind(i,j)] = sum;
            }
        tEnd = mysecond();
        t = tEnd - tStart;
        dummy(matA, matB, matC);
        if (t < tLoop) tLoop = t;
        if (matC[ind(0,0)] < 0) {
            fprintf(stderr, "Failed matC sign test\n");
        }
    }

    /* Note that explicit formats are used to limit the number of
       significant digits printed (at most this many digits are significant) */
    printf("Matrix size = %d\n", matSize);
    rate = (2.0 * matSize) * matSize * (matSize / tLoop);
    printf("Rate        = %.2e MFLOP/s\n", rate * 1.0e-6);
    printf("Time        = %.2e secs\n", tLoop);


    return 0;
}
