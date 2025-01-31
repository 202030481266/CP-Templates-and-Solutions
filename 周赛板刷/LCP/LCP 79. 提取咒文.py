from typing import List

# 使用BFS来搜索可以保证使用空间上的优势来O(1)转移最短路的状态
# 否则的话，转移的难度将会大大加大，这是一个十分有力的技巧：优先使用1权重的边的图而不是使用大于1权重的图

class Solution:
    def extractMantra(self, matrix: List[str], mantra: str) -> int:
        m, n = len(matrix), len(matrix[0])
        q = [(0, 0, 0)]
        vis = {q[0]}
        step = 1
        while q:
            tmp = q
            q = []
            for i, j, k in tmp:
                if matrix[i][j] == mantra[k]:  # 可以提取
                    if k == len(mantra) - 1:  # 下一步就是终点，直接返回
                        return step
                    p = (i, j, k + 1)
                    if p not in vis:
                        vis.add(p)
                        q.append(p)
                # 枚举周围四个格子
                for x, y in (i + 1, j), (i - 1, j), (i, j + 1), (i, j - 1):
                    if 0 <= x < m and 0 <= y < n:
                        p = (x, y, k)
                        if p not in vis:
                            vis.add(p)
                            q.append(p)
            step += 1
        return -1