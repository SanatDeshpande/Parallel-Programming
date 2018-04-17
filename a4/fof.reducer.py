#!/usr/bin/env python

import sys

data = sys.stdin.read().split("\n")

prev_key = data[0].split("\t")[0]
count = 1
for d in data[1:]:
    k = d.split("\t")[0]
    if k == prev_key:
        count += int(d.split("\t")[1])
    else:
        if count >= 3:
            triad = [int(i) for i in prev_key.split(" ")]
            print(str(triad[0]) + " " + str(triad[1]) + " " + str(triad[2]))
            count = 1
        prev_key = k

if count >= 3:
    triad = [int(i) for i in prev_key.split(" ")]
    print(str(triad[0]) + " " + str(triad[1]) + " " + str(triad[2]))
