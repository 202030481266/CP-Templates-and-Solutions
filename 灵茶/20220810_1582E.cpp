// 这是正确的代码，因为贪心策略是对的，从右到左，能够确保尾部的值越大肯定越好，因为能够取得到的收益是固定的
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

static constexpr int MAXN = 100003;

int n, m, arr[MAXN];
ll sum[MAXN];
ll dp[MAXN][449];

void solve() {
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> arr[i];
    for (int i = 1; i <= n; ++i) sum[i] = sum[i - 1] + arr[i];
    int m = static_cast<int>(sqrt(2 * n));
    for (int j = 1; j <= m; ++j) dp[n + 1][j] = 0;
    for (int i = n; i >= 1; --i) {
        for (int j = 1; j <= m; ++j) dp[i][j] = 0;
        for (int j = 1; j <= min(m, n - i + 1); ++j) {
            dp[i][j] = dp[i + 1][j];
            if (j == 1) dp[i][1] = max(dp[i][1], 1ll * arr[i]);
            if (sum[i + j - 1] - sum[i - 1] < dp[i + j][j - 1]) {
                dp[i][j] = max(dp[i][j], sum[i + j - 1] - sum[i - 1]);
            }
        }
    }
    int ans = 0;
    for (int i = m; i >= 1; --i) {
        if (dp[1][i]) {
            ans = i;
            break;
        }
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) solve();
}

// 这是错误的代码逻辑
// 这是因为dp[i][j]的时候，不能够确定到底有多少的收益，可以是1个，也可以是2个，但是问题来了，1个的时候显然尾部可能会低，为2的时候尾部变高，无法谈心
// 下面维护了dp[i][j]的最大值以及对应的尾部最小值，事实上这是不对的

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

static constexpr int MAXN = 100003;

int n, m, arr[MAXN];
ll sum[MAXN];
int dp[MAXN][449], f[MAXN][449];

void solve() {
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> arr[i];
    for (int i = 1; i <= n; ++i) sum[i] = sum[i - 1] + arr[i];
    int m = static_cast<int>(sqrt(2 * n));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= min(m, i); ++j) {
            dp[i][j] = dp[i - 1][j];
            f[i][j] = f[i - 1][j];
            if (dp[i][j] == 0 || sum[i] - sum[i - j] < f[i][j] && dp[i][j] == 1) {
                dp[i][j] = 1;
                f[i][j] = sum[i] - sum[i - j];
            }
            if (j + 1 <= m && sum[i] - sum[i - j] > f[i - j][j + 1]) {
                int x = dp[i - j][j + 1] + 1;
                if (x > dp[i][j] || x == dp[i][j] && sum[i] - sum[i - j] < f[i][j]) {
                    dp[i][j] = x;
                    f[i][j] = sum[i] - sum[i - j];
                }
            }
        }
    }
    cout << dp[n][1] << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) solve();
}
