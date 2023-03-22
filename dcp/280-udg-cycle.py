#!/usr/bin/env python

# Given an undirected graph, determine if it contains a cycle
# Hmm, what is it even?
# For a acyclic graph it is clear: There is cycle, whenever
# we reach the same state twice by traversal.
#
# For an undirected graph: This is possible for every state (if there is
# at least one edge), because we simply can go backwards.
#
# So let's define: for an undirected graph, it has a cylce, when we can
# reach the same state without using any edge more than once
#
# There surely are better ways to represent the graph,
# but here, let's concentrate on the cycle fider

g = set([(1,2),(1,3),(3,4),(1,5),(3,5),(1,5)])

def all_neighbours(n, edge_list):
    return {e[0] for e in edge_list if e[1] == n}.union(
        {e[1] for e in edge_list if e[0] == n})

def edges_without((a,b), edge_list):
    res = edge_list.copy()
    if (a,b) in res:
        res.remove((a,b))
    if (b,a) in res:
        res.remove((b,a))

print(g)
print('Neighbors of 1: ', get_all_neighbours(3,g))

