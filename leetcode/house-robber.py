# You are a professional robber planning to rob houses along a street.
# Each house has a certain amount of money stashed, the only constraint stopping
# you from robbing each of them is that adjacent houses have security systems
# connected and it will automatically contact the police if two adjacent houses
# were broken into on the same night.

# Given an integer array nums representing the amount of money of each house, 
# return the maximum amount of money you can rob tonight without alerting the police.

from typing import List

# class Solution:
#     def rob(self, nums: List[int]) -> int:
#         if len(nums) == 0: return 0
#         if len(nums) == 1: return nums[0]
#         return max(nums[0]+self.rob(nums[2:]),
#                     nums[1]+self.rob(nums[3:]))


class Solution:
    def rob(self, nums: List[int]) -> int:
        sol = [0] * len(nums)
        for i in range(len(nums)):
            if i == 0: sol[i] = nums[0]
            elif i == 1: sol[i] = max(nums[1], nums[0])
            else: sol[i] = max(sol[i-2]+nums[i],
                           sol[i-1])
        return sol[-1]

assert Solution().rob([1,2,3,1])==4
assert Solution().rob([2,7,9,3,1])==12
print(Solution().rob([226,174,214,16,218,48,153,131,128,17,157,142,88,43,37,157,43,221,191,68,206,23,225,82,54,118,111,46,80,49,245,63,25,194,72,80,143,55,209,18,55,122,65,66,177,101,63,201,172,130,103,225,142,46,86,185,62,138,212,192,125,77,223,188,99,228,90,25,193,211,84,239,119,234,85,83,123,120,131,203,219,10,82,35,120,180,249,106,37,169,225,54,103,55,166,124]))