# 使用ord函数计算字符差值, chr函数将数字转换为字符
class Solution:
    def countSubTrees(self, n: int, edges: List[List[int]], labels: str) -> List[int]:
        g = [[] for _ in range(n)]
        for e in edges:
            g[e[0]].append(e[1])
            g[e[1]].append(e[0])
        cnt = [[0] * 26 for _ in range(n)]
        # dfs函数
        def dfs(u, fa):
            nonlocal cnt, g
            cnt[u][ord(labels[u]) - ord('a')] = 1
            for v in g[u]:
                if v != fa:
                    dfs(v, u)
                    for i in range(26):
                        cnt[u][i] += cnt[v][i]
        dfs(0, -1)
        return [cnt[i][ord(labels[i]) - ord('a')] for i in range(n)]