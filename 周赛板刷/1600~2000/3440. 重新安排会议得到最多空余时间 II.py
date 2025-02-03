class Solution:
    def maxFreeTime(self, eventTime: int, startTime: List[int], endTime: List[int]) -> int:
        n = len(startTime)
        ans = 0
        pre = [0] * n
        suf = [0] * n
        pre[0] = startTime[0]
        suf[n-1] = eventTime - endTime[n-1]
        for i in range(1,n):
            pre[i] = pre[i-1]
            dura = startTime[i] - endTime[i-1]
            if dura > ans:
                ans = dura
            if dura > pre[i]:
                pre[i] = dura
        for i in range(n-2, -1, -1):
            suf[i] = suf[i+1]
            dura = startTime[i+1] - endTime[i]
            if dura > suf[i]:
                suf[i] = dura
        print(ans)
        for i in range(n):
            if i == 0:
                dura = endTime[0] - startTime[0]
                r = suf[1]
                if startTime[1] - dura > ans:
                    ans = startTime[1] - dura
                if r >= dura:
                    if ans < startTime[1]:
                        ans = startTime[1]
            elif i == n-1:
                dura = endTime[n-1] - startTime[n-1]
                if eventTime - endTime[n-2] - dura > ans:
                    ans = eventTime - endTime[n-2] - dura
                l = pre[n-2]
                if l >= dura:
                    if ans < eventTime - endTime[n-2]:
                        ans = eventTime - endTime[n-2]
            else:
                l, r = pre[i-1], suf[i+1]
                mx = startTime[i+1] - endTime[i-1]
                dura = endTime[i] - startTime[i]
                if l >= dura or r >= dura:
                    if ans < mx:
                        ans = mx
                if ans < mx - dura:
                    ans = mx - dura
        return ans
                