#include <iostream>
#include <armadillo>

using namespace std;
using namespace arma;

double mysecond(void);

int main()
{
    double t0,t1,T,r,t_run;

    vec n_vals = {250, 1000, 5e3, 1e4, 5e4, 1e5, 5e5, 1e6, 5e6};
    vec nmbr_of_tests = {5221468, 1593036, 339095, 170965, 32543, 16196, 2328, 1212, 208};

    int i,j,k,n,tests;
    // Loop through all elements of a and copy to c
    for (j=0; j<n_vals.n_elem; j++){
        T     = 0; // Total time (aiming for 1 sec)
        n     = n_vals(j);
        tests = nmbr_of_tests(j);

        // Initialize vectors of length n:
        // a is filled with random numbers and c is zeroes
        vec c = zeros(n);
        vec a = randu(n);

        for (k=0; k<tests; k++){
            t0 = mysecond();
            for (i=0; i<n; i++){
                c(i) = a(i);
            }
            t1 = mysecond();
            T += t1-t0;
        }

        t_run = T/tests;
        r     = n*8*2 / (1e6*t_run); // MB/s
        cout << "n, tests:      " << n << ", " << tests << endl;
        cout << "Tot. t, t/run: " << T << ", " << t_run << endl;
        cout << "Rate MB/s:     " << r << endl;
        cout << " " << endl;
    }
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