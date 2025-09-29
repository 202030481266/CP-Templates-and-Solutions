#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;

static constexpr int MAXN = 100005;
static constexpr int MOD = 1000000007;

#define INT(x) static_cast<int>(x)

int dp[5001][5001];

void solve() {
    string s, t;
    cin >> s >> t;
    int n = s.size(), m = t.size(), ans = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (s[i] == t[j]) {
                dp[i][j] = 1;
                if (i > 0 && j > 0) dp[i][j] = (dp[i][j] + dp[i - 1][j - 1]) % MOD;
            }
        }
        for (int j = 1; j < m; ++j) {
            dp[i][j] = (dp[i][j] + dp[i][j - 1]) % MOD;
        }
        ans = (ans + dp[i][m - 1]) % MOD;
    }
    cout << ans << '\n';
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
}