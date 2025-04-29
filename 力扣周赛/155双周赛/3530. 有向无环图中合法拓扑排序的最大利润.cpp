#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll llinf = 0x3f3f3f3f3f3f3f3f;

int dp[1<<22];
int g[23];

class Solution {
public:
    int maxProfit(int n, vector<vector<int>>& edges, vector<int>& score) {
        for (int i = 0; i < (1<<n); ++i) dp[i] = 0;
        for (int i = 0; i < n; ++i) g[i] = 0;
        for (auto& e : edges) {
            int u = e[0], v = e[1];
            g[v] |= (1<<u);
        }
        for (int i = 0; i < (1<<n); ++i) {
            if (i == 0 || dp[i]) {
                int cnt = __builtin_popcount(i);
                for (int j = 0; j < n; ++j) {
                    if ((i & (1<<j)) == 0 && (g[j] & i) == g[j]) {
                        dp[i | (1<<j)] = max(dp[i | (1<<j)], dp[i] + score[j] * (cnt+1));
                    }
                }
            }
        }
        return dp[(1<<n)-1];
    }
};