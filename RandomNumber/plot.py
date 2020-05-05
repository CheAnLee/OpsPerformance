import matplotlib.pyplot as plt
import numpy as np
import sys

N = 1000

L = list()

with open('log','r') as fp:
	for line in fp.readlines():
		L.append(int(line.split(':')[1].strip()))

L = np.array(L)
L = np.sort(L)

avg = abs(sum(L)/float(N))/sys.maxsize

plt.plot(L, 'ro', markersize=1)
plt.plot([0,N], [avg,avg])
plt.show()
