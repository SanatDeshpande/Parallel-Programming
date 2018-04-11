#!/usr/bin/env python2.7

import sys

friends = [i.strip() for i in sys.stdin.read().split("\n")]
outstring = []
for f in friends:
    keys = f.split(" ")[:2]
    vals = [i for i in " ".join(f.split(" ")[2:]).split(",")]
    vals = [set(i.split(" ")) for i in vals]
    if len(vals) > 2:
        vals = vals[:-1] #eliminates empty set at end
    vals = set.intersection(*vals)
    for v in vals:
        if v != keys[0] and v != keys[1]:
            output = [int(keys[1]), int(v)] #integer sorting on last 2
            output.sort()
            output = [keys[0]] + [str(i) for i in output]
            outstring.append(output[0] + " " + output[1] + " " + output[2])
            #print(output[0] + " " + output[1] + " " + output[2])
outstring = list(set(outstring))
for o in outstring:
    print(o)
