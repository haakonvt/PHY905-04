static inline int index(int i, int j, int size) {
    return j * (size+2) + i;
}

export void wavesolver_ispc(uniform int size, uniform float c,
                        uniform const float u[], uniform const float u_prev[], uniform float u_next[])
{
    foreach(i = 0 ... size, j = 0 ... size) {
        int m = j+1;
        int n = i+1;
        float ddx = u[index(m+1, n, size)] + u[index(m-1, n, size)];
        float ddy = u[index(m, n+1, size)] + u[index(m, n-1, size)];
        float ddt_rest = 2.0*u[index(m, n, size)] - u_prev[index(m, n, size)];

        u_next[index(m, n, size)] = c*(ddx + ddy - 4.0*u[index(m, n, size)]) + ddt_rest;
    }
}

