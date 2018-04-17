#!/usr/bin/env python

import sys

all_lines = sys.stdin.read().split("\n")

for line in all_lines:
    data = line.strip().split(" ")
    head = data[0]

    for i in range(1, len(data)):
        for j in range(i+1, len(data)):
            key = sorted([int(head), int(data[i]), int(data[j])])
            print(str(key[2]) + " " + str(key[0]) + " " + str(key[1]) + "\t1")
            print(str(key[0]) + " " + str(key[1]) + " " + str(key[2]) + "\t1")
            print(str(key[1]) + " " + str(key[0]) + " " + str(key[2]) + "\t1")
