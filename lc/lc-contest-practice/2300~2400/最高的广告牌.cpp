class Solution {
public:
    int tallestBillboard(vector<int>& rods) {
        int n = rods.size();
        // 对于每一个钢筋有三种状态,所以可以看做是加权-1,1,0
        // 目标是所有的数字的和为0，然后让正数和尽可能大
        int dp[n][10010];
        memset(dp, -1, sizeof(dp));
        function<int(int, int)> dfs = [&](int p, int sum) {
            if (p == n) 
                return sum == 5000 ? 0 : -10000000;
            int& res = dp[p][sum];
            if (res != -1) return dp[p][sum]; 
            res = 0;
            int w_0 = dfs(p + 1, sum);
            int w_1 = dfs(p + 1, sum + rods[p]) + rods[p];
            int w_2 = dfs(p + 1, sum - rods[p]);
            res = max({w_0, w_1, w_2});
            return res;
        };
        // s == 0 做了偏移
        return dfs(0, 5000);
    }
};