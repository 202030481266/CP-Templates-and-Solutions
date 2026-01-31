class Solution:
    def getWinner(self, arr: List[int], k: int) -> int:
        n = len(arr)
        if k > n:
            k = n
        mx = max(arr)
        st = []
        r = [n] * n
        # 单调栈
        for i in range(n):
            while len(st) and arr[st[-1]] < arr[i]:
                r[st[-1]] = i 
                st.pop()
            st.append(i)
        if r[0] >= k + 1 or arr[0] == mx:
            return arr[0]
        pre = arr[0]
        for i in range(1, n):
            if arr[i] == mx:
                return mx
            res = 0 if arr[i] < pre else r[i] - i
            if res >= k:
                return arr[i]
            pre = max(pre, arr[i])
        return -1
        
