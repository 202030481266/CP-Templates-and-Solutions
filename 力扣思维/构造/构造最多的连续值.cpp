// https://leetcode.cn/problems/maximum-number-of-consecutive-values-you-can-make/description/
// 技巧： 构造，利用已经的结果进行干扰，贪心构造
// [0, x] 是前 i - 1个数中的可以构造的数，那么对于剩下的数我们可以构造出 y
// 那么表明可以构造出 [y, x + y], if y <= x + 1 -> [0, x + y]
// 所以我们每一次选择最小的数 y 来进行构造，如果最小的都连接不了表明后面的都不行了


class Solution {
public:
    int getMaximumConsecutive(vector<int>& coins) {
        int res = 1;
        sort(coins.begin(), coins.end());
        for (auto& i : coins) {
            if (i > res) {
                break;
            }
            res += i;
        }
        return res;
    }
};
