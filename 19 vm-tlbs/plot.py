#!/usr/bin/env python3
#
# plot.py
# calls tlb.c and makes plot.
#
# Nadine Görzen, 15.11.2021
# Gruppe 5

import matplotlib as mpl
mpl.use('Agg')
import matplotlib.pyplot as plt
import subprocess as sp
import re # regex

# call to tlb.c and filter measured time
def tlb(numpages, iterations):
    proc = sp.Popen(["./tlb", f"-n {numpages}" , f"-l {iterations}"], stdout=sp.PIPE)
    time = 0
    while True:
          line = proc.stdout.readline()
          if not line: # end
              break
          if (output := re.search('(average cost: )([0-9]*)( ns)', line.rstrip().decode("utf-8"))) is not None:
            # print("time: " + output.group(2))
            # print("number of pages " + str(numpages))
            time = int(output.group(2))
    proc.wait()
    return time


def main():
    maxpages = 11 # 2^maxpages
    iterations = 100000

    x = range(1, maxpages)
    plt.plot([2**k for k in x],[tlb((2**i), iterations) for i in x])
    plt.title("TLB size measurement")
    plt.xlabel("Number of Pages")
    plt.ylabel("Time per access (ns)")
    plt.savefig(f"plot-{maxpages}-{iterations}.png")


if __name__ == "__main__":
    main()