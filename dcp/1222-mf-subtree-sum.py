### Good morning! Here's your coding interview problem for today.
### 
### This problem was asked by Apple.
### 
### Given the root of a binary tree, find the most frequent subtree sum. The subtree sum of a node is the sum of all values under a node, including the node itself.
### 
### For example, given the following tree:
### 
###   5
###  / \
### 2  -5
### Return 2 as it occurs twice: once as the left leaf, and once as the sum of 2 + 5 - 5.


## 1. Represent tree
class BTree:

    def __init__(self, value, left=None, right=None):
        self.value = value
        self.left = left
        self.right = right
        self.num_value_read = 0

    def get_value(self):
        self.num_value_read += 1
        return self.value


# Naive implementation

ex1 = BTree(5, BTree(2), BTree(-5))


def bt_sum(bt):
    #print(bt.value, bt.left, bt.right)
    return bt.get_value() + (bt_sum(bt.left) if bt.left else 0) + (bt_sum(bt.right) if bt.right else 0)

def get_value_sum(bt):
    #print(bt.value, bt.left, bt.right)
    return bt.num_value_read + (get_value_sum(bt.left) if bt.left else 0) + (get_value_sum(bt.right) if bt.right else 0)

def enum_trees(bt):
   yield bt
   if bt.left:
       yield bt.left
   if bt.right:
       yield bt.right
       
ts = enum_trees(ex1)
from collections import defaultdict
counts = defaultdict(int)
for t in ts:
    counts[bt_sum(t)] += 1

print(sorted(counts.items(), key=lambda x:x[1], reverse=True)[0][0])
print(get_value_sum(ex1))



# Problem: it iterates multiple times over the subtrees
# solution 1: aggregate and cache in node

## 1. Represent tree
class BTree:

    def __init__(self, value, left=None, right=None):
        self.value = value
        self.left = left
        self.right = right
        self.num_value_read = 0
        self.subtree_sum = None

    def get_value(self):
        self.num_value_read += 1
        return self.value


# Naive implementation

ex1 = BTree(5, BTree(2), BTree(-5))


#def bt_sum(bt):
#    #print(bt.value, bt.left, bt.right)
#    return bt.get_value() + (bt_sum(bt.left) if bt.left else 0) + (bt_sum(bt.right) if bt.right else 0)

def bt_sum(bt):
    #print(bt.value, bt.left, bt.right)
    if bt.subtree_sum:
        return bt.subtree_sum
    sts = bt.get_value() + (bt_sum(bt.left) if bt.left else 0) + (bt_sum(bt.right) if bt.right else 0)
    bt.subtree_sum = sts
    return sts

ts = enum_trees(ex1)
counts = defaultdict(int)
for t in ts:
    counts[bt_sum(t)] += 1

print(sorted(counts.items(), key=lambda x:x[1], reverse=True)[0][0])
print(get_value_sum(ex1))


## solution 2: iterate bottom-up and keep track
# ...

