#include <libiomp/omp.h>
#include <armadillo>

int main(void){
    const int n = 20; int Nt_max = 8; // Matrix size and max threads
    arma::mat A(n,n),B(n,n),C(n,n);
    double t0,t1,T,s;
    double T_end_tests = 0.5; // Seconds passed before quitting loop
    int test = 0;
    int max_tests_default = 300000; int max_tests = max_tests_default;

    // Fill A and B with numbers to check C is correctly computed
    for (int i=0; i<n; i++){
        for (int j=0; j<n; j++){
            A(i,j) = i+j+1;
            B(i,j) = 2*j+i+1;
            }
        }
    // One thread, NO openMP
    printf("Matrix %dx%d, No openMP, ",n,n);

    for (test = 0; test<max_tests; test++){
        t0 = omp_get_wtime(); // Start timing
        for (int i=0; i<n; i++){
            for (int j=0; j<n; j++){
                s = 0.0; // The sum for C(i,j)
                for (int k=0; k<n; k++){
                    s += A(i,k)*B(k,j);
                    }
                C(i,j) = s;
                }
            }
        t1 = omp_get_wtime(); // End timing
        T += t1-t0;
        if (T>T_end_tests){max_tests = test+1;}
        }
    printf("Total t: %.2f, t/loop: %.7f, tests: %d, %f\n",T,T/max_tests,max_tests,C(1,1));

     // 1-8 threads, with openMP
    for (int Nt=1; Nt<Nt_max+1; Nt++){
        T = 0; // Reset timer
        max_tests = max_tests_default; // Reset counter
        omp_set_num_threads(Nt);
        printf("Matrix %dx%d, threads: %d, ",n,n,Nt);

        for (test = 0; test<max_tests; test++){
            t0 = omp_get_wtime(); // Start timing
#pragma omp parallel for
                for (int i=0; i<n; i++){
                    for (int j=0; j<n; j++){
                        s = 0.0; // The sum for C(i,j)
                        for (int k=0; k<n; k++){
                            s += A(i,k)*B(k,j);
                            }
                        C(i,j) = s;
                        }
                    }
            t1 = omp_get_wtime(); // End timing
            T += t1-t0;
            if (T>T_end_tests){max_tests = test+1;}
            }
