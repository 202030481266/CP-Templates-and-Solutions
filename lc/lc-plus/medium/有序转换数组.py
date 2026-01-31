class Solution:
    def sortTransformedArray(self, nums: List[int], a: int, b: int, c: int) -> List[int]:
        ans = []
        # 双指针
        if a != 0:
            mid = -b/(2*a)
            p = 0
            while p < len(nums) and nums[p] <= mid:
                p += 1
            # [0,p) <= mid
            i, j = p-1, p
            while i >= 0 and j < len(nums):
                if abs(nums[i]-mid) < abs(nums[j]-mid):
                    ans.append(a*nums[i]**2+b*nums[i]+c)
                    i -= 1
                else:
                    ans.append(a*nums[j]**2+b*nums[j]+c)
                    j += 1
            while i >= 0:
                ans.append(a*nums[i]**2+b*nums[i]+c)
                i -= 1
            while j < len(nums):
                ans.append(a*nums[j]**2+b*nums[j]+c)
                j += 1
            if a < 0:
                ans.reverse()
        else:
            ans = [b*v+c for v in nums]
            if b < 0:
                ans.reverse()
        return ans