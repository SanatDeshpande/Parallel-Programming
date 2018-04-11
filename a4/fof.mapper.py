#!/usr/bin/env python2.7

import sys

#initialize map and list
friend_map = {}
friend_list = [i for i in sys.stdin.read().split("\n") if len(i) > 0]

#build map
for i in friend_list:
    main = int(i.split(" ")[0])
    for j in i.split(" ")[1:]:
        key = [main, int(j)]
        key.sort(reverse=False)
        if (key[0], key[1]) in friend_map:
            friend_map[(key[0], key[1])].append([int(k) for k in i.split(" ")[1:]])
        else:
            friend_map[(key[0], key[1])] = [[int(k) for k in i.split(" ")[1:]]]
        key.sort(reverse=True)
        if (key[0], key[1]) in friend_map:
            friend_map[(key[0], key[1])].append([int(k) for k in i.split(" ")[1:]])
        else:
            friend_map[(key[0], key[1])] = [[int(k) for k in i.split(" ")[1:]]]

for f in friend_map:
    sys.stdout.write(str(f[0]) + " " + str(f[1]) + " ")
    for i in friend_map[f]:
        sys.stdout.write(" ".join([str(j) for j in i]) + ",")
    sys.stdout.write("\n")
