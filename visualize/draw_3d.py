import matplotlib.pyplot as plt
import numpy as np
f = open("trajectory.txt")
X = []
Y = []
Z = []
for line in f:
    t,x,y,z = [float(a) for a in line.split()]
    X.append(x)
    Y.append(y)
    Z.append(z)

ax = plt.figure().add_subplot(projection='3d')

ax.plot(X, Y, Z)

u, v = np.mgrid[0:2 * np.pi:30j, 0:np.pi:20j]
MAJOR_AXIS = 6378137; 
MINOR_AXIS = 6356752.3142; 
x_r = MAJOR_AXIS * np.cos(u) * np.sin(v)
y_r = MAJOR_AXIS * np.sin(u) * np.sin(v)
z_r = MINOR_AXIS * np.cos(v)

ax.plot_surface(x_r, y_r, z_r, cmap=plt.cm.YlGnBu_r, alpha=0.6)

x,y,z = [float(a) for a in '1.34283e+06 -5.42516e+06 3.06318e+06'.split()]
xv,yv,zv = 1.68295,-6.79927,3.8649
xv *= 1e6
yv *= 1e6
zv *= 1e6

ax.scatter(x,y,z)
ax.plot([0,xv],[0,yv],[0,zv])
plt.show()