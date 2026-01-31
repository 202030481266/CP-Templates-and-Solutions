class Solution:
    def minCostSetTime(self, startAt: int, moveCost: int, pushCost: int, targetSeconds: int) -> int:
        mn, sc = targetSeconds // 60, targetSeconds % 60
        ans = 0x3f3f3f3f
        while mn > 99:
            mn -= 1
            sc += 60
        while 0 <= sc <= 99:
            #  我们一开始拥有了startAt的时间
            cost = 0
            cur = "" if mn == 0 else str(mn)
            if sc <= 9 and mn > 0:
                cur += "0" + str(sc)
            else:
                cur += str(sc)
            num = str(startAt)
            for c in cur:
                if c == num:
                    cost += pushCost
                else:
                    cost += moveCost + pushCost
                    num = c
            ans = min(ans, cost)
            print(mn, sc, cost)
            mn -= 1
            sc += 60
        return ans