#include <sys/time.h>

double mysecond(void);
double mysecond_(void);

/* The gettimeofday function may have low resolution, so do not use this
   for high-resolution (microsecond) timing.

   Note that gettimeofday is not guaranteed to be monotone increasing.
   However,for short timing tests, it is likely to be to be accurate.
   This function is used because it is the most portable timer without
   using either OpenMP or MPI.
*/
double mysecond(void)
{
    struct timeval tVal;
    gettimeofday(&tVal,NULL);
    return (double)tVal.tv_sec + 1.0e-6 * (double)tVal.tv_usec;
}
/* By adding this name, most Fortran program will be able to use
   mysecond() as a double precision function */
double mysecond_(void)
{
    return mysecond();
}
