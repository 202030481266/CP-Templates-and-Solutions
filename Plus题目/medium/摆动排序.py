class Solution:
    def wiggleSort(self, nums: List[int]) -> None:
        """
        Do not return anything, modify nums in-place instead.
        """
        n = len(nums)
        if n <= 1:
            return nums
        flag = 0 # ascend , a <= b
        for i in range(1,n):
            if flag:
                # descend
                if nums[i] > nums[i-1]:
                    nums[i],nums[i-1] = nums[i-1],nums[i]
            else:
                if nums[i] < nums[i-1]:
                    nums[i],nums[i-1] = nums[i-1],nums[i]
            flag ^= 1
        return nums
