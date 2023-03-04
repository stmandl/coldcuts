def fibo(n):
    if n<=1: return 1
    return fibo(n-1) + fibo(n-2)



class Node:
    def __init__(self, args, value, prev=None, next=None) -> None:
        self.args = args
        self.value = value
        self.prev = prev
        self.next = next

    def unchain(self):
        if self.prev is not None:
            self.prev.next = self.next
        if self.next is not None:
            self.next.prev = self.prev

    def __str__(self):
        return "["+str(self.args)+"::"+str(self.value)+"]"
    def __repr__(self) -> str:
        return str(self)
    

class LRUTable:
    def __init__(self, size) -> None:
        self.values_dict = {}
        self.values_list = None
        self.bottom = None
        self.size = size
    
    def set(self, key, value):
        #print("set",key,value)
        if key in self.values_dict:
            node = self.values_dict[key]
            node.value = value
        else:
            if len(self.values_dict) >= self.size:
                self.vacuum()
            node = Node(key, value)
            self.values_dict[key] = node
        self.hoist(node)
    
    def hoist(self, node):
        if self.values_list is None:
            self.values_list = node
            self.bottom = node
        else:
            node.unchain()
            node.prev = None
            node.next = self.values_list
            self.values_list.prev = node
            self.values_list = node
        #print("hoist: ", self.values_dict, self.values_list, self.bottom)        

    def vacuum(self):        
        bottom = self.bottom
        if bottom is None: return        
        self.bottom = bottom.prev
        if self.bottom is not None:
            self.bottom.next = None
        else:
            self.values_list = None        
        del self.values_dict[bottom.args]
        #print("vaccum", self.values_dict, self.values_list, self.bottom)
        
        
    def get(self, key):        
        if key in self.values_dict:
            return self.values_dict[key].value
        else:
            return None
    
    def __contains__(self, m):
        return m in self.values_dict
    

        

def memo(f):
    table = LRUTable(2) ## only two values are needed for Fibo ;-)

    def mf(*args):        
        if args in table:
            return table.get(args)
        else:            
            res = f(*args)            
            table.set(args,res)
            return res
    return mf


fibo = memo(fibo)

for x in range(100):
    print(fibo(x))
