class Solution {
public:
    int maximumProcessableQueries(vector<int>& nums, vector<int>& queries) {
        // 要求尽量的数组两端大一点，这样可以处理的请求就是更多的
        // 左边或者右边，有两个选择，可以考虑正向的选择，dp[l][r]表示区间[l,r]消除可以得到的最大长度
        // 因为每一次从左到右进行一个消除，所以正向的dp非常困难，因为会多一层的维度（小区间求解大区间）
        // 改变状态设计：选择反向思考，我们将大区间的答案向小区间堆，dp[l][r]表示区间[l,r]还没有消除能够消除的最大长度
        int n = nums.size(), dp[n][n], ans = 0, m = queries.size();
        memset(dp, 0, sizeof(dp));
        for (int len = n; len >= 1; --len) {
            for (int i = 0; i + len - 1 < n; ++i) {
                int j = i + len - 1; // [i, j]
                int tmp = 0;
                if (i - 1 >= 0 ) {
                    if (nums[i - 1] >= queries[dp[i - 1][j]])
                        tmp = max(tmp, dp[i - 1][j] + 1);
                    else tmp = max(tmp, dp[i - 1][j]);
                }
                if (j + 1 < n) {
                    if (nums[j + 1] >= queries[dp[i][j + 1]]) 
                        tmp = max(tmp, dp[i][j + 1] + 1);
                    else tmp = max(tmp, dp[i][j + 1]);
                }
                dp[i][j] = tmp;
                if (tmp == m) return m;
            }
        }
        for (int i = 0; i < n; ++i)
            ans = max(ans, dp[i][i] + (nums[i] >= queries[dp[i][i]]));
        return ans;
    }
};