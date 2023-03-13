# Definition for singly-linked list.
class ListNode:
    def __init__(self, x):
        self.val = x
        self.next = None

from typing import Optional

# class Solution:
#     def hasCycle(self, head: Optional[ListNode]) -> bool:
#         seen = set()
#         while head:
#             if id(head) in seen:
#                 return True
#             seen.add(id(head))
#             head = head.next
#         return False

class Solution:
    def hasCycle(self, head: Optional[ListNode]) -> bool:
        c1 = head
        c2 = head.next
        while c1 or c2:
            if id(c1) == id(c2):
                return True
            if c1.next: c1 = c1.next
            if c2.next: c2 = c2.next
            if c2.next: c2 = c2.next
        return False