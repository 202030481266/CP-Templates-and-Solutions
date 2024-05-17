import bisect

class Solution:
    def maxProfitAssignment(self, difficulty: List[int], profit: List[int], worker: List[int]) -> int:
        n = len(difficulty)
        idx = list(range(n))
        idx.sort(key=lambda x: difficulty[x])
        mx = [0] * n
        mx[0] = profit[idx[0]]
        for i in range(1,n):
            mx[i] = max(mx[i-1], profit[idx[i]])    
        ans = 0
        for w in worker:        
            p = bisect.bisect_right(idx, w, key=lambda x: difficulty[x])
            if p == n:
                ans += mx[n-1]
            else:
                if difficulty[idx[p]] > w:
                    p -= 1
                if p >= 0:
                    ans += mx[p]
        return ans
