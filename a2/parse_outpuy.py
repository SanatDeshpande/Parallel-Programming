import sys

f = open(sys.argv[1], "r").read().split("\n")

for i in range(0, len(f), 2):
    flips = 0
    elapsed = 0
    for j in f[i].split(" "):
        try:
            flips = int(j)
        except:
            pass

    for j in f[i+1].split(" "):
        if j.endswith("ms"):
            elapsed = int(j[:-2])
    print(str(flips) + ", " + str(elapsed))
