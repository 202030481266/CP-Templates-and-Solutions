from typing import List
from collections import defaultdict

class Node:
    def __init__(self):
        self.adj = defaultdict(Node)

# Trie去重
class Solution:
    def countDistinct(self, nums: List[int], k: int, p: int) -> int:
        n = len(nums)
        mx = max(nums)
        root = Node()
        
        def insert(st, ed):
            cur = root
            for i in range(ed, st - 1, -1):
                if nums[i] not in cur.adj:
                    cur.adj[nums[i]] = Node()
                cur = cur.adj[nums[i]]

        l = 0
        cur = 0
        for i in range(n): 
            if nums[i] % p == 0:
                cur += 1
            while cur > k:
                if nums[l] % p == 0:
                    cur -= 1
                l += 1
            insert(l, i)
        
        ans = 0
        def dfs(node):
            nonlocal ans
            ans += 1
            for nxt in node.adj.values():
                dfs(nxt)
        
        for nxt in root.adj.values():
            dfs(nxt)
        return ans
        


        