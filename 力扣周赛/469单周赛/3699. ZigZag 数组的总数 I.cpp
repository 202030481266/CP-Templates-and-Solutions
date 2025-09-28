#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
static constexpr int mod = 1e9 + 7;
static constexpr int inf = 0x3f3f3f3f;

int f[2][2002];
int dp[2][2002];

class Solution {
public:
    int zigZagArrays(int n, int l, int r) {
        int m = r - l + 1;
        for (int i = 1; i <= m; ++i) {
            f[0][i] = (f[0][i - 1] + 1) % mod;
            f[1][i] = (f[1][i - 1] + 1) % mod;
        }
        for (int k = 2; k <= n; ++k) {
            for (int i = 1; i <= m; ++i) {
                dp[0][i] = f[1][i - 1];
                dp[1][i] = ((f[0][m] - f[0][i]) % mod + mod) % mod;
            }
            for (int i = 1; i <= m; ++i) {
                f[0][i] = (f[0][i - 1] + dp[0][i]) % mod;
                f[1][i] = (f[1][i - 1] + dp[1][i]) % mod;
            }
        }
        return (f[0][m] + f[1][m]) % mod;
    }
};