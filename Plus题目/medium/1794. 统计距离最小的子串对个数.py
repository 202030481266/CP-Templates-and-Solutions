class Solution:
    def countQuadruples(self, firstString: str, secondString: str) -> int:
        p1 = [-1] * 26
        p2 = [-1] * 26

        n = len(firstString)
        m = len(secondString)

        for i in range(n):
            ch = ord(firstString[i])-ord('a')
            if p1[ch] == -1:
                p1[ch] = i
        for i in range(m-1,-1,-1):
            ch = ord(secondString[i])-ord('a')
            if p2[ch] == -1:
                p2[ch] = i

        mx = -0x3f3f3f3f
        ans = 0
        for i in range(26):
            if p1[i] != -1 and p2[i] != -1:
                if p2[i] - p1[i] > mx:
                    mx= p2[i] - p1[i]
                    ans = 1
                elif p2[i] - p1[i] == mx:
                    ans += 1
        return ans