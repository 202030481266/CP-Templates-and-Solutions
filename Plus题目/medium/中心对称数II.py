class Solution:
    def findStrobogrammatic(self, n: int) -> List[str]:
        mp = {
            '0': '0',
            '1': '1',
            '6': '9',
            '8': '8',
            '9': '6'
        }
        len = (n - 1) // 2 + 1
        ans, cur = [], []
        def dfs(p: int):
            nonlocal ans, cur, len, n
            if p == len:
                if n % 2 == 0:
                    ans.append(''.join(cur) + ''.join([mp[k] for k in cur[::-1]]))
                else:
                    ans.append(''.join(cur) + ''.join([mp[k] for k in cur[:-1][::-1]]))
                return
            elif p == len - 1:
                if n % 2 == 0:
                    for k in mp.keys():
                        if p == 0 and k == '0':
                            continue
                        cur.append(k)
                        dfs(p + 1)
                        cur.pop()
                else:
                    for k in ['0', '1', '8']:
                        cur.append(k)
                        dfs(p + 1)
                        cur.pop()
            else:
               for k in mp.keys():
                   if p == 0 and k == '0':
                       continue
                   cur.append(k)
                   dfs(p + 1)
                   cur.pop() 
        dfs(0)
        return ans
                