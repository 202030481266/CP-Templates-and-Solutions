from typing import List

class Solution:
    def minBitwiseArray(self, nums: List[int]) -> List[int]:
        ans = []
        for n in nums:
            if n == 2:
                ans.append(-1)
                continue
            bs = list(bin(n)[2:])  # 将字符串转换为列表
            l = len(bs)
            j = l - 1
            while j >= 0 and bs[j] == '1':
                j -= 1
            if j < 0:
                ans.append(n >> 1)
            else:
                bs[j+1] = '0'  # 修改列表中的字符
                for i in range(j + 2, l):
                    bs[i] = '1'
                ans.append(int(''.join(bs), 2))  # 将列表转换回字符串并转换为整数
        return ans