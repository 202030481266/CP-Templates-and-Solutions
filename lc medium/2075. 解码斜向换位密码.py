class Solution:
    def decodeCiphertext(self, encodedText: str, rows: int) -> str:
        N = len(encodedText)
        n, m = rows, N // rows
        ans = ""
        for i in range(m):
            x, y = 0, i
            while x >= 0 and x < n and y >= 0 and y < m:
                ans += encodedText[x * m + y]
                x += 1
                y += 1
        return ans.rstrip()
        
        