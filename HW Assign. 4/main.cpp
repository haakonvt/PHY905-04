#include <iostream>
#include <armadillo>
#include <time.h>
#include <algorithm>

using namespace std;
using namespace arma;

int main(){
    /* This code compares different approaches to matrix-matrix-multiply.
     * Uncomment ONE method at the time */

    // Matrix sizes, n x n
    vec nvec = {20,100,400,1000,1200,1500,3000,4000};
    clock_t start, finish;

    int i,j,k,l,n;

    int use_blocked = 2; // 1 = blocked, 0 not, 2 = arma
    double s;

    int bsize = 20;

    for (l=0; l<int(nvec.n_elem); l++){
        n = nvec(l);
        mat A(n,n,fill::randu); // Generate matrix with random elements
        mat B(n,n,fill::randu);
        mat C(n,n);             // Will hold the matrix product


        start = clock();

        if (use_blocked == 1){ // Assumption: n is multiple of bsize
            cout << "Using BLOCKED code" << endl;
            int kk,jj,i,j,k;
            double sum = 0;
            int en = bsize*(n/bsize);
            for (kk = 0; kk < en; kk += bsize) {
                for (jj = 0; jj < en; jj += bsize) {
                    for (i = 0; i < n; i++) {
                        for (j = jj; j < jj + bsize; j++) {
                            sum = C(i,j);
                            for (k = kk; k < kk + bsize; k++) {
                                sum += A(i,k)*B(k,j);
                            }
                            C(i,j) = sum;
                        }
                    }
                }
            }
            finish   = clock();
        }


        if (use_blocked == 0){
            cout << "Using SIMPLE code" << endl;
            start = clock();
            for (i=0; i<n; i++){
                for (j=0; j<n; j++){
                    s = 0.0;        // The sum for C(i,j)
                    for (k=0; k<n; k++){
                        s += A(i,k)*B(k,j);
                    }
                    C(i,j) = s;
                }
            }
            finish = clock();
        }

        if (use_blocked == 2){
            cout << "Using ARMA code" << endl;
            start = clock();
            C = A*B;
            finish = clock();
        }
        double new_time = (finish-start)/(double) CLOCKS_PER_SEC;

        mat C2 = A*B;
        double diff = sum(sum(C2-C));
        //cout << A << endl;
        //cout << B << endl;
        cout << "n: " << n << ", time: " << new_time << ", diff: " << diff << endl;
        //cout << C << endl;
        cout << "----" << endl;
        //cout << C2 << endl;
    }

    return 0;
}
