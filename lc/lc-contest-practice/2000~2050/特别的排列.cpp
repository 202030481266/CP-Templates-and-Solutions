class Solution {
    static constexpr int mod = 1e9 + 7;
public:
    int specialPerm(vector<int>& nums) {
        int n = nums.size(), dp[n][1 << n];
        sort(nums.begin(), nums.end());
        memset(dp, -1, sizeof(dp));
        function<int(int,int)> dfs = [&](int p, int S) -> int {
            if (S == 0) return 1;
            if (dp[p][S] != -1) return dp[p][S];
            int& res = dp[p][S];
            res = 0;
            for (int i = 0; i < n; ++i) {
                if (((S >> i) & 1) && ((nums[p] % nums[i] == 0 || nums[i] % nums[p] == 0))) 
                    res = (res + dfs(i, S - (1 << i))) % mod;
            }
            return res;
        };
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            int S = (1 << n) - 1 - (1 << i);
            ans = (ans + dfs(i, S)) % mod;
        }
        return ans;
    }
};