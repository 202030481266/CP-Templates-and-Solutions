// https://www.luogu.com.cn/problem/P2513
#include <bits/stdc++.h>
using namespace std;

static constexpr int mod = 10000;
int n, k;

int main() {
    cin >> n >> k;
    if (n <= 1) {
        if (k == 0) cout << n << endl;
        else cout << 0 << endl;
        return 0;
    }
    vector dp(n + 1, vector<int>(k + 1, 0));
    dp[2][0] = 1;
    for (int i = 1; i <= k; ++i) dp[2][i] = 2;
    for (int i = 3; i <= n; ++i) {
        for (int j = 0; j <= min(n * (n-1) / 2, k); ++j) {
            int x = min(i - 1, j);
            if (x == j) dp[i][j] = dp[i-1][j];
            else dp[i][j] = (dp[i-1][j] - dp[i-1][j-x-1] + mod) % mod;
        }
        if (i == n) break;
        for (int j = 1; j <= k; ++j) {
            dp[i][j] = (dp[i][j] + dp[i][j-1]) % mod;
        }
    }
    cout << dp[n][k] << endl;
}