
import matplotlib.pyplot as plt
import numpy as np

class TrajectoryDrawer:
    def __init__(self, trajectoryFilename, b, a):
        self.fileTrajectory = open(trajectoryFilename, 'r')
        self.drawTrasse = False
        self.withECI = True
        self.a = a # MAJOR AXIS
        self.b = b # MINOR AXIS

    def prepareTrasse(self):
        self.drawTrasse = True

    def draw(self, ax, inECEF = False, telescopesECEFFile = None):
        data = self.fileTrajectory.read().split('\n')
        xd,yd,zd = [], [], [] # ECEF
        
        for c in data[:-1]:
            t, x,y,z = [float(a) for a in c.split()]
            xd.append(x)
            yd.append(y)
            zd.append(z)
        # Scaling
        to_all = lambda f, ar1, ar2, ar3: f(f(ar1), f(ar2), f(ar3))
        l = to_all(min, xd, yd, zd)
        u = to_all(max, xd, yd, zd)

        ax.set_xlim3d(l, u)
        ax.set_ylim3d(l, u)
        ax.set_zlim3d(l, u)

        #ax.plot(xd, yd, zd, label='SC trajectory ecef', c='#0000FF')

        ax.plot(xd, yd, zd, label='SC trajectory ecef', c='#FF0000')
        ax.scatter(xd[0], yd[0], zd[0], label='Start', c='#FFFF00')

        # trasse
        if not self.drawTrasse:
            return

        fig = plt.figure()
        ax = fig.add_subplot()
        img = plt.imread("../visualize/map.jpg")
        plt.imshow(img, extent=[-180, 180, -90, 90])
        ax.set_aspect("auto")


        xd = np.array(xd)
        yd = np.array(yd)
        zd = np.array(zd)

        r1 = np.sqrt(xd**2 + yd**2)
        alpha = 1/298.257
        phi = np.arcsin(zd / np.sqrt((1-alpha)**2 * r1**2 + zd**2))
        lmbd = np.arctan2(yd,xd)

        # discontinuities
        for i in range(len(lmbd)-1): 
            if lmbd[i] - lmbd[i+1] > np.pi:
                lmbd[i] = np.nan

        lmbd *= 180 / np.pi
        phi *= 180 / np.pi

        ax.plot(lmbd, phi)
        ax.scatter(lmbd[0], phi[0], label='start', c="#00FF00")
        ax.scatter(lmbd[-1], phi[-1], label='end', c='#FF0000')
        
        ax.legend()
        
