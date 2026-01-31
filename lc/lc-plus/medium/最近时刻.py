class Solution:
    def nextClosestTime(self, time: str) -> str:
        # 直接构造错误率很高，实际上最好的方法依然是搜索
        num = []
        for c in time:
            if c.isdigit():
                num.append(int(c))
        cur = []
        ans = ""
        res = 2e9
        t = int(time[:2])*60+int(time[3:])
        def dfs(p):
            nonlocal num,ans,res,t
            if p==4:
                h = cur[0]*10+cur[1]
                m = cur[2]*10+cur[3]
                if 0 <= h <= 23 and 0 <= m <= 59:
                    # 计算时间差,0~1439
                    now = h*60+m
                    sub = (now-t+1440)%1440
                    if sub == 0: # 转了一圈
                        sub = 1440
                    if sub < res:
                        ans = str(h).zfill(2)+":"+str(m).zfill(2) # 输出格式问题
                        res = sub
                return
            for v in num:
                cur.append(v)
                dfs(p+1)
                cur.pop()
        dfs(0)
        return ans
            
            