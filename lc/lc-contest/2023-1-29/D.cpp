class Solution {
public:
    long long countQuadruplets(vector<int>& nums) {
        int n = nums.size();
        vector<vector<long long>> f(n + 2, vector<long long>(n + 1));
        vector<vector<long long>> g(n + 2, vector<long long>(n + 1));

        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j) 
                f[i][j] = f[i - 1][j] + (nums[i - 1] < j);
        for (int i = n; i >= 1; --i) 
            for (int j = 1; j <= n; ++j)
                g[i][j] = g[i + 1][j] + (nums[i - 1] > j);
        long long ans = 0;
        for (int j = 2; j <= n - 2; ++j)
            for (int k = j + 1; k <= n - 1; ++k)
                if (nums[k - 1] < nums[j - 1])
                    ans += (f[j - 1][nums[k - 1]] * g[k + 1][nums[j - 1]]);
        return ans;
    }
};