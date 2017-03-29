from mpl_toolkits.mplot3d import Axes3D
from matplotlib import cm
from matplotlib.ticker import LinearLocator, FormatStrFormatter
import matplotlib.pyplot as plt
import numpy as np

for i in [0,100,200,300]:
    u = np.loadtxt("wave_u_t%d.txt" %i)
    size_u = len(u[:,0])

    fig = plt.figure()
    ax = fig.gca(projection='3d')
    X = np.linspace(-1,1,size_u)
    Y = np.linspace(-1,1,size_u)
    X, Y = np.meshgrid(X, Y)
    surf = ax.plot_surface(X,Y,u, rstride=1, cstride=1, cmap=cm.coolwarm,
                           linewidth=0, antialiased=False)
    plt.savefig('fig_u_t%d.png' %i, dpi=200)
    #plt.show()

"""

# 2D plot seen from above:
plt.imshow(u)
plt.show()
"""
