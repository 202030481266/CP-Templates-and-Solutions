# 贪心难题

def ceil_div(a, b):
    q = a // b
    r = a % b
    if r != 0 and ((a ^ b) > 0):
        q += 1
    return q

def cal(arr):
    # 2, 3, 5 7
    res = arr[2] + arr[3]
    if (arr[1] & 1) and (arr[0] > 0):
        res += 1 + ceil_div(arr[0]-1, 3) + ceil_div(arr[1]-1, 2)
    else:
        res += ceil_div(arr[0], 3) + ceil_div(arr[1], 2)
    return res


change = [
    [0, 0, 0, 0], # 0
    [0, 0, 0, 0], # 1
    [1, 0, 0, 0], # 2
    [0, 1, 0, 0], # 3
    [2, 0, 0, 0], # 4
    [0, 0, 1, 0], # 5
    [1, 1, 0, 0], # 6
    [0, 0, 0, 1], # 7
    [3, 0, 0, 0], # 8
    [0, 2, 0, 0], # 9
]

inf = 0x3f3f3f3f

class Solution:
    def smallestNumber(self, num: str, t: int) -> str:
        n = len(num)
        cnt = [0] * 4 # 2, 3, 5, 7
        
        for i,v in enumerate([2,3,5,7]):
            while t % v == 0:
                cnt[i] += 1
                t /= v
        if t != 1:
            return "-1"
        
        def check(status, pos) -> bool:
            nonlocal n
            a, b, c, d = status # 2, 3, 5, 7
            s1, s2 = inf, inf
            if (b & 1) and (a > 0):
                s1 = 1 + ceil_div(a-1, 3) + ceil_div(b-1,2)
            s2 = ceil_div(a,3) + ceil_div(b,2)
            # [pos, n)
            tmp = min(s1, s2) + c + d
            if n-pos < tmp:
                return False
            # 判断是否可以更大
            if tmp == n-pos:
                n_6 = 0
                n_9 = ceil_div(b,2)
                n_8 = ceil_div(a,3)
                if s1 < s2:
                    n_6 = 1 # use 6
                    n_8 = ceil_div(a-1,3)
                    n_9 = ceil_div(b-1,2)
                # 最大的排列就是 9999, 8888, 777, 666, 555
                s = '9' * n_9 + '8' * n_8 + '7' * d + '6' * n_6 + '5' * c
                i, j = 0, pos
                while i < len(s) and j < n and s[i] == num[j]:
                    i += 1
                    j += 1
                if i < len(s) and j < n:
                    return s[i] > num[j]
                return True
            else:
                # have more space, we could add more 9 and 8
                n_9 = ceil_div(b,2)
                n_8 = ceil_div(a,3)
                rm = n-pos-n_9-n_8-c-d
                # 最大的排列
                n_9 += rm
                s = '9' * n_9 + '8' * n_8 + '7' * d + '5' * c
                i, j = 0, pos
                while i < len(s) and j < n and s[i] == num[j]:
                    i += 1
                    j += 1
                if i < len(s) and j < n:
                    return s[i] > num[j]
                return True
        
        S = [[0] * 4 for _ in range(n)]
        S[0] = cnt
        for i in range(1,n):
            c = int(num[i-1])
            # (i, n)
            for j in range(4):
                S[i][j] = S[i-1][j] - change[c][j]
                if S[i][j] < 0:
                    S[i][j] = 0
        
        l, r = -1, 0 # (l,r)
        while r < n and num[r] != '0':
            r += 1
        r = r if r == n else r+1
        while l+1 < r:
            mid = (l+r) // 2
            if (check(S[mid], mid)):
                l = mid
            else:
                r = mid
            
        if l == n-1 and num[n-1] != '0':
            # 最后一个元素很难确定是否可以相等，因为边界的关系
            ok = True
            last = int(num[n-1])
            for i in range(4):
                if S[n-1][i] > change[last][i]:
                    ok = False
                    break
            if ok:
                return num

        ans = ""
        if l == -1:
            # 长度不能构造出来，要么是n不够长，要么是n每一个数位太大了
            need = cal(cnt)
            # res 是最后的长度
            res = n + 1
            if need > n:
                res = need
            # [0, res-need) [res-need, res)
            ans = "1" * (res-need)
            cur = cnt
            for i in range(res-need, res):
                for k in range(1, 10):
                    nxt = [0] * 4
                    for j in range(4):
                        nxt[j] = cur[j] - change[k][j]
                        if nxt[j] < 0:
                            nxt[j] = 0
                    # (i, res)
                    if cal(nxt) <= res-i-1:
                        ans += str(k)
                        cur = nxt
                        break
        else:
            # [l, n)
            ans = num[:l]
            cur = S[l]
            for i in range(l, n):
                st = int(num[l])+1 if i == l else 1
                for k in range(st, 10):
                    nxt = [0] * 4
                    for j in range(4):
                        nxt[j] = cur[j] - change[k][j]
                        if nxt[j] < 0:
                            nxt[j] = 0
                    # (i,n)
                    if cal(nxt) <= n-i-1:
                        ans += str(k)
                        cur = nxt
                        break
        return ans
                