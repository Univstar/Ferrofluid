import copy

import matplotlib.pyplot as plt
import numpy as np

maxIter = 5000
lenX = 5
lenY = 20
U = 5
d = 4
kai = 0

epsBelow = np.ones((lenY + 1, lenX))
epsLeft = np.ones((lenY, lenX + 1))
for i in range(lenX):
    for j in range(d + 1, lenY - d):
        epsBelow[j, i] = 1 + kai
for i in range(lenX + 1):
    for j in range(d + 1, lenY - 1 - d):
        epsLeft[j, i] = 1 + kai
    epsLeft[d, i] = 1 + 0.5 * kai
    epsLeft[lenY-1-d, i] = 1 + 0.5 * kai

phi = np.zeros((lenY, lenX))
phi[(lenY-1):, :] = +U
phi[:1, :] = -U

phiLast = copy.deepcopy(phi)

print("Solving...")

for Iter in range(maxIter):
    for i in range(1, lenX - 1):
        for j in range(1, lenY - 1):
            neighbors = np.array([phiLast[j, i+1], phiLast[j+1, i], phiLast[j, i-1], phiLast[j-1, i]])
            phi[j, i] = np.average(neighbors, weights=[epsLeft[j, i+1], epsBelow[j+1, i], epsLeft[j, i], epsBelow[j, i]])
    i = 0
    for j in range(1, lenY - 1):
        neighbors = np.array([phiLast[j, i+1], phiLast[j+1, i], phiLast[j-1, i]])
        phi[j, i] = np.average(neighbors, weights=[epsLeft[j, i+1], epsBelow[j+1, i], epsBelow[j, i]])
    i = lenX - 1
    for j in range(1, lenY - 1):
        neighbors = np.array([phiLast[j+1, i], phiLast[j, i-1], phiLast[j-1, i]])
        phi[j, i] = np.average(neighbors, weights=[epsBelow[j+1, i], epsLeft[j, i], epsBelow[j, i]])
    print("Iter: %d, difference: %f." % (Iter, abs(phi - phiLast).max()))
    phiLast = copy.deepcopy(phi)

print("Finished!")

plt.title("Contour of Temperature")
X, Y = np.meshgrid(np.arange(0, lenX), np.arange(0, lenY))
plt.contourf(X, Y, phi, 50, cmap=plt.get_cmap('jet'))
plt.colorbar()
# plt.savefig('plt1.pdf')
plt.show()
