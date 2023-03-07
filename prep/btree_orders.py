class BTree:
    def __init__(self, value, children=[]) -> None:
        assert 0 <= len(children) <= 2
        self.value = value
        self.children = children

    def preorder(self, fn):
        fn(self)
        for n in self.children:
            n.preorder(fn)

    def inorder(self, fn):
        if len(self.children) == 0:
            fn(self)
            return
        if len(self.children) == 1:
            self.children[0].inorder(fn)
            fn(self)
            return            
        if len(self.children) == 2:
            self.children[0].inorder(fn)
            fn(self)
            self.children[1].inorder(fn)
            return            
        assert False, "E1"
    
    def postorder(self, fn):
        for n in self.children:
            n.postorder(fn)
        fn(self)

#
#     5
#    / \
#   3   7
#  / \   \
# 2   4   8

ex = BTree(5,[BTree(3,[BTree(2), BTree(4)]), BTree(7,[BTree(8)])])

def tp(tree):
    print(tree.value)



ex.postorder(tp)

# 2, 4, 3, 8, 7, 5
# write me !!
def postorder_to_tree(lst):
    children = []
    for t in lst:
        if len(children) < 2:
            children.append(BTree(t))
        else:
            children = [BTree(t,children)]
    if
            
