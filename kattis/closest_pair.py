#!/usr/bin/env python3
import random

C = 10

for _ in range(C):
    N = random.randint(2,100000)
    print(N)
    for _ in range(N):
        x = random.randint(-10000000, 10000000)    
        y = random.randint(-10000000, 10000000)
        #y = 12
        print(x/100, y/100)
print(0)