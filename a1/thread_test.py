import os

count = [1,2,4,8,16]

print("*****serial testing******")
os.system("./runloop ./filter_serial")

print("******parallel testing no speedup*****")
os.system("./runloop ./filter_parallel")

print("******parallel testing with speedup*****")
for c in count:
    os.system("./runloop ./filter_parallel " + str(c))

print("******loop unrolling*****")
os.system("./runloop ./filter_parallel_unrolling 8")

print("******dynamic scheduling*****")
os.system("./runloop ./filter_parallel_dynamic 8")
