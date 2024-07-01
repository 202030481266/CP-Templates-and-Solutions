from collections import defaultdict
class Solution:
    def leadsToDestination(self, n: int, edges: List[List[int]], source: int, destination: int) -> bool:
        vis = [0] * n
        instack = [0] * n # 判环
        g = defaultdict(list)
        for e in edges:
            g[e[0]].append(e[1])
        if g[destination]:
            return False
        #dfs需要点技巧
        #需要两个状态数组
        def dfs(u):
            nonlocal g, vis, instack, destination
            if g[u]:
                for v in g[u]:
                    if instack[v]:
                        return False
                    if not vis[v]:
                        vis[v] = 1
                        instack[v] = 1
                        if not dfs(v):
                            return False
                        instack[v] = 0
                return True
            return u == destination
        instack[source] = 1
        vis[source] = 1
        return dfs(source)

               
            
            