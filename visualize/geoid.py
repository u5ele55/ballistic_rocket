import numpy as np
import matplotlib.pyplot as plt

class GeoidDrawer:
    def __init__(self, minor_axis, major_axis):
        self.minor_axis = minor_axis
        self.major_axis = major_axis

    def draw(self, ax):
        u, v = np.mgrid[0:2 * np.pi:30j, 0:np.pi:20j]
        MAJOR_AXIS = 6378137; 
        MINOR_AXIS = 6356752.3142; 
        x_r = MAJOR_AXIS * np.cos(u) * np.sin(v)
        y_r = MAJOR_AXIS * np.sin(u) * np.sin(v)
        z_r = MINOR_AXIS * np.cos(v)

        ax.plot_surface(x_r, y_r, z_r, cmap=plt.cm.YlGnBu_r, alpha=0.6)