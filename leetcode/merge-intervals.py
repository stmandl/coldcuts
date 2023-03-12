# Given an array of intervals where intervals[i] = [starti, endi], merge all overlapping intervals,
# and return an array of the non-overlapping intervals that cover all the intervals in the input.

from pprint import pprint
from deepdiff import DeepDiff
from typing import List

# class Solution:
#     def merge(self, intervals: List[List[int]]) -> List[List[int]]:
#         intervals = sorted(intervals, key=lambda x:x[0])
#         res = []
#         current = intervals[0]
#         cand_idx = 1        
#         while cand_idx < len(intervals):
#             cand = intervals[cand_idx]
#             if cand[0] <= current[1]:
#                 # merge
#                 current = [min(cand[0], current[0]), max(cand[1], current[1])]
#                 cand_idx += 1                
#                 # and continue with next candidate
#             else:
#                 # there is a gap and therefore a new interval begins
#                 res.append(current) # be careful at the end!
#                 current = cand
#                 cand_idx += 1                
#         res.append(current)
#         return res
                

class Solution:
    def merge(self, intervals: List[List[int]]) -> List[List[int]]:
        intervals = sorted(intervals, key=lambda x:x[0])
        res = []
        start, end = intervals[0]
        for si,ei in intervals:   # Python thing to remember: iterating over intervals[1:] is actually slower
            if si <= end:
                end = max(ei,end)
            else:
                res.append([start,end])
                start, end = si,ei
        res.append([start,end])
        return res
                


res = Solution().merge([[1,3],[2,6],[8,10],[15,18]])
pprint(res)
assert DeepDiff(res,[[1,6],[8,10],[15,18]]) == {}, f"Differences: {DeepDiff(res,[[1,6],[8,10],[15,18]])}"

res = Solution().merge([[1,4],[4,5]])
assert DeepDiff(res,[[1,5]]) == {}, f"Differences: {DeepDiff(res,[[1,5]])}"