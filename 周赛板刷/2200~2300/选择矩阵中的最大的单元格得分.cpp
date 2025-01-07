#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;



class Solution {
public:
    int maxScore(vector<vector<int>>& grid) {
        // 相当于是一个有限制的方案
        // dp
        // 1<=val<=100, 1<=n,m<=10
        int n = grid.size(), m = grid[0].size();
        // dp[i][j] = Max(dp[i-1][j ^ (1<<v)] + v) // 对值域进行dp
        vector<vector<int>> arr(101);
        for (int i = 0; i < n; ++i) {
            for (int v : grid[i]) arr[v].push_back(i);
        }
        // dp
        // dp[i][s] = Max (dp[i-1][s ^ (1<<v)] + i)
        vector<int> dp(1<<n, -1);
        dp[0] = 0;
        for (int i = 1; i <= 100; ++i) {
            for (int j = (1<<n)-1; j >= 0; --j) {
                for (int v : arr[i]) {
                    if ((j & (1<<v)) && dp[j ^ (1<<v)] != -1) {
                        dp[j] = max(dp[j], dp[j ^ (1<<v)] + i);
                    }
                }
            }
        }
        int ans = 0;
        for (int i = 1; i < (1<<n); ++i) ans = max(ans, dp[i]);
        return ans;
    }
};