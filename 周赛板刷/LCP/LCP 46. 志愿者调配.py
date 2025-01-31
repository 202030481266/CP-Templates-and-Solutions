from typing import List

class Solution:
    def volunteerDeployment(self, finalCnt: List[int], totalNum: int, edges: List[List[int]], plans: List[List[int]]) -> List[int]:
        n = len(finalCnt) + 1
        a = [1] + [0] * (n-1)
        b = [0] + finalCnt
        adj = [[] for _ in range(n)]
        for u, v in edges:
            adj[u].append(v)
            adj[v].append(u)
        for op, idx in reversed(plans):
            if op == 1:
                a[idx] *= 2
                b[idx] *= 2
            elif op == 2:
                for v in adj[idx]:
                    a[v] -= a[idx]
                    b[v] -= b[idx]
            else:
                for v in adj[idx]:
                    a[v] += a[idx]
                    b[v] += b[idx]
        sa, sb = 0, 0
        for i in range(n):
            sa += a[i]
            sb += b[i]
        # sa * x = totalNum - sb
        x = (totalNum - sb) // sa
        ans = [0] * n
        for i in range(n):
            ans[i] = a[i] * x + b[i]
        return ans