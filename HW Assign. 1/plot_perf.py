import matplotlib.pyplot as plt
import numpy as np

N = np.array([ 100,  200,  400,  800, 1000, 1200, 1400, 1600, 2000])

f = np.array([2.83e3,2.59e3,2.29e3,1.37e3,1.61e3,3.32e2,2.92e2,2.94e2,2.46e2])
t = np.array([7.06e-4,6.18e-3,5.58e-2,7.48e-1,1.24e0,1.04e1,1.88e1,2.79e1,6.52e1])

cpu = 2.5e9
T   = t[0]
c1  = T/(2*N[0]**3)
c2  = 1./cpu

plt.plot(N,f)
plt.title("Measured Performance MFLOP/s")
plt.xlabel("Matrix size [N]")
plt.ylabel("MFLOP/s")

plt.show()
