// https://leetcode.cn/problems/super-washing-machines/
// 经典均分纸牌问题，使用贪心技巧即可，因为最后要所有的相等，那么逐个遍历即可
// 此题进行了一定的改造，可以同时移动，所以答案变成了某个洗衣机中衣服中衣服移动的最大次数
// 在x处进行统计，流经x的衣服分为两种情况。
// 1.不包含x自身，x的左右两侧的衣服不是平均分配，假设左侧多于右侧，我们只需要计算左侧，因为右侧与左侧移动的衣服数量相等。那么，左侧多余的衣服数量全部要经过x来到达右侧，这就是sum[i]。为什么要取绝对值？因为左侧可能少于右侧，这时候就要取绝对值。总结，我们每次只需要统计x左侧的sum[i]，还要取绝对值。
// 2.x自身的衣服向两侧移动。这种情况一定是x多余平均值。为什么？假设目前左侧>平均值>x>右侧，那么在上一步计算左侧的sum[i]的时候，已经考虑了这种情况。总结，计算x多余平均值的数量，即machines[i]′
// 最后，x处的最小操作数就是上述两个值取最大值。计算整个数组的最小操作数，就要从左侧到右侧进行遍历。

class Solution {
public:
    int findMinMoves(vector<int> &machines) {
        int tot = accumulate(machines.begin(), machines.end(), 0);
        int n = machines.size();
        if (tot % n) {
            return -1;
        }
        int avg = tot / n;
        int ans = 0, sum = 0;
        for (int num: machines) {
            num -= avg;
            sum += num;
            ans = max(ans, max(abs(sum), num));
        }
        return ans;
    }
};
