// https://leetcode.cn/problems/jump-game-ii/description/
// 可以贪心也可以动态规划，但是这道题目数据很大，动态规划应该会炸
// 贪心策略：每一步选择可以让现在可达范围最大的点进行跳跃，这样可以保证相同代价情况下，下一步的选择更多。


// 贪心做法
class Solution {
public:
    int jump(vector<int>& nums) {
        int n = nums.size();
        int end = 0, right = 0, ans = 0;

        // 不能使用最后一个点
        for (int i = 0; i < n - 1; ++i) {
            if (right >= i) {
                right = max(right, i + nums[i]);
                if (i == end) {
                    end = right;
                    ++ans;
                }
            }
        }
        return ans;
    }
};




// 动态规划做法 
class Solution {
public:
    int jump(vector<int>& nums) {
        int n = nums.size();
        if (n == 1) return 0;

        vector<int> dp(n, 2e9);
        vector<bool> vis(n, false);
        dp[n - 1] = 0;
        vis[0] = true;

        function<int(int)> dfs = [&](int pos) -> int {
            if(dp[pos] != 2e9) return dp[pos];

            int left = max(0, pos - nums[pos]);
            int right = min(n - 1, pos + nums[pos]);

            int res = 2e9;
            for (int i = left; i <= right; i++) {
                if (!vis[i]) {
                    vis[i] = true;
                    res = min(res, dfs(i));
                    vis[i] = false;
                }
            }

            return dp[pos] = res + 1;
        };

        return dfs(0);
    }
};