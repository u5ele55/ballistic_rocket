from trajectory import *
from geoid import GeoidDrawer
from distanceToHeights import HeightsDrawer

MAJOR_AXIS = 6378137; 
MINOR_AXIS = 6356752.3142; 

if __name__ == '__main__':
    ax = plt.figure(1).add_subplot(projection='3d')
    trdr = TrajectoryDrawer(r"trajectory.txt", MINOR_AXIS, MAJOR_AXIS)
    heights = HeightsDrawer("heights.txt")
    geoidDr = GeoidDrawer(MINOR_AXIS, MAJOR_AXIS)

    trdr.prepareTrasse()

    geoidDr.draw(ax)
    trdr.draw(ax)

    heights.draw()

    plt.show()