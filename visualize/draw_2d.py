import matplotlib.pyplot as plt
f = open("trajectory.txt")
X = []
Y = []
for line in f:
    t,x,y = [float(a) for a in line.split()]
    X.append(x)
    Y.append(y)

plt.plot(X, Y)
plt.show()