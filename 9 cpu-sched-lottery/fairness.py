#! /usr/bin/env python

import random
import matplotlib.pyplot as plt
import numpy as np
from scipy.ndimage.filters import gaussian_filter1d

plt.axis([1, 1000, 0, 1])
plt.ylabel('Fairness')
plt.xlabel('Job Length')

y = [*range(1000)]
count = 0
for i in y:
    j1 = 0
    j2 = 0
    # j = 0
    while j1 < count and j2 < count:
        h = random.randint(1, 200)
        if h <= 100:
            j1 = j1 + 1
        else:
            j2 = j2 + 1
        # j = j + 1

    if j1 == 0 and j2 == 0:
        y[count] = 1
    elif j1 == 0 and j2 != 0:
        y[count] = 1 / j2
    elif j1 != 0 and j2 == 0:
        y[count] = 1 / j1
    else:
        y[count] = j1 / j2
        if y[count] > 1:
            y[count] = j2 / j1

    count = count + 1

x = range(1000)
val = range(len(x))

ysmooth = gaussian_filter1d(y, sigma=4)

plt.plot(x, ysmooth)

plt.show()
plt.savefig(f"fairness.png")