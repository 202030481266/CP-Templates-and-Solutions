from collections import defaultdict

class Solution:
    def singleDivisorTriplet(self, nums: List[int]) -> int:
        # (a+b+c)//a==0 || (a+b+c)//b == 0 || (a+b+c)//c == 0
        # (b+c)//a==0 || (c+a)//b == 0 || (a+b)//c == 0
        # 1 <= a,b,c <= 100
        cnt = defaultdict(int)
        for v in nums:
            cnt[v] += 1
        arr = sorted(cnt.keys())
        ans = 0
        n = len(arr)
        # 3 are different
        for i in range(n):
            for j in range(i+1, n):
                for k in range(j+1, n):
                    a, b, c = arr[i], arr[j], arr[k]
                    s = a+b+c
                    if s%a==0 and s%b > 0 and s%c > 0 \
                        or s%a > 0 and s%b==0 and s%c > 0 \
                        or s%a > 0 and s%b > 0 and s%c==0:
                        ans += cnt[a] * cnt[b] * cnt[c]
        # 2 are same
        for i in range(n):
            for j in range(n):
                if cnt[arr[i]] > 1 and i != j:
                    a, b = arr[i],arr[j]
                    if 2*a % b == 0 and b % a > 0:
                        ans += cnt[a]*(cnt[a]-1)//2 * cnt[b]
        return ans*6