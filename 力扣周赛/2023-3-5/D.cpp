class Solution {
public:
    static constexpr int mod = 1000000007;
    int waysToReachTarget(int target, vector<vector<int>>& types) {
        int n = types.size();

        vector<long long> f(target + 1);
        f[0] = 1;
        for (int i = 0; i < n; ++i)
            for (int j = target; j >= types[i][1]; --j)
                for (int k = 1; types[i][1] * k <= j && k <= types[i][0]; ++k)
                    f[j] = (f[j] + f[j - k * types[i][1]]) % mod;
        return f[target];
    }
};