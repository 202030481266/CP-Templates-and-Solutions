class Solution:
    def tripletCount(self, a: List[int], b: List[int], c: List[int]) -> int:
        arr = [a,b,c]
        cnt = [[0] * 2 for _ in range(3)]
        for i,nums in enumerate(arr):
            for v in nums:
                c = 0
                while v:
                    c += 1
                    v &= (v-1)
                cnt[i][c%2] += 1
        ans = cnt[0][0] * cnt[1][0] * cnt[2][0] + \
              cnt[0][1] * cnt[1][1] * cnt[2][0] + \
              cnt[0][1] * cnt[1][0] * cnt[2][1] + \
              cnt[0][0] * cnt[1][1] * cnt[2][1]
        return ans