from os import write
import subprocess
import re
import matplotlib as mpl
import matplotlib.pyplot as plt
from itertools import cycle

def callSub(policy, cache_size):
    proc = subprocess.Popen(["./paging-policy.py", "-fin.txt", f"-p{policy}", f"-C{cache_size}", "-c"], stdout=subprocess.PIPE)
    ret = 0
    while True:
          line = proc.stdout.readline()
          # print(line)
          if not line:
            break
          if (m := re.search(".*hitrate\s([0-9.]+)", line.rstrip().decode("utf-8"))) is not None:
            ret = float(m.group(1))
    proc.wait()
    print(ret)
    return ret

def main():
    x = range(1,10)
    policies = ["FIFO","RAND","CLOCK","OPT","LRU","UNOPT"]
    for policy in policies:
        plt.plot(x, [callSub(policy, i) for i in x])
    plt.xlabel("Cache size")
    plt.ylabel("Hit Rate")
    plt.legend(policies)
    plt.savefig(f"hit-rate.png")


if __name__ == "__main__":
    main()