from typing import List

def char_to_num(c):
    # 处理小写字母 a-z -> 0-25
    if 'a' <= c <= 'z':
        return ord(c) - ord('a')
    # 处理大写字母 A-Z -> 26-51
    elif 'A' <= c <= 'Z':
        return ord(c) - ord('A') + 26
    # 如果输入非法字符，可以返回-1或抛出异常
    return -1

class Solution:
    def spellchecker(self, wordlist: List[str], queries: List[str]) -> List[str]:
        ori = {}
        ins = {}
        tem = {}
        for i, s in enumerate(wordlist):
            h = 0
            n = len(s)
            for j in range(n):
                t = char_to_num(s[j])
                h |= (t<<(6*j))
            if h not in ori:
                ori[h] = i
            h = 0
            s_lower = s.lower()
            h = 0
            k = 0
            for j in range(n):
                t = char_to_num(s_lower[j])
                h |= (t<<(6*j))
                if s_lower[j] not in ['a', 'e', 'i', 'o','u']:
                    k |= (t<<(6*j))
            if h not in ins:
                ins[h] = i
            if k not in tem:
                tem[k] = i
        ans = []
        for q in queries:
            h = 0
            n = len(q)
            for i in range(n):
                t = char_to_num(q[i])
                h |= (t<<(6*i))
            if h in ori:
                ans.append(ori[h])
                continue
            h = 0
            k = 0
            q_lower = q.lower()
            for i in range(n):
                t = char_to_num(q_lower[i])
                h |= (t<<(6*i))
                if q_lower[i] not in ['a','e', 'i','o', 'u']:
                    k |= (t<<(6*i))
            if h in ins:
                ans.append(ins[h])
                continue
            if k in tem:
                ans.append(tem[k])
                continue
            ans.append(-1)
            
        return [wordlist[i] if i >= 0 else "" for i in ans]