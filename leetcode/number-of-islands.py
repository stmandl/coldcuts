from typing import List

class Solution:
    def dfs(self,r,c,grid,visited):
        if r<0 or r>=len(grid) or c<0 or c>=len(grid[0]) or grid[r][c] == '0' or (r,c) in visited:
            return
        visited.add((r,c))
        self.dfs(r-1,c,grid,visited)
        self.dfs(r+1,c,grid,visited)
        self.dfs(r,c-1,grid,visited)
        self.dfs(r,c+1,grid,visited)
    
    def numIslands(self, grid: List[List[str]]) -> int:
        ic = 0
        visited = set()
        for r in range(len(grid)):
            for c in range(len(grid[0])):
                if grid[r][c] == '1' and (r,c) not in visited:
                    ic+=1
                    self.dfs(r,c,grid,visited)
        return ic

print(Solution().numIslands(grid = [
  ["1","1","1","1","0"],
  ["1","1","0","1","0"],
  ["1","1","0","0","0"],
  ["0","0","0","0","0"]
])) # => 1


print(Solution().numIslands(grid = [
  ["1","1","0","0","0"],
  ["1","1","0","0","0"],
  ["0","0","1","0","0"],
  ["0","0","0","1","1"]
])) # => 3

