# You are given an array of non-overlapping intervals intervals where intervals[i] = [starti, endi] 
# represent the start and the end of the ith interval and intervals is sorted in ascending order by starti. 
# You are also given an interval newInterval = [start, end] that represents the start and end of another interval.

# Insert newInterval into intervals such that intervals is still sorted in ascending order by starti and intervals still
# does not have any overlapping intervals (merge overlapping intervals if necessary).

# Return intervals after the insertion.

 

# Example 1:

# Input: intervals = [[1,3],[6,9]], newInterval = [2,5]
# Output: [[1,5],[6,9]]
# Example 2:

# Input: intervals = [[1,2],[3,5],[6,7],[8,10],[12,16]], newInterval = [4,8]
# Output: [[1,2],[3,10],[12,16]]
# Explanation: Because the new interval [4,8] overlaps with [3,5],[6,7],[8,10].


# Step1: insert at correct start position
# Step2: merge left and right


from typing import List

def merge(intervals,p):
    #print(intervals, p)
    current = intervals[p]
    if p > 0:        
        if intervals[p-1][1] >= current[0]:
            intervals[p-1][0] = min(current[0],intervals[p-1][0])
            intervals[p-1][1] = max(current[1],intervals[p-1][1])
            intervals.pop(p)
            merge(intervals,p-1)
    if p < len(intervals)-1:
        if current[1] >= intervals[p+1][0]:
            intervals[p][0] = min(current[0],intervals[p+1][0])
            intervals[p][1] = max(current[1],intervals[p+1][1])
            #print("Removing,",p+1, "in list", intervals)
            intervals.pop(p+1)
            merge(intervals,p)

class Solution:
    def insert(self, intervals: List[List[int]], newInterval: List[int]) -> List[List[int]]:        
        insert_pos = -1
        for p in range(len(intervals)):
            if newInterval[0] <= intervals[p][0]:
                intervals.insert(p,newInterval)
                insert_pos = p
                break
        if insert_pos == -1:
            intervals.append(newInterval)
            merge(intervals,len(intervals)-1)
        else:
            merge(intervals, insert_pos)
        return intervals
                

from pprint import pprint
pprint(Solution().insert([[1,3],[6,9]], [2,5])) # => [[1,5],[6,9]]
pprint(Solution().insert([[1,2],[3,5],[6,7],[8,10],[12,16]], [4,8])) # => [[1,2],[3,10],[12,16]]
pprint(Solution().insert([[1,5]], [2,3])) # [[1,5]]