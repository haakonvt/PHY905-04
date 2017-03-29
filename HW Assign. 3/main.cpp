#include <iostream>
#include <armadillo>
#include <time.h>
#include <algorithm>

using namespace std;
using namespace arma;

int main(){
    /* This code compares different approaches to transposing a matrix.
     * Uncomment ONE method at the time */

    // Matrix sizes, n x n
    vec nvec = {20,   100,  500,  800, 1000, 1500, 1750, 2000, 3000, 4000};
    vec test = {5000,2000, 1000,  500, 300,  200,  100,  75,   50,   25}; // Max tests

    clock_t start, finish;

    int i,j,k,l,n,T;
    double comp_time = 1e100;
    double new_time;
    vec sum_time = zeros(nvec.n_elem);

    for (l=0; l<nvec.n_elem; l++){
        n = nvec(l);
        T = test(l);
        mat X(n,n,fill::randu); // Will generate matrix with random elements
        mat Y(n,n);             // Will hold the transpose

        for (k=0; k<T; k++){    // Iterations for each n
            start = clock();
            // --- Start of methods ---

            // Standard transpose
            for (i=0; i<n; i++){
                for (j=0; j<n; j++){
                    Y(j,i) = X(i,j);
                }
            }

            // Block transpose
            int i1,j1;
            int bsize = 16;
            for (i=0; i<n; i+=bsize){
                for (j=0; j<n; j+=bsize){
                    for (i1=i; i1<min(i+bsize-1,n); i1++){
                        for (j1=j; j1<min(j+bsize-1,n); j1++){
                            Y(i1,j1) = X(j1,i1);
                        }
                    }
                }
            }

            //Inbuilt transpose function (armadillo)
            Y = X.t();

            // --- End of methods ---
            finish   = clock();
            new_time = (finish-start)/(double) CLOCKS_PER_SEC;
            if (new_time < comp_time){
                comp_time = new_time;
            }
            if (k > 0){ // Skip "cold start"
                sum_time(l) += new_time;
            }
        }
        cout << "n: " << n << ", tests : " << T + Y(n-1,n-1)*0.0 << endl;
        cout << "t min: " << comp_time << ", t avg: " << sum_time(l)/(k-1) << endl;
        cout << "------------" << endl;
        comp_time = 1e100; // Prepare for next iteration
    }

    /* Write out times for easy copying
    for (int m=0; m<nvec.n_elem; m++){
        cout << sum_time(m)/(test(m)-1) << "," << endl;
    }*/

    return 0;
}

