from typing import List

# hard implementation
# include rectangles overlap check

# hard version
class Solution:
    def checkValidCuts(self, n: int, rectangles: List[List[int]]) -> bool:
        xs, ys = [], []
        for x1, y1, x2, y2 in rectangles:
            xs.append((x1, x2, y1, y2))
            ys.append((y1, y2, x1, x2))
        xs.sort()
        ys.sort()
        n = len(rectangles)
        
        def check(arr) -> bool:
            flag = True
            i = 0
            cnt = 0
            while i < n:
                cnt += 1
                j = i
                r = arr[i][1]
                tmp = []
                while j < n and arr[j][0] < r:
                    tmp.append((arr[j][2], arr[j][3], arr[j][0], arr[j][1]))
                    r = max(r, arr[j][1])
                    j += 1
                tmp.sort()
                for i in range(len(tmp)-1):
                    if tmp[i+1][0] < tmp[i][1] and max(tmp[i+1][2], tmp[i][2]) < min(tmp[i+1][3], tmp[i][3]):
                        return False
                i = j
            return flag and cnt >= 3

        return check(xs) or check(ys) 
    

