from typing import List

class Solution:
    def combinationSum2(self, candidates: List[int], target: int) -> List[List[int]]:
        n = len(candidates)
        candidates.sort()
        ans = []
        cur = []
        def dfs(i, sum):
            nonlocal ans, cur
            if sum == 0:
                ans.append(cur.copy())
                return
            if i == n:
                return
            p = i+1
            while p < n and candidates[p] == candidates[i]:
                p += 1
            for j in range(i, p):
                c = j - i + 1
                if candidates[i] * c > sum:
                    break
                cur.extend([candidates[i]] * c)
                dfs(p, sum-candidates[i] * c)
                cur = cur[:len(cur)-c]
            dfs(p, sum)
        dfs(0, target)
        return ans