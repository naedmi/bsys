#! /usr/bin/env python
import random
import matplotlib.pyplot as plt

adrSpace = 1000
limit = 0
iter = 1000

# naming the x axis
plt.xlabel('limit')
# naming the y axis
plt.ylabel('fraction of valid virtual addresses')
# giving a title to my graph
plt.title('hw chapter 15')

arr = [*range(adrSpace)]
lim = [*range(adrSpace)] # filled with num from 0 to adrSpace

while limit < adrSpace:
    for _ in range(iter):
        rnd = random.randint(0, adrSpace)
        if rnd < lim[limit]:
            arr[limit] += 100
    arr[limit] = (float(arr[limit]) / float(iter)) / 100
    limit += 1

x = lim
y = arr
# setting the axis
plt.axis([0, adrSpace, 0, 1])
plt.grid()
# plotting the points
plt.plot(x, y)

plt.show()