class Node:
    def __init__(self, val = 0, neighbors = None):
        self.val = val
        self.neighbors = neighbors if neighbors is not None else []

    def __eq__(self, o) -> bool:
        return self.val == o.val
    
    def __hash__(self) -> int:
        return self.val

    def __str__(self) -> str:
        return f"({self.val}|{[n.val for n in self.neighbors]})"


from collections import defaultdict

def make_graph(adj_list):
    connections = defaultdict(list)
    nodes = {}
    for a,b in adj_list:
        if a not in nodes: nodes[a] = Node(a)
        if b not in nodes: nodes[b] = Node(b)
        nodes[a].neighbors.append(nodes[b])
    return nodes

def check_graph(g1,g2):
    if g1.keys() != g2.keys():
        print("Keys dont match: ",list(g1.keys()), list(g2.keys()))
        return False
    for k,v1 in g1.items():
        v2 = g2[k]
        if id(v1) == id(v2):
            print("Identical: ", v1, v2)
            return False
    return True



class Solution:

    def clone(self, node, graph):
        if node.val in graph:
            return graph[node.val]
        nn = Node(node.val)
        for n in node.neighbors:
            cn = self.clone(n,graph)
            nn.neighbors.append(cn)
        graph[node.val] = nn
        return nn

    def cloneGraph(self, node):
        return self.clone(node, {})
        
        
            


ex = make_graph([[2,4],[1,3],[2,4],[1,3]])
print(check_graph(Solution().cloneGraph(ex[1]), ex))