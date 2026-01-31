class Solution:
    def generateString(self, str1: str, str2: str) -> str:
        n, m = len(str1), len(str2)
        ans = [""] * (n+m-1)
        vis = [0] * (n+m-1)
        for i, c in enumerate(str1):
            if c == 'T':
                for j in range(i, i+m):
                    if not ans[j]:
                        ans[j] = str2[j-i]
                    elif ans[j] != str2[j-i]:
                        return ""
                    vis[j] = 1
        for i in range(n):
            if str1[i] == 'F':
                j = i
                while j < i+m and ans[j] and ans[j] == str2[j-i]:
                    j += 1
                if j == i+m:
                    return ""
        for i in range(n+m-1):
            if not ans[i]:
                ans[i] = 'a'
        for i in range(n): 
            # 这里有一个很巧妙的思维：试填法，先尝试构造一个最佳答案然后贪心修正
            # 这种思维对于一些难以正向求解但是具有良好的必要条件的问题有用，根据必要条件反向构造，再验证充分性。
            if str1[i] == 'F':
                j = i
                while j < i+m and ans[j] == str2[j-i]:
                    j += 1
                if j == i+m:
                    j = i+m-1
                    while j > i and vis[j]:
                        j -= 1
                    ans[j] = 'b'
        return ''.join(ans)