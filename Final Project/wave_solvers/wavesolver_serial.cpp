#include <libiomp/omp.h>

static inline int index(int i, int j, int size) {
    return j * (size+2) + i;
}

void wavesolver_serial( int size, float c,
                        float u[], float u_prev[], float u_next[], int omp_threads){
    omp_set_num_threads(omp_threads);
#pragma omp parallel for
    for (int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            int m = j+1;
            int n = i+1;
            float ddx = u[index(m+1, n, size)] + u[index(m-1, n, size)];
            float ddy = u[index(m, n+1, size)] + u[index(m, n-1, size)];
            float ddt_rest = 2.0*u[index(m, n, size)] - u_prev[index(m, n, size)];

            u_next[index(m, n, size)] = c*(ddx + ddy - 4.0*u[index(m, n, size)]) + ddt_rest;

            //u_next[index(m,n,size)] = 2.0*u[index(m,n,size)] - u_prev[index(m,n,size)] - 4.0*u[index(m,n,size)] + u[index(m+1,n,size)] + u[index(m-1,n,size)] + u[index(m,n+1,size)] + u[index(m,n-1,size)];

            /*
            float ddx = u[index(m+1,n,size)] + u[index(m-1,n,size)];
            float ddy = u[index(m,n+1,size)] + u[index(m,n-1,size)];
            float ddt_rest = (ddx + ddy - 4.0*u[index(m,n,size)]); // * c*c*dt*dt/(dx*dx) = 1
            u_next[index(m,n,size)] = 2.0*u[index(m,n,size)] - u_prev[index(m,n,size)] + ddt_rest;*/
        }
    }
    // Swap u, u_p and u_n
    /*std::swap(u_prev, u);
    std::swap(u_next, u);
    for (int i = 0; i < size; i++) {
      for(int j = 0; j < size; j++) {
        int m = j+1;
        int n = i+1;
        u_prev[index(m,n,size)] = u[index(m,n,size)];
      }
    }
    for (int i = 0; i < size; i++) {
      for(int j = 0; j < size; j++) {
        int m = j+1;
        int n = i+1;
        u[index(m,n,size)] = u_next[index(m,n,size)];
      }
    }*/
}
