#!/usr/bin/env python3
# generate some data
import random
#MAX_DEGREE=131071

MAX_DEGREE1=int(131071)#*1.5)
MAX_DEGREE2=int(131071)#*1.5)

print("1")
p1 = [str(random.randint(-100,100)) for _ in range(MAX_DEGREE1+1)]
p2 = [str(random.randint(-100,100)) for _ in range(MAX_DEGREE2+1)]
print(len(p1)-1)
print(" ".join(p1))
print(len(p2)-1)
print(" ".join(p2))


