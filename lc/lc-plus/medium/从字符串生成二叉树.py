class Solution:
    def str2tree(self, s: str) -> Optional[TreeNode]:
        node = []
        i = 0
        while i < len(s):
            if s[i] == '-' or s[i].isdigit():
                j = i+1 if s[i] == '-' else i
                while j < len(s) and s[j].isdigit():
                    j += 1
                val = int(s[i:j]) if s[i].isdigit() else -int(s[i+1:j])
                node.append(TreeNode(val))
                i = j-1
            elif s[i] == ')':
                t = node.pop()
                if node[-1].left is None:
                    node[-1].left = t
                else:
                    node[-1].right = t
            i += 1
        return None if len(node) == 0 else node[0]
