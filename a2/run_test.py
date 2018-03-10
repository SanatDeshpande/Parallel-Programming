import os

iterations = [1e8, 1e9, 1e10]
threads = [1, 2, 4, 8, 16]

for i in iterations:
    for t in threads:
        os.system("java CoinFlip " + str(t) + " " + str(int(i)))
