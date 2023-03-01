# There are a total of numCourses courses you have to take, labeled from 0 to numCourses - 1.
# You are given an array prerequisites where prerequisites[i] = [ai, bi] indicates that you must take
# course bi first if you want to take course ai.

# For example, the pair [0, 1], indicates that to take course 0 you have to first take course 1.
# Return true if you can finish all courses. Otherwise, return false.


from typing import List

from collections import defaultdict





class Solution:

    def canFinish(self, numCourses: int, prerequisites: List[List[int]]) -> bool:
        before = defaultdict(list)
        for [a,b] in prerequisites:
            before[a].append(b)
        
        marks = [0] * numCourses
        for p in range(numCourses):
            if marks[p] == 0:
                #print(">>>",p)
                if not self.visit(p, marks, before): return False
        return True

    def visit(self, p, marks, before):
        #print(p,marks,before)
        if marks[p] == 1:
            #print("T")
            return True
        if marks[p] == 2:
            #print("F")
            return False
        marks[p] = 2
        for m in before[p]:
            if not self.visit(m, marks, before):
                #marks[p] = 1
                return False
        marks[p] = 1
        return True

        



#assert Solution().canFinish(2, [[1,0]])==True
#assert Solution().canFinish(2, [[1,0],[0,1]])==False
print(Solution().canFinish(5, [[1,4],[2,4],[3,1],[3,2]]))
print(Solution().canFinish(8, [[1,0],[2,6],[1,7],[6,4],[7,0],[0,5]]))