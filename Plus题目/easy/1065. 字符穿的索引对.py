from typing import List
from collections import deque

class ACNode:
    def __init__(self):
        self.children = {}
        self.is_word = False
        self.fail = None
        self.length = 0
        
class Solution:
    def build_ac(self, words):
        root = ACNode()
        
        # Build Trie
        for word in words:
            node = root
            for char in word:
                if char not in node.children:
                    node.children[char] = ACNode()
                node = node.children[char]
            node.is_word = True
            node.length = len(word)
            
        # Build Failure Links
        queue = deque([root])
        while queue:
            curr = queue.popleft()
            for char, child in curr.children.items():
                if curr == root:
                    child.fail = root
                else:
                    fail = curr.fail
                    while fail:
                        if char in fail.children:
                            child.fail = fail.children[char]
                            break
                        fail = fail.fail
                    if not fail:
                        child.fail = root
                queue.append(child)
        return root

    def indexPairs(self, text: str, words: List[str]) -> List[List[int]]:
        root = self.build_ac(words)
        res = []
        curr = root
        
        # Search text
        for i in range(len(text)):
            while curr != root and text[i] not in curr.children:
                curr = curr.fail
            
            if text[i] in curr.children:
                curr = curr.children[text[i]]
                temp = curr
                while temp != root:
                    if temp.is_word:
                        res.append([i - temp.length + 1, i])
                    temp = temp.fail
                    
        return sorted(res)