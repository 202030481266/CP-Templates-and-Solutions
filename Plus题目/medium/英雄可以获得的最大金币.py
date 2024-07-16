# bisect_left 找到第一个大于等于target的数字
# bisect_right 找到第一个大于target的数字
# key 参数是一个很好用的参数，算是锻炼了python的语法

class Solution:
    def maximumCoins(self, heroes: List[int], monsters: List[int], coins: List[int]) -> List[int]:
        n = len(monsters)
        ids = [i for i in range(n)]
        ids.sort(key=lambda x: monsters[x])
        s = [0 for _ in range(n)] 
        s[0] = coins[ids[0]]
        for i in range(1,n):
            s[i] = s[i-1] + coins[ids[i]]
        ans = []
        for v in heroes:
            x = bisect_right(ids, v, key=lambda x: monsters[x])
            ans.append(s[x-1] if x > 0 else 0)
        return ans
        
