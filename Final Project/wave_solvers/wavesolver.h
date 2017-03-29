#ifndef WAVESOLVER_H
#define WAVESOLVER_H
#include <functional>
#define DX 0.1
#define DT 0.1

class WaveSolver{
  private:
      float m_C = 0.5;
      unsigned int m_nx = 512;
      unsigned int m_nxPlusTwo = m_nx+2;
      unsigned int m_timesteps = 0;
      float *u;
      float *u_next;
      float *u_prev;
  public:
      WaveSolver(unsigned int nx);
      ~WaveSolver();
      void step(int which_code, bool write_to_file);
      void initializeGauss(float x0, float y0, float variance);
      void copyBoundary();
      void write_to_file(float *u, int width, int height, int serial);
      inline int index(int i, int j) { return j * m_nxPlusTwo + i; }
      unsigned int gridSize() { return m_nx; }
      unsigned int timesteps() const;
};

#endif // WAVESOLVER_H
