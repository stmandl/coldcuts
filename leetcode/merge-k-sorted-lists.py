#Definition for singly-linked list.
class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next
    
    def __str__(self):
        return f"[{self.val}]"+ ("." if self.next is None else ","+str(self.next))

from typing import Optional, List

def make_list(l):
    list_nodes = [ListNode(val) for val in l]
    for current, next in zip(list_nodes,list_nodes[1:]):
        current.next = next
    return list_nodes[0]

class Solution:
    def mergeKLists(self, lists: List[Optional[ListNode]]) -> Optional[ListNode]:
        try:
            min_value = min([n.val for n in lists if n is not None])
        except:
            return None
        for i,n in enumerate(lists):
            if n and n.val == min_value:
                head = n                
                lists[i] = lists[i].next
                head.next = None
                break
        assert head is not None
        tail = head

        while True:
            #print('Res',head)
            min_idx = None
            min_val = None
            for i, n in enumerate(lists):
                #print("List",i,n)
                if n and (min_val is None or n.val < min_val):
                    min_val = n.val
                    min_idx = i
            #print(min_idx,min_val)
            if min_idx is None:
                break
            tail.next = lists[min_idx]
            tail = tail.next            
            lists[min_idx] = lists[min_idx].next
        return head


#print(Solution().mergeKLists([make_list([1,4,5]),make_list([1,3,4]),make_list([2,6])]))
print(Solution().mergeKLists([make_list([0,0,0]),make_list([1,3,4,6])]))