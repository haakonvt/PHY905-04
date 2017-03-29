import matplotlib.pyplot as plt
import numpy as np

N = np.array([ 100,  200,  400,  800, 1000, 1200, 1400, 1600, 2000])

f = np.array([2.83e3,2.59e3,2.29e3,1.37e3,1.61e3,3.32e2,2.92e2,2.94e2,2.46e2])
t = np.array([7.06e-4,6.18e-3,5.58e-2,7.48e-1,1.24e0,1.04e1,1.88e1,2.79e1,6.52e1])

cpu = 2.5e9
T   = t[0]
c1  = T/(2*N[0]**3)
c2  = 1./cpu

print "c1, c2: ", c1, c2

c1t = 2*c1*N**3
c2t = 2*c2*N**3

for i in range(len(N)):
    print N[i],"& %.2e  & %.2e & %.2e & %.2e" %(f[i],t[i],c1t[i],c2t[i])

plt.subplot(2,1,1)
plt.plot(N,t)
plt.plot(N,c1t)
plt.plot(N,c2t)
plt.title("Measured Time vs Estimates")
plt.xlabel("Matrix size [N]")
plt.ylabel("Time [sec]")
plt.legend(["Actual time","Estimate C1","Estimate C2"],loc=2)

plt.subplot(2,1,2)
plt.loglog(N,t,'ro-')
plt.loglog(N,c1t)
plt.loglog(N,c2t)
plt.title("Same Plot, Log-Log")
plt.xlabel("Matrix size [log(N)]")
plt.ylabel("Time [log(sec)]")
plt.axis([80, 2000*1.1, t[0]*0.7, t[-1]*1.6])
plt.legend(["Actual time","Estimate C1","Estimate C2"],loc=2)

plt.show()
