import numpy as np
import matplotlib.pyplot as plt

class HeightsDrawer:
    def __init__(self, filename):
        self.file = open(filename, 'r')

    def draw(self):
        ax = plt.figure(3).add_subplot()
        dist, h = [], []
        for line in self.file:
            x,y = [float(a) for a in line.split()]
            dist.append(x)
            h.append(y)
        dist = np.array(dist) / 1000
        h = np.array(h) / 1000

        plt.xlabel('range, km')
        plt.ylabel('height, km')

        ax.plot(dist, h)