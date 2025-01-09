from typing import List

class Solution:
    def maxAmount(self, initialCurrency: str, pairs1: List[List[str]], rates1: List[float], pairs2: List[List[str]], rates2: List[float]) -> float:
        curr = set()
        for p in pairs1 + pairs2:
            for c in p:
                curr.add(c)
        curr.add(initialCurrency)
        curr = list(curr)
        ids = {c: i for i, c in enumerate(curr,1)}
        n = len(curr)
        g = [[] for _ in range(2*n+2)]
        for (u, v), w in zip(pairs1, rates1):
            u, v = ids[u], ids[v]
            g[u].append((v, w))
            g[v].append((u, 1/w))
        for (u, v), w in zip(pairs2, rates2):
            u, v = ids[u]+n, ids[v]+n
            g[u].append((v, w))
            g[v].append((u, 1/w)) 
        for i in range(1, n+1):
            g[i].append((i+n, 1))
        st = ids[initialCurrency]
        g[0].append((st, 1))
        g[st].append((2*n+1, 1))
        g[st+n].append((2*n+1, 1))
        dis = [0] * (2*n+2)
        dis[0] = 1
        q = [0]
        while q:
            u = q.pop()
            for v, w in g[u]:
                if dis[v] < dis[u] * w:
                    dis[v] = dis[u] * w
                    q.append(v)
        return dis[2*n+1]