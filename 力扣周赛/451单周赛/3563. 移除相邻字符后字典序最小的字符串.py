valid = [[0] * 26 for _ in range(26)]
flag = True

def init():
    for i in range(26):
        valid[i][(i+1)%26] = 1
        valid[(i+1)%26][i] = 1
        valid[i][(i+25)%26] = 1
        valid[(i+25)%26][i] = 1

class Solution:
    def lexicographicallySmallestString(self, s: str) -> str:
        global flag
        n = len(s) 
        if flag:
            flag = False
            init()
        dp = [[0] * n for _ in range(n)]
        for L in range(2, n + 1, 2):
            for i in range(n + 1 - L):
                j = i + L - 1
                a = ord(s[i]) - ord('a')
                b = ord(s[j]) - ord('a')
                if L == 2:
                    dp[i][j] = valid[a][b]
                else:
                    dp[i][j] = valid[a][b] & dp[i+1][j-1]
                    if not dp[i][j]:
                        for k in range(i+1, j-1, 2):
                            dp[i][j] = dp[i][k] & dp[k+1][j]
                            if dp[i][j]:
                                break
        f = [["{"] * 2 for _ in range(n)] # '{' always the most bigger!
        f[n-1][0] = s[n-1]
        for i in range(n-2, -1, -1):
            if f[i+1][0] < f[i+1][1]:
                f[i][0] = s[i] + f[i+1][0]
            else:
                f[i][0] = s[i] + f[i+1][1]
            for j in range(i+1, n, 2):
                if dp[i][j]:
                    if j == n-1:
                        f[i][1] = "" # delete all
                    else:
                        mn = f[j+1][0] if f[j+1][0] < f[j+1][1] else f[j+1][1]
                        if mn < f[i][1]:
                            f[i][1] = mn
        return f[0][0] if f[0][0] < f[0][1] else f[0][1]