from typing import List

class Solution:
    def elementInNums(self, nums: List[int], queries: List[List[int]]) -> List[int]:
        n, m = len(nums),len(queries)
        for i in range(m):
            queries[i][0] %= 2*n
        ind = list(range(m))
        ind.sort(key=lambda x: queries[x])
        ans = [-1] * m
        t, p = 0, 0
        for q in ind:
            while t < queries[q][0]:
                t += 1
                if t==n:
                    p = n-1
                else:
                    p = (p+1)%n
            if t < n and p+queries[q][1] < n:
                ans[q] = nums[p+queries[q][1]]
            elif t > n and p >= queries[q][1]:
                ans[q] = nums[queries[q][1]]
        return ans
        

        