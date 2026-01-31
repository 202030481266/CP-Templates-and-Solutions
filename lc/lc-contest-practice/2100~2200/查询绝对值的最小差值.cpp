// https://leetcode.cn/problems/minimum-absolute-difference-queries/



class Solution {
public:
    vector<int> minDifference(vector<int>& nums, vector<vector<int>>& queries) {
        // 如果 a 中所有元素都 相同 ，那么差绝对值的最小值为 -1 。
        // 1 <= nums[i] <= 100
        int n = nums.size(), m = queries.size(), pre[n + 1][110]; 
        vector<int> ans(m, INT_MAX);
        memset(pre, 0, sizeof(pre));

        for (int i = 1; i <= n; ++i) 
            for (int j = 1; j <= 100; ++j) pre[i][j] = pre[i - 1][j] + (nums[i - 1] == j);
        for (int i = 0; i < m; ++i) {
            int l = queries[i][0] + 1, r = queries[i][1] + 1, last = nums[l - 1];
            // 检查是否全部都是相同的元素
            if (pre[r][last] - pre[l - 1][last] == (r - l + 1)) ans[i] = -1;
            else {
                last = -1;
                for (int j = 1; j <= 100; ++j)
                    if (pre[r][j] - pre[l - 1][j] > 0) {
                        if (last == -1) last = j;
                        else ans[i] = min(ans[i], j - last), last = j;
                    }
            }
        }
        return ans;
    }
};