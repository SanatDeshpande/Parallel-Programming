#!/usr/bin/env python2.7

import sys

#initialize map and list
friend_map = {}
friend_list = [i for i in sys.stdin.read().split("\n") if len(i) > 0]

#build map
for f in friend_list:
    f_key = f.split(" ")[0] #gets key
    friends = [i for i in f.split(" ")[1:]] #gets value list (friends)
    if f_key in friend_map:
        friend_map[f_key].append(friends)
    else:
        friend_map[f_key] = [friends]

#outputs mapping
for i in friend_map:
    sys.stdout.write(i + "|")
    for j in friend_map[i]:
        for k in j:
            sys.stdout.write(k + " ")
        sys.stdout.write(", ")
    sys.stdout.write("\n")
