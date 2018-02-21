import os

count = [1,2,4,8,16]

for c in count:
    os.system("./filter_parallel " + str(c))
