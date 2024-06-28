#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;

class Solution {
public:
    int numberOfPermutations(int n, vector<vector<int>>& requirements) {
        int mx = 0;
        for (auto& r : requirements) mx = max(mx, r[1]);
        sort(requirements.begin(), requirements.end());
        vector dp(n+1, vector<ll>(mx+1));
        int p = 0;
        dp[0][0] = 1;
        for (int i = 1; i <= n; ++i) { // 考虑将最大的数字放在哪里就行了,在线算法 + dp
            for (int j = 0; j <= mx; ++j) {
                for (int x = 0; x < i; ++x) {
                    if (j >= x)
                        dp[i][j] = (dp[i][j] + dp[i-1][j-x]) % mod;
                }
            }
            if (i-1 == requirements[p][0]) {
                for (int j = 0; j <= mx; ++j) {
                    if (j != requirements[p][1]) dp[i][j] = 0;
                }
                ++p;
            }
        }
        return dp[n][mx];
    }
};