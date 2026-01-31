from collections import defaultdict

class Solution:
    def numberOfPairs(self, nums1: List[int], nums2: List[int], k: int) -> int:
        ans = 0
        mx = max(nums1)
        cnt = [0] * (mx+1)
        nums = defaultdict(int)
        for v in nums2:
            nums[v] += 1
        for v, t in nums.items():
            c = v * k
            for x in range(c,mx+1,c):
                cnt[x] += t
        for v in nums1:
            ans += cnt[v]
        return ans
        