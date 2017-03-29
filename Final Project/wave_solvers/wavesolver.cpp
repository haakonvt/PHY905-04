#include "wavesolver.h"
#include "wavesolver_ispc.h"
#include <cmath>
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>

using namespace std;
using namespace ispc;

extern void wavesolver_serial( int nx, float c,
                             float u[],  float u_prev[], float u_next[], int omp_threads);

/*extern void wavesolver_omp(int nx, float c, float u[],  float u_prev[], float u_next[]);
*/
unsigned int WaveSolver::timesteps() const
{
    return m_timesteps;
}

WaveSolver::WaveSolver(unsigned int nx)
{
    m_nx = nx;
    m_nxPlusTwo = m_nx+2;
    int nxnx = m_nxPlusTwo * m_nxPlusTwo;

    u      = new float[nxnx];
    u_next = new float[nxnx];
    u_prev = new float[nxnx];

    memset(u,      0, nxnx * sizeof(float));
    memset(u_next, 0, nxnx * sizeof(float));
    memset(u_prev, 0, nxnx * sizeof(float));

    initializeGauss(0, 0, 0.2*m_nx/64.0);
}

WaveSolver::~WaveSolver()
{
    delete[] u;
    delete[] u_prev;
    delete[] u_next;
}

void WaveSolver::initializeGauss(float x0, float y0, float variance)
{
    for(unsigned int i=0; i<m_nx+2; i++) {
        unsigned int n = i+1;
        float x = (i - 0.5*(m_nx+2))*DX;
        float dx = x-x0;

        for(unsigned int j=0; j<m_nx+2; j++) {
            unsigned int m = j+1;
            float y = (j - 0.5*(m_nx+2))*DX;
            float dy = y-y0;
            float dr2 = dx*dx + dy*dy;
            u[index(i,j)]      = exp(-0.5*dr2/variance);
            //u_prev[index(n,m)] = exp(-0.5*dr2/variance);
        }
    }
    copyBoundary();
}

void WaveSolver::copyBoundary() {
    for(unsigned int i=0; i<m_nx+2;i++) {
        u[index(0, i)]           = 0;//u[index(m_nx, i+1)];
        u[index(m_nx+1, i)]      = 0;//u[index(1, i+1)];
        u[index(i, 0)]           = 0;//u[index(i+1, m_nx)];    // y=0 row
        u[index(i, m_nx+1)]      = 0;//u[index(i+1, 1)];  // y=n-1 row
        u_prev[index(0, i)]      = 0;//u_prev[index(m_nx, i+1)];
        u_prev[index(m_nx+1, i)] = 0;//u_prev[index(1, i+1)];
        u_prev[index(i, 0)]      = 0;//u_prev[index(i+1, m_nx)];    // y=0 row
        u_prev[index(i, m_nx+1)] = 0;//u_prev[index(i+1, 1)];  // y=n-1 row
    }
}

void WaveSolver::write_to_file(float *u, int width, int height, int which_code) {
    cout << "Storing u(x,y) in file wave_u.txt" << endl;
    ofstream myfile;
    string filename;
    if (which_code == 1) filename = "wave_u_serial.txt";
    if (which_code == 2) filename = "wave_u_ispc.txt";
    if (which_code == 3) filename = "wave_u_omp.txt";
    myfile.open (filename);
    for (int i=0; i<width+2; i++){
      for (int j=0; j<height+2; j++){
        myfile << u[index(j,i)] << " ";
      }
      myfile << "\n";
    }
    myfile.close();

    //printf("Wrote image file, frame %i\n" %m_timesteps);
    //printf("Wrote image file %s\n", fn);

}

void WaveSolver::step(int which_code, bool write_to_file_now) {
    if(which_code == 1){
        int omp_threads = 1;
        wavesolver_serial(m_nx, m_C, u, u_prev, u_next, omp_threads);
        if (write_to_file_now){cout << "serial" << endl;}
    }
    if(which_code == 2){
        wavesolver_ispc(m_nx, m_C, u, u_prev, u_next);
        if (write_to_file_now){cout << "ispc solver" << endl;}
    }
    if(which_code == 3){
        int omp_threads = 4;
        wavesolver_serial(m_nx, m_C, u, u_prev, u_next, omp_threads);
        if (write_to_file_now){cout << "omp solver" << endl;}
    }

    if (write_to_file_now){
      write_to_file(u_next, m_nx, m_nx, which_code);
      write_to_file_now = false;
      cout << "for solution at timestep: " << m_timesteps << endl;
    }

    std::swap(u_prev, u);
    std::swap(u_next, u);
    //copyBoundary();
    m_timesteps++;
}
