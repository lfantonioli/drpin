#!/usr/bin/python
import sys

if len(sys.argv) != 2:
    print("need only one file name as argument")
    sys.exit(1)
    
discarted_lines = 0
with open(sys.argv[1], 'r') as f:
    for line in f:
        if ":" not in line:
            discarted_lines += 1
            continue
        inst = line.split(":")[1].strip().split(" ")[0]
        print(inst)

print("discarted {} lines ".format(discarted_lines))