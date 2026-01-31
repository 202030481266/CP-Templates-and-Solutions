class Solution {
public:
    int findRotateSteps(string ring, string key) {
        // n <= 100, m <= 100

        int n = ring.size(), m = key.size(), dp[n + 1][m + 1];
        memset(dp, -1, sizeof(dp));

        // get the position of differenet characters
        vector<int> p[26];
        for (int i = 0; i < n; ++i)
            p[ring[i] - 'a'].push_back(i);

        function<int(int, int)> dfs = [&](int l, int r) -> int {
            if (r == m) return 0; // already match over
            if (dp[l][r] != -1) return dp[l][r];
            int& res = dp[l][r];
            res = INT_MAX;
            for (int& v : p[key[r] - 'a']) 
                res = min(res, dfs(v, r + 1) + min(abs(v - l), n - abs(v - l)) + 1);
            return res;
        };
        return dfs(0, 0);
    }
};