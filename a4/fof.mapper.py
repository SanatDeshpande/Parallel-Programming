#!/usr/bin/env python2.7

import sys

data = sys.stdin.read().strip().split(" ")
head = data[0]

for i in data:
    for j in data:
        for k in data:
            if int(j) < int(k) and i != j and i != k:
                sys.stdout.write(i + " " + j + " " + k + "\t1\n")
