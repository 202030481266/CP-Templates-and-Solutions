from typing import List

class Solution:
    def widestPairOfIndices(self, nums1: List[int], nums2: List[int]) -> int:
        # a[r]-a[l] == b[r]-b[l]
        # a[r] - b[r] == a[l] - b[l]
        n = len(nums1)
        a = [0] * (n+1)
        b = [0] * (n+1)
        for i in range(n):
            a[i+1] = a[i] + nums1[i]
            b[i+1] = b[i] + nums2[i]
        pos = {}
        pos[0] = 0
        ans = 0
        for i in range(1,n+1):
            s = a[i]-b[i]
            if pos.get(s) is not None:
                ans = max(ans, i-pos[s])
            else:
                pos[s] = i
        return ans

