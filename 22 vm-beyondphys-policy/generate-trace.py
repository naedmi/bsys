#! /usr/bin/env python
import random
import numpy as np
import subprocess as sp
import re

LOCALITY = False
LENGTH = 10
MAXPAGE = 10
CACHE = 3

def pagingPolicy(trace, policy, cache):
    proc = sp.Popen(["./paging-policy.py", f"-a{trace}" , f"-p{policy}", f"-C{cache}", "-c"], stdout=sp.PIPE)
    stats = ""
    while True:
          line = proc.stdout.readline()
          if not line: # end
              break
          if (output := re.search("FINALSTATS .*", line.rstrip().decode("utf-8"))) is not None:
            stats = output.string
    proc.wait()
    return stats


def main():
    print("ARG numaddrs " + str(LENGTH))
    print("ARG maxpage " + str(MAXPAGE))
    print("ARG cachesize " + str(CACHE) + "\n")

    # generate a random trace of length 10 with values between 1 and 10
    randomint = np.random.randint(1,MAXPAGE,LENGTH)

    if (LOCALITY == True): # generate a trace with locality
        randomint.sort()

    trace = ",".join(map(str, randomint))
    pol = ['FIFO', 'LRU', 'OPT', 'UNOPT', 'RAND', 'CLOCK']
    for policy in pol:
        print(policy)
        print(str(pagingPolicy(trace, policy, CACHE)) + '\n')


if __name__ == "__main__":
    main()

# page size: 4096
# address length: 32 bits
# log2(4096) = 12 -> offset: 12 bits
# VPN: 20 bits (in hex 20/8 = 5)