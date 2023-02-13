// https://leetcode.cn/problems/partition-to-k-equal-sum-subsets/
// 爆搜+状态规划+贪心剪枝


class Solution {
public:
    bool canPartitionKSubsets(vector<int>& nums, int k) {
        int n = nums.size();
        int s = accumulate(nums.begin(), nums.end(), 0);
        if (s % k) return false;

        int t = s / k;
        int N = (1 << n);
        vector<bool> vis(N, false);

        // 贪心技巧： 每次都选大的数，进行可行性剪枝
        sort(nums.begin(), nums.end());  

        function<bool(int,int)> dfs=[&](int st,int p) -> bool {
            if (st == 0) return true;
            if (vis[st]) return false;
            vis[st] = true;
            for (int i = 0; i < n; ++i) {
                if (p + nums[i] > t) {
                    break;
                }
                if ((st >> i) & 1) {
                    if (dfs(st ^ (1 << i), (p + nums[i]) % t))
                        return true;
                }
            }
            return false;
        };
        return dfs(N - 1, 0);
    }
};