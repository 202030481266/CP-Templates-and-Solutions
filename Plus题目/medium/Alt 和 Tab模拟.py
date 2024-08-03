class Node:
    def __init__(self, key):
        self.key = key
        self.prev = None
        self.next = None
    def __str__(self):
        return f'Node({self.key}, {self.value})'
    def insert_after(self, node):
        node.prev = self
        node.next = self.next
        if self.next:
            self.next.prev = node
            self.next = node
        self.next = node
    def remove(self):
        self.prev.next = self.next
        if self.next:
            self.next.prev = self.prev

class Solution:
    def simulationResult(self, windows: List[int], queries: List[int]) -> List[int]:
        # 超级简单，就是一个 cache的问题
        idx = [None] * (len(windows)+1)
        head = Node(0)
        idx[0] = head
        cur = head
        def print_list():
            nonlocal head
            p = head
            while p.next:
                print(p.next.key,end=' ')
                p = p.next
            print()
        for w in windows:
            n = Node(w)
            idx[w] = n
            cur.insert_after(n)
            cur = cur.next
        for q in queries:
            n = idx[q]
            n.remove()
            head.insert_after(n)
        ans = []
        while head.next:
            ans.append(head.next.key)
            head = head.next
        return ans





        
        