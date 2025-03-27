from typing import List


class Solution:
    def moveZeroes(self, nums: List[int]) -> None:
        left = 0
        right = 0
        l = len(nums)
        while right < l:
            if nums[left] == 0:
                while nums[right] == 0 and right < l - 1:
                    right += 1
                nums[left], nums[right] = nums[right], nums[left]
            left += 1
            right += 1

nums = [1, 0, 1]
Solution().moveZeroes(nums)
print(nums)