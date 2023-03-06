from typing import List

from collections import defaultdict


# def connected_components(graph, nodes):
#     nodes = list(nodes)
#     visited = set()

#     def dfs(pos):            
#         if pos in visited:
#             return 0
#         else:
#             visited.add(pos)
#             return 1 + sum([dfs(p) for p in graph[pos]])

#     longest = 0
#     for n in range(len(nodes)):
#         if n not in visited:                        
#             longest = max(longest, dfs(nodes[n]))
    
#     return longest

# class Solution:
#     def longestConsecutive(self, nums: List[int]) -> int:
#         graph = defaultdict(set)
#         nums = set(nums)
#         for n in nums:
#             if n+1 in nums:
#                 graph[n].add(n+1)
#                 graph[n+1].add(n)
#         print(graph)
#         return connected_components(graph, nums)        


class Solution:
    def longestConsecutive(self, nums: List[int]) -> int:        
        nums = set(nums)
        longest = 0
        for n in nums:
            if n-1 not in nums:
                l = 0
                i = n
                while i in nums:
                    l += 1
                    i += 1
                longest = max(longest,l)
        return longest

#Explanation: The longest consecutive elements sequence is [1, 2, 3, 4]. Therefore its length is 4.
print(Solution().longestConsecutive([100,4,200,1,3,2]), 4)
print(Solution().longestConsecutive([0,3,7,2,5,8,4,6,0,1]), 9)
print(Solution().longestConsecutive([1,3,5,2,4]))
print(Solution().longestConsecutive([-8,-4,9,9,4,6,1,-4,-1,6,8]),2)