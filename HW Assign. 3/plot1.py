import matplotlib.pyplot as plt
import numpy as np

N = np.array([20, 100, 500, 800, 1000, 1500, 1750, 2000, 3000, 4000])

t1 = np.array([6.80736e-07,9.69135e-06,0.000370444,0.00156074,0.00228637,0.0177088,0.0244948,0.0338263,0.0885535,0.162465])
t2 = np.array([7.28346e-07,9.30865e-06,0.000370497,0.000810285,0.00125598,0.00457981,0.00599432,0.00687195,0.0337341,0.0612233])
t3 = np.array([1.43e-07,0.000008,0.000416,0.000687,0.001223,0.004273,0.005007,0.005627,0.017374,0.046988])
t4 = np.array([4.38488e-07,
4.89695e-06,
0.00024,
0.00093,
0.0017,
0.018,
0.024,
0.037,
0.087,
0.17])

t0  = N**2*16.0/23e9
t00 = N**2.325*16.0/23e9

#plt.subplot(2,1,1)
plt.plot(N,t0,'o-')
plt.plot(N,t00,'o-')
plt.plot(N,t1,'o-')
plt.plot(N,t2,'o-')
plt.plot(N,t3,'o-')
plt.plot(N,t4,'o-')
plt.title("Measured Time")
plt.xlabel("Matrix size [N]")
plt.ylabel("Time [sec]")
plt.legend(["Performance model","Perf. model modified","Basic transpose","16 blocked transpose","'cotranspose.c'","Armadillo transpose"],loc=2)

"""plt.subplot(2,1,2)
plt.plot(N,t0,'o-')
plt.loglog(N,t1,'o-')
plt.loglog(N,t2,'o-')
plt.loglog(N,t3,'o-')
plt.loglog(N,t4,'o-')
plt.title("Same Plot, Log-Log")
plt.xlabel("Matrix size, [N]")
plt.ylabel("Time, [sec]")
plt.legend(["Performance model","Basic transpose","16 blocked transpose","'cotranspose.c'","Armadillo transpose"],loc=2)
"""
plt.show()
