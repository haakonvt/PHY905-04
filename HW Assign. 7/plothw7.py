import matplotlib.pyplot as plt
import numpy as np

n200 = [0.0076198,
0.0111508,
0.0056743,
0.0041479,
0.0032425,
0.0048592,
0.0048625,
0.0045487,
0.0045377]

n20 = [0.0000076,
0.0000140,
0.0000111,
0.0000131,
0.0000111,
0.0000109,
0.0000111,
0.0000100,
0.0000105]


n1000 = [1.5808103,
2.0836124,
1.0475019,
0.7182074,
0.5719213,
0.7219584,
0.8571372,
1.0851663,
1.6104866]


n1300 = [14.8448560,
14.7208230,
7.4410930,
5.0569435,
3.8527725,
3.9048190,
3.8934925,
3.9231955,
3.8589960]

Nt = range(1,9)

plt.subplot(2,2,1)
plt.plot(Nt,n20[1:],'bo-')
plt.plot(1,n20[0],'rx', mew=2, ms=10)
plt.ylabel("Seconds")
plt.ticklabel_format(style='sci', axis='y', scilimits=(0,0))
plt.legend(["n = 20","No OpenMP"])
plt.xlim(0, 8)

plt.subplot(2,2,2)
plt.plot(Nt,n200[1:],'bo-')
plt.plot(1,n200[0],'rx', mew=2, ms=10)
plt.ticklabel_format(style='sci', axis='y', scilimits=(0,0))
plt.legend(["n = 200","No OpenMP"])
plt.xlim(0, 8)

plt.subplot(2,2,3)
plt.plot(Nt,n1000[1:],'bo-')
plt.plot(1,n1000[0],'rx', mew=2, ms=10)
plt.xlabel("Threads")
plt.ylabel("Seconds")
plt.legend(["n = 1000","No OpenMP"])
plt.xlim(0, 8)

plt.subplot(2,2,4)
plt.plot(Nt,n1300[1:],'bo-')
plt.plot(1,n1300[0],'rx', mew=2, ms=10)
plt.xlabel("Threads")
plt.legend(["n = 1300","No OpenMP"])
plt.xlim(0, 8)


plt.show()
