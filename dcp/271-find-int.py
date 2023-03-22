# Given a sorted list of integers of length N, determine if an element x is
# in the list without performing any multiplication, division, or bit-shift operations
# Do this in O(log N) time

# O(N) version:
def find_N1(list,N):
    for e in list:
        if e == N:
            return True
    return False

# Assumption:
# "list" is a Python list, so really, it's an Array that can be freely accessed
# Normally, we'd use binary search: start at the middle, compare and then recurse left or right.
# Clearly, the challenge is to do the same but without mult, div and shift, how do we find the middle?

import random
vals1 = sorted(list(set([random.randint(1,50) for _ in range(10)])))
vals2 = sorted(list(set([random.randint(1,5000000) for _ in range(100000)])))

# idee: vergrößere Schrittweite, bis drüber, dann wieder einen SChritt zurück und rekursiv

def speed_find(l,e):

    ll = len(l)

    def sf(pos,step,last):
        if pos > ll or l[pos] > e:
            return 'stop'
        if l[pos] == e: return pos
        
        if (l[first] == e) return first
        elif (l[first] > e):
            r = sf(first+step,last,step+1)
        #l[first]<e
        else:



    ########################
    return sf(0,2,1)
