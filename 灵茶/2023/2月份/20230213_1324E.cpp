#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<vector<int>>;
using vl = vector<long long>;
using vll = vector<vector<long long>>;
static constexpr int INF = 0x3f3f3f3f;
static constexpr ll LLINF = 0x3f3f3f3f3f3f3f3f;


void solve() {
    int n, h, l, r;
    cin >> n >> h >> l >> r;
    vii dp(n + 1, vi(h, -INF));
    vi arr(n + 1);
    for (int i = 1; i <= n; ++i) cin >> arr[i];
    dp[0][0] = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < h; ++j) {
            if (dp[i - 1][j] != -INF) {
                int sum = (j + arr[i]) % h;
                if (l <= sum && sum <= r) dp[i][sum] = max(dp[i][sum], dp[i - 1][j] + 1);
                else dp[i][sum] = max(dp[i][sum], dp[i - 1][j]);
                sum = (j + arr[i] - 1) % h;
                if (l <= sum && sum <= r) dp[i][sum] = max(dp[i][sum], dp[i - 1][j] + 1);
                else dp[i][sum] = max(dp[i][sum], dp[i - 1][j]);
            }
        }
    }
    int ans = -INF;
    for (int i = 0; i < h; ++i) {
        ans = max(ans, dp[n][i]);
    }
    cout << ans << '\n';
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
}
