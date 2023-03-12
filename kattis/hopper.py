#!/usr/bin/env python3




import random
# D = random.randint(1,7)
# M = random.randint(1,10000)
#n = random.randint(1,1000)
D = 7
M = 1000
n = 1000

elems = []
for _ in range(n):
    elem = random.randint(-1000000, 1000000)
    elems.append(str(elem))
    
elems = []
for _ in range(10):
    for i in range(100):
        elems.append(str(i))

print(n,D,M)
print(" ".join(elems))