from typing import List

class Solution:
    def maximumMatchingIndices(self, nums1: List[int], nums2: List[int]) -> int:
        a = nums1 + nums1
        n = len(a)
        m = len(nums2)
        ans = 0
        for i in range(n-m+1):
            cur = 0
            for j in range(i,i+m):
                if a[j] == nums2[j-i]:
                    cur += 1
            ans = max(ans,cur)
        return ans


                

        