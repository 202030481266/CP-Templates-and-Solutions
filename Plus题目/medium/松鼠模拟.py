class Solution:
    def minDistance(self, height: int, width: int, tree: List[int], squirrel: List[int], nuts: List[List[int]]) -> int:
        s = sum([2 * (abs(nut[0]-tree[0])+abs(nut[1]-tree[1])) for nut in nuts])
        ans = 2e15
        for nut in nuts:
            ans = min(ans,s-(abs(nut[0]-tree[0])+abs(nut[1]-tree[1]))+abs(nut[0]-squirrel[0])+abs(nut[1]-squirrel[1]))
        return ans