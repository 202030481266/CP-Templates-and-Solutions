from collections import defaultdict
class Solution:
    def treeDiameter(self, edges: List[List[int]]) -> int:
        g = defaultdict(list)
        for u, v in edges:
            g[u].append(v)
            g[v].append(u)
        sc, d = 0, 0
        def dfs(u, fa, dep):
            nonlocal sc, d
            if dep > d:
                sc, d = u, dep
            for v in g[u]:
                if v != fa:
                    dfs(v, u, dep + 1)
        dfs(0, 0, 0)
        dfs(sc, sc, 0)
        return d
        