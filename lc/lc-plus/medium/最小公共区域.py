from collections import defaultdict
class Solution:
    def findSmallestRegion(self, regions: List[List[str]], region1: str, region2: str) -> str:
        # 转换为Lca的问题
        fa = defaultdict(str)
        for region in regions:
            n = len(region)
            for i in range(1,n):
                fa[region[i]] = region[0]
        r1, r2 = [], [] 
        while region1:
            r1.append(region1)
            region1 = fa[region1]
        while region2:
            r2.append(region2)
            region2 = fa[region2]
        p, q = len(r1)-1, len(r2)-1
        while p >= 0 and q >= 0 and r1[p] == r2[q]:
            p -= 1
            q -= 1
        return r1[p+1] if p >= 0 else r2[q+1] if q >= 0 else r1[0]
        
        