#include <stdio.h>
#include <stdlib.h>
#include "mysecond.cpp"

double mysecond(void);

int main(void){

    // HW7 *******************
    int max_tests = 25;
    const int n = 100;
    double A[n][n],B[n][n],C[n][n];
    double t0,t1,T;
    int test;
    T = 0;

    for (int i=0; i<n; i++){
        for (int j=0; j<n; j++){
            A[i][j] = i+j+1;
            B[i][j] = 2*j+i+1;
        }
    }

    for (test = 0; test<max_tests; test++){
        t0 = mysecond();                            // Start timing
        for (int i=0; i<n; i++){
            for (int j=0; j<n; j++){
                double s = 0.0;        // The sum for C(i,j)
                for (int k=0; k<n; k++){
                    s += A[i][k]*B[k][j];
                }
                C[i][j] = s;
            }
        }
        t1 = mysecond(); // End timing
        T += t1-t0;
        if (T>1.0){
            max_tests = test;
        }
    }
    printf("Total t: %.2f, t/loop: %.3f\n",T,T/max_tests);
    printf("%f, %f\n%f, %f\n", C[0][0],C[0][1],C[1][0],C[1][1]);

    return 0;
}



/* // HW6 ***********************
 int n = 1000000;
 int a[n],c[n];
 double t0,t1;
 int nk = 1000;

 // Loop over number of threads from 1,2,4,6...,14,16
 for (int Nt = 1; Nt<17; Nt += 2){
 omp_set_num_threads(Nt);
 t0 = omp_get_wtime(); // Start timing

 for (int k=0; k<nk; k++) { // Number of tests
 #pragma omp parallel for
 for (int i=0; i<n; i++){
 c[i] = a[i];
 }
 }
 t1 = omp_get_wtime(); // End timing
 double tpl = (t1-t0)/nk; // Time per loop
 double rate = n*4*2 / (1e6*tpl);
 printf("%.2d threads, t/loop: %.5f sec, rate: %.0f MB/s\n",Nt,tpl,rate);

 if (Nt%2 != 0){Nt = 0;} // Fix step from 1->2

 }
 */

/*
 double sum = 0;
 int      N = 78;
 double   v[N];
 for (int i=1; i<N+1; i++){v[i-1] = i;}

 #pragma omp parallel for reduction(+:sum)
 for (int i=0; i<N; i++){
 sum += v[i];
 }
 double cor_sum = N*(N+1)/2.0;
 printf("%f while correct sum is %f\n", sum,cor_sum);
 */


/*
 omp_set_num_threads(4);
 #pragma omp parallel
 {
 int id = omp_get_thread_num();
 int np = omp_get_num_threads();
 printf("%d / %d\n",id,np);
 }*/
