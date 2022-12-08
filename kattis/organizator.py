#!/usr/bin/env python

import random

N = 3000

s = str(N)+"\n"

for i in range(N):
    s += str(random.randrange(1,2000000))
    if i < N-1:
        s += " "
print(s)

