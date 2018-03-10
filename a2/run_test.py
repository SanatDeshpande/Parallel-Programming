import os

iterations = [1e6, 1e7, 1e8, 1e9]
threads = [1, 2, 4, 8, 16]

for i in iterations:
    for t in threads:
        os.system("java CoinFlip " + str(t) + " " + str(int(i)))
