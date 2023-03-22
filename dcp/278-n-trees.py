#!/usr/bin/env python3
# Given an integer N, construct all possible binary search trees with N nodes

from collections import namedtuple

Tree = namedtuple('Tree',['value','left','right'])

def all_trees_rec(low,high):
    if (low > high): return [None]
    res = []
    for i in range(low,high+1):
        all_left = all_trees_rec(low,i-1)
        all_right = all_trees_rec(i+1,high)
        for l in all_left:
            for r in all_right:
                res.append(Tree(i,l,r))
    return res

def all_trees(N):
    return all_trees_rec(1,N)

r = all_trees(3)
print(len(r))
print(r)


## According to https://www.geeksforgeeks.org/total-number-of-possible-binary-search-trees-with-n-keys/
## the number of bst with N nodes is the nth catalan number
from math import factorial as fac

def num_bst(N):
     return fac(2*N) / (fac(N + 1) * fac(N))


for x in range(1,10):
    r = all_trees(x)
    print(len(r),'=?=', num_bst(x))

