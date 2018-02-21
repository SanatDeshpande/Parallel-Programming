import os

count = [1,2,4,8,16]

os.system("make")

print("*****serial testing******")
os.system("./runloop.sh ./filter_serial")

print("******parallel testing no speedup*****")
os.system("./runloop.sh ./filter_parallel")

print("******parallel testing with speedup*****")
for c in count:
    os.system("./runloop.sh ./filter_parallel " + str(c))

print("******loop unrolling*****")
os.system("./runloop.sh ./filter_parallel_unrolling 8")

print("******dynamic scheduling*****")
os.system("./runloop.sh ./filter_parallel_dynamic 8")
