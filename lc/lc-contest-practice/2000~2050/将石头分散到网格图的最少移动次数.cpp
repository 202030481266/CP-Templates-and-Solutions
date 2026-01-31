class Solution {
    int dp[1 << 9], N = (1 << 9);
public:
    int minimumMoves(vector<vector<int>>& grid) {
        vector<int> a;
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j) 
                for (int k = 0; k < grid[i][j]; ++k)
                    a.push_back(i * 3 + j);
        assert(a.size() == 9);
        auto f = [](int x, int y) {
            return abs(x / 3 - y / 3) + abs(x % 3 - y % 3);
        };
        memset(dp, 0x3f, sizeof(dp));
        dp[0] = 0;
        for (int i = 0; i < 9; ++i) 
            for (int j = N - 1; j >= 1; --j)
                for (int k = 0; k < 9; ++k)
                    if ((j >> k) & 1) dp[j] = min(dp[j], dp[j ^ (1 << k)] + f(k, a[i]));
        return dp[N - 1];
    }
};