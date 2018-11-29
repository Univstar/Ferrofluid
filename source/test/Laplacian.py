import copy

import matplotlib.pyplot as plt
import numpy as np

maxIter = 500

lenX = 20
lenY = 20
delta = 1

T_top = 100
T_bottom = 0
T_left = 0
T_right = 0

T_init = 30

colorInterpolation = 50
colorMap = plt.get_cmap('jet')

X, Y = np.meshgrid(np.arange(0, lenX), np.arange(0, lenY))

T = np.empty((lenX, lenY))
T.fill(T_init)

T[(lenY - 1) : , : ] = T_top
T[ : 1, : ] = T_bottom
T[ : , (lenX - 1) : ] = T_right
T[ : , : 1] = T_left

TLast = copy.deepcopy(T)

print("Solving...")

for iteration in range(0, maxIter):
    for i in range(1, lenX - 1, delta):
        for j in range(1, lenY - 1, delta):
            T[i, j] = 0.25 * (T[i + 1, j] + T[i - 1, j] + T[i, j + 1] + T[i, j - 1])
    print("Iter: %d, difference: %f." % (iteration, abs(T - TLast).max()))
    TLast = copy.deepcopy(T)

print("Finished!")

plt.title("Contour of Temperature")
plt.contourf(X, Y, T, colorInterpolation, cmap=colorMap)
plt.colorbar()
# plt.savefig('plt1.pdf')
plt.show()
