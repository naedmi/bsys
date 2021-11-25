file = open('./final.txt', 'r')
trace = open('./in.txt', 'w')

for line in file:
    trace.write(str((int("0x" + line, 16) & 0xfffff000) >> 12) + "\n")

file.close()
trace.close()