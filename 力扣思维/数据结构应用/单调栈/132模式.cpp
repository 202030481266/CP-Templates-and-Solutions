// https://leetcode.cn/problems/132-pattern/
// 寻找到 i < j < k && nums[i] < nums[k] < nums[j]
// 技巧在于逆序对，可以枚举每一个i然后判断后面是否存在逆序，但是这道题目数据很大，这样做不行
// 实际上用单调栈就很简单，维护一个子序列，并且让nums[k]尽可能大，所以维护单调下降


class Solution {
public:
    bool find132pattern(vector<int>& nums) {
        int n = nums.size(), tt = 0;
        if (is_sorted(nums.begin(), nums.end())) return false;
        vector<int> S(n + 1, -1);
        int minn = INT_MIN;
        // minn 表示的是nums[k]的最小值
        for (int i = n - 1; i >= 0; i--) {
            if (nums[i] < minn) return true;
            while (tt > 0 && nums[S[tt]] < nums[i]) minn = max(minn, nums[S[tt--]]);
            S[++tt] = i;
        }
        return false;
    }
};