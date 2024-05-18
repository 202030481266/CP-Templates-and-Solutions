class Solution:
    def minimumOperations(self, nums: List[int], start: int, goal: int) -> int:
        inf = 0x3f3f3f3f
        dis = [inf] * 1001
        dis[start] = 0
        q = [start]
        while len(q) > 0:
            nxt = []
            for x in q:
                for y in nums:
                    for k in [x - y, x + y, x ^ y]:
                        if 0 <= k <= 1000:
                            if dis[k] == inf:
                                dis[k] = dis[x] + 1
                                nxt.append(k)
                        else:
                            if k == goal:
                                return dis[x] + 1
            q = nxt
        return dis[goal] if 0 <= goal <= 1000 and dis[goal] != inf else -1
            