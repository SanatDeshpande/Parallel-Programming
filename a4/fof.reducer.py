#!/usr/bin/env python2.7

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
            sys.stdout.write(prev_key + "\t\n")
            count = 0
        prev_key = k

'''
prev_key = "" #holds previous key
cum_vals = [] #cumulative values, flushed between keys
intersection = None

for d in data:
    if len(d) == 0:
        continue
    k = d.strip().split("\t")[0]
    v = d.strip().split("\t")[1]

    if k == prev_key:
        cum_vals += [v.split(" ")]
    else:
        #writes out prev_key and values
        #flushes out values and prev_key with new ones
        if prev_key != "": #check for base condition
            if len(cum_vals) != 1:
                cum_set = [set(i) for i in cum_vals]
                intersection = set.intersection(*cum_set)
                sys.stdout.write(prev_key + "....." + " ".join(list(intersection)) + "\n")
        prev_key = k #sets new previous key
        cum_vals = [v.split(" ")]

#prints out last key->value
if intersection != None and len(cum_vals) != 1:
    sys.stdout.write(prev_key + "....." + " ".join(list(intersection)) + "\n")
'''
