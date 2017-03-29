import matplotlib.pyplot as plt
import numpy as np

n = [250, 1000, 5e3, 1e4, 5e4, 1e5, 5e5, 1e6, 5e6]
t = [2.02E-07,6.70E-07,3.07E-06,5.77E-06,3.03E-05,6.07E-05,3.53E-04,8.15E-04,4.54E-03]
r = [19.8E03,23.9E03,26.1E03,27.7E03,26.3E03,26.4E03,22.6E03,19.6E03,17.6E03]

plt.subplot(2,1,1)
plt.loglog(n,t,'-bo')
plt.xlabel("Array length [n]")
plt.ylabel("Time for loop [s]")
plt.title("Loglog plot of array size n vs. time spent copying")

plt.subplot(2,1,2)
plt.semilogx(n,r,'-bo')
plt.xlabel("Array length [n]")
plt.ylabel("Rate [MB/s]")
plt.title("Semilog plot of array size n vs. memory bandwidth")

plt.show()
