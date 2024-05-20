class UnionFind:
    def __init__(self, size):
        self.parent = list(range(size))
        self.size = [1] * size
        self.sz = size

    def find(self, x):
        if self.parent[x] != x:
            self.parent[x] = self.find(self.parent[x])
        return self.parent[x]

    def union(self, x, y):
        rootX = self.find(x)
        rootY = self.find(y)
        if rootX != rootY:
            self.sz -= 1
            if self.size[rootX] < self.size[rootY]:
                self.parent[rootX] = rootY
                self.size[rootY] += self.size[rootX]
            else:
                self.parent[rootY] = rootX
                self.size[rootX] += self.size[rootY]

    def is_connected(self, x, y):
        return self.find(x) == self.find(y)

class Solution:
    def earliestAcq(self, logs: List[List[int]], n: int) -> int:
        un = UnionFind(n)
        logs.sort()
        for time, u, v in logs:
            un.union(u, v)
            if un.sz == 1:
                return time
        return -1