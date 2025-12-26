// Problem: D - Swap and Flip
// Contest: AtCoder - Keyence Programming Contest 2020
// URL: https://atcoder.jp/contests/keyence2020/tasks/keyence2020_d
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<vector<int> >;
static constexpr int MAXN = 500005;
static constexpr int MOD = 1e9 + 7;
static constexpr int INF = 0x3f3f3f3f;


int dp[18][2][1 << 18];
int a[18][2];
int mn[1 << 18];
int n;

int dfs(int mask, int flip, int last, int status) {
    if (mask == 0) return 0;
    if (dp[last][flip][mask] != -1) return dp[last][flip][mask];
    int& res = dp[last][flip][mask];
    res = INF;
    int ed = a[last][flip];
    if (mn[mask] < ed) return res;
    int cnt = 0, cur, nxt; // count the offset
    for (int i = 0; i < n; ++i) {
        if (mask >> i & 1) {
            cur = status >> i & 1;
            nxt = cur ^ (cnt & 1);
            if (a[i][nxt] >= ed) {
                res = min(res, cnt + dfs(mask ^ 1 << i, nxt, i, (status ^ (1 << i) - 1) & (mask ^ 1 << i)));
            }
            ++cnt;
        }
    }
    return res;
}

void solve() {
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> a[i][0];
    for (int i = 0; i < n; ++i) cin >> a[i][1];
    for (int i = 0; i < n; ++i) {
        memset(dp[i][0], -1, (1 << n) * sizeof(int));
        memset(dp[i][1], -1, (1 << n) * sizeof(int));
    }
    for (int i = 0; i < 1 << n; ++i) {
        mn[i] = INF;
        for (int j = 0; j < n; ++j) {
            if (i >> j & 1) mn[i] = min(mn[i], max(a[j][0], a[j][1]));
        }
    }
    int N = (1 << n) - 1, ans = INF;
    for (int i = 0; i < n; ++i) {
        int status = ((1 << i) - 1) & (N ^ 1 << i);
        int res = i + dfs(N ^ 1 << i, i & 1, i, status);
        ans = min(ans, res);
    }
    cout << (ans == INF ? -1 : ans) << '\n';
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    // cin >> t;
    while (t--) solve();
    return 0;
}
