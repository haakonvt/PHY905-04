#include <iostream>
#include "wavesolver.h"
#include <stdlib.h>
#include <sys/time.h>
#include <libiomp/omp.h>
#include <string>

using namespace std;

double run(int gridSize, int timesteps, int which_code, bool write_to_file) {
    WaveSolver solver(gridSize);
    unsigned int N = timesteps;
    bool write_to_file_now = false; // Set to true last timestep

    double t = 0;
    for(int j=0; j<N; j++) {
        if (write_to_file){
          if (j+1 >= N){
            write_to_file_now = true;
          }
        }
        struct timeval start, end;
        gettimeofday(&start, NULL);
        solver.step(which_code,write_to_file_now);
        gettimeofday(&end, NULL);
        double timeElapsed = ((end.tv_sec  - start.tv_sec) * 1000000u + end.tv_usec - start.tv_usec) / 1.e6;
        t += timeElapsed;
    }

    return t;
}

int main(int args, char **argv)
{
    bool write_to_file = true;
    int maxGridSize = 1024;
    int timesteps = 5;
    if(args>1) maxGridSize = atoi(argv[1]);
    if(args>2) timesteps = atoi(argv[2]);
    if(args>3) write_to_file = false;

    for(int gridSize=maxGridSize; gridSize<=maxGridSize; gridSize += 128) {
        double timeSerial = run(gridSize, timesteps, 1, write_to_file);
        double timeISPC   = run(gridSize, timesteps, 2, write_to_file);
        double timeOMP = run(gridSize, timesteps, 3, write_to_file);
        double speedSerial = gridSize*gridSize*timesteps/timeSerial*1e-6;
        double speedISPC   = gridSize*gridSize*timesteps/timeISPC*1e-6;
        double speedOMP    = gridSize*gridSize*timesteps/timeOMP*1e-6;
        double timePerTimestepSerial = timeSerial / timesteps;
        double timePerTimestepISPC   = timeISPC   / timesteps;
        double timePerTimestepOMP    = timeOMP    / timesteps;
        /*cout << "---------------------------" << endl;
        cout << "N=" << gridSize << ", speed is in million grid points per second" << endl;
        cout << "Speed: " << speedSerial << " (SERIAL) vs " << speedISPC << " (ISPC), speedup: " << speedISPC/speedSerial << " x" << endl;
        cout << "Speed: " << speedSerial << " (SERIAL) vs " << speedOMP <<  " (OMP),  speedup: " << speedOMP/speedSerial << " x" << endl;
        cout << "Speed: " << speedOMP    << " (OMP)    vs " << speedISPC << " (ISPC), speedup: " << speedISPC/speedOMP << " x" << endl;
        */
        printf("%i & %.0f & %.0f & %.0f & %.2f & %.2f & %.2f \\\\ \n",gridSize, speedSerial, speedISPC, speedOMP, speedISPC/speedSerial, speedOMP/speedSerial, speedISPC/speedOMP);
//        cout << gridSize << " & " << speedSerial << " & " << speedISPC << " & " << speedOMP << " & " << speedISPC/speedSerial  << " & " << speedOMP/speedSerial << " & " << speedISPC/speedOMP << "\\\\" << endl;
    }
    return 0;
}
