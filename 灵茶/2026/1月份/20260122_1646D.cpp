#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<vector<int>>;
using vl = vector<long long>;
using vll = vector<vector<long long>>;


void solve() {
    int n;
    cin >> n;
    if (n <= 2) {
        cout << n << ' ' << n << '\n';
        for (int i = 1; i <= n; ++i) cout << 1 << ' ';
        return;
    }
    vii g(n + 1);
    for (int i = 1, u, v; i < n; ++i) {
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vll dp(n + 1, vl(2));
    vii cnt(n + 2, vi(2));
    auto dfs = [&](auto&& self, int u, int fa) -> void {
        cnt[u][1] = 1;
        dp[u][1] += g[u].size();
        dp[u][0] = 1;
        for (int v : g[u]) {
            if (v != fa) {
                self(self, v, u);
                cnt[u][0] += max(cnt[v][0], cnt[v][1]);
                if (cnt[v][0] == cnt[v][1]) dp[u][0] += min(dp[v][0], dp[v][1]);
                else if (cnt[v][0] > cnt[v][1]) dp[u][0] += dp[v][0];
                else dp[u][0] += dp[v][1];
                cnt[u][1] += cnt[v][0];
                dp[u][1] += dp[v][0];
            }
        }
    };
    dfs(dfs, 1, 0);
    vi arr(n + 1);
    auto cal = [&](auto&& self, int u, int fa, int flag) -> void {
        if (flag) {
            arr[u] = g[u].size();
            for (int v : g[u]) {
                if (v != fa) {
                    self(self, v, u, 0);
                }
            }
        }
        else {
            arr[u] = 1;
            for (int v : g[u]) {
                if (v != fa) {
                    if (cnt[v][0] > cnt[v][1]) self(self, v, u, 0);
                    else if (cnt[v][1] > cnt[v][0]) self(self, v, u, 1);
                    else {
                        if (dp[v][0] <= dp[v][1]) self(self, v, u, 0);
                        else self(self, v, u, 1);
                    }
                }
            }
        }
    };
    if (cnt[1][0] > cnt[1][1]) {
        cout << cnt[1][0] << ' ' << dp[1][0] << '\n';
        cal(cal, 1, 0, 0);
    }
    else if (cnt[1][1] > cnt[1][0]) {
        cout << cnt[1][1] << ' ' << dp[1][1] << '\n';
        cal(cal, 1, 0, 1);
    }
    else {
        if (dp[1][0] <= dp[1][1]) {
            cout << cnt[1][0] << ' ' << dp[1][0] << '\n';
            cal(cal, 1, 0, 0);
        }
        else {
            cout << cnt[1][1] << ' ' << dp[1][1] << '\n';
            cal(cal, 1, 0, 1);
        }
    }
    for (int i = 1; i <= n; ++i) cout << arr[i] << ' ';
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
}
