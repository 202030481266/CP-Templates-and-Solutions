const int N = 10, inf = 0x3f3f3f3f;
int dp[1<<N];
class Solution {
public:
    int assignBikes(vector<vector<int>>& workers, vector<vector<int>>& bikes) {
        int n = workers.size(), m = bikes.size();
        memset(dp, 0x3f, sizeof(dp));
        auto dis = [&](int x, int y) -> int {
            return abs(workers[x][0] - bikes[y][0]) + abs(workers[x][1] - bikes[y][1]);
        };
        dp[0] = 0;
        for (int i = 0; i < n; ++i) 
            for (int s = (1 << m) - 1; s >= 0; --s) 
                if (__builtin_popcount(s) == i + 1) 
                    for (int j = 0; j < m; ++j) 
                        if ((s >> j) & 1) dp[s] = min(dp[s], dp[s ^ (1 << j)] + dis(i, j));
        int ans = inf;
        for (int s = (1<<m) - 1; s >= 0; --s)
            if (__builtin_popcount(s) == n) ans = min(ans, dp[s]);
        return ans;
    }
};