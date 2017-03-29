import matplotlib.pyplot as plt
import numpy as np

n  = [20, 100, 400, 1000, 1200, 1500]
x  = [5e-5, 0.006, 0.5, 7, 15, 36]
xx = [1e-5, 0.001, 0.07, 1.4, 10, 24]
y  = [8e-5, 0.007, 0.4, 7.5, 12, 23]
yy = [4e-5, 0.00057, 0.04, 0.7, 1.3, 3.4]

plt.subplot(2,1,1)
plt.plot(n,x, '-o')
plt.plot(n,xx,'-o')
plt.plot(n,y, '-o')
plt.plot(n,yy,'-o')
plt.title("Comparison of matrix-matrix multiply algorithms")
plt.xlabel("Matrix size [n]")
plt.ylabel("Time [sec]")
plt.legend(["Simple, -O0","Simple, -O3","Blocked, -O0","Blocked, -O3"],loc=2)

plt.subplot(2,1,2)
plt.loglog(n,x, '-o')
plt.loglog(n,xx,'-o')
plt.loglog(n,y, '-o')
plt.loglog(n,yy,'-o')
plt.title("Same plot, LOGLOG")
plt.xlabel("Matrix size [n]")
plt.ylabel("Time [sec]")
plt.legend(["Simple, -O0","Simple, -O3","Blocked, -O0","Blocked, -O3"],loc=2)

plt.show()
