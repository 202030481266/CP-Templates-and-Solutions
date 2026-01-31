from typing import List

class Node():
    def __init__(self, val):
        self.val = val
        self.left = None
        self.right = None
    def evaluate(self) -> int:
        if self.val.isdigit():
            return int(self.val)
        if self.val == '+':
            return self.left.evaluate() + self.right.evaluate()
        if self.val == '-':
            return self.left.evaluate() - self.right.evaluate()
        if self.val == '*':
            return self.left.evaluate() * self.right.evaluate()
        if self.val == '/':
            return self.left.evaluate() // self.right.evaluate()

class TreeBuilder(object):
    def buildTree(self, postfix: List[str]) -> 'Node':
        if not postfix: return None
        node = Node(postfix.pop())
        if node.val.isdigit():
            return node
        node.right = self.buildTree(postfix)
        node.left = self.buildTree(postfix)
        return node