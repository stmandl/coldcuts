# Given an array of intervals intervals where intervals[i] = [starti, endi],
# return the minimum number of intervals you need to remove to make the rest of the intervals non-overlapping.

from typing import List
# from collections import defaultdict

# def overlaps(int1, int2):    
#     [_,e1], [s2,_] = (int1, int2) if int1[0] <= int2[0] else (int2, int1)
#     print("overlaps", int1, int2, s2 < e1 )
#     return s2 < e1        



# class Solution:
#     def eraseOverlapIntervals(self, intervals: List[List[int]]) -> int:
#         overlaps_with = defaultdict(set)        
#         count = 0
#         print(intervals)
#         for i, i1 in enumerate(intervals):
#             for j, i2 in enumerate(intervals[i+1:]):
#                 if overlaps(i1,i2):
#                     overlaps_with[i].add(j+i+1)
#                     overlaps_with[j+i+1].add(i)
#         print('oool:', overlaps_with)
#         while len(overlaps_with) > 0:            
#             ol = sorted(overlaps_with.items(), key=lambda x: len(x[1]), reverse=True)
#             #print('ol',ol)
#             cand = ol[0][0]
#             print('cand',cand)
#             overlaps_with.pop(cand)
#             erase = []
#             for k, v in overlaps_with.items():
#                 if cand in v:
#                     v.remove(cand)
#                 if len(v) == 0:
#                     erase.append(k)
#             for k in erase:
#                 overlaps_with.pop(k)
#             count += 1
#         return count
            
                    
# Wrong:
# Solution:
# 1. Sort by end
# 2. iterate and in conflict, keep the one with the smaller end.

class Solution:
    def eraseOverlapIntervals(self, intervals: List[List[int]]) -> int:
        count = 0                
        intervals = sorted(intervals, key=lambda x: x[1])
        _, end = intervals[0]
        for s,e in intervals[1:]:
            if s >= end:
                # no overlap, continue with next interval
                end = e
            else:
                # overlap, remove and don't continue with next interval
                # , there might be an overlap later!!
                count +=1            
        return count

res = Solution().eraseOverlapIntervals(intervals = [[1,2],[2,3],[3,4],[1,3]])
print(res)
assert res == 1

res = Solution().eraseOverlapIntervals(intervals= [[1,2],[1,2],[1,2]])
print(res)
assert res == 2

res = Solution().eraseOverlapIntervals(intervals=[[1,2],[2,3]])
print(res)
assert res == 0


res = Solution().eraseOverlapIntervals(intervals=[[0,2],[1,3],[1,3],[2,4],[3,5],[3,5],[4,6]])
print(res)
assert res == 4